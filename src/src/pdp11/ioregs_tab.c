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

#if IO_TABLE == 1

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


//##########################################################################################################
// read I/O byte
//##########################################################################################################
unsigned char r_zero()
{
	return 0;
}

// FFFE - psw
unsigned char r_FFFE()
{
	return (psw & 0xff);
}
unsigned char r_FFFF()
{
	return ((psw >> 8) & 0xff);
}

// FF00 - rkds
unsigned char r_FF00()
{
	return (rkds & 0xff);
}
unsigned char r_FF01()
{
	return ((rkds >> 8) & 0xff);
}

// FF02 - rker
unsigned char r_FF02()
{
	return (rker & 0xff);
}
unsigned char r_FF03()
{
	return ((rker >> 8) & 0xff);
}

// FF04 - rkcs
unsigned char r_FF04()
{
	return (rkcs & 0xff);
}
unsigned char r_FF05()
{
	return ((rkcs >> 8) & 0xff);
}

// FF06 - rkwc
unsigned char r_FF06()
{
	return (rkwc & 0xff);
}
unsigned char r_FF07()
{
	return ((rkwc >> 8) & 0xff);
}

// FF08 - rkba
unsigned char r_FF08()
{
	return (rkba & 0xff);
}
unsigned char r_FF09()
{
	return ((rkba >> 8) & 0xff);
}

// FF0A - rkda
unsigned char r_FF0A()
{
	return (rkda & 0xff);
}
unsigned char r_FF0B()
{
	return ((rkda >> 8) & 0xff);
}

// FF66 - lks
unsigned char r_FF66()
{
	return (lks & 0xff);
}
unsigned char r_FF67()
{
	return ((lks >> 8) & 0xff);
}

// FF70 - tks8
unsigned char r_FF70()
{
	return (tks8 & 0xff);
}

// FF72 - tkb8 receive buffer
unsigned char r_FF72()
{
	if(tks8 & 0x0080)		//only if RCVR DONE = 1
	{
		tks8 &= 0xFF7E;		//clear RCVR DONE
		return (tkb8 & 0xff);
	}
	return 0;
}

// FF74 - tps8 transmit status
unsigned char r_FF74()
{
	return (tps8 & 0xff);
}

// FF76 - tpb8 transmit buffer
unsigned char r_FF76()
{
	return 0;
}

// FF78 - switches
unsigned char r_FF78()
{
	return 0;
}

// FD40 - tks9
unsigned char r_FD40()
{
	return (tks9 & 0xff);
}

// FD42 - tkb8 receive buffer
unsigned char r_FD42()
{
	if(tks9 & 0x0080)		//only if RCVR DONE = 1
	{
		tks9 &= 0xFF7E;		//clear RCVR DONE
		return (tkb9 & 0xff);
	}
	return 0;
}

// FD44 - tps8 transmit status
unsigned char r_FD44()
{
	return (tps9 & 0xff);
}

// FD46 - tpb8 transmit buffer
unsigned char r_FD46()
{
	return 0;
}

// FFFC - stack limit
unsigned char r_FFFC()
{
#if USE_STACKLIMIT == 1
		return (stack_limit & 0xff);
#else
		return 0;
#endif
}
unsigned char r_FFFD()
{
#if USE_STACKLIMIT == 1
		return ((stack_limit >> 8) & 0xff);
#else
		return 0;
#endif
}


//##########################################################################################################
// read I/O word
//##########################################################################################################
unsigned short g_zero()
{
	return 0;
}

// FFFE - psw
unsigned short g_FFFE()
{
	return psw;
}

// FF00 - rkds
unsigned short g_FF00()
{
	return rkds;
}

// FF02 - rker
unsigned short g_FF02()
{
	return rkds;
}

// FF04 - rkcs
unsigned short g_FF04()
{
	return rkcs;
}

// FF06 - rkwc
unsigned short g_FF06()
{
	return rkwc;
}

// FF08 - rkba
unsigned short g_FF08()
{
	return rkba;
}

