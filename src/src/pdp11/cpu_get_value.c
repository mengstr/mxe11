//###############################################################################
//#										#
//# MXE11 PDP11-Unix Emulator for Mikrocontrollers				#
//#										#
//# copyright (c) 2017-2ß18 Joerg Wolfram (joerg@jcwolfram.de)			#
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
//# direct register sources
//##############################################################################
unsigned short getw_00(void)
{
	return register0.ureg;
}

unsigned char getb_00(void)
{
	return register0.bytes[LOBYTE];
}

unsigned short getw_01(void)
{
	return register1.ureg;
}

unsigned char getb_01(void)
{
	return register1.bytes[LOBYTE];
}

unsigned short getw_02(void)
{
	return register2.ureg;
}

unsigned char getb_02(void)
{
	return register2.bytes[LOBYTE];
}

unsigned short getw_03(void)
{
	return register3.ureg;
}

unsigned char getb_03(void)
{
	return register3.bytes[LOBYTE];
}

unsigned short getw_04(void)
{
	return register4.ureg;
}

unsigned char getb_04(void)
{
	return register4.bytes[LOBYTE];
}

unsigned short getw_05(void)
{
	return register5.ureg;
}

unsigned char getb_05(void)
{
	return register5.bytes[LOBYTE];
}

unsigned short getw_06(void)
{
	return sp.ureg;
}

unsigned char getb_06(void)
{
	return sp.bytes[LOBYTE];
}

unsigned short getw_07(void)
{
	return pc;
}

unsigned char getb_07(void)
{
	return pc & 0xFF;
}

