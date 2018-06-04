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
#include "xvars.h"

//#######################################################################
//# init the memory array
//#######################################################################
void memory_init(void)
{
	int i;
	
	for(i=0;i<28672;i++) user_memory_data.word[i]=0;
}

//#######################################################################
//# show some memory data
//#######################################################################
void show_mem(unsigned short addr,int lines)
{
#if MCU < 9

	unsigned short a;
	int i,j;
	
	a=addr;
	
	printf("\r\n");	
	for(i=0;i<lines;i++)
	{
		printf("%04X => ",a);
		for(j=0;j<8;j++)
		{
			printf("%04X ",user_memory_data.word[a >> 1]);
			a+=2;
		}
		printf("\r\n");	
	}
#else
	unsigned short a;
	int i,j;
	
	a=addr;
	
	KPRINTF("\r\n");	
	for(i=0;i<lines;i++)
	{
		KPRINTF("%04x => ",a);
		for(j=0;j<8;j++)
		{
			KPRINTF("%04x ",user_memory_data.word[a >> 1]);
			a+=2;
		}
		KPRINTF("\r\n");	
	}

#endif

}


//#######################################################################
//# show some memory data (octal)
//#######################################################################
void show_mem_oct(unsigned short addr,int lines)
{
#if MCU < 9
	unsigned short a;
	int i,j;
	
	a=addr;
	
	for(i=0;i<lines;i++)
	{
		printf("%06o => ",a);
		for(j=0;j<8;j++)
		{
			printf("%06o ",user_memory_data.word[a >> 1]);
			a+=2;
		}
		printf("\n");	
	}
#endif
}