// FF0A - rkda
unsigned short g_FF0A()
{
	return rkda;
}

// FF66 - lks
unsigned short g_FF66()
{
	return lks;
}

// FF70 - tks8
unsigned short g_FF70()
{
	return tks8;
}

// FF72 - tkb8 receive buffer
unsigned short g_FF72()
{
	if(tks8 & 0x0080)		//only if RCVR DONE = 1
	{
		tks8 &= 0xFF7E;		//clear RCVR DONE
		return tkb8;
	}
	return 0;
}

// FF74 - tps8 transmit status
unsigned short g_FF74()
{
	return tps8;
}

// FF76 - tpb8 transmit buffer
unsigned short g_FF76()
{
	return 0;
}

// FF78 - switches
unsigned short g_FF78()
{
	return 0;
}

// FD40 - tks9
unsigned short g_FD40()
{
	return tks9;
}

// FF42 - tkb8 receive buffer
unsigned short g_FD42()
{
	if(tks9 & 0x0080)		//only if RCVR DONE = 1
	{
		tks9 &= 0xFF7E;		//clear RCVR DONE
		return tkb9;
	}
	return 0;
}

// FD44 - tps8 transmit status
unsigned short g_FD44()
{
	return tps9;
}

// FD46 - tpb8 transmit buffer
unsigned short g_FD46()
{
	return 0;
}


// TIMESTAMP - upper word
unsigned short g_FAB0()
{
#if MCU < 10		
		atime=time(NULL)-(1261440000+864000);
//		printf("GETDATE (HIGH) = %08lx\n",atime);
#else
		atime=xrtc_get_date();
#endif					
		return (atime >> 16) & 0xFFFF;
}
		
// TIMESTAMP - lower word
unsigned short g_FAB2()
{
#if MCU < 10		
//		printf("GETDATE (LOW)\n");
#endif
		return (atime & 0xFFFF);
}

// FFFC - stack limit
unsigned short g_FFFC()
{
#if USE_STACKLIMIT == 1
		return stack_limit;
#else
		return 0;
#endif
}


//##########################################################################################################
// write I/O byte
//##########################################################################################################
void w_none(unsigned char data)
{
}

// FFFE - psw
void w_FFFE(unsigned char data)
{
	psw = (psw & 0xFF00) | (data & 0xff);
}
void w_FFFF(unsigned char data)
{
	psw = (psw & 0xFF) | ((data & 0xff) << 8);
}

// FFFC - stack limit
void w_FFFC(unsigned char data)
{
#if USE_STACKLIMIT == 1
	stack_limit = (stack_limit & 0xFF00) | (data & 0xff);
#endif
}
void w_FFFD(unsigned char data)
{
#if USE_STACKLIMIT == 1
	stack_limit = (stack_limit & 0xFF) | ((data & 0xff) << 8);
#endif
}

// FF00 - rkds
void w_FF00(unsigned char data)
{
}
void w_FF01(unsigned char data)
{
}

// FF02 - rker
void w_FF02(unsigned char data)
{
}
void w_FF03(unsigned char data)
{
}



// FF04	- RKCS
void w_FF04(unsigned char data)
{
	rkcs &= 0xFFB0;
	rkcs |= data & 0x004F;
	if((rkcs & 0x000e) != 0) 
	{
		cycle_type |= (16 << SHIFT_CYCLE);
		rk11_state=1;	
	}
}
void w_FF05(unsigned char data)
{
	rkcs &= 0xE0FF;
	rkcs |= (data << 8) & 0x1F00;
}	

// FF06	- RKWC
void w_FF06(unsigned char data)
{
	rkwc = (rkwc & 0xFF00) | (data & 0xff);
}
void w_FF07(unsigned char data)
{
	rkwc = (rkwc & 0xFF) | (data << 8);
}

// FF08	- RKBA
void w_FF08(unsigned char data)
{
	rkba = (rkba & 0xFF00) | (data & 0xff);
}
void w_FF09(unsigned char data)
{
	rkba = (rkba & 0xFF) | (data << 8);
}

