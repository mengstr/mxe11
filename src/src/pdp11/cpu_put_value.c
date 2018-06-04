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
//# direct register sources
//##############################################################################
void putw_00(unsigned short value)
{
	register0.ureg = value;
}

void putb_00(unsigned char value)
{
	register0.bytes[LOBYTE] = value;
}

void putbm_00(unsigned char value)
{
	if(value & 0x80) register0.ureg = value | 0xFF00; else register0.ureg = value & 0x00FF;
}


void putw_01(unsigned short value)
{
	register1.ureg = value;
}

void putb_01(unsigned char value)
{
	register1.bytes[LOBYTE] = value;
}

void putbm_01(unsigned char value)
{
	if(value & 0x80) register1.ureg = value | 0xFF00; else register1.ureg = value & 0x00FF;
}


void putw_02(unsigned short value)
{
	register2.ureg = value;
}

void putb_02(unsigned char value)
{
	register2.bytes[LOBYTE] = value;
}

void putbm_02(unsigned char value)
{
	if(value & 0x80) register2.ureg = value | 0xFF00; else register2.ureg = value & 0x00FF;
}


void putw_03(unsigned short value)
{
	register3.ureg = value;
}

void putb_03(unsigned char value)
{
	register3.bytes[LOBYTE] = value;
}

void putbm_03(unsigned char value)
{
	if(value & 0x80) register3.ureg = value | 0xFF00; else register3.ureg = value & 0x00FF;
}


void putw_04(unsigned short value)
{
	register4.ureg = value;
}

void putb_04(unsigned char value)
{
	register4.bytes[LOBYTE] = value;
}

void putbm_04(unsigned char value)
{
	if(value & 0x80) register4.ureg = value | 0xFF00; else register4.ureg = value & 0x00FF;
}


void putw_05(unsigned short value)
{
	register5.ureg = value;
}

void putb_05(unsigned char value)
{
	register5.bytes[LOBYTE] = value;
}

void putbm_05(unsigned char value)
{
	if(value & 0x80) register5.ureg = value | 0xFF00; else register5.ureg = value & 0x00FF;
}


void putw_06(unsigned short value)
{
	sp.ureg = value;
}

void putb_06(unsigned char value)
{
	sp.bytes[LOBYTE] = value;
}

void putbm_06(unsigned char value)
{
	if(value & 0x80) sp.ureg = value | 0xFF00; else sp.ureg = value & 0x00FF;
}


void putw_07(unsigned short value)
{
	pc = value;
}

void putb_07(unsigned char value)
{
	pc = (pc & 0xFF00) | value;
}

void putbm_07(unsigned char value)
{
	if(value & 0x80) pc = value | 0xFF00; else pc = value & 0x00FF;
}

//##############################################################################
//# indirect register sources
//##############################################################################
void putw_10(unsigned short value)
{
	iwrite_word(register0.ureg,value);	
}

void putb_10(unsigned char value)
{
	iwrite_byte(register0.ureg,value);	
}


void putw_11(unsigned short value)
{
	iwrite_word(register1.ureg,value);	
}

void putb_11(unsigned char value)
{
	iwrite_byte(register1.ureg,value);	
}


void putw_12(unsigned short value)
{
	iwrite_word(register2.ureg,value);	
}

void putb_12(unsigned char value)
{
	iwrite_byte(register2.ureg,value);	
}


void putw_13(unsigned short value)
{
	iwrite_word(register3.ureg,value);	
}

void putb_13(unsigned char value)
{
	iwrite_byte(register3.ureg,value);	
}


void putw_14(unsigned short value)
{
	iwrite_word(register4.ureg,value);	
}

void putb_14(unsigned char value)
{
	iwrite_byte(register4.ureg,value);	
}


void putw_15(unsigned short value)
{
	iwrite_word(register5.ureg,value);	
}

void putb_15(unsigned char value)
{
	iwrite_byte(register5.ureg,value);	
}


void putw_16(unsigned short value)
{
	iwrite_word(sp.ureg,value);	
}

void putb_16(unsigned char value)
{
	iwrite_byte(sp.ureg,value);	
}


void putw_17(unsigned short value)
{
	iwrite_word(pc,value);	
}

void putb_17(unsigned char value)
{
	iwrite_byte(pc,value);	
}

//##############################################################################
//# register post increment
//##############################################################################
void putw_20(unsigned short value)
{
	iwrite_word(register0.ureg,value);	
	register0.ureg+=2;	
}