//##############################################################################
//# indirect register sources
//##############################################################################
unsigned short getw_10(void)
{
	last_addr=register0.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_10(void)
{
	last_addr=register0.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_11(void)
{
	last_addr=register1.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_11(void)
{
	last_addr=register1.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_12(void)
{
	last_addr=register2.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_12(void)
{
	last_addr=register2.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_13(void)
{
	last_addr=register3.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_13(void)
{
	last_addr=register3.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_14(void)
{
	last_addr=register4.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_14(void)
{
	last_addr=register4.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_15(void)
{
	last_addr=register5.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_15(void)
{
	last_addr=register5.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_16(void)
{
	last_addr=sp.ureg;
	return iread_word(last_addr);	
}

unsigned char getb_16(void)
{
	last_addr=sp.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_17(void)
{
	last_addr=pc;
	return iread_word(last_addr);	
}

unsigned char getb_17(void)
{
	last_addr=pc;
	return iread_byte(last_addr);	
}


//##############################################################################
//# register post increment
//##############################################################################
unsigned short getw_20(void)
{
	last_addr=register0.ureg;
	register0.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_20(void)
{
	last_addr=register0.ureg;
	register0.ureg+=1;	
	return iread_byte(last_addr);	
}

unsigned short getw_21(void)
{
	last_addr=register1.ureg;
	register1.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_21(void)
{
	last_addr=register1.ureg;
	register1.ureg+=1;	
	return iread_byte(last_addr);	
}

unsigned short getw_22(void)
{
	last_addr=register2.ureg;
	register2.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_22(void)
{
	last_addr=register2.ureg;
	register2.ureg+=1;	
	return iread_byte(last_addr);	
}

unsigned short getw_23(void)
{
	last_addr=register3.ureg;
	register3.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_23(void)
{
	last_addr=register3.ureg;
	register3.ureg+=1;	
	return iread_byte(last_addr);	
}


unsigned short getw_24(void)
{
	last_addr=register4.ureg;
	register4.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_24(void)
{
	last_addr=register4.ureg;
	register4.ureg+=1;	
	return iread_byte(last_addr);	
}


unsigned short getw_25(void)
{
	last_addr=register5.ureg;
	register5.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_25(void)
{
	last_addr=register5.ureg;
	register5.ureg+=1;	
	return iread_byte(last_addr);	
}


unsigned short getw_26(void)
{
	last_addr=sp.ureg;
	sp.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_26(void)
{
	last_addr=sp.ureg;
	sp.ureg+=2;	
	return iread_byte(last_addr);	
}

unsigned short getw_27(void)
{
	last_addr=pc;
	pc+=2;
	return iread_word(last_addr);
}

unsigned char getb_27(void)
{
	last_addr=pc;
	pc+=2;
	return (iread_byte(last_addr));
}


//##############################################################################
//# indirect register post increment
//##############################################################################
unsigned short getw_30(void)
{
	last_addr=iread_word(register0.ureg);
	register0.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_30(void)
{
	last_addr=iread_word(register0.ureg);
	register0.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_31(void)
{
	last_addr=iread_word(register1.ureg);
	register1.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_31(void)
{
	last_addr=iread_word(register1.ureg);
	register1.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_32(void)
{
	last_addr=iread_word(register2.ureg);
	register2.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_32(void)
{
	last_addr=iread_word(register2.ureg);
	register2.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_33(void)
{
	last_addr=iread_word(register3.ureg);
	register3.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_33(void)
{
	last_addr=iread_word(register3.ureg);
	register3.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_34(void)
{
	last_addr=iread_word(register4.ureg);
	register4.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_34(void)
{
	last_addr=iread_word(register4.ureg);
	register4.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_35(void)
{
	last_addr=iread_word(register5.ureg);
	register5.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_35(void)
{
	last_addr=iread_word(register5.ureg);
	register5.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_36(void)
{
	last_addr=iread_word(sp.ureg);
	sp.ureg+=2;	
	return iread_word(last_addr);
}

unsigned char getb_36(void)
{
	last_addr=iread_word(sp.ureg);
	sp.ureg+=2;	
	return iread_byte(last_addr);
}

unsigned short getw_37(void)
{
	last_addr=ifetch_next();	
	return iread_word(last_addr);	
}

unsigned char getb_37(void)
{
	last_addr=ifetch_next();
	return iread_byte(last_addr);	
}

//##############################################################################
//# register pre decrement
//##############################################################################
unsigned short getw_40(void)
{
	register0.ureg-=2;	
	last_addr=register0.ureg;
	return iread_word(last_addr);
}

unsigned char getb_40(void)
{
	register0.ureg-=1;	
	last_addr=register0.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_41(void)
{
	register1.ureg-=2;	
	last_addr=register1.ureg;
	return iread_word(last_addr);
}

unsigned char getb_41(void)
{
	register1.ureg-=1;	
	last_addr=register1.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_42(void)
{
	register2.ureg-=2;	
	last_addr=register2.ureg;
	return iread_word(last_addr);
}

unsigned char getb_42(void)
{
	register2.ureg-=1;	
	last_addr=register2.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_43(void)
{
	register3.ureg-=2;	
	last_addr=register3.ureg;
	return iread_word(last_addr);
}

unsigned char getb_43(void)
{
	register3.ureg-=1;	
	last_addr=register3.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_44(void)
{
	register4.ureg-=2;	
	last_addr=register4.ureg;
	return iread_word(last_addr);
}

unsigned char getb_44(void)
{
	register4.ureg-=1;	
	last_addr=register4.ureg;
	return iread_byte(last_addr);	
}


unsigned short getw_45(void)
{
	register5.ureg-=2;	
	last_addr=register5.ureg;
	return iread_word(last_addr);
}

unsigned char getb_45(void)
{
	register5.ureg-=1;	
	last_addr=register5.ureg;
	return iread_byte(last_addr);	
}

unsigned short getw_46(void)
{
	sp.ureg-=2;	
	last_addr=sp.ureg;
#if USE_STACKLIMIT == 1
	if(last_addr < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
	return iread_word(last_addr);
}

unsigned char getb_46(void)
{
	sp.ureg-=2;	
	last_addr=sp.ureg;
#if USE_STACKLIMIT == 1
	if(last_addr < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
	return iread_byte(last_addr);	
}

unsigned short getw_47(void)
{	
	pc-=2;	
	last_addr=pc;
	return iread_word(last_addr);		
}

unsigned char getb_47(void)
{
	pc-=2;	
	last_addr=pc;
	return iread_byte(last_addr);			
}


//##############################################################################
//# indirect register pre decrement
//##############################################################################
unsigned short getw_50(void)
{
	register0.ureg-=2;	
	last_addr=iread_word(register0.ureg);
	return iread_word(last_addr);
}

unsigned char getb_50(void)
{
	register0.ureg-=2;	
	last_addr=iread_word(register0.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_51(void)
{
	register1.ureg-=2;	
	last_addr=iread_word(register1.ureg);
	return iread_word(last_addr);
}

unsigned char getb_51(void)
{
	register1.ureg-=2;	
	last_addr=iread_word(register1.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_52(void)
{
	register2.ureg-=2;	
	last_addr=iread_word(register2.ureg);
	return iread_word(last_addr);
}

unsigned char getb_52(void)
{
	register2.ureg-=2;	
	last_addr=iread_word(register2.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_53(void)
{
	register3.ureg-=2;	
	last_addr=iread_word(register3.ureg);
	return iread_word(last_addr);
}

unsigned char getb_53(void)
{
	register3.ureg-=2;	
	last_addr=iread_word(register3.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_54(void)
{
	register4.ureg-=2;	
	last_addr=iread_word(register4.ureg);
	return iread_word(last_addr);
}

unsigned char getb_54(void)
{
	register4.ureg-=2;	
	last_addr=iread_word(register4.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_55(void)
{
	register5.ureg-=2;	
	last_addr=iread_word(register5.ureg);
	return iread_word(last_addr);
}

unsigned char getb_55(void)
{
	register5.ureg-=2;	
	last_addr=iread_word(register5.ureg);
	return iread_byte(last_addr);
}

unsigned short getw_56(void)
{
	sp.ureg-=2;	
	last_addr=iread_word(sp.ureg);
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
	return iread_word(last_addr);
}

unsigned char getb_56(void)
{
	sp.ureg-=2;	
	last_addr=iread_word(sp.ureg);
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
	return iread_byte(last_addr);
}

unsigned short getw_57(void)
{
	pc-=2;	
	last_addr=iread_word(pc);
	return iread_word(last_addr);
}

unsigned char getb_57(void)
{
	pc-=2;	
	last_addr=iread_word(pc);
	return iread_word(last_addr);
}

//##############################################################################
//# indexed
//##############################################################################
unsigned short getw_60(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register0.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_60(void)
{
	unsigned short x=ifetch_next();
	last_addr=register0.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_61(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register1.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_61(void)
{
	unsigned short x=ifetch_next();
	last_addr=register1.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_62(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register2.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_62(void)
{
	unsigned short x=ifetch_next();
	last_addr=register2.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_63(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register3.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_63(void)
{
	unsigned short x=ifetch_next();
	last_addr=register3.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_64(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register4.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_64(void)
{
	unsigned short x=ifetch_next();
	last_addr=register4.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_65(void)
{	
	unsigned short x=ifetch_next();
	last_addr=register5.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_65(void)
{
	unsigned short x=ifetch_next();
	last_addr=register5.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_66(void)
{	
	unsigned short x=ifetch_next();
	last_addr=sp.ureg+x;
	return iread_word(last_addr);
}

unsigned char getb_66(void)
{
	unsigned short x=ifetch_next();
	last_addr=sp.ureg+x;
	return iread_byte(last_addr);	
}

unsigned short getw_67(void)
{	
	unsigned short x=ifetch_next();
	last_addr=pc+x;
	return iread_word(last_addr);
}

unsigned char getb_67(void)
{
	unsigned short x=ifetch_next();
	last_addr=pc+x;
	return iread_byte(last_addr);
}

//##############################################################################
//# index deferred
//##############################################################################
unsigned short getw_70(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register0.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_70(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register0.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_71(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register1.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_71(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register1.ureg+x);
	return iread_byte(last_addr);
}


unsigned short getw_72(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register2.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_72(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register2.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_73(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register3.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_73(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register3.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_74(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register4.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_74(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register4.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_75(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(register5.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_75(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(register5.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_76(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(sp.ureg+x);
	return iread_word(last_addr);
}

unsigned char getb_76(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(sp.ureg+x);
	return iread_byte(last_addr);
}

unsigned short getw_77(void)
{	
	unsigned short x=ifetch_next();
	last_addr=iread_word(pc+x);
	return iread_word(last_addr);
}

unsigned char getb_77(void)
{
	unsigned short x=ifetch_next();
	last_addr=iread_word(pc+x);
	return iread_byte(last_addr);
}


//##############################################################################
//# tables
//##############################################################################

get_op_t	getw_op[64]=
{
getw_00,	getw_01,	getw_02,	getw_03,	getw_04,	getw_05,	getw_06,	getw_07,
getw_10,	getw_11,	getw_12,	getw_13,	getw_14,	getw_15,	getw_16,	getw_17,
getw_20,	getw_21,	getw_22,	getw_23,	getw_24,	getw_25,	getw_26,	getw_27,
getw_30,	getw_31,	getw_32,	getw_33,	getw_34,	getw_35,	getw_36,	getw_37,
getw_40,	getw_41,	getw_42,	getw_43,	getw_44,	getw_45,	getw_46,	getw_47,
getw_50,	getw_51,	getw_52,	getw_53,	getw_54,	getw_55,	getw_56,	getw_57,
getw_60,	getw_61,	getw_62,	getw_63,	getw_64,	getw_65,	getw_66,	getw_67,
getw_70,	getw_71,	getw_72,	getw_73,	getw_74,	getw_75,	getw_76,	getw_77
};

getb_op_t getb_op[64]=
{
getb_00,	getb_01,	getb_02,	getb_03,	getb_04,	getb_05,	getb_06,	getb_07,
getb_10,	getb_11,	getb_12,	getb_13,	getb_14,	getb_15,	getb_16,	getb_17,
getb_20,	getb_21,	getb_22,	getb_23,	getb_24,	getb_25,	getb_26,	getb_27,
getb_30,	getb_31,	getb_32,	getb_33,	getb_34,	getb_35,	getb_36,	getb_37,
getb_40,	getb_41,	getb_42,	getb_43,	getb_44,	getb_45,	getb_46,	getb_47,
getb_50,	getb_51,	getb_52,	getb_53,	getb_54,	getb_55,	getb_56,	getb_57,
getb_60,	getb_61,	getb_62,	getb_63,	getb_64,	getb_65,	getb_66,	getb_67,
getb_70,	getb_71,	getb_72,	getb_73,	getb_74,	getb_75,	getb_76,	getb_77
};


