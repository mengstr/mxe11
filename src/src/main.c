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
#include "board.h"
#include "cpu.h"
#include "vars.h"

#if MCU == 2
	#define SCREEN_WIDTH 640
	#define SCREEN_HEIGHT 480
	extern SDL_Surface* screen;
#endif

#if MCU == 1
	#define SCREEN_WIDTH 960
	#define SCREEN_HEIGHT 480
	extern SDL_Surface* screen;
#endif

#if MCU < 10
	extern void set_outchar_routine(void (*outfunc)(unsigned char));
#endif

#if MCU > 9
	extern long get_date();
	extern void set_date(unsigned long);
#endif

#if MCU == 11
	extern void masterloop(void);
#endif

extern void cpu_init();
extern void cpu_step();
extern void memory_init();
extern void console_init();
extern void serve_console();
extern void terminal_init();
extern void console_exit();
extern void rk11_init();
extern void rk11_flush();
extern void kl11_init();
extern void rk11_bootsetup();
extern void serve_kl11();
extern void console_out(unsigned char);

extern unsigned short system_state;

extern volatile unsigned short rx_rptr8,rx_wptr8,rx_cap8;
extern volatile unsigned short tx_rptr8,tx_wptr8,tx_cap8;
extern volatile unsigned short rx_rptr9,rx_wptr9,rx_cap9;
extern volatile unsigned short tx_rptr9,tx_wptr9,tx_cap9;

extern cycle_t do_cycle[32];

int c;


//######################################################################################

int main()
{
#if MCU > 9
	char c;
#else
	int prev=0;
#endif
#if MCU == 0

	fcntl(0,F_SETFL,O_NONBLOCK);
//	system("/bin/stty/ -icanon -echo");
#endif

#if MCU == 1
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_SWSURFACE);
	SDL_WM_SetCaption("MXE11-SDL", "MXE11-SDL");
#endif


#if MCU == 2
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 16, SDL_SWSURFACE);
	SDL_WM_SetCaption("MXE11-SDL", "MXE11-SDL");
#endif

#if MCU > 9
	unilib_init();
	set_clock(CLOCK_SETTING);
	set_portpin_output(STAT_LED);
	set_portpin_output(DRIVE_LED);
	set_portpin_zero(STAT_LED);
	set_portpin_one(DRIVE_LED);

//	while(1);
	
	xrtc_init(RTC_CLOCK,RTC_DATA);

#if MCU == 30
	//Disable U7
	set_portpin_output(PORT_E,3);
	set_portpin_one(PORT_E,3);
#endif	
	
	unilib_pause_ms(250);
	
	enable_tick(TICK);

	TERMINAL_UART_INIT(TERMINAL_BAUD_DIVIDER);	//terminal 1
	TERM9_UART_INIT(TERM9_BAUD_DIVIDER);		//terminal 2
	TERMINAL_PUT(0x0c);
	TERM9_PUT(0x0c);
	c=TERMINAL_GET();				//flush input
	c=TERM9_GET();					//flush input

	unilib_pause_ms(100);
#endif

#if MCU > 0
	set_outchar_routine(console_out);
#endif
	memory_init();	
	cpu_init();
	console_init();
#if LOAD_TEST == 0
	kl11_init();
	rk11_init();
#endif
	rk11_bootsetup();
/*
	unsigned long *xptr;
	unsigned long xdat;
	xptr=0x40013000;
	xdat=*xptr;	
	KPRINTF("CR1=%lx\r\n",xdat);
	xptr=0x40013004;
	xdat=*xptr;	
	KPRINTF("CR2=%lx\r\n",xdat);
*/

#ifdef F1_OVERCLOCKING
	unilib_pause_ms(200);
	FLASH.ACR.BIT.LATENCY = 3;
	set_clock(CLOCK_SETTING2);
	enable_tick(TICK2);
	TERMINAL_UART_INIT(TERMINAL_BAUD_DIVIDER2);	//terminal 1
	TERM9_UART_INIT(TERM9_BAUD_DIVIDER2);		//terminal 2
#endif


#if MCU > 9

	unilib_pause_ms(10);
	set_portpin_one(STAT_LED);			//set status to run

#if MCU == 11
	masterloop();
#endif
	while(1)
	{
		do_cycle[cycle_type >> SHIFT_CYCLE]();
	}
#endif

#if MCU < 10
	do
	{
		do_cycle[cycle_type]();
/*
		if(pc == 0x3ce0)
		{
			printf("DEV=%d\n",register4.ureg);
		}
*/
/*
		if(pc == 0x3d12)
		{
			printf("DEV=%d\n",register2.ureg);
		}
*/
		if(++prev > 200)
		{
			serve_console();
			serve_kl11();
			prev=0;
		}
	}
	while(system_state != 0);
	rk11_flush();
	console_exit();
#endif


	return 0;
}


#if MCU > 0
void console_out(unsigned char c)
{
	while(tx_cap8 < 1);
#if MCU > 9
	disable_interrupts();
#endif
	txbuffer8[tx_wptr8++]= c;
	tx_wptr8 &= 0xFF;
	tx_cap8--;
#if MCU > 9
	enable_interrupts();
#endif
}
#endif


#if MCU > 0
unsigned char console_in(void)
{
	unsigned char c;
	
	if (rx_cap8 == 0) return 0;
#if MCU > 9
	disable_interrupts();
#endif
	c=rxbuffer8[rx_rptr8++];
	rx_rptr8 &= 0xFF;
	rx_cap8--;
#if MCU > 9
	enable_interrupts();
#endif
	return c;
}
#endif

#if MCU > 9
void console2_out(unsigned char c)
{
	while(tx_cap9 < 1);
	disable_interrupts();
	txbuffer9[tx_wptr9++]= c;
	tx_wptr9 &= 0xFF;
	tx_cap9--;
	enable_interrupts();
}

unsigned char console2_in(void)
{
	unsigned char c;
	
	if (rx_cap9 == 0) return 0;
	disable_interrupts();
	c=rxbuffer9[rx_rptr9++];
	rx_rptr9 &= 0xFF;
	rx_cap9--;
	enable_interrupts();
	return c;
}
#endif
