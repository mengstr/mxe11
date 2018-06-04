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


#ifndef FALSE
	#define FALSE 0
#endif

#ifndef TRUE
	#define TRUE !FALSE 
#endif

typedef union
{
	unsigned short ureg;
	short ireg;
	unsigned char bytes[2];
}registers_t;

typedef union
{
	unsigned long ureg;
	long ireg;
	unsigned short wreg[2];
}lregisters_t;

typedef union
{
	float freg;
	unsigned long ureg;
	unsigned short wreg[2];
}fregisters_t;


#if MCU < 10
typedef union
{
	unsigned short word[32768];
	unsigned char byte[65536];
}memory_t;
#endif
#if MCU == 11
typedef union
{
	unsigned short word[32768];
	unsigned char byte[65536];
}memory_t;
#endif
#if MCU == 10
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 20
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 25
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 30
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 31
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 35
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif
#if MCU == 40
typedef union
{
	unsigned short word[28672];
	unsigned char byte[28672*2];
}memory_t;
#endif


typedef unsigned short (*get_op_t) (void);
typedef unsigned char (*getb_op_t) (void);
typedef void (*put_op_t) (unsigned short);
typedef void (*putb_op_t) (unsigned char);

typedef void (*cycle_t) (void);
typedef void (*mov_op_t) (void);

typedef unsigned short (*get_mem_t) (unsigned short);
typedef void (*put_mem_t) (unsigned short,unsigned short);
typedef void (*putw_mem_t) (unsigned short,unsigned short);
typedef void (*putb_mem_t) (unsigned short,unsigned char);

typedef unsigned short (*get_io_t) (void);
typedef void (*put_io_t) (unsigned short);

typedef void (*trap_t) (void);



