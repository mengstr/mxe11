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
#include "cpu.h"
#include "xvars.h"
#include "memfunc.h"

//##############################################################################
//# direct register write
//##############################################################################
void bputw_00(unsigned short value)
{
	register0.ureg = value;
}

void bputb_00(unsigned char value)
{
	register0.bytes[LOBYTE] = value;
}

void bputw_01(unsigned short value)
{
	register1.ureg = value;
}

void bputb_01(unsigned char value)
{
	register1.bytes[LOBYTE] = value;
}

void bputw_02(unsigned short value)
{
	register2.ureg = value;
}


void bputb_02(unsigned char value)
{
	register2.bytes[LOBYTE] = value;
}

void bputw_03(unsigned short value)
{
	register3.ureg = value;
}

void bputb_03(unsigned char value)
{
	register3.bytes[LOBYTE] = value;
}

void bputw_04(unsigned short value)
{
	register4.ureg = value;
}

void bputb_04(unsigned char value)
{
	register4.bytes[LOBYTE] = value;
}

void bputw_05(unsigned short value)
{
	register5.ureg = value;
}

void bputb_05(unsigned char value)
{
	register5.bytes[LOBYTE] = value;
}

void bputw_06(unsigned short value)
{
	sp.ureg = value;
}

void bputb_06(unsigned char value)
{
	sp.bytes[LOBYTE] = value;
}

void bputw_07(unsigned short value)
{
	pc = value;
}

void bputb_07(unsigned char value)
{
	pc = (pc & 0xff00) | value;
}

//##############################################################################
//# all other addr
//##############################################################################
void bputw(unsigned short value)
{
	iwrite_word(last_addr,value);
}

void bputb(unsigned char value)
{
	iwrite_byte(last_addr,value);	
}

//##############################################################################
//# tables
//##############################################################################
put_op_t	bputw_op[64]=
{
bputw_00,	bputw_01,	bputw_02,	bputw_03,	bputw_04,	bputw_05,	bputw_06,	bputw_07,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,
bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw,		bputw
};

putb_op_t bputb_op[64]=
{
bputb_00,	bputb_01,	bputb_02,	bputb_03,	bputb_04,	bputb_05,	bputb_06,	bputb_07,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,
bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb,		bputb
};
