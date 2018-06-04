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

unsigned short cmd_status;			//for debug
unsigned short system_state;

unsigned short do_wait;

extern void show_mem(unsigned short,int);
extern void show_mem_oct(unsigned short,int);
extern void view_regs(void);
extern void show_rk11(void);
extern void rk11_flush(void);

typedef void (*decode_stage_t) (void);

#include "cpu_stage1_tables.h"
#include "cpu_stage2_tables.h"
#include "cpu_stage3_tables.h"

extern get_op_t getw_op[64];
extern getb_op_t getb_op[64];
extern put_op_t putw_op[64];
extern putb_op_t putb_op[64];
extern put_op_t putbm_op[64];
extern put_op_t bputw_op[64];
extern put_op_t bputb_op[64];
extern get_op_t getja_op[64];

#include "memfunc.h"

//##############################################################################
//# reserved operations will cause traps
//##############################################################################
void stage2_undf(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(8);			//010
	psw=iread_word(10);
}

void stage3_undef(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(8);			//010
	psw=iread_word(10);
}


//##############################################################################
//# stage 1 routines
//##############################################################################
void stage1_00(void)
{
	decode_stage2_00[(this_cmd >> 6) & 0x3F]();
}

//MOV
void stage1_01(void)
{
	unsigned short dst;
	dst = getw_op[(this_cmd >> 6) & 0x3f]();
	psw &= 0xFFF1;
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N
	putw_op[this_cmd & 0x3f](dst);
}

//CMP
void stage1_02(void)
{
	unsigned short src,dst,res;
	src = getw_op[(this_cmd >> 6) & 0x3f]();
	dst = getw_op[this_cmd & 0x3f]();
	res = src - dst;
	psw &= 0xFFF0;
	if (dst > src) psw |= 1;						//C
	if (((src ^ dst) & 0x8000) && (!((res ^ dst) & 0x8000))) psw |= 2;	//V
	if (res == 0) psw |= 4;							//Z
	if (res & 0x8000) psw |= 8;						//N
}

//BIT
void stage1_03(void)
{
	unsigned short src,dst;
	src = getw_op[(this_cmd >> 6) & 0x3f]();
	dst = getw_op[this_cmd & 0x3f]();
	dst &= src;

	psw &= 0xFFF1;			//V=0
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N
}

//BIC
void stage1_04(void)
{
	unsigned short src,dst;
	src = getw_op[(this_cmd >> 6) & 0x3f]();
	dst = getw_op[this_cmd & 0x3f]();
	dst &= ~src;
	psw &= 0xFFF1;			//V=0
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N
	bputw_op[this_cmd & 0x3f](dst);
}

//BIS
void stage1_05(void)
{
	unsigned short src,dst;
	src = getw_op[(this_cmd >> 6) & 0x3f]();
	dst = getw_op[this_cmd & 0x3f]();
	dst |= src;
	psw &= 0xFFF1;				//V=0
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N
	bputw_op[this_cmd & 0x3f](dst);
}

//ADD
void stage1_06(void)
{
	unsigned long src,dst;
	unsigned long resval32;
	src = (unsigned long) getw_op[(this_cmd >> 6) & 0x3f]();
	dst = (unsigned long) getw_op[this_cmd & 0x3f]();
	resval32 = dst + src;
	psw &= 0xFFF0;
	if (resval32 & 0x10000) psw |= 1;					//C
	if ((!((src ^ dst) & 0x8000)) && ((resval32 ^ dst) & 0x8000)) psw |= 2;	//V
	if ((resval32 & 0xffff) == 0) psw |= 4;					//Z
	if (resval32 & 0x8000) psw |= 8;					//N
	bputw_op[this_cmd & 0x3f](resval32 & 0xFFFF);
}

void stage1_07(void)
{
	decode_stage2_07[(this_cmd >> 6) & 0x3F]();
}

void stage1_10(void)
{
	decode_stage2_10[(this_cmd >> 6) & 0x3F]();
}

//MOVB
void stage1_11(void)
{
	unsigned char src;
	src = getb_op[(this_cmd >> 6) & 0x3f]();
	psw &= 0xFFF1;
	if (src == 0) psw |= 4;
	if (src & 0x80) psw |= 8;
	putbm_op[this_cmd & 0x3f](src);
}