void putb_20(unsigned char value)
{
	iwrite_byte(register0.ureg,value);	
	register0.ureg+=1;	
}


void putw_21(unsigned short value)
{
	iwrite_word(register1.ureg,value);	
	register1.ureg+=2;	
}

void putb_21(unsigned char value)
{
	iwrite_byte(register1.ureg,value);	
	register1.ureg+=1;	
}


void putw_22(unsigned short value)
{
	iwrite_word(register2.ureg,value);	
	register2.ureg+=2;	
}

void putb_22(unsigned char value)
{
	iwrite_byte(register2.ureg,value);	
	register2.ureg+=1;	
}


void putw_23(unsigned short value)
{
	iwrite_word(register3.ureg,value);	
	register3.ureg+=2;	
}

void putb_23(unsigned char value)
{
	iwrite_byte(register3.ureg,value);	
	register3.ureg+=1;	
}


void putw_24(unsigned short value)
{
	iwrite_word(register4.ureg,value);	
	register4.ureg+=2;	
}

void putb_24(unsigned char value)
{
	iwrite_byte(register4.ureg,value);	
	register4.ureg+=1;	
}


void putw_25(unsigned short value)
{
	iwrite_word(register5.ureg,value);	
	register5.ureg+=2;	
}

void putb_25(unsigned char value)
{
	iwrite_byte(register5.ureg,value);	
	register5.ureg+=1;	
}


void putw_26(unsigned short value)
{
	iwrite_word(sp.ureg,value);	
	sp.ureg+=2;	
}

void putb_26(unsigned char value)
{
	iwrite_byte(sp.ureg,value);	
	sp.ureg+=2;	
}


void putw_27(unsigned short value)
{
	iwrite_word(pc,value);	
	pc+=2;
}

void putb_27(unsigned char value)
{
	iwrite_byte(pc,value);	
	pc+=2;
}


//##############################################################################
//# indirect register post increment
//##############################################################################
void putw_30(unsigned short value)
{
	iwrite_word(iread_word(register0.ureg),value);
	register0.ureg+=2;	
}

void putb_30(unsigned char value)
{
	iwrite_byte(iread_word(register0.ureg),value);
	register0.ureg+=2;	
}

void putw_31(unsigned short value)
{
	iwrite_word(iread_word(register1.ureg),value);
	register1.ureg+=2;	
}

void putb_31(unsigned char value)
{
	iwrite_byte(iread_word(register1.ureg),value);
	register1.ureg+=2;	
}


void putw_32(unsigned short value)
{
	iwrite_word(iread_word(register2.ureg),value);
	register2.ureg+=2;	
}

void putb_32(unsigned char value)
{
	iwrite_byte(iread_word(register2.ureg),value);
	register2.ureg+=2;	
}


void putw_33(unsigned short value)
{
	iwrite_word(iread_word(register3.ureg),value);
	register3.ureg+=2;	
}

void putb_33(unsigned char value)
{
	iwrite_byte(iread_word(register3.ureg),value);
	register3.ureg+=2;	
}


void putw_34(unsigned short value)
{
	iwrite_word(iread_word(register4.ureg),value);
	register4.ureg+=2;	
}

void putb_34(unsigned char value)
{
	iwrite_byte(iread_word(register4.ureg),value);
	register4.ureg+=2;	
}


void putw_35(unsigned short value)
{
	iwrite_word(iread_word(register5.ureg),value);
	register5.ureg+=2;	
}

void putb_35(unsigned char value)
{
	iwrite_byte(iread_word(register5.ureg),value);
	register5.ureg+=2;	
}


void putw_36(unsigned short value)
{
	iwrite_word(iread_word(sp.ureg),value);
	sp.ureg+=2;	
}

void putb_36(unsigned char value)
{
	iwrite_byte(iread_word(sp.ureg),value);
	sp.ureg+=2;	
}


void putw_37(unsigned short value)
{
	iwrite_word(iread_word(pc),value);
	pc+=2;	
}

void putb_37(unsigned char value)
{
	iwrite_byte(iread_word(pc),value);
	pc+=2;
}


//##############################################################################
//# register pre decrement
//##############################################################################
void putw_40(unsigned short value)
{
	register0.ureg-=2;	
	iwrite_word(register0.ureg,value);	
}

