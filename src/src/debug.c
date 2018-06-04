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
#if MCU < 10

#include "board.h"
#include "cpu.h"
#include "xvars.h"
#include "memfunc.h"


void view_regs(void)
{
	DEBUG_PRINTF("PC=%04x (%06o)  ",pc,pc);
	DEBUG_PRINTF("R0=%04x    ",register0.ureg);
	DEBUG_PRINTF("R1=%04x    ",register1.ureg);
	DEBUG_PRINTF("R2=%04x    ",register2.ureg);
	DEBUG_PRINTF("R3=%04x    ",register3.ureg);
	DEBUG_PRINTF("R4=%04x    ",register4.ureg);
	DEBUG_PRINTF("R5=%04x    ",register5.ureg);
	DEBUG_PRINTF("SP=%04x->%04X  ",sp.ureg,iread_word(sp.ureg));
	DEBUG_PRINTF("PSW=%04x    ",psw);
	if(psw & 8) DEBUG_PRINTF("N"); else DEBUG_PRINTF("n");
	if(psw & 4) DEBUG_PRINTF("Z"); else DEBUG_PRINTF("z");
	if(psw & 2) DEBUG_PRINTF("V"); else DEBUG_PRINTF("v");
	if(psw & 1) DEBUG_PRINTF("C"); else DEBUG_PRINTF("c");
	DEBUG_PRINTF("\n");
	DEBUG_PRINTF("PC=%04x (%06o)  ",pc,pc);
	DEBUG_PRINTF("R0=%06o  ",register0.ureg);
	DEBUG_PRINTF("R1=%06o  ",register1.ureg);
	DEBUG_PRINTF("R2=%06o  ",register2.ureg);
	DEBUG_PRINTF("R3=%06o  ",register3.ureg);
	DEBUG_PRINTF("R4=%06o  ",register4.ureg);
	DEBUG_PRINTF("R5=%06o  ",register5.ureg);
	DEBUG_PRINTF("SP=%06o->%06o  ",sp.ureg,iread_word(sp.ureg));
	DEBUG_PRINTF("PSW=%06o    ",psw);
	DEBUG_PRINTF("\n");

}

#endif