//CMPB
void stage1_12(void)
{
	unsigned char src,dst,res;
	src = getb_op[(this_cmd >> 6) & 0x3f]();
	dst = getb_op[(this_cmd) & 0x3f]();
	res = src - dst;
	psw &= 0xFFF0;
	if (res & 0x80) psw |= 1;					//C
	if (((src ^ dst) & 0x80) && (!((res ^ dst) & 0x80))) psw |= 2;	//V
	if (res == 0) psw |= 4;						//Z
	if (res & 0x80) psw |= 8;					//N
}

//BITB
void stage1_13(void)
{
	unsigned char src,dst;
	src = getb_op[(this_cmd >> 6) & 0x3f]();
	dst = getb_op[(this_cmd) & 0x3f]();
	dst &= src;
	psw &= 0xFFF1;
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N
}

//BICB
void stage1_14(void)
{
	unsigned char src,dst;
	src = getb_op[(this_cmd >> 6) & 0x3f]();
	dst = getb_op[this_cmd & 0x3f]();
	dst &= ~src;
	psw &= 0xFFF1;				//V=0
	if (dst == 0) psw |= 4;			//Z
	if (dst & 0x80) psw |= 8;		//N
	bputb_op[this_cmd & 0x3f](dst);
}

//BISB
void stage1_15(void)
{
	unsigned char src,dst;
	src = getb_op[(this_cmd >> 6) & 0x3f]();
	dst = getb_op[this_cmd & 0x3f]();
	dst |= src;
	psw &= 0xFFF1;				//V=0
	if (dst == 0) psw |= 4;			//Z
	if (dst & 0x80) psw |= 8;		//N
	bputb_op[this_cmd & 0x3f](dst);
}

//SUB
void stage1_16(void)
{
	unsigned long src,dst;
	unsigned long resval32;

	src = getw_op[(this_cmd >> 6) & 0x3f]();
	dst = getw_op[this_cmd & 0x3f]();
	resval32 = dst - src;
	psw &= 0xFFF0;
	if (resval32 & 0x10000) psw |= 1;					//C
	if (((src ^ dst) & 0x8000) && (!((resval32 ^ src) & 0x8000))) psw |= 2;	//V
	if ((resval32 & 0xffff) == 0) psw |= 4;					//Z
	if (resval32 & 0x8000) psw |= 8;					//N
	bputw_op[this_cmd & 0x3f](resval32 & 0xFFFF);
}


void stage1_17(void)
{
	decode_stage2_17[(this_cmd >> 6) & 0x3F]();
}


//##############################################################################
//# stage 20 routines
//##############################################################################
//SWAB
void stage2_0003(void)
{
	unsigned short dst,temp;
	dst = getw_op[this_cmd & 0x3f]();
	temp=(dst & 0xff) << 8;
	dst >>= 8;
	dst |= temp;		
	psw &= 0xFFF0;				//C=V=0
	if ((dst & 0xff) == 0) psw |= 4;	//Z
	if (dst & 0x0080) psw |= 8;		//N
	bputw_op[this_cmd & 0x3f](dst);
}


//CLR
void stage2_0050(void)
{
	putw_op[(this_cmd) & 0x3f](0x0000);
	psw &= 0xFFF0;
	psw |= 4;			//Z	
}

//COM
void stage2_0051(void)
{
	unsigned short dst;
	dst = ~getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;			//V=0
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N
	psw |= 1;			//C=1	
	bputw_op[this_cmd & 0x3f](dst);
}

//INC
void stage2_0052(void)
{
	unsigned short dst;
	dst = getw_op[this_cmd & 0x3f]() + 1;
	psw &= 0xFFF1;
	if (dst == 0x8000) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
	bputw_op[this_cmd & 0x3f](dst);
}

//DEC
void stage2_0053(void)
{
	unsigned short dst;
	dst = getw_op[this_cmd & 0x3f]() - 1;
	psw &= 0xFFF1;
	if (dst == 0x7FFF) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
	bputw_op[this_cmd & 0x3f](dst);
}

