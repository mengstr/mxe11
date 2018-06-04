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

#if USE_STACKLIMIT == 1
unsigned short stack_limit;
#endif

//###############################################################################
//# PC
//###############################################################################
#if MCU <10
unsigned short pc;
unsigned short this_cmd;
unsigned short last_addr;
unsigned short psw;
unsigned short cycle_type;
registers_t sp;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;
#endif


//###############################################################################
//# SPC56EL60
//###############################################################################
#if MCU == 10
register unsigned short pc asm ("r25");
register unsigned short this_cmd asm ("r26");
register unsigned short last_addr asm ("r27");
register unsigned short psw asm ("r28");
unsigned short cycle_type;
//unsigned short psw;
register registers_t sp asm ("r29");
register registers_t register5 asm ("r30");
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
//registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif


//###############################################################################
//# SPC56EL60 ASM
//###############################################################################
#if MCU == 11
register registers_t register0 asm ("r18");
register registers_t register1 asm ("r19");
register registers_t register2 asm ("r20");
register registers_t register3 asm ("r21");
register registers_t register4 asm ("r22");
register registers_t register5 asm ("r23");
register unsigned short cycle_type asm ("r24");
register unsigned short pc asm ("r25");
register unsigned short this_cmd asm ("r26");
register unsigned short last_addr asm ("r27");
register unsigned short psw asm ("r28");
register registers_t sp asm ("r29");
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

//###############################################################################
//# STM32F103
//###############################################################################
#if MCU == 20
register unsigned short pc asm ("r7");
register unsigned short psw asm ("r8");
register unsigned short this_cmd asm ("r9");
register unsigned short last_addr asm ("r10");
unsigned short cycle_type;
//unsigned short psw;
registers_t sp;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

//###############################################################################
//# STM32F107
//###############################################################################
#if MCU == 25
register unsigned short pc asm ("r7");
register unsigned short psw asm ("r8");
register unsigned short this_cmd asm ("r9");
register registers_t sp asm ("r10");
unsigned short last_addr;
unsigned short cycle_type;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

//###############################################################################
//# STM32F411
//###############################################################################
#if MCU == 30
register unsigned short pc asm ("r7");
register unsigned short psw asm ("r8");
register unsigned short this_cmd asm ("r9");
register registers_t sp asm ("r10");
unsigned short last_addr;
unsigned short cycle_type;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

//###############################################################################
//# STM32F411 without regopt
//###############################################################################
#if MCU == 31
unsigned short pc;
unsigned short this_cmd;
unsigned short last_addr;
unsigned short psw;
unsigned short cycle_type;
registers_t sp;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

//###############################################################################
//# STM32F405
//###############################################################################
#if MCU == 35
register unsigned short pc asm ("r7");
register unsigned short psw asm ("r8");
register unsigned short this_cmd asm ("r9");
register registers_t sp asm ("r10");
unsigned short last_addr;
unsigned short cycle_type;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
//memory_t user_memory_data;
memory_t __attribute__((section(".ccm"))) user_memory_data;
unsigned char rk11_disk_cache[MAX_CACHE][512];
unsigned short rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif


//###############################################################################
//# STM32L475
//###############################################################################
#if MCU == 40
register unsigned short pc asm ("r7");
register unsigned short psw asm ("r8");
register unsigned short this_cmd asm ("r9");
register registers_t sp asm ("r10");
unsigned short last_addr;
unsigned short cycle_type;
registers_t register0;			//CPU register
registers_t register1;			//CPU register
registers_t register2;			//CPU register
registers_t register3;			//CPU register
registers_t register4;			//CPU register
registers_t register5;			//CPU register
memory_t user_memory_data;
unsigned char __attribute__((section(".ram2"))) rk11_disk_cache[MAX_CACHE][512];
unsigned short __attribute__((section(".ram2"))) rk11_disk_cache_entry[MAX_CACHE];
unsigned short rk11_disk_cache_pointer;
volatile char rxbuffer8[SERIAL_BUFFER_SIZE];
volatile char txbuffer8[SERIAL_BUFFER_SIZE];
volatile char rxbuffer9[SERIAL_BUFFER_SIZE];
volatile char txbuffer9[SERIAL_BUFFER_SIZE];
volatile unsigned long rxint_queue;
volatile unsigned long txint_queue;

#endif

