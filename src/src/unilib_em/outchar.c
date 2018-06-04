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

#include <board.h>

#if MCU < 9


void (*printf_output) (unsigned char);

unsigned char *memptr;

//#######################################################################
//#									#
//#	set printf channel						#
//#									#
//#######################################################################
void set_outchar_routine(void (*outfunc)(unsigned char))
{
	printf_output = outfunc;
}

void unilib_outchar(unsigned char c)
{
	(*printf_output) (c);
}

//#######################################################################
//#									#
//#	dummy output							#
//#									#
//#######################################################################
void OUTPUT_NONE(unsigned char c)
{
	asm volatile("nop");
}

//#######################################################################
//#									#
//#	memory output							#
//#									#
//#######################################################################
void OUTPUT_MEMORY(unsigned char c)
{
	*memptr++ = c;
	*memptr=0;
}


//#######################################################################
//#									#
//#	memory output							#
//#									#
//#######################################################################
void set_outchar_memory(unsigned char *c)
{
	printf_output=OUTPUT_MEMORY;
	memptr = c;
	*memptr=0;
}

#endif