//NEG
void stage2_0054(void)
{
	unsigned short dst;
	dst = ~getw_op[this_cmd & 0x3f]() + 1;
	psw &= 0xFFF0;			//
	if (dst != 0) psw |= 1;		//C
	if (dst == 0x8000) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
	bputw_op[this_cmd & 0x3f](dst);
}

//ADC
void stage2_0055(void)
{
	unsigned short dst;
	unsigned char ctemp=psw & 1;		//old carry

	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(ctemp == 1)
	{
		dst++;
		if(dst == 0x8000) psw |= 2;	//V
		if(dst == 0x0000) psw |= 1;	//C
	}
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
	bputw_op[this_cmd & 0x3f](dst);
}

//SBC
void stage2_0056(void)
{
	unsigned short dst;
	unsigned char ctemp=psw & 1;		//old carry

	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst == 0x8000) psw |= 2;	
	if(ctemp)
	{	
		if(dst == 0x0000) psw |= 0x0001;	
		dst--;
	}
	
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
	bputw_op[this_cmd & 0x3f](dst);
}

//TST
void stage2_0057(void)
{
	unsigned short dst;
	dst = getw_op[this_cmd & 0x3f]() ;
	psw &= 0xFFF0;			//C+V cleared
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x8000) psw |= 8;	//N	
}

//ROR
void stage2_0060(void)
{
	unsigned short dst;
	unsigned char ctemp=psw & 1;	//old carry
	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x0001) psw |= 3;	//C+V
	dst >>= 1;
	if(ctemp)
	{
		psw ^= 10;		//N,V
		dst |= 0x8000;
	}	
	if (dst == 0) psw |= 4;		//Z
	bputw_op[this_cmd & 0x3f](dst);
}

//ROL
void stage2_0061(void)
{
	unsigned short dst;
	unsigned char ctemp=psw & 1;		//old carry
	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x8000) psw |= 3;		//C+V
	dst <<= 1;
	if(ctemp) dst |= 0x0001;
	if(dst & 0x8000) psw ^= 10;		//N+V
	if (dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}


//ASR
void stage2_0062(void)
{
	unsigned short dst;
	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 1) psw |= 3;		//C+V
	dst >>= 1;
	if(dst & 0x4000)
	{
		psw ^= 10;		//N,V
		dst |= 0x8000;
	}
	if (dst == 0) psw |= 4;		//Z
	bputw_op[this_cmd & 0x3f](dst);
}

//ASL
void stage2_0063(void)
{
	unsigned short dst;
	dst = getw_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x8000) psw |= 3;		//C+V
	dst <<= 1;
	if(dst & 0x8000) psw ^= 10;		//set N, invert V
	if (dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}


//SXT
void stage2_0067(void)
{
	if(psw & 8)				//N?
	{
		putw_op[(this_cmd) & 0x3f](0xFFFF);
		psw &= 0xFFFB;			//Z=0
	}
	else
	{
		putw_op[(this_cmd) & 0x3f](0x0000);
		psw |= 4;			//Z=1
	}
}


//##############################################################################
//# stage 21 routines
//##############################################################################
//CLRB
void stage2_1050(void)
{
	putb_op[(this_cmd) & 0x3f](0x00);
	psw &= 0xFFF0;
	psw |= 4;			//Z	
}

//COMB
void stage2_1051(void)
{
	unsigned char dst;

	dst = ~getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;			//V=0
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N
	psw |= 1;			//C	
	bputb_op[this_cmd & 0x3f](dst);
}

//INCB
void stage2_1052(void)
{
	unsigned char dst;

	dst = getb_op[this_cmd & 0x3f]() + 1;
	psw &= 0xFFF1;			//
	if (dst == 0x80) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N	
	bputb_op[this_cmd & 0x3f](dst);
}

//DECB
void stage2_1053(void)
{
	unsigned char dst;

	dst = getb_op[this_cmd & 0x3f]() - 1;
	psw &= 0xFFF1;			//
	if (dst == 0x7F) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N	
	bputb_op[this_cmd & 0x3f](dst);
}

//NEGB
void stage2_1054(void)
{
	unsigned char dst;

	dst = ~getb_op[this_cmd & 0x3f]() + 1;
	psw &= 0xFFF0;			//
	if (dst != 0) psw |= 1;		//C
	if (dst == 0x80) psw |= 2;	//V
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N	
	bputb_op[this_cmd & 0x3f](dst);
}