void putb_40(unsigned char value)
{
	register0.ureg-=1;	
	iwrite_byte(register0.ureg,value);	
}


void putw_41(unsigned short value)
{
	register1.ureg-=2;	
	iwrite_word(register1.ureg,value);	
}

void putb_41(unsigned char value)
{
	register1.ureg-=1;	
	iwrite_byte(register1.ureg,value);	
}


void putw_42(unsigned short value)
{
	register2.ureg-=2;	
	iwrite_word(register2.ureg,value);	
}

void putb_42(unsigned char value)
{
	register2.ureg-=1;	
	iwrite_byte(register2.ureg,value);	
}

void putw_43(unsigned short value)
{
	register3.ureg-=2;	
	iwrite_word(register3.ureg,value);	
}

void putb_43(unsigned char value)
{
	register3.ureg-=1;	
	iwrite_byte(register3.ureg,value);	
}


void putw_44(unsigned short value)
{
	register4.ureg-=2;	
	iwrite_word(register4.ureg,value);	
}

void putb_44(unsigned char value)
{
	register4.ureg-=1;	
	iwrite_byte(register4.ureg,value);	
}


void putw_45(unsigned short value)
{
	register5.ureg-=2;	
	iwrite_word(register5.ureg,value);	
}

void putb_45(unsigned char value)
{
	register5.ureg-=1;	
	iwrite_byte(register5.ureg,value);	
}

void putw_46(unsigned short value)
{
	sp.ureg-=2;	
	iwrite_word(sp.ureg,value);	
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
}

void putb_46(unsigned char value)
{
	sp.ureg-=2;	
	iwrite_byte(sp.ureg,value);	
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
}

void putw_47(unsigned short value)
{	
	pc-=2;	
	iwrite_word(pc,value);	
}

void putb_47(unsigned char value)
{
	pc-=2;	
	iwrite_byte(pc,value);	
}


//##############################################################################
//# indirect register post increment
//##############################################################################
void putw_50(unsigned short value)
{
	register0.ureg-=2;	
	iwrite_word(iread_word(register0.ureg),value);
}

void putb_50(unsigned char value)
{
	register0.ureg-=2;	
	iwrite_byte(iread_word(register0.ureg),value);
}

void putw_51(unsigned short value)
{
	register1.ureg-=2;	
	iwrite_word(iread_word(register1.ureg),value);
}

void putb_51(unsigned char value)
{
	register1.ureg-=2;	
	iwrite_byte(iread_word(register1.ureg),value);
}

void putw_52(unsigned short value)
{
	register2.ureg-=2;	
	iwrite_word(iread_word(register2.ureg),value);
}

void putb_52(unsigned char value)
{
	register2.ureg-=2;	
	iwrite_byte(iread_word(register2.ureg),value);
}

void putw_53(unsigned short value)
{
	register3.ureg-=2;	
	iwrite_word(iread_word(register3.ureg),value);
}

void putb_53(unsigned char value)
{
	register3.ureg-=2;	
	iwrite_byte(iread_word(register3.ureg),value);
}

void putw_54(unsigned short value)
{
	register4.ureg-=2;	
	iwrite_word(iread_word(register4.ureg),value);
}

void putb_54(unsigned char value)
{
	register4.ureg-=2;	
	iwrite_byte(iread_word(register4.ureg),value);
}

void putw_55(unsigned short value)
{
	register5.ureg-=2;	
	iwrite_word(iread_word(register5.ureg),value);
}

void putb_55(unsigned char value)
{
	register5.ureg-=2;	
	iwrite_byte(iread_word(register5.ureg),value);
}

void putw_56(unsigned short value)
{
	sp.ureg-=2;	
	iwrite_word(iread_word(sp.ureg),value);
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
}

void putb_56(unsigned char value)
{
	sp.ureg-=2;	
	iwrite_byte(iread_word(sp.ureg),value);
#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		push_data(psw);
		push_data(pc);
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
}

void putw_57(unsigned short value)
{	
	pc-=2;	
	iwrite_word(iread_word(pc),value);
}

void putb_57(unsigned char value)
{
	pc-=2;	
	iwrite_byte(iread_word(pc),value);
}