// FF0A	- RKDA
void w_FF0A(unsigned char data)
{
	rkda = (rkda & 0xFF00) | (data & 0xff);
}
void w_FF0B(unsigned char data)
{
	rkda = (rkda & 0xFF) | (data << 8);
}

// FF66	- KL11
void w_FF66(unsigned char data)
{
	lks = (lks & 0xFF00) | (data & 0xff);
}
void w_FF67(unsigned char data)
{
	lks = (lks & 0xFF) | (data << 8);
}


// FF70 - tks8 receive status
void w_FF70(unsigned char data)
{
	if(data & 0x0040) tks8 |= 0x40; else tks8 &= 0xFFBF;
}
void w_FF71(unsigned char data)
{
}

// FF72 - tkb8 receive buffer
void w_FF72(unsigned char data)
{
}
void w_FF73(unsigned char data)
{
}


// FF74 - tps8 transmit status
void w_FF74(unsigned char data)
{
	if(data & 0x0040) tps8 |= 0x40; else tps8 &= 0xFFBF;
}
void w_FF75(unsigned char data)
{
}

// FF76 - tpb8 transmit data
void w_FF76(unsigned char data)
{
	tpb8=data & 0xFF;
	tps8 &= 0xFF7F;
}
void w_FF77(unsigned char data)
{
}

// FD40 - tks9 receive status
void w_FD40(unsigned char data)
{
	if(data & 0x0040) tks9 |= 0x40; else tks9 &= 0xFFBF;
}
void w_FD41(unsigned char data)
{
}

// FD42 - tkb9 receive buffer
void w_FD42(unsigned char data)
{
}
void w_FD43(unsigned char data)
{
}


// FD44 - tps9 transmit status
void w_FD44(unsigned char data)
{
	if(data & 0x0040) tps9 |= 0x40; else tps9 &= 0xFFBF;
}
void w_FD45(unsigned char data)
{
}

// FD46 - tpb9 transmit data
void w_FD46(unsigned char data)
{
	tpb9=data & 0xFF;
	tps9 &= 0xFF7F;
}
void w_FD47(unsigned char data)
{
}

//##########################################################################################################
// write I/O word
//##########################################################################################################
void p_none(unsigned short data)
{
}

// FFFE - psw
void p_FFFE(unsigned short data)
{
		psw=data;
}

// FF00 - rkds
void p_FF00(unsigned short data)
{
}

// FF02 - rker
void p_FF02(unsigned short data)
{
}

// FF04 - RKCS
void p_FF04(unsigned short data)
{
	rkcs &= 0xE0B0;
	rkcs |= data & 0x1F4F;
	if((rkcs & 0x000e) != 0) 
	{
		cycle_type |= (16 << SHIFT_CYCLE);
		rk11_state=1;	
	}
}

// FF06 - RKWC
void p_FF06(unsigned short data)
{
	rkwc=data;
}

// FF08 - RKBA
void p_FF08(unsigned short data)
{
	rkba=data;
}

// FF0A - RKDA
void p_FF0A(unsigned short data)
{
	rkda=data;
}

// FF66 - KL11
void p_FF66(unsigned short data)
{
	lks=data;
}

// FF70 - tks8 receive status
void p_FF70(unsigned short data)
{
	if(data & 0x0040) tks8 |= 0x40; else tks8 &= 0xFFBF;
	if(data & 1) tks8 &= 0xFF7F;
}

// FF72 - tps8
void p_FF72(unsigned short data)
{
}

// FF74 - tps8 transmit status
void p_FF74(unsigned short data)
{
	if(data & 0x0040) tps8 |= 0x40; else tps8 &= 0xFFBF;
}

// FF76 - tpb8 transmit data
void p_FF76(unsigned short data)
{
	tpb8=data & 0xff;	
	tps8 &= 0xFF7F;
}

// FD40 - tks9 receive status
void p_FD40(unsigned short data)
{
	if(data & 0x0040) tks9 |= 0x40; else tks9 &= 0xFFBF;
	if(data & 1) tks9 &= 0xFF7F;
}