//ADCB
void stage2_1055(void)
{
	unsigned char dst;
	unsigned char ctemp=psw & 1;	//old carry

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(ctemp)
	{
		dst++;
		if(dst == 0x80) psw |= 2;	
		if((dst & 0xff) == 0x00) psw |= 1;	
	
	}
	if (dst == 0) psw |= 4;		//Z
	if (dst & 0x80) psw |= 8;	//N	
	bputb_op[this_cmd & 0x3f](dst);
}

//SBCB
void stage2_1056(void)
{
	unsigned char dst;
	unsigned char ctemp=psw & 1;	//old carry

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;

	if((dst & 0xff) == 0x80) psw |= 2;	
	if(ctemp)
	{	
		if((dst & 0xff) == 0x00) psw |= 0x0001;	
		dst--;
	}

	if ((dst & 0xff) == 0) psw |= 4;	//Z
	if (dst & 0x80) psw |= 8;		//N	
	bputb_op[this_cmd & 0x3f](dst);
}


//TSTB
void stage2_1057(void)
{
	unsigned char dst;

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;				//C+V cleared
	if ((dst & 0xff) == 0) psw |= 4;	//Z
	if (dst & 0x80) psw |= 8;		//N	
}


//RORB
void stage2_1060(void)
{
	unsigned char dst;
	unsigned char ctemp=psw & 1;		//old carry

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x01) psw |= 3;	//C+V
	dst >>= 1;
	if(ctemp)
	{
		psw ^= 10;		//N,V
		dst |= 0x80;
	}	
	if ((dst & 0xFF) == 0) psw |= 4;	//Z
	bputb_op[this_cmd & 0x3f](dst);
}

//ROLB
void stage2_1061(void)
{
	unsigned char dst;
	unsigned char ctemp=psw & 1;		//old carry

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x80) psw |= 3;	//C
	dst <<= 1;
	if(ctemp) dst |= 0x01;
	if(dst & 0x80) psw ^= 10;	//N+V
	if (dst == 0) psw |= 4;		//Z
	bputb_op[this_cmd & 0x3f](dst);
}

//ASRB
void stage2_1062(void)
{
	unsigned char dst;

	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 1) psw |= 3;		//C+V
	dst >>= 1;
	if(dst & 0x40)
	{
		psw ^= 10;		//N,V
		dst |= 0x80;
	}
	if (dst == 0) psw |= 4;		//Z
	bputb_op[this_cmd & 0x3f](dst);
}

//ASLB
void stage2_1063(void)
{
	unsigned char dst;
	
	dst = getb_op[this_cmd & 0x3f]();
	psw &= 0xFFF0;
	if(dst & 0x80) psw |= 3;	//C+V
	dst <<= 1;
	if(dst & 0x80) psw ^= 10;	//N,V
	if (dst == 0) psw |= 4;		//Z
	bputb_op[this_cmd & 0x3f](dst);
}

//##############################################################################
//# EIS routines
//##############################################################################

//MUL
void stage2_0700(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register0.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register1.ureg=mres & 0xFFFF;
	register0.ureg=mres >> 16;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}

void stage2_0701(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register1.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register1.ureg=mres & 0xFFFF;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}

void stage2_0702(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register2.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register3.ureg=mres & 0xFFFF;
	register2.ureg=mres >> 16;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}

void stage2_0703(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register3.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register3.ureg=mres & 0xFFFF;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}


void stage2_0704(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register4.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register5.ureg=mres & 0xFFFF;
	register4.ureg=mres >> 16;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}

void stage2_0705(void)
{
	long mres,f1,f2;
	f1=getw_op[this_cmd & 0x3f]() & 0xFFFF; if(f1 & 0x8000) f1 |= 0xFFFF0000; 
	f2=register5.ureg & 0xFFFF; if(f2 & 0x8000) f2 |= 0xFFFF0000;
	mres = f1*f2;
	register5.ureg=mres & 0xFFFF;
	psw &= 0xFFF0;
	if(((mres & 0x8000) == 0) && ((mres & 0xFFFF0000) != 0x00000000)) psw |= 1;	//C
	if(((mres & 0x8000) != 0) && ((mres & 0xFFFF0000) != 0xFFFF0000)) psw |= 1;	//C
	if(mres & 0x80000000) psw |= 8;			//N
	if (mres == 0) psw |= 4;			//Z
}


