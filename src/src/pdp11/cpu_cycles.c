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

typedef void (*decode_stage_t) (void);

#include "cpu_stage1_etables.h"

extern unsigned short do_wait;
extern void rk11_task(void);


//##############################################################################
//# only cpu
//##############################################################################
void do_n0000(void)
{	
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

void do_r0000(void)
{
	rk11_task();
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

//##############################################################################
//# cpu and console TX
//##############################################################################
void do_n0004(void)
{
	if(psw < 0x80)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x34);
		psw=iread_word(0x36)+(txint_queue & 0x0F)-1;
		//clear this interrupt request
		txint_queue >>= 8;
		if(txint_queue == 0) cycle_type &= ~(1 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

void do_r0004(void)
{
	rk11_task();
	if(psw < 0x80)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x34);
		psw=iread_word(0x36)+(txint_queue & 0x0F)-1;
		//clear this interrupt request
		txint_queue >>= 8;
		if(txint_queue == 0) cycle_type &= ~(1 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

//##############################################################################
//# cpu and console RX
//##############################################################################
void do_n0040(void)
{
	if(psw < 0x80)
	{
//		printf("RXINT %08lX\n",rxint_queue);
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x30);
		psw=iread_word(0x32)+(rxint_queue & 0x0F)-1;
//		if((rxint_queue & 3) == 2) KPRINTF("K0 ");
		//clear this interrupt request
		rxint_queue >>= 8;
		if(rxint_queue == 0) cycle_type &= ~(2 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

void do_r0040(void)
{
	rk11_task();
	if(psw < 0x80)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x30);
		psw=iread_word(0x32)+(rxint_queue & 0x0F)-1;
		//clear this interrupt request
		rxint_queue >>= 8;
		if(rxint_queue == 0) cycle_type &= ~(2 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}


//##############################################################################
//# RK11
//##############################################################################
void do_n0500(void)
{
	if(psw < 0xA0)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x90);
		psw=iread_word(0x92);
		//clear this interrupt request
		cycle_type &= ~(4 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

void do_r0500(void)
{
	rk11_task();
	if(psw < 0xA0)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x90);
		psw=iread_word(0x92);
		//clear this interrupt request
		cycle_type &= ~(4 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}


//##############################################################################
//# KL11
//##############################################################################
void do_n6000(void)
{
//	printf("KLI %d (PSW = %04X -> %d)\n",do_wait,psw,cpu_priority);
	if(psw < 0xE0)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x40);
		psw=iread_word(0x42);
		//clear this interrupt request
		cycle_type &= ~(8 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}

void do_r6000(void)
{
	rk11_task();
	if(psw < 0xe0)
	{
		//prepare int execution
		push_data(psw);
		push_data(pc);
		pc=iread_word(0x40);
		psw=iread_word(0x42);
		//clear this interrupt request
		cycle_type &= ~(8 << SHIFT_CYCLE);
		//exit wait if necessary
		if(do_wait == 1) do_wait=2;
	}
	this_cmd=ifetch2_next();
	decode_estage1[this_cmd >> 12]();
}


//##############################################################################
//# teh cycle selection table
//##############################################################################
cycle_t do_cycle[32]=
{
do_n0000,	do_n0004,	do_n0040,	do_n0040,	do_n0500,	do_n0500,	do_n0500,	do_n0500,
do_n6000,	do_n6000,	do_n6000,	do_n6000,	do_n6000,	do_n6000,	do_n6000,	do_n6000,
do_r0000,	do_r0004,	do_r0040,	do_r0040,	do_r0500,	do_r0500,	do_r0500,	do_r0500,
do_r6000,	do_r6000,	do_r6000,	do_r6000,	do_r6000,	do_r6000,	do_r6000,	do_r6000
};