// FD42 - tps9
void p_FD42(unsigned short data)
{
}

// FD44 - tps9 transmit status
void p_FD44(unsigned short data)
{
	if(data & 0x0040) tps9 |= 0x40; else tps9 &= 0xFFBF;
}

// FD46 - tpb9 transmit data
void p_FD46(unsigned short data)
{
	tpb9=data & 0xff;	
	tps9 &= 0xFF7F;
}

// FFFC - stack limit
void p_FFFC(unsigned short data)
{
#if USE_STACKLIMIT == 1
	stack_limit=data;
#endif
}

// FABC - halt system
void p_FABC(unsigned short data)
{
	if(data!=0x1234) return;	//magic
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
}


	
const getb_op_t read_iob[8192] = {
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE000
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE008
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE010
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE018
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE020
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE028
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE030
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE038
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE040
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE048
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE050
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE058
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE060
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE068
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE070
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE078
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE080
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE088
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE090
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE098
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0F0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE0F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE100
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE108
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE110
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE118
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE120
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE128
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE130
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE138
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE140
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE148
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE150
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE158
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE160
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE168
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE170
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE178
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE180
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE188
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE190
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE198
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1F1
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE1F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE200
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE208
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE210
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE218
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE220
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE228
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE230
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE238
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE240
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE248
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE250
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE258
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE260
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE268
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE270
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE278
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE280
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE288
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE290
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE298
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2F2
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE2F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE300
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE308
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE310
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE318
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE320
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE328
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE330
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE338
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE340
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE348
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE350
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE358
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE360
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE368
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE370
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE378
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE380
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE388
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE390
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE398
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3F3
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE3F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE400
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE408
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE410
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE418
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE420
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE428
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE430
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE438
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE440
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE448
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE450
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE458
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE460
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE468
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE470
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE478
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE480
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE488
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE490
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE498
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4F4
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE4F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE500
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE508
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE510
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE518
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE520
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE528
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE530
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE538
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE540
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE548
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE550
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE558
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE560
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE568
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE570
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE578
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE580
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE588
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE590
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE598
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5F5
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE5F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE600
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE608
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE610
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE618
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE620
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE628
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE630
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE638
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE640
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE648
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE650
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE658
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE660
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE668
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE670
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE678
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE680
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE688
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE690
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE698
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6F6
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE6F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE700
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE708
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE710
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE718
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE720
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE728
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE730
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE738
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE740
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE748
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE750
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE758
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE760
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE768
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE770
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE778
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE780
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE788
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE790
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE798
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7F7
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE7F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE800
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE808
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE810
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE818
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE820
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE828
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE830
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE838
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE840
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE848
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE850
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE858
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE860
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE868
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE870
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE878
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE880
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE888
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE890
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE898
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8F8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE8F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE900
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE908
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE910
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE918
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE920
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE928
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE930
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE938
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE940
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE948
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE950
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE958
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE960
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE968
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE970
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE978
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE980
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE988
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE990
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE998
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9F9
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xE9F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEA98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAFA
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEAF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEB98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBFB
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEBF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEC98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECFC
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xECF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xED98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDFD
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEDF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEE98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEED0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEED8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEFE
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEEF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEF98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFFF
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xEFF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF000
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF008
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF010
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF018
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF020
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF028
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF030
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF038
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF040
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF048
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF050
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF058
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF060
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF068
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF070
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF078
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF080
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF088
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF090
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF098
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0F0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF0F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF100
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF108
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF110
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF118
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF120
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF128
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF130
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF138
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF140
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF148
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF150
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF158
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF160
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF168
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF170
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF178
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF180
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF188
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF190
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF198
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1F1
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF1F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF200
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF208
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF210
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF218
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF220
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF228
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF230
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF238
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF240
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF248
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF250
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF258
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF260
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF268
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF270
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF278
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF280
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF288
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF290
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF298
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2F2
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF2F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF300
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF308
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF310
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF318
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF320
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF328
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF330
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF338
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF340
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF348
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF350
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF358
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF360
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF368
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF370
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF378
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF380
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF388
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF390
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF398
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3F3
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF3F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF400
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF408
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF410
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF418
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF420
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF428
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF430
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF438
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF440
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF448
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF450
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF458
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF460
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF468
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF470
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF478
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF480
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF488
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF490
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF498
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4F4
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF4F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF500
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF508
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF510
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF518
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF520
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF528
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF530
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF538
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF540
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF548
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF550
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF558
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF560
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF568
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF570
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF578
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF580
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF588
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF590
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF598
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5F5
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF5F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF600
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF608
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF610
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF618
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF620
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF628
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF630
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF638
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF640
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF648
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF650
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF658
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF660
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF668
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF670
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF678
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF680
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF688
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF690
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF698
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6F6
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF6F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF700
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF708
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF710
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF718
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF720
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF728
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF730
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF738
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF740
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF748
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF750
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF758
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF760
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF768
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF770
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF778
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF780
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF788
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF790
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF798
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7F7
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF7F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF800
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF808
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF810
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF818
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF820
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF828
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF830
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF838
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF840
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF848
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF850
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF858
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF860
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF868
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF870
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF878
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF880
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF888
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF890
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF898
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8F8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF8F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF900
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF908
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF910
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF918
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF920
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF928
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF930
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF938
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF940
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF948
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF950
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF958
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF960
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF968
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF970
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF978
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF980
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF988
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF990
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF998
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9A0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9A8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9B0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9B8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9C0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9C8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9D0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9D8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9E0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9E8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9F9
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xF9F8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFA98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAFA
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFAF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFB98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBFB
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFBF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFC98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCFC
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFCF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD38
	r_FD40,	r_zero,	r_FD42,	r_zero,	r_FD44,	r_zero,	r_FD46,	r_zero,		//0xFD40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFD98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDFD
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFDF8

	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE00
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE68
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFE98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFED0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFED8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEFE
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFEF8

	r_FF00,	r_FF01,	r_FF02,	r_FF03,	r_FF04,	r_FF05,	r_FF06,	r_FF07,		//0xFF00
	r_FF08,	r_FF09,	r_FF0A,	r_FF0B,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF08
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF10
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF18
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF20
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF28
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF30
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF38
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF40
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF48
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF50
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF58
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_FF66,	r_FF67,		//0xFF60
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF68
	r_FF70,	r_zero,	r_FF72,	r_zero,	r_FF74,	r_zero,	r_FF76,	r_zero,		//0xFF70
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF78
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF80
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF88
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF90
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFF98
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFA0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFA8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFB0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFB8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFC0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFC8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFD0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFD8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFE0
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFE8
	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,	r_zero,		//0xFFFF
	r_zero,	r_zero,	r_zero,	r_zero,	r_FFFC,	r_FFFD,	r_FFFE,	r_FFFF};	//0xFFF8
	