void stage2_0706(void)
{
	stage2_undf();
}

void stage2_0707(void)
{
	stage2_undf();
}


//DIV
void stage2_0710(void)
{
	long d1,d2,dr;
	registers_t temp;

	psw &= 0xFFF0;	
	temp.ureg = getw_op[this_cmd & 0x3f]();		//divisor

	d2 = (long) temp.ireg;
	if(d2 != 0)
	{	
		d1 = register1.ureg | (register0.ureg << 16);
		dr = d1 / d2;

//		printf("DIV %ld / %ld = %ld\n",d1,d2,dr);
		if((dr < -32767) || (dr > 32767)) 
		{
			psw |= 2;				//set V				
			if(dr < 0) psw |= 8;
		}
		else
		{
			register0.ureg = dr & 0xffff;
			register1.ureg = d1 % d2;
			if(register0.ureg & 0x8000) psw |= 8;		//N
			if (register0.ureg == 0) psw |= 4;		//Z
		}	
	}
	else
	{
		psw |= 7;			//set C+V+Z (divide by zero)
	
	}	
}

void stage2_0712(void)
{
	long d1,d2,dr;
	registers_t temp;

	psw &= 0xFFF0;	
	temp.ureg = getw_op[this_cmd & 0x3f]();		//divisor
	d2 = (long) temp.ireg;
	if(d2 != 0)
	{	
		d1 = register3.ureg | (register2.ureg << 16);
		dr = d1 / d2;
		if((dr < -32767) || (dr > 32767)) 
		{
			psw |= 2;				//set V				
			if(dr < 0) psw |= 8;
		}
		else
		{
			register2.ureg = dr & 0xffff;
			register3.ureg = d1 % d2;
			if(register2.ureg & 0x8000) psw |= 8;		//N
			if (register2.ureg == 0) psw |= 4;			//Z
		}	
	}
	else
	{
		psw |= 7;			//set C+V+Z
	
	}	
}

void stage2_0714(void)
{
	long d1,d2,dr;
	registers_t temp;

	psw &= 0xFFF0;	
	temp.ureg = getw_op[this_cmd & 0x3f]();		//divisor
	d2 = (long) temp.ireg;
	if(d2 != 0)
	{	
		d1 = register5.ureg | (register4.ureg << 16);
		dr = d1 / d2;
		if((dr < -32767) || (dr > 32767)) 
		{
			psw |= 2;				//set V				
			if(dr < 0) psw |= 8;
		}
		else
		{
			register4.ureg = dr & 0xffff;
			register5.ureg = d1 % d2;
			if(register4.ureg & 0x8000) psw |= 8;		//N
			if (register4.ureg == 0) psw |= 4;			//Z
		}	
	}
	else
	{
		psw |= 7;			//set C+V+Z
	
	}	
}

void stage2_0716(void)
{
	stage2_undf();
}

