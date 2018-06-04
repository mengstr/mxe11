//###############################################################################
//#										#
//# MXE11 PDP11-Unix Emulator for Mikrocontrollers				#
//#										#
//# copyright (c) 2017-2018 Joerg Wolfram (joerg@jcwolfram.de)			#
//#										#
//#										#
//# This program is free software; you can redistribute it and/or		#
//# modify it under the terms of the GNU General Public License			#
//# as published by the Free Software Foundation; either version 3		#
//# of the License, or (at your option) any later version.			#
//#										#
//# This program is distributed in the hope that it will be useful,		#
//# but WITHOUT ANY WARRANTY; without even the implied warranty of		#
//# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU		#
//# General Public License for more details.					#
//#										#
//# You should have received a copy of the GNU General Public			#
//# License along with this library// if not, write to the			#
//# Free Software Foundation, Inc., 59 Temple Place - Suite 330,		#
//# Boston, MA 02111-1307, USA.							#
//#										#
//###############################################################################
#include "board.h"

#if IO_TABLE == 0

#include "cpu.h"
#include "xvars.h"

#if MCU < 10
	#include "time.h"
#endif

extern unsigned short rkds,rker,rkcs,rkwc,rkba,rkda;

unsigned short tps8,tks8,tpb8,tkb8;
unsigned short tps9,tks9,tpb9,tkb9;

extern unsigned short lks;
extern unsigned short system_state;
extern unsigned long rk11_state;

extern void rk11_flush(void);
extern unsigned long get_date(void);

#if MCU < 10
	time_t atime;
#else
	unsigned long atime;
#endif


//#######################################################################
//# read a word from I/O space
//#######################################################################
unsigned short read_io_word(unsigned short address)
{

	address &= 0xFFFE;

	switch(address)
	{
		// FFFE - psw
		case 0xfffe:		return psw;

		// FF00	- RKDS
		case 0xff00:		return rkds;

		// FF02	- RKER
		case 0xff02:		return rker;

		// FF04	- RKCS
		case 0xff04:		return rkcs;

		// FF06	- RKWC
		case 0xff06:		return rkwc;

		// FF08	- RKBA
		case 0xff08:		return rkba;

		// FF0A	- RKDA
		case 0xff0a:		return rkda;

		// FF66	- KL11
		case 0xff66:		return lks;

		// FF70 - tks8 receive status
		case 0xff70:		return tks8;

		// FF72 - tkb8 receive buffer
		case 0xff72:		if(tks8 & 0x0080)		//only if RCVR DONE = 1
					{
						tks8 &= 0xFF7E;		//clear RCVR DONE
						return tkb8;
					}
					return 0;

		// FD44 - tps9 transmit status
		case 0xFD44:		return tps9;

		// FD46 - tpb9 transmit buffer
		case 0xFD46:		return 0;

		// FD40 - tks9 receive status
		case 0xFD40:		return tks9;

		// FD42 - tkb9 receive buffer
		case 0xFD42:		if(tks9 & 0x0080)		//only if RCVR DONE = 1
					{
						tks9 &= 0xFF7E;		//clear RCVR DONE
						return tkb9;
					}
					return 0;

		// FF74 - tps8 transmit status
		case 0xff74:		return tps8;

		// FF76 - tpb8 transmit buffer
		case 0xff76:		return 0;



		// FF78 - switches
		case 0xff78:		return 0;



		// TIMESTAMP - upper word
		case 0xfab0:		
#if MCU < 10		
					atime=time(NULL)-(1261440000+864000);
//					atime=0;
//					printf("GETDATE (HIGH) = %08lx\n",atime);
#else
					atime=xrtc_get_date();
					if((atime == 0xFFFFFFFF) || (atime == 0)) atime=1521180293;
					 
#endif					
					return (atime >> 16) & 0xFFFF;
						
		// TIMESTAMP - lower word
		case 0xfab2:
#if MCU < 10		
//					printf("GETDATE (LOW)\n");
#endif
					return (atime & 0xFFFF);

#if USE_STACKLIMIT == 1
		// FFFC - stack limit
		case 0xfffc:		return stack_limit;
#endif

		default:								
#if MCU == 1
					DEBUG_PRINTF("  IO-WREAD ADDR=%04X AT %04X\n",address,pc);
#endif
					return 0;
	}

	return 0;
}