const putb_op_t write_iob[8192] = {
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE000
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE008
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE010
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE018
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE020
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE028
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE030
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE038
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE040
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE048
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE050
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE058
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE060
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE068
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE070
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE078
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE080
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE088
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE090
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE098
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0F0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE0F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE100
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE108
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE110
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE118
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE120
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE128
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE130
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE138
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE140
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE148
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE150
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE158
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE160
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE168
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE170
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE178
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE180
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE188
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE190
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE198
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1F1
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE1F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE200
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE208
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE210
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE218
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE220
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE228
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE230
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE238
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE240
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE248
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE250
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE258
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE260
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE268
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE270
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE278
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE280
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE288
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE290
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE298
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2F2
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE2F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE300
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE308
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE310
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE318
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE320
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE328
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE330
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE338
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE340
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE348
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE350
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE358
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE360
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE368
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE370
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE378
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE380
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE388
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE390
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE398
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3F3
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE3F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE400
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE408
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE410
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE418
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE420
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE428
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE430
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE438
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE440
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE448
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE450
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE458
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE460
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE468
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE470
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE478
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE480
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE488
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE490
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE498
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4F4
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE4F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE500
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE508
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE510
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE518
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE520
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE528
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE530
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE538
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE540
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE548
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE550
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE558
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE560
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE568
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE570
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE578
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE580
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE588
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE590
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE598
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5F5
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE5F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE600
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE608
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE610
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE618
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE620
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE628
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE630
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE638
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE640
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE648
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE650
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE658
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE660
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE668
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE670
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE678
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE680
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE688
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE690
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE698
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6F6
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE6F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE700
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE708
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE710
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE718
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE720
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE728
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE730
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE738
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE740
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE748
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE750
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE758
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE760
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE768
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE770
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE778
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE780
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE788
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE790
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE798
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7F7
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE7F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE800
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE808
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE810
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE818
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE820
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE828
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE830
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE838
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE840
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE848
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE850
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE858
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE860
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE868
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE870
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE878
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE880
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE888
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE890
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE898
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8F8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE8F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE900
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE908
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE910
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE918
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE920
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE928
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE930
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE938
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE940
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE948
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE950
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE958
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE960
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE968
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE970
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE978
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE980
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE988
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE990
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE998
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9F9
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xE9F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEA98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAFA
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEAF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEB98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBFB
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEBF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEC98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECFC
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xECF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xED98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDFD
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEDF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEE98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEED0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEED8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEFE
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEEF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEF98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFFF
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xEFF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF000
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF008
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF010
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF018
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF020
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF028
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF030
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF038
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF040
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF048
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF050
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF058
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF060
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF068
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF070
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF078
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF080
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF088
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF090
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF098
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0F0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF0F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF100
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF108
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF110
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF118
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF120
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF128
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF130
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF138
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF140
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF148
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF150
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF158
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF160
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF168
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF170
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF178
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF180
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF188
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF190
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF198
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1F1
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF1F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF200
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF208
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF210
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF218
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF220
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF228
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF230
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF238
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF240
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF248
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF250
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF258
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF260
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF268
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF270
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF278
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF280
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF288
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF290
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF298
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2F2
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF2F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF300
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF308
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF310
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF318
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF320
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF328
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF330
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF338
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF340
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF348
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF350
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF358
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF360
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF368
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF370
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF378
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF380
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF388
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF390
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF398
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3F3
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF3F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF400
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF408
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF410
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF418
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF420
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF428
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF430
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF438
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF440
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF448
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF450
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF458
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF460
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF468
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF470
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF478
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF480
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF488
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF490
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF498
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4F4
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF4F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF500
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF508
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF510
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF518
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF520
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF528
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF530
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF538
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF540
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF548
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF550
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF558
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF560
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF568
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF570
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF578
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF580
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF588
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF590
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF598
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5F5
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF5F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF600
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF608
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF610
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF618
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF620
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF628
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF630
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF638
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF640
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF648
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF650
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF658
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF660
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF668
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF670
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF678
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF680
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF688
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF690
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF698
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6F6
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF6F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF700
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF708
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF710
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF718
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF720
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF728
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF730
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF738
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF740
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF748
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF750
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF758
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF760
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF768
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF770
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF778
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF780
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF788
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF790
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF798
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7F7
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF7F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF800
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF808
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF810
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF818
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF820
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF828
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF830
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF838
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF840
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF848
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF850
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF858
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF860
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF868
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF870
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF878
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF880
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF888
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF890
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF898
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8F8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF8F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF900
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF908
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF910
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF918
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF920
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF928
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF930
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF938
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF940
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF948
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF950
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF958
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF960
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF968
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF970
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF978
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF980
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF988
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF990
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF998
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9A0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9A8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9B0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9B8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9C0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9C8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9D0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9D8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9E0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9E8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9F9
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xF9F8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFA98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAFA
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFAF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFB98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBFB
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFBF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFC98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCFC
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFCF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD38
	w_FD40,	w_FD41,	w_FD42,	w_FD43,	w_FD44,	w_FD45,	w_FD46,	w_FD47,		//0xFD40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFD98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDFD
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFDF8

	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE00
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE68
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFE98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFED0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFED8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEFE
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFEF8

	w_FF00,	w_FF01,	w_FF02,	w_FF03,	w_FF04,	w_FF05,	w_FF06,	w_FF07,		//0xFF00
	w_FF08,	w_FF09,	w_FF0A,	w_FF0B,	w_none,	w_none,	w_none,	w_none,		//0xFF08
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF10
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF18
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF20
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF28
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF30
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF38
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF40
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF48
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF50
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF58
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_FF66,	w_FF67,		//0xFF60
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF68
	w_FF70,	w_FF71,	w_FF72,	w_FF73,	w_FF74,	w_FF75,	w_FF76,	w_FF77,		//0xFF70
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF78
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF80
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF88
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF90
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFF98
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFA0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFA8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFB0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFB8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFC0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFC8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFD0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFD8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFE0
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFE8
	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,	w_none,		//0xFFFF
	w_none,	w_none,	w_none,	w_none,	w_FFFC,	w_FFFD,	w_FFFE,	w_FFFF};	//0xFFF8