//ASH
void stage2_0720(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getw_op[this_cmd & 0x3f]() & 0x3f;
	resval32 = register0.ureg & 0xFFFF;
	src &= 0x3F;
	//left shift
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register0.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register0.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if(dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register0.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0721(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = register1.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register1.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register1.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register1.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0722(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = register2.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register2.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register2.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register2.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0723(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = register3.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register3.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register3.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register3.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0724(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = register4.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register4.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register4.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register4.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0725(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = register5.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((register5.ureg ^ dst) & 0x8000) psw |= 2;	//V
		register5.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		register5.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0726(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = sp.ureg;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((sp.ureg ^ dst) & 0x8000) psw |= 2;	//V
		sp.ureg = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		sp.ureg = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

void stage2_0727(void)
{
	unsigned short src,dst;
	unsigned long resval32;

	src = getb_op[this_cmd & 0x3f]() & 0x3F;
	resval32 = pc;
	src &= 0x3F;
	if(!(src & 0x20))
	{
		resval32 <<= src;
		dst = resval32 & 0xFFFF;
		psw &= 0xFFF0;
		if((pc ^ dst) & 0x8000) psw |= 2;		//V
		pc = dst;
		if(resval32 & 0x00010000) psw |= 1;		//C
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z
	}
	else
	{
		if(resval32 & 0x8000) resval32 |= 0xFFFF0000;
		resval32 >>= (63 - src);
		psw &= 0xFFF0;
		if(resval32 & 0x00000001) psw |= 1;		//C
		resval32 >>= 1;
		dst = resval32 & 0xFFFF;
		pc = dst;
		if(dst & 0x8000) psw |= 8;		//N
		if (dst == 0) psw |= 4;			//Z	
	}
}

//ASHC
void stage2_0730(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register1.ureg | (register0.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register1.ureg = resval32 & 0xFFFF;
		register0.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register1.ureg = resval32 & 0xFFFF;
		register0.ureg = resval32 >> 16;
	}
}

void stage2_0731(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register1.ureg | (register1.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register1.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register1.ureg = resval32 >> 16;
	}
}

void stage2_0732(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register3.ureg | (register2.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register3.ureg = resval32 & 0xFFFF;
		register2.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register3.ureg = resval32 & 0xFFFF;
		register2.ureg = resval32 >> 16;
	}
}

void stage2_0733(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register3.ureg | (register3.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register3.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register3.ureg = resval32 >> 16;
	}
}

void stage2_0734(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register5.ureg | (register4.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register5.ureg = resval32 & 0xFFFF;
		register4.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register5.ureg = resval32 & 0xFFFF;
		register4.ureg = resval32 >> 16;
	}
}

void stage2_0735(void)
{
	unsigned long temp,ctemp,resval32;
	unsigned short shifts=getb_op[this_cmd & 0x3f]() & 0x3F;
	int i;

	resval32 = register5.ureg | (register5.ureg << 16);
	temp = resval32;	
	if(shifts == 0)		//no shift
	{
		psw &= 0xFFF1;					//preserve carry
		if(resval32 & 0x80000000) psw |= 8;		//N
		if (resval32 == 0) psw |= 4;			//Z	
	}
	else if(shifts < 0x20)	//left shift
	{
		psw &= 0xFFF0;
		resval32 <<= (shifts - 1);
		if(resval32 & 0x80000000) psw |= 1;		//C
		resval32 <<= 1;
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register5.ureg = resval32 >> 16;
	}
	else				//right shift
	{
		for(i=shifts;i<64;i++)
		{
			ctemp = resval32;
			resval32 >>= 1;
			if(resval32 & 0x40000000) resval32 |= 0x80000000;
		}
		psw &= 0xFFF0;
		if(ctemp & 0x00000001) psw |= 1;		//C
		if((temp ^ resval32) & 0x80000000) psw |= 2;	//V
		if(resval32 & 0x80000000) psw |= 8;		//N
		if(resval32 == 0) psw |= 4;			//Z
		register5.ureg = resval32 >> 16;
	}
}


//XOR
void stage2_0740(void)
{
	unsigned short dst;
	
	dst = getw_op[this_cmd & 0x3f]() ^ register0.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0741(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ register1.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0742(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ register2.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0743(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ register3.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0744(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ register4.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0745(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ register5.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0746(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ sp.ureg;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

void stage2_0747(void)
{
	unsigned short dst;

	dst = getw_op[this_cmd & 0x3f]() ^ pc;
	psw &= 0xFFF1;
	if(dst & 0x8000) psw |= 8;		//N
	if(dst == 0) psw |= 4;			//Z
	bputw_op[this_cmd & 0x3f](dst);
}

//##############################################################################
//# Branches
//##############################################################################
//BR
void stage2_0004(void)	//+0005
{
	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0006(void)	//+0007
{
	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BNE
void stage2_0010(void)	//+0011
{
	if((psw & 4) == 0)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0012(void)	//+0013
{
	if((psw & 4) == 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BEQ
void stage2_0014(void)	//+0015
{
	if((psw & 4) == 4)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0016(void)	//+0017
{
	if((psw & 4) == 4)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BPL
void stage2_1000(void)	//+1001
{
	if((psw & 8) == 0)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1002(void)	//+1003
{
	if((psw & 8) == 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BMI
void stage2_1004(void)	//+1005
{
	if((psw & 8) == 8)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1006(void)	//+1007
{
	if((psw & 8) == 8)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BVC
void stage2_1020(void)	//+1021
{
	if((psw & 2) == 0) 	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1022(void)	//+1023
{
	if((psw & 2) == 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BVS
void stage2_1024(void)	//+1025
{
	if((psw & 2) == 2) 	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1026(void)	//+1027
{
	if((psw & 2) == 2)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BCC
void stage2_1030(void)	//+1031
{
	if((psw & 1) == 0) 	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1032(void)	//+1033
{
	if((psw & 1) == 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BCS
void stage2_1034(void)	//+1035
{
	if((psw & 1) == 1)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1036(void)	//+1037
{
	if((psw & 1) == 1)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BGE
void stage2_0020(void)	//+0021
{
	if(((psw & 10) == 10) || ((psw & 10) == 0))	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0022(void)	//+0023
{
	if(((psw & 10) == 10) || ((psw & 10) == 0))	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BLT
void stage2_0024(void)	//+0025
{
	if(((psw & 10) == 8) || ((psw & 10) == 2))	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0026(void)	//+0027
{
	if(((psw & 10) == 8) || ((psw & 10) == 2))	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BGT
void stage2_0030(void)	//+0031
{
	if(((psw & 14) == 10) || ((psw & 14) == 0))	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0032(void)	//+0033
{
	if(((psw & 14) == 10) || ((psw & 14) == 0))	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BLE
void stage2_0034(void)	//+0035
{
	if(((psw & 10) == 8) || ((psw & 10) == 2) || ((psw & 4) == 4))	pc += (this_cmd & 0x7f) << 1;
}

void stage2_0036(void)	//+0037
{
	if(((psw & 10) == 8) || ((psw & 10) == 2) || ((psw & 4) == 4))	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BHI
void stage2_1010(void)	//+1011
{
	if((psw & 5) == 0)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1012(void)	//+1013
{
	if((psw & 5) == 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//BLOS
void stage2_1014(void)	//+1015
{
	if((psw & 5) != 0)	pc += (this_cmd & 0x7f) << 1;
}

void stage2_1016(void)	//+1017
{
	if((psw & 5) != 0)	pc += (-128 + (this_cmd & 0x7f)) << 1;
}

//##############################################################################
//# Jump, JSR...
//##############################################################################
//JMP
void stage2_0001(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

//JSR
void stage2_0040(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();
	push_data(register0.ureg);
	register0.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0041(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	 
	push_data(register1.ureg);
	register1.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0042(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(register2.ureg);
	register2.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0043(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(register3.ureg);
	register3.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0044(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(register4.ureg);
	register4.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0045(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(register5.ureg);
	register5.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

void stage2_0046(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(sp.ureg);
	sp.ureg=pc;
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}
void stage2_0047(void)
{
	unsigned short tpc=getja_op[this_cmd & 0x3f]();	
	push_data(pc);
#if USR_RESTRICT == 1
	if((pc > 0x5FFE) && (tpc < 0x6000))
	{
		stage2_undf();
		return;
	}
#endif	
	pc = tpc;
}

//##############################################################################
//# RTS
//##############################################################################
void stage2_0002(void)
{
	unsigned short temp_psw;

	//stage 3 (rts)
	if((this_cmd & 0x38) == 0)
	{
		decode_stage3_rts[this_cmd & 0x07]();
	}	

	//clear flags
	else if ((this_cmd & 0x30) == 0x20)
	{
		temp_psw = ~(this_cmd & 0x0F);
		psw &= temp_psw;
	}
	
	//set flags
	else if ((this_cmd & 0x30) == 0x30)
	{
		temp_psw = this_cmd & 0x0F;
		psw |= temp_psw;
	}

	//SPL
	else if ((this_cmd & 0x98) == 0x98)
	{
		temp_psw = (this_cmd & 0x07) << 5;
		psw &= 0xFF1F;
		psw |= temp_psw;
	}
	
	else
	{
		stage2_undf();
	}

}

void stage3_rts00(void)
{
	pc=register0.ureg;
	register0.ureg=pop_data();
}

void stage3_rts01(void)
{
	pc=register1.ureg;
	register1.ureg=pop_data();
}

void stage3_rts02(void)
{
	pc=register2.ureg;
	register2.ureg=pop_data();
}

void stage3_rts03(void)
{
	pc=register3.ureg;
	register3.ureg=pop_data();
}

void stage3_rts04(void)
{
	pc=register4.ureg;
	
	register4.ureg=pop_data();
}

void stage3_rts05(void)
{
	pc=register5.ureg;
	register5.ureg=pop_data();
}

void stage3_rts06(void)
{
	pc=sp.ureg;
	sp.ureg=pop_data();
}

void stage3_rts07(void)
{
	pc=pop_data();
}

//MARK
void stage2_0064(void)
{
//	printf("MARK S1=%04X\n",sp.ureg);
//	printf("MARK %d\n",this_cmd & 0x3F);
	sp.ureg+=((this_cmd & 0x3F) << 1);
//	printf("MARK S2=%04X\n",sp.ureg);
	pc=register5.ureg;
	register5.ureg=pop_data();
//	printf("MARK S3=%04X\n",sp.ureg);
}

//##############################################################################
//# SOB
//##############################################################################

void stage2_0770(void)
{
	register0.ureg--;
	if (register0.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

void stage2_0771(void)
{
	register1.ureg--;
	if (register1.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

void stage2_0772(void)
{
	register2.ureg--;
	if (register2.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

void stage2_0773(void)
{
	register3.ureg--;
	if (register3.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

void stage2_0774(void)
{
	register4.ureg--;
	if (register4.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

void stage2_0775(void)
{
	register5.ureg--;
	if (register5.ureg != 0) pc -=((this_cmd & 0x3F) << 1);
}

//##############################################################################
//# TRAPS + SYSTEM CTL
//##############################################################################
void stage2_0000(void)
{
//	printf("STAGE3 (%6o)\n",this_cmd);fflush(stdout);
	decode_stage3_ctrl[this_cmd & 0x3F]();
}

//EMT
void stage2_1040(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(24);			//030
	psw=iread_word(26);
}

//TRAP
void stage2_1044(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(28);			//034
	psw=iread_word(30);
}

//BPT
void stage3_ctrl03(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(12);			//014
	psw=iread_word(14);
}

//IOT
void stage3_ctrl04(void)
{
	push_data(psw);
	push_data(pc);
	pc=iread_word(16);			//020
	psw=iread_word(18);
}

//RTI
void stage3_ctrl02(void)
{
	pc=pop_data();
	psw=pop_data();
}

//RTT
void stage3_ctrl06(void)
{
	pc=pop_data();
	psw=pop_data();
}

//HALT
void stage3_ctrl00(void)
{
	if(system_state < 2)
	{
#if MCU < 10
		printf("\r\nUSR_HALT AT %04x\r\n",pc-2);
#else
		KPRINTF("\r\nUSR_HALT AT %04x\r\n",pc-2);
#endif
		rk11_flush();		//flush write cache
		system_state = 2;	// 2 clear run
	}
	pc-=2;
#if MCU < 10
	exit(0);
#endif
}

//WAIT (for interrupt)
void stage3_ctrl01(void)
{
	if(do_wait==0) do_wait=1;
	if(do_wait==1) pc-=2;
	if(do_wait==2) do_wait=0;
#if HAVE_SLEEP
	unilib_sleep();
#endif
}


//RESET
void stage3_ctrl05(void)
{
	//reset peripherials is not supported (dummy function)
}

//##############################################################################
//# PSW FUNCTIONS
//##############################################################################
//MTPS
void stage2_1064(void)
{
	psw = getw_op[this_cmd & 0x3f]();
}

//MFPS
void stage2_1067(void)
{
	putw_op[this_cmd & 0x3f](psw);
}

//##############################################################################
//# cpu initialize
//##############################################################################
void cpu_init(void)
{
	register0.ureg=0;
	register1.ureg=0;
	register2.ureg=0;
	register3.ureg=0;
	register4.ureg=0;
	register5.ureg=0;
	sp.ureg=0xDFFE;
	pc=0;
	psw=0xE4;
	cycle_type=0;
	system_state=1;
	rxint_queue=0;
	txint_queue=0;
}

