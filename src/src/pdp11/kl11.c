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

#if MCU < 10

#include "board.h"
#include "cpu.h"
#include "time.h"
#include "xvars.h"

extern unsigned short cycle_type;

unsigned short lks;
long kl11_counter;
struct timespec t1,t2,tres;


//##############################################################################
//# serve only for PC
//##############################################################################
void serve_kl11(void)
{
	long n1,n2; 
	clock_gettime(CLOCK_REALTIME,&t2);

	n1=t1.tv_nsec+16666667;
	n2=t2.tv_nsec;

	if(t2.tv_sec > t1.tv_sec) n2 += 1000000000;
	
	if(n2 > n1)
	{
		t1=t2;
		lks |= 0x80;
		
		if(lks & 0x40)
		{
//			printf("USR= %04X    SYS=%04X (IPL=%d)\n",read_word(0x5D0A),read_word(0x5D0C),(psw >> 5) & 7);
//			printf("*");
//			fflush(stdout);
			cycle_type |= (8 << SHIFT_CYCLE);
		}
	}
}

void kl11_init(void)
{
	lks=0x80;
	clock_gettime(CLOCK_REALTIME,&t1);
	clock_getres(CLOCK_REALTIME,&tres);
//	printf("SEC= %ld   NSEC= %ld\n",tres.tv_sec,tres.tv_nsec);
}
#else

#include "board.h"
#include "cpu.h"

unsigned short lks;
void kl11_init(void)
{
	lks=0x80;
}
#endif