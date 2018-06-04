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
//# 0 direct register sources are not possible
//##############################################################################
unsigned short getja_il(void)
{
	return 0xF014;	//illegal jump vector
}

//##############################################################################
//# 1 Rn is holding the address
//##############################################################################
unsigned short getja_10(void)
{
	return register0.ureg;	
}

unsigned short getja_11(void)
{
	return register1.ureg;	
}

unsigned short getja_12(void)
{
	return register2.ureg;	
}

unsigned short getja_13(void)
{
	return register3.ureg;	
}

unsigned short getja_14(void)
{
	return register4.ureg;	
}

unsigned short getja_15(void)
{
	return register5.ureg;	
}

unsigned short getja_16(void)
{
	return sp.ureg;	
}

unsigned short getja_17(void)
{
	return pc;	
}


//##############################################################################
//# 2 Rn+ is holding the address
//##############################################################################
unsigned short getja_20(void)
{
	unsigned short w=register0.ureg;	
	register0.ureg+=2;
	return w;
}

unsigned short getja_21(void)
{
	unsigned short w=register1.ureg;
	register1.ureg+=2;
	return w;
}

unsigned short getja_22(void)
{
	unsigned short w=register2.ureg;
	register2.ureg+=2;
	return w;
}

unsigned short getja_23(void)
{
	unsigned short w=register3.ureg;
	register3.ureg+=2;
	return w;
}

unsigned short getja_24(void)
{
	unsigned short w=register4.ureg;
	register4.ureg+=2;
	return w;
}

unsigned short getja_25(void)
{
	unsigned short w=register5.ureg;
	register5.ureg+=2;
	return w;
}

unsigned short getja_26(void)
{
	unsigned short w=sp.ureg;	
	sp.ureg+=2;
	return w;
}

unsigned short getja_27(void)
{
	unsigned short w=pc;	
	pc+=2;
	return w;
}

//##############################################################################
//# 3 (Rn)+ is holding the address of the adrress
//##############################################################################
unsigned short getja_30(void)
{
	unsigned short w=iread_word(register0.ureg);	
	register0.ureg+=2;
	return w;
}

unsigned short getja_31(void)
{
	unsigned short w=iread_word(register1.ureg);	
	register1.ureg+=2;
	return w;
}

unsigned short getja_32(void)
{
	unsigned short w=iread_word(register2.ureg);	
	register2.ureg+=2;
	return w;
}

unsigned short getja_33(void)
{
	unsigned short w=iread_word(register3.ureg);	
	register3.ureg+=2;
	return w;
}

unsigned short getja_34(void)
{
	unsigned short w=iread_word(register4.ureg);	
	register4.ureg+=2;
	return w;
}

unsigned short getja_35(void)
{
	unsigned short w=iread_word(register5.ureg);	
	register5.ureg+=2;
	return w;
}

unsigned short getja_36(void)
{
	unsigned short w=iread_word(sp.ureg);	
	sp.ureg+=2;
	return w;
}

unsigned short getja_37(void)
{
	unsigned short w=iread_word(pc);	
	pc+=2;
	return w;
}


//##############################################################################
//# 4 -Rn is holding the address
//##############################################################################
unsigned short getja_40(void)
{
	register0.ureg-=2;
	return register0.ureg;	
}

unsigned short getja_41(void)
{
	register1.ureg-=2;
	return register1.ureg;	
}

unsigned short getja_42(void)
{
	register2.ureg-=2;
	return register2.ureg;	
}

unsigned short getja_43(void)
{
	register3.ureg-=2;
	return register3.ureg;	
}

unsigned short getja_44(void)
{
	register4.ureg-=2;
	return register4.ureg;	
}

unsigned short getja_45(void)
{
	register5.ureg-=2;
	return register5.ureg;	
}

unsigned short getja_46(void)
{
	sp.ureg-=2;
	return sp.ureg;	
}

unsigned short getja_47(void)
{
	pc-=2;
	return pc;	
}


//##############################################################################
//# 5 -(Rn) is holding the address of the address
//##############################################################################
unsigned short getja_50(void)
{
	register0.ureg-=2;
	return iread_word(register0.ureg);	
}

unsigned short getja_51(void)
{
	register1.ureg-=2;
	return iread_word(register1.ureg);	
}

unsigned short getja_52(void)
{
	register2.ureg-=2;
	return iread_word(register2.ureg);	
}

unsigned short getja_53(void)
{
	register3.ureg-=2;
	return iread_word(register3.ureg);	
}

unsigned short getja_54(void)
{
	register4.ureg-=2;
	return iread_word(register4.ureg);	
}

unsigned short getja_55(void)
{
	register5.ureg-=2;
	return iread_word(register5.ureg);	
}

unsigned short getja_56(void)
{
	sp.ureg-=2;
	return iread_word(sp.ureg);	
}

unsigned short getja_57(void)
{
	pc-=2;
	return iread_word(pc);	
}


//##############################################################################
//# 6 indexed
//##############################################################################
unsigned short getja_60(void)
{	
	unsigned short x=ifetch_next();
	return x+register0.ureg;
}

unsigned short getja_61(void)
{	
	unsigned short x=ifetch_next();
	return x+register1.ureg;
}

unsigned short getja_62(void)
{	
	unsigned short x=ifetch_next();
	return x+register2.ureg;
}

unsigned short getja_63(void)
{	
	unsigned short x=ifetch_next();
	return x+register3.ureg;
}

unsigned short getja_64(void)
{	
	unsigned short x=ifetch_next();
	return x+register4.ureg;
}

unsigned short getja_65(void)
{	
	unsigned short x=ifetch_next();
	return x+register5.ureg;
}

unsigned short getja_66(void)
{	
	unsigned short x=ifetch_next();
	return x+sp.ureg;
}

unsigned short getja_67(void)
{	
	unsigned short x=ifetch_next();
	return x+pc;
}

//##############################################################################
//# 7 index deferred
//##############################################################################
unsigned short getja_70(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register0.ureg+x);
}

unsigned short getja_71(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register1.ureg+x);
}

unsigned short getja_72(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register2.ureg+x);
}

unsigned short getja_73(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register3.ureg+x);
}

unsigned short getja_74(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register4.ureg+x);
}

unsigned short getja_75(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(register5.ureg+x);
}

unsigned short getja_76(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(sp.ureg+x);
}

unsigned short getja_77(void)
{	
	unsigned short x=ifetch_next();
	return iread_word(pc+x);
}

//##############################################################################
//# tables
//##############################################################################

get_op_t	getja_op[64]=
{
getja_il,	getja_il,	getja_il,	getja_il,	getja_il,	getja_il,	getja_il,	getja_il,
getja_10,	getja_11,	getja_12,	getja_13,	getja_14,	getja_15,	getja_16,	getja_17,
getja_20,	getja_21,	getja_22,	getja_23,	getja_24,	getja_25,	getja_26,	getja_27,
getja_30,	getja_31,	getja_32,	getja_33,	getja_34,	getja_35,	getja_36,	getja_37,
getja_40,	getja_41,	getja_42,	getja_43,	getja_44,	getja_45,	getja_46,	getja_47,
getja_50,	getja_51,	getja_52,	getja_53,	getja_54,	getja_55,	getja_56,	getja_57,
getja_60,	getja_61,	getja_62,	getja_63,	getja_64,	getja_65,	getja_66,	getja_67,
getja_70,	getja_71,	getja_72,	getja_73,	getja_74,	getja_75,	getja_76,	getja_77
};
