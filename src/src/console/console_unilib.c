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

#if MCU > 9

#include "board.h"
#include "cpu.h"
#include "xvars.h"

extern volatile unsigned short tks8,tkb8,tps8,tpb8;
extern volatile unsigned short tks9,tkb9,tps9,tpb9;

volatile unsigned short rx_wptr8,rx_rptr8,rx_cap8;
volatile unsigned short tx_wptr8,tx_rptr8,tx_cap8;

volatile unsigned short rx_wptr9,rx_rptr9,rx_cap9;
volatile unsigned short tx_wptr9,tx_rptr9,tx_cap9;

unilib_date_time act_time;

extern unsigned long get_date(void);
extern void set_date(unsigned long);

extern unsigned char console_in(void);
extern void console_out(unsigned char);
extern void console2_out(unsigned char);

void console_init()
{
	int i,n;
	unsigned char c;
	unsigned long dt;
	
	
	tpb8=0;
	tps8=0x80;
	tkb8=0;
	tks8=0;
	
	rx_rptr8=0;
	rx_wptr8=0;
	tx_rptr8=0;
	tx_wptr8=0;
	rx_cap8=0;
	tx_cap8=SERIAL_BUFFER_SIZE-2;

	tpb9=0;
	tps9=0x80;
	tkb9=0;
	tks9=0;

	rx_rptr9=0;
	rx_wptr9=0;
	tx_rptr9=0;
	tx_wptr9=0;
	rx_cap9=0;
	tx_cap9=SERIAL_BUFFER_SIZE-2;

	dt=xrtc_get_date();
	if(dt==0xFFFFFFFF)
	{
		enable_interrupts();
		goto TS_ESC;
	}

	KPRINTF(SINTRO,0);
//	KPRINTF("SC=%d\r\n",SHIFT_CYCLE);
	enable_interrupts();
	
	i=0;
	
	do
	{	
		c=console_in();
		if(c == 0x20) i=100;
		wait_ticks(750);
		i++;
	}while(i<15);

	if(i > 50)
	{
		dt=xrtc_get_date();
		KPRINTF("\fCURRENT TIMESTAMP:%lx\r\n",dt);
		unix2date(dt,&act_time);
		KPRINTF("CURRENT TIME:%04d/%d/%d  %02i:%02i:%02i\r\n\r\n",act_time.year,act_time.month,act_time.day,act_time.hour,act_time.min,act_time.sec);
		
		act_time.year=0;
		do{
			i=0;
			KPRINTF("NEW YEAR     :%04d\r",act_time.year);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.year = ((act_time.year * 10) + 0) % 10000; break;	
				case '1':	act_time.year = ((act_time.year * 10) + 1) % 10000; break;	
				case '2':	act_time.year = ((act_time.year * 10) + 2) % 10000; break;	
				case '3':	act_time.year = ((act_time.year * 10) + 3) % 10000; break;	
				case '4':	act_time.year = ((act_time.year * 10) + 4) % 10000; break;	
				case '5':	act_time.year = ((act_time.year * 10) + 5) % 10000; break;	
				case '6':	act_time.year = ((act_time.year * 10) + 6) % 10000; break;	
				case '7':	act_time.year = ((act_time.year * 10) + 7) % 10000; break;	
				case '8':	act_time.year = ((act_time.year * 10) + 8) % 10000; break;	
				case '9':	act_time.year = ((act_time.year * 10) + 9) % 10000; break;	
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.year < 1970) || (act_time.year > 2037));
		
		KPRINTF("\n");
			
		act_time.month=0;
		do{
			i=0;
			KPRINTF("NEW MONTH    :%02d\r",act_time.month);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.month = ((act_time.month * 10) + 0) % 100; break;	
				case '1':	act_time.month = ((act_time.month * 10) + 1) % 100; break;	
				case '2':	act_time.month = ((act_time.month * 10) + 2) % 100; break;	
				case '3':	act_time.month = ((act_time.month * 10) + 3) % 100; break;	
				case '4':	act_time.month = ((act_time.month * 10) + 4) % 100; break;	
				case '5':	act_time.month = ((act_time.month * 10) + 5) % 100; break;	
				case '6':	act_time.month = ((act_time.month * 10) + 6) % 100; break;	
				case '7':	act_time.month = ((act_time.month * 10) + 7) % 100; break;	
				case '8':	act_time.month = ((act_time.month * 10) + 8) % 100; break;	
				case '9':	act_time.month = ((act_time.month * 10) + 9) % 100; break;	
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.month < 1) || (act_time.month > 12));

		KPRINTF("\n");
	
		n=get_max_day(act_time.year,act_time.month);
		
		act_time.day=0;
		do{
			i=0;
			KPRINTF("NEW DAY      :%02d\r",act_time.day);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.day = ((act_time.day * 10) + 0) % 100;	 break;
				case '1':	act_time.day = ((act_time.day * 10) + 1) % 100;	 break;
				case '2':	act_time.day = ((act_time.day * 10) + 2) % 100;	 break;
				case '3':	act_time.day = ((act_time.day * 10) + 3) % 100;	 break;
				case '4':	act_time.day = ((act_time.day * 10) + 4) % 100;	 break;
				case '5':	act_time.day = ((act_time.day * 10) + 5) % 100;	 break;
				case '6':	act_time.day = ((act_time.day * 10) + 6) % 100;	 break;
				case '7':	act_time.day = ((act_time.day * 10) + 7) % 100;	 break;
				case '8':	act_time.day = ((act_time.day * 10) + 8) % 100;	 break;
				case '9':	act_time.day = ((act_time.day * 10) + 9) % 100;	 break;
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.day < 1) || (act_time.day > n));

		KPRINTF("\n");

		act_time.hour=0;
		do{
			i=0;
			KPRINTF("NEW HOUR     :%02d\r",act_time.hour);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.hour = ((act_time.hour * 10) + 0) % 100; break;	
				case '1':	act_time.hour = ((act_time.hour * 10) + 1) % 100; break;	
				case '2':	act_time.hour = ((act_time.hour * 10) + 2) % 100; break;	
				case '3':	act_time.hour = ((act_time.hour * 10) + 3) % 100; break;	
				case '4':	act_time.hour = ((act_time.hour * 10) + 4) % 100; break;	
				case '5':	act_time.hour = ((act_time.hour * 10) + 5) % 100; break;	
				case '6':	act_time.hour = ((act_time.hour * 10) + 6) % 100; break;	
				case '7':	act_time.hour = ((act_time.hour * 10) + 7) % 100; break;	
				case '8':	act_time.hour = ((act_time.hour * 10) + 8) % 100; break;	
				case '9':	act_time.hour = ((act_time.hour * 10) + 9) % 100; break;	
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.hour > 23));

		KPRINTF("\n");

		act_time.min=0;
		do{
			i=0;
			KPRINTF("NEW MIN      :%02d\r",act_time.min);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.min = ((act_time.min * 10) + 0) % 100;	 break;
				case '1':	act_time.min = ((act_time.min * 10) + 1) % 100;	 break;
				case '2':	act_time.min = ((act_time.min * 10) + 2) % 100;	 break;
				case '3':	act_time.min = ((act_time.min * 10) + 3) % 100;	 break;
				case '4':	act_time.min = ((act_time.min * 10) + 4) % 100;	 break;
				case '5':	act_time.min = ((act_time.min * 10) + 5) % 100;	 break;
				case '6':	act_time.min = ((act_time.min * 10) + 6) % 100;	 break;
				case '7':	act_time.min = ((act_time.min * 10) + 7) % 100;	 break;
				case '8':	act_time.min = ((act_time.min * 10) + 8) % 100;	 break;
				case '9':	act_time.min = ((act_time.min * 10) + 9) % 100;	 break;
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.min > 59));
		
		KPRINTF("\n");

		act_time.sec=0;
		do{
			i=0;
			KPRINTF("NEW SEC      :%02d\r",act_time.sec);
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case '0':	act_time.sec = ((act_time.sec * 10) + 0) % 100;	 break;
				case '1':	act_time.sec = ((act_time.sec * 10) + 1) % 100;	 break;
				case '2':	act_time.sec = ((act_time.sec * 10) + 2) % 100;	 break;
				case '3':	act_time.sec = ((act_time.sec * 10) + 3) % 100;	 break;
				case '4':	act_time.sec = ((act_time.sec * 10) + 4) % 100;	 break;
				case '5':	act_time.sec = ((act_time.sec * 10) + 5) % 100;	 break;
				case '6':	act_time.sec = ((act_time.sec * 10) + 6) % 100;	 break;
				case '7':	act_time.sec = ((act_time.sec * 10) + 7) % 100;	 break;
				case '8':	act_time.sec = ((act_time.sec * 10) + 8) % 100;	 break;
				case '9':	act_time.sec = ((act_time.sec * 10) + 9) % 100;	 break;
				case 'q':	goto TS_ESC;
				case 'Q':	goto TS_ESC;
				case 0x0d:	i=1; break;
				default:	i=0;
			}
		}while((i==0) || (act_time.sec > 59));

		KPRINTF("\n\n");
		
		KPRINTF("NEW TIME:%04d/%d/%d  %02i:%02i:%02i\r\n",act_time.year,act_time.month,act_time.day,act_time.hour,act_time.min,act_time.sec);
		dt=date2unix(&act_time);
		KPRINTF("NEW TIMESTAMP:%lx\r\n\n",dt);

		KPRINTF("(S)et or (Q)uit ?\r\n");

		do{
			i=0;
			do
			{
				c=console_in();
			}while(c==0);
			
			switch(c)
			{
				case 's':	i=1; xrtc_set_date(dt); break;
				case 'S':	i=1; xrtc_set_date(dt); break;
				case 'q':	i=1; break;
				case 'Q':	i=1; break;
				default:	i=0;
			}
		}while(i==0);
	}

TS_ESC:
	
	c=TERMINAL_GET();		//flush input
	
	do
	{
		c=console_in();
	}while(c !=0 );
			 
	
	tpb8=0;
	tps8=0x80;
	tkb8=0;
	tks8=0;
	
	rx_rptr8=0;
	rx_wptr8=0;
	tx_rptr8=0;
	tx_wptr8=0;
	rx_cap8=0;
	tx_cap8=SERIAL_BUFFER_SIZE-2;

	set_outchar_routine(console_out);	
	KPRINTF(INTRO,0);	
}

#endif


