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
#if MCU == 0

#include "board.h"
#include "cpu.h"
#include "xvars.h"
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


extern unsigned short tks8,tkb8,tps8,tpb8;

extern void add_interrupt(unsigned short, unsigned short);
extern unsigned short cycle_type;

struct termios oldt,newt;

void console_init(void)
{
	tpb8=0;
	tps8=0x80;
	tkb8=0;
	tks8=0;

	tcgetattr(STDIN_FILENO,&oldt);
	
	newt=oldt;
	
	newt.c_lflag &= ~(ICANON);
	newt.c_lflag &= ~(ECHO);
	
	tcsetattr(STDIN_FILENO,TCSANOW,&newt);	

//	printf("MXE11 V1.30 (c)2017-2018 Joerg Wolfram\r\n--------------------------------------\r\n\r\r"); 
	printf(INTRO); 
}

void console_exit(void)
{
	tcsetattr(STDIN_FILENO,TCSANOW,&oldt);	
}

void serve_console(void)
{
	char c;
	int i;

	//check if char available
	i=read(0,&c,1);
	if (i==1) 
	{
		tkb8=c;
		tks8 |= 0x80;
		if(tks8 & 0x40) 	cycle_type |= (2 << SHIFT_CYCLE);
	}

	if((tps8 & 0x80) == 0)
	{
		printf("%c",tpb8 & 0x7F);
		fflush(stdout);
		tps8 |= 0x80;
		if(tps8 & 0x40) 	cycle_type |= (1 << SHIFT_CYCLE);
	}
}


#endif