//##############################################################################
//# indexed
//##############################################################################
void putw_60(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register0.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_60(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register0.ureg+x;
	iwrite_byte(last_addr,value);
}

void putw_61(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register1.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_61(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register1.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_62(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register2.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_62(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register2.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_63(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register3.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_63(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register3.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_64(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register4.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_64(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register4.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_65(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=register5.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_65(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=register5.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_66(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=sp.ureg+x;
	iwrite_word(last_addr,value);
}

void putb_66(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=sp.ureg+x;
	iwrite_byte(last_addr,value);	
}

void putw_67(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=pc+x;
	iwrite_word(last_addr,value);
}

void putb_67(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=pc+x;
	iwrite_byte(last_addr,value);	
}


//##############################################################################
//# index deferred
//##############################################################################
void putw_70(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register0.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_70(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register0.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_71(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register1.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_71(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register1.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_72(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register2.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_72(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register2.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_73(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register3.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_73(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register3.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_74(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register4.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_74(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register4.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_75(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(register5.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_75(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(register5.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_76(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(sp.ureg+x);
	iwrite_word(last_addr,value);
}

void putb_76(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(sp.ureg+x);
	iwrite_byte(last_addr,value);	
}

void putw_77(unsigned short value)
{	
	unsigned short x = ifetch_next();
	last_addr=iread_word(pc+x);
	iwrite_word(last_addr,value);
}

void putb_77(unsigned char value)
{
	unsigned short x = ifetch_next();
	last_addr=iread_word(pc+x);
	iwrite_byte(last_addr,value);	
}

//##############################################################################
//# tables
//##############################################################################
put_op_t	putw_op[64]=
{
putw_00,	putw_01,	putw_02,	putw_03,	putw_04,	putw_05,	putw_06,	putw_07,
putw_10,	putw_11,	putw_12,	putw_13,	putw_14,	putw_15,	putw_16,	putw_17,
putw_20,	putw_21,	putw_22,	putw_23,	putw_24,	putw_25,	putw_26,	putw_27,
putw_30,	putw_31,	putw_32,	putw_33,	putw_34,	putw_35,	putw_36,	putw_37,
putw_40,	putw_41,	putw_42,	putw_43,	putw_44,	putw_45,	putw_46,	putw_47,
putw_50,	putw_51,	putw_52,	putw_53,	putw_54,	putw_55,	putw_56,	putw_57,
putw_60,	putw_61,	putw_62,	putw_63,	putw_64,	putw_65,	putw_66,	putw_67,
putw_70,	putw_71,	putw_72,	putw_73,	putw_74,	putw_75,	putw_76,	putw_77
};

putb_op_t putb_op[64]=
{
putb_00,	putb_01,	putb_02,	putb_03,	putb_04,	putb_05,	putb_06,	putb_07,
putb_10,	putb_11,	putb_12,	putb_13,	putb_14,	putb_15,	putb_16,	putb_17,
putb_20,	putb_21,	putb_22,	putb_23,	putb_24,	putb_25,	putb_26,	putb_27,
putb_30,	putb_31,	putb_32,	putb_33,	putb_34,	putb_35,	putb_36,	putb_37,
putb_40,	putb_41,	putb_42,	putb_43,	putb_44,	putb_45,	putb_46,	putb_47,
putb_50,	putb_51,	putb_52,	putb_53,	putb_54,	putb_55,	putb_56,	putb_57,
putb_60,	putb_61,	putb_62,	putb_63,	putb_64,	putb_65,	putb_66,	putb_67,
putb_70,	putb_71,	putb_72,	putb_73,	putb_74,	putb_75,	putb_76,	putb_77
};

putb_op_t putbm_op[64]=
{
putbm_00,	putbm_01,	putbm_02,	putbm_03,	putbm_04,	putbm_05,	putbm_06,	putbm_07,
putb_10,	putb_11,	putb_12,	putb_13,	putb_14,	putb_15,	putb_16,	putb_17,
putb_20,	putb_21,	putb_22,	putb_23,	putb_24,	putb_25,	putb_26,	putb_27,
putb_30,	putb_31,	putb_32,	putb_33,	putb_34,	putb_35,	putb_36,	putb_37,
putb_40,	putb_41,	putb_42,	putb_43,	putb_44,	putb_45,	putb_46,	putb_47,
putb_50,	putb_51,	putb_52,	putb_53,	putb_54,	putb_55,	putb_56,	putb_57,
putb_60,	putb_61,	putb_62,	putb_63,	putb_64,	putb_65,	putb_66,	putb_67,
putb_70,	putb_71,	putb_72,	putb_73,	putb_74,	putb_75,	putb_76,	putb_77
};