//#######################################################################
//# write a word to I/O space
//#######################################################################
void write_io_word(unsigned short address, unsigned short data)
{
		
#if DEBUG_IO == 1
		DEBUG_PRINTF("  IO-WWRITE ADDR=%04X    DATA=%04X\n",address,data);
#endif

	if(address & 1)
	{

		return;
	}

	switch(address)
	{
		// FF00	- RKDS (read only)
//		case 0xff00:		break;

		// FF02	- RKER (read only)
//		case 0xff02:		break;

		// FFFE - psw
		case 0xfffe:		psw=data;
					return;

		// FF04	- RKCS
		case 0xff04:		rkcs &= 0xE0B0;
					rkcs |= data & 0x1F4F;
					if((rkcs & 0x000e) != 0) 
					{
						cycle_type |= (16 << SHIFT_CYCLE);
						rk11_state=1;	
					}
					return;

		// FF06	- RKWC
		case 0xff06:		rkwc=data;
					return;
		// FF08	- RKBA
		case 0xff08:		rkba=data;
					return;
		// FF04	- RKDA
		case 0xff0a:		rkda=data;
					return;

		// FF66	- KL11
		case 0xff66:		lks=data;
					return;

		// FF70 - tks8 receive status
		case 0xff70:		if(data & 0x0040) tks8 |= 0x40; else tks8 &= 0xFFBF;
					if(data & 1) tks8 &= 0xFF7F;
					return;

		// FF74 - tps8 transmit status
		case 0xff74:		if(data & 0x0040) tps8 |= 0x40; else tps8 &= 0xFFBF;
					return;

		// FF76 - tpb8 transmit data
		case 0xff76:		tpb8=data & 0xff;	
					tps8 &= 0xFF7F;
					return;

		// FD40 - tks9 receive status
		case 0xFD40:		if(data & 0x0040) tks9 |= 0x40; else tks9 &= 0xFFBF;
					if(data & 1) tks9 &= 0xFF7F;
					return;

		// FD44 - tps9 transmit status
		case 0xFD44:		if(data & 0x0040) tps9 |= 0x40; else tps9 &= 0xFFBF;
					return;

		// FD46 - tpb9 transmit data
		case 0xFD46:		tpb9=data & 0xff;	
					tps9 &= 0xFF7F;
					return;

#if USE_STACKLIMIT == 1
		// FFFC - stack limit
		case 0xfffc:		stack_limit=data;
					return;
#endif


		case 0xfabc:		if(data!=0x1234) return;	//magic
#if MCU > 9
					rk11_flush();
					KPRINTF("\r\nMXE11: SYSTEM HALTED\r\n");
					set_portpin_zero(STAT_LED);
					while(1)
					{
#ifdef HAVE_SLEEP
						unilib_sleep();
#endif				
					}
#endif
						system_state=0;
						return;


											
		default:
#if MCU == 1
					DEBUG_PRINTF("  IO-WWRITE ADDR=%04X    DATA=%04X\n",address,data);
#endif
					return;		//dummy
	}
}


//#######################################################################
//# write a byte to I/O space
//#######################################################################
void write_io_byte(unsigned short address, unsigned short data)
{

#if DEBUG_IO == 1
		DEBUG_PRINTF("  IO-BWRITE ADDR=%04X    DATA=%04X\n",address,data);
#endif

	switch(address)
	{
		// FFFE - psw
		case 0xfffe:		psw = (psw & 0xFF00) | (data & 0xff);
					return;

		// FF04	- RKCS
		case 0xff04:		rkcs &= 0xFFB0;
					rkcs |= data & 0x004F;
					if((rkcs & 0x000e) != 0) 
					{
						cycle_type |= (16 << SHIFT_CYCLE);
						rk11_state=1;	
					}
					return;

		case 0xff05:		rkcs &= 0xE0FF;
					rkcs |= (data << 8) & 0x1F00;
					return;

		// FF06	- RKWC
		case 0xff06:		rkwc = (rkwc & 0xFF00) | (data & 0xff);
					return;

		case 0xff07:		rkwc = (rkwc & 0xFF) | (data << 8);
					return;


		// FF08	- RKBA
		case 0xff08:		rkba = (rkba & 0xFF00) | (data & 0xff);
					return;

		case 0xff09:		rkba = (rkba & 0xFF) | (data << 8);
					return;

		// FF0A	- RKDA
		case 0xff0a:		rkda = (rkda & 0xFF00) | (data & 0xff);
					return;

		case 0xff0b:		rkda = (rkda & 0xFF) | (data << 8);
					return;


		// FF66	- KL11
		case 0xff66:		lks=data & 0xff;
					DEBUG_PRINTF("  IO-BWRITE ADDR=%04X    DATA=%04X\n",address,data);
					return;


		// FF70 - tks8 receive status
		case 0xff70:		if(data & 0x0040) tks8 |= 0x40; else tks8 &= 0xFFBF;
					if(data & 1) tks8 &= 0xFF7F;
					return;

		// FF74 - tps8 transmit status
		case 0xff74:		if(data & 0x0040) tps8 |= 0x40; else tps8 &= 0xFFBF;
					return;

		// FF76 - tpb8 transmit data
		case 0xff76:		tpb8=data & 0xFF;
					tps8 &= 0xFF7F;


		// FD40 - tks9 receive status
		case 0xFD40:		if(data & 0x0040) tks9 |= 0x40; else tks9 &= 0xFFBF;
					if(data & 1) tks9 &= 0xFF7F;
					return;

		// FD44 - tps9 transmit status
		case 0xFD44:		if(data & 0x0040) tps9 |= 0x40; else tps9 &= 0xFFBF;
					return;

		// FD46 - tpb9 transmit data
		case 0xFD46:		tpb9=data & 0xFF;
					tps9 &= 0xFF7F;


#if USE_STACKLIMIT == 1
		// FFFC - stack limit
		case 0xfffc:		stack_limit = (stack_limit & 0xFF) | (data << 8);
					return;
#endif


		case 0xffff:		psw = (psw & 0xFF) | (data << 8);
					return;
									
		default:
#if MCU == 1
					DEBUG_PRINTF("  IO-BWRITE ADDR=%04X    DATA=%04X\n",address,data);
#endif
		
				return;		//dummy
	}
}
	
#endif