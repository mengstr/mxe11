//###############################################################################
//#										#
//# MXE11 PDP11-Unix Emulator for Mikrocontrollers				#
//#										#
//# copyright (c) 2017 Joerg Wolfram (joerg@jcwolfram.de)			#
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
#if MCU > 9

#include "board.h"
#include "cpu.h"
#include "xvars.h"


extern unsigned short tks8,tkb8,tps8,tpb8,lks;
extern volatile unsigned short rx_rptr8,rx_wptr8,rx_cap8;
extern volatile unsigned short tx_rptr8,tx_wptr8,tx_cap8;

extern unsigned short tks9,tkb9,tps9,tpb9;
extern volatile unsigned short rx_rptr9,rx_wptr9,rx_cap9;
extern volatile unsigned short tx_rptr9,tx_wptr9,tx_cap9;

extern unsigned short system_state;

unsigned short kl11_prescaler;
unsigned short blink_prescaler;
unsigned short blink_val;

/**************************************************************************
  timer interrupt
***************************************************************************/
void user_tick()
{
	char c;

	//serve scheduler timer 60 Hz
	if(kl11_prescaler++ == KL11_FACTOR)
	{
		kl11_prescaler=0;
		lks |= 0x80;
		//interrupt, if enabled
		if(lks & 0x40) 	cycle_type |= (8 << SHIFT_CYCLE);

		if(blink_prescaler++ == 20) 
		{
			blink_prescaler=0;
			blink_val++;
			if(system_state == 2) set_portpin_level(STAT_LED,blink_val & 1);
		}
	}

	//serial in
	if((rx_cap8 < (SERIAL_BUFFER_SIZE-2)) && (TERMINAL_RCHECK() == 1))
	{
		c=TERMINAL_GET() & 0x7F;
		rxbuffer8[rx_wptr8++] = c;
		if(rx_wptr8 >= SERIAL_BUFFER_SIZE) rx_wptr8=0;
		rx_cap8++;
//		KPRINTF("KEY: %02x\r\n",c);
	}

	
	//serve console in
	if(((tks8 & 0x80) == 0) && (rx_cap8 > 0))
	{
		tkb8 = rxbuffer8[rx_rptr8++];
		if(rx_rptr8 >= SERIAL_BUFFER_SIZE) rx_rptr8=0;
		rx_cap8--;

		tks8 |= 0x80;
		//interrupt, if enabled
		if(tks8 & 0x40)
		{
			if(!(((rxint_queue & 0x000000FFul) == 0x00000001ul) ||
			     ((rxint_queue & 0x0000FF00ul) == 0x00000100ul) ||
			     ((rxint_queue & 0x00FF0000ul) == 0x00010000ul) ||
			     ((rxint_queue & 0xFF000000ul) == 0x01000000ul)))
			{
			 	cycle_type |= (2 << SHIFT_CYCLE);
			 	if ((rxint_queue & 0x000000FFul) == 0)
			 		rxint_queue |= 0x00000001ul;
			 		else if ((rxint_queue & 0x0000FF00ul) == 0)
				 		rxint_queue |= 0x00000100ul;
				 		else if ((rxint_queue & 0x00FF0000ul) == 0)
					 		rxint_queue |= 0x00010000ul;
			 				else rxint_queue |= 0x01000000ul;
			}
		}

//		if(tks8 & 0x40) cycle_type |= (2 << SHIFT_CYCLE);
	}

	//serve console out
	if(((tps8 & 0x80) == 0) && (tx_cap8 > 0))
	{
		txbuffer8[tx_wptr8++]= tpb8;
		if(tx_wptr8 >= SERIAL_BUFFER_SIZE) tx_wptr8=0;
		tx_cap8--;
		
		tps8 |= 0x80;

		//interrupt, if enabled
		if(tps8 & 0x40)
		{
			if(!(((txint_queue & 0x000000FFul) == 0x00000001ul) ||
			     ((txint_queue & 0x0000FF00ul) == 0x00000100ul) ||
			     ((txint_queue & 0x00FF0000ul) == 0x00010000ul) ||
			     ((txint_queue & 0xFF000000ul) == 0x01000000ul)))
			{
			 	cycle_type |= (1 << SHIFT_CYCLE);
			 	if ((txint_queue & 0x000000FFul) == 0)
			 		txint_queue |= 0x00000001ul;
			 		else if ((txint_queue & 0x0000FF00ul) == 0)
				 		txint_queue |= 0x00000100ul;
				 		else if ((txint_queue & 0x00FF0000ul) == 0)
					 		txint_queue |= 0x00010000ul;
			 				else txint_queue |= 0x01000000ul;
			}
		}

//		if(tps8 & 0x40) cycle_type |= (1 << SHIFT_CYCLE);
	}

	//serial out
	if((tx_cap8 < (SERIAL_BUFFER_SIZE -2)) && (kl11_prescaler & 1))
	{
		TERMINAL_PUT(txbuffer8[tx_rptr8++] & 0x7F);
		if(tx_rptr8 >= SERIAL_BUFFER_SIZE) tx_rptr8=0;
		tx_cap8++;
	}


	//serial9 in
	if((rx_cap9 < (SERIAL_BUFFER_SIZE-2)) && (TERM9_RCHECK() == 1))
	{
		c=TERM9_GET() & 0x7F;
		rxbuffer9[rx_wptr9++] = c;
		if(rx_wptr9 >= SERIAL_BUFFER_SIZE) rx_wptr9=0;
		rx_cap9++;
//		KPRINTF("KEY: %02x\r\n",c);
	}

	
	//serve console9 in
	if(((tks9 & 0x80) == 0) && (rx_cap9 > 0))
	{
		tkb9 = rxbuffer9[rx_rptr9++];
//		KPRINTF("SKEY: %02x\r\n",tkb9);
		if(rx_rptr9 >= SERIAL_BUFFER_SIZE) rx_rptr9=0;
		rx_cap9--;

		tks9 |= 0x80;
		//interrupt, if enabled
		if(tks9 & 0x40)
		{
			if(!(((rxint_queue & 0x000000FFul) == 0x00000002ul) ||
			     ((rxint_queue & 0x0000FF00ul) == 0x00000200ul) ||
			     ((rxint_queue & 0x00FF0000ul) == 0x00020000ul) ||
			     ((rxint_queue & 0xFF000000ul) == 0x02000000ul)))
			{
			 	cycle_type |= (2 << SHIFT_CYCLE);
			 	if ((rxint_queue & 0x000000FFul) == 0)
			 		rxint_queue |= 0x00000002ul;
			 		else if ((rxint_queue & 0x0000FF00ul) == 0)
				 		rxint_queue |= 0x00000200ul;
				 		else if ((rxint_queue & 0x00FF0000ul) == 0)
					 		rxint_queue |= 0x00020000ul;
			 				else rxint_queue |= 0x02000000ul;
			}
		}

//		if(tks9 & 0x40) cycle_type |= (2 << SHIFT_CYCLE);
	}

	//serve console9 out
	if(((tps9 & 0x80) == 0) && (tx_cap9 > 0))
	{
		txbuffer9[tx_wptr9++]= tpb9;
		if(tx_wptr9 >= SERIAL_BUFFER_SIZE) tx_wptr9=0;
		tx_cap9--;
		
		tps9 |= 0x80;
		//interrupt, if enabled
		if(tps9 & 0x40)
		{
			if(!(((txint_queue & 0x000000FFul) == 0x00000002ul) ||
			     ((txint_queue & 0x0000FF00ul) == 0x00000200ul) ||
			     ((txint_queue & 0x00FF0000ul) == 0x00020000ul) ||
			     ((txint_queue & 0xFF000000ul) == 0x02000000ul)))
			{
			 	cycle_type |= (1 << SHIFT_CYCLE);
			 	if ((txint_queue & 0x000000FFul) == 0)
			 		txint_queue |= 0x00000002ul;
			 		else if ((txint_queue & 0x0000FF00ul) == 0)
				 		txint_queue |= 0x00000200ul;
				 		else if ((txint_queue & 0x00FF0000ul) == 0)
					 		txint_queue |= 0x00020000ul;
			 				else txint_queue |= 0x02000000ul;
			}
		}
//		if(tps9 & 0x40) cycle_type |= (1 << SHIFT_CYCLE);
	}

	//serial9 out
	if((tx_cap9 < (SERIAL_BUFFER_SIZE -2)) && (kl11_prescaler & 1))
	{
		TERM9_PUT(txbuffer9[tx_rptr9++] & 0x7F);
		if(tx_rptr9 >= SERIAL_BUFFER_SIZE) tx_rptr9=0;
		tx_cap9++;
	}
}


void drv_on(void)
{
	set_portpin_one(DRIVE_LED);
}


#endif