const get_op_t read_iow[4096] = {
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE000
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE010
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE020
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE030
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE040
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE050
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE060
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE070
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE080
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE090
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE0F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE100
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE110
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE120
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE130
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE140
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE150
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE160
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE170
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE180
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE190
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE1F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE200
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE210
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE220
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE230
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE240
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE250
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE260
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE270
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE280
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE290
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE2F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE300
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE310
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE320
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE330
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE340
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE350
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE360
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE370
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE380
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE390
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE3F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE400
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE410
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE420
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE430
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE440
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE450
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE460
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE470
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE480
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE490
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE4F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE500
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE510
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE520
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE530
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE540
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE550
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE560
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE570
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE580
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE590
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE5F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE600
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE610
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE620
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE630
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE640
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE650
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE660
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE670
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE680
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE690
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE6F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE700
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE710
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE720
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE730
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE740
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE750
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE760
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE770
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE780
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE790
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE7F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE800
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE810
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE820
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE830
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE840
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE850
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE860
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE870
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE880
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE890
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE8F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE900
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE910
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE920
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE930
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE940
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE950
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE960
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE970
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE980
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE990
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xE9F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEA90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEAF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEB90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEBF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEC90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xECF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xED90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEDF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEE90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEEA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEEB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEEC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEED0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEEE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xEEF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF000
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF010
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF020
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF030
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF040
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF050
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF060
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF070
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF080
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF090
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF0F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF100
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF110
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF120
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF130
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF140
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF150
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF160
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF170
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF180
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF190
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF1F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF200
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF210
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF220
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF230
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF240
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF250
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF260
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF270
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF280
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF290
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF2F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF300
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF310
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF320
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF330
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF340
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF350
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF360
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF370
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF380
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF390
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF3F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF400
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF410
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF420
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF430
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF440
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF450
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF460
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF470
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF480
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF490
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF4F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF500
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF510
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF520
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF530
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF540
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF550
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF560
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF570
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF580
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF590
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF5F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF600
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF610
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF620
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF630
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF640
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF650
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF660
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF670
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF680
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF690
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF6F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF700
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF710
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF720
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF730
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF740
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF750
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF760
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF770
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF780
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF790
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF7F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF800
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF810
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF820
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF830
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF840
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF850
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF860
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF870
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF880
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF890
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF8F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF900
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF910
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF920
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF930
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF940
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF950
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF960
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF970
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF980
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF990
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9A0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9B0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9C0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9D0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9E0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xF9F0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFA90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAA0
	g_FAB0,	g_FAB2,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFAF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFB90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFBF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFC90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFCF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD30
	g_FD40,	g_FD42,	g_FD44,	g_FD46,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFD90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFDF0

	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE50
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE60
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFE90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFEA0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFEB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFEC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFED0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFEE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFEF0

	g_FF00,	g_FF02,	g_FF04,	g_FF06,	g_FF08,	g_FF0A,	g_zero,	g_zero,		//0xFF00
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF10
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF20
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF30
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF40
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF50
	g_zero,	g_zero,	g_zero,	g_FF66,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF60
	g_FF70,	g_FF72,	g_FF74,	g_FF76,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF70
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF80
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFF90
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFA0
	g_FAB0,	g_FAB2,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFB0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFC0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFD0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,		//0xFFE0
	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_zero,	g_FFFE};	//0xFFF0

	
const put_op_t write_iow[4096] = {
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE000
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE010
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE020
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE030
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE040
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE050
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE060
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE070
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE080
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE090
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE0F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE100
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE110
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE120
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE130
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE140
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE150
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE160
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE170
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE180
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE190
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE1F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE200
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE210
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE220
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE230
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE240
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE250
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE260
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE270
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE280
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE290
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE2F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE300
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE310
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE320
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE330
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE340
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE350
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE360
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE370
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE380
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE390
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE3F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE400
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE410
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE420
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE430
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE440
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE450
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE460
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE470
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE480
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE490
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE4F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE500
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE510
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE520
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE530
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE540
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE550
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE560
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE570
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE580
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE590
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE5F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE600
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE610
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE620
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE630
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE640
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE650
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE660
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE670
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE680
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE690
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE6F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE700
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE710
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE720
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE730
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE740
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE750
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE760
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE770
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE780
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE790
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE7F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE800
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE810
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE820
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE830
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE840
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE850
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE860
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE870
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE880
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE890
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE8F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE900
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE910
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE920
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE930
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE940
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE950
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE960
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE970
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE980
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE990
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xE9F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEA90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEAF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEB90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEBF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEC90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xECF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xED90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEDF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEE90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEEA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEEB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEEC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEED0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEEE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEEF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEF90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xEFF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF000
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF010
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF020
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF030
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF040
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF050
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF060
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF070
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF080
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF090
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF0F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF100
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF110
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF120
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF130
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF140
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF150
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF160
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF170
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF180
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF190
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF1F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF200
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF210
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF220
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF230
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF240
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF250
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF260
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF270
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF280
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF290
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF2F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF300
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF310
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF320
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF330
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF340
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF350
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF360
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF370
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF380
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF390
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF3F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF400
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF410
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF420
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF430
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF440
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF450
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF460
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF470
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF480
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF490
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF4F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF500
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF510
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF520
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF530
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF540
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF550
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF560
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF570
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF580
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF590
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF5F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF600
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF610
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF620
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF630
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF640
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF650
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF660
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF670
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF680
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF690
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF6F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF700
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF710
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF720
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF730
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF740
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF750
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF760
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF770
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF780
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF790
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF7F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF800
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF810
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF820
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF830
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF840
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF850
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF860
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF870
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF880
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF890
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF8F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF900
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF910
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF920
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF930
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF940
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF950
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF960
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF970
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF980
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF990
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9A0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9B0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9C0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9D0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9E0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xF9F0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFA90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFAA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_FABC,	p_none,		//0xFAB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFAC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFAD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFAE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFAF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFB90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFBF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFC90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFCF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD30
	p_FD40,	p_FD42,	p_FD44,	p_FD46,	p_none,	p_none,	p_none,	p_none,		//0xFD40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFD90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFDF0

	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE50
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE60
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFE90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFEA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFEB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFEC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFED0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFEE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFEF0

	p_FF00,	p_FF02,	p_FF04,	p_FF06,	p_FF08,	p_FF0A,	p_none,	p_none,		//0xFF00
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF10
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF20
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF30
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF40
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF50
	p_none,	p_none,	p_none,	p_FF66,	p_none,	p_none,	p_none,	p_none,		//0xFF60
	p_FF70,	p_FF72,	p_FF74,	p_FF76,	p_none,	p_none,	p_none,	p_none,		//0xFF70
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF80
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFF90
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFFA0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_FABC,	p_none,		//0xFFB0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFFC0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFFD0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,		//0xFFE0
	p_none,	p_none,	p_none,	p_none,	p_none,	p_none,	p_FFFC,	p_FFFE};	//0xFFF0

#endif