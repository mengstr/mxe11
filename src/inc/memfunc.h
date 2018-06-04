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

#if IO_TABLE == 1
extern getb_op_t read_iob[8192];
extern get_op_t read_iow[4096];
extern putb_op_t write_iob[8192];
extern put_op_t write_iow[4096];
#else
extern unsigned short read_io_word(unsigned short);
extern void write_io_word(unsigned short,unsigned short);
extern void write_io_byte(unsigned short,unsigned char);
#endif

//#######################################################################
//# read data from memory
//#######################################################################
static inline unsigned short iread_word(unsigned short address)
{
	if(address < 0xE000) return(user_memory_data.word[address>>1]);
#if IO_TABLE == 1
	return(read_iow[(address & 0x1FFF) >> 1]());
#else
	return read_io_word(address);
#endif
}

static inline unsigned short iread_byte(unsigned short address)
{
	if(address < 0xE000)
	{
#ifdef IS_LITTLE_ENDIAN
		return user_memory_data.byte[address];
#else
		return user_memory_data.byte[address ^ 1];
#endif
 	}
	else
	{
#if IO_TABLE == 1
		return(read_iob[address & 0x1FFF]());
#else
		if(address & 1)
			return(read_io_word(address) >> 8);
		else			 
			return(read_io_word(address) & 0xff);

#endif
 	}
 }


//#######################################################################
//# write data to memory
//#######################################################################
static inline void iwrite_word(unsigned short address,unsigned short data)
{
		if(address < 0xE000) user_memory_data.word[address>>1] = data;
#if IO_TABLE == 1
		else write_iow[(address & 0x1FFF) >> 1](data);
#else
		else write_io_word(address,data);
#endif
}

static inline void iwrite_byte(unsigned short address,unsigned short data)
{
#ifdef IS_LITTLE_ENDIAN
	if(address < 0xE000)
	{
			user_memory_data.byte[address] = data & 0xff;
 	}
	
#if IO_TABLE == 1
	else write_iob[address & 0x1FFF](data);
#else
	else write_io_byte(address,data & 0xff);
#endif

#else
	if(address < 0xE000)
	{
			user_memory_data.byte[address ^ 1] = data & 0xff;
 	}
	
#if IO_TABLE == 1
	else write_iob[(address ^ 1) & 0x1FFF](data & 0xff);

#else
	else write_io_byte(address ^ 1,data & 0xff);
#endif
#endif

}


//#######################################################################
//# read a word (instruction addr space)
//#######################################################################
static inline unsigned short ifetch_next(void)
{
	unsigned short xptr=pc >> 1;
	pc += 2;
#if CHECK_FETCH == 1	
	if(xptr < 0x7000) return user_memory_data.word[xptr];
	return 0;
#else
	return user_memory_data.word[xptr];
#endif
}

//#######################################################################
//# read a word (instruction addr space)
//#######################################################################
static inline unsigned short ifetch2_next(void)
{
	unsigned short xptr=pc >> 1;
//	set_portpin_zero(DRIVE_LED);

//PC
#if MCU < 10
	pc += 2;
#endif

//SPC56EL60
#if MCU == 10
	asm volatile ("se_addi 25,2");
#endif

//SPC56EL60 ASM
#if MCU == 11
	asm volatile ("se_addi 25,2");
#endif

//STM32F103
#if MCU == 20
	asm volatile ("adds r7,#2");
#endif

//STM32F107
#if MCU == 25
	asm volatile ("adds r7,#2");
#endif

//STM32F411
#if MCU == 30
	asm volatile ("adds r7,#2");
#endif

//STM32F411 without regopt
#if MCU == 31
	pc += 2;
#endif

//STM32F405
#if MCU == 35
	asm volatile ("adds r7,#2");
#endif

//STM32L475
#if MCU == 40
//	pc += 2;
	asm volatile ("adds r7,#2");
#endif

#if CHECK_FETCH == 1	
	if(xptr < 0x7000) return user_memory_data.word[xptr];
	return 0;
#else
	return user_memory_data.word[xptr];
#endif
}



//##############################################################################
//# stack manipulation
//##############################################################################
static inline void push_data(unsigned short data)
{
	sp.ureg-=2;	
	if(sp.ureg < 0xE000) user_memory_data.word[sp.ureg>>1] = data;
#if IO_TABLE == 1
	else write_iow[(sp.ureg & 0x1FFF) >> 1](data);
#else
	else write_io_word(sp.ureg,data);
#endif

#if USE_STACKLIMIT == 1
	if(sp.ureg < stack_limit)
	{
		sp.ureg-=2;	
		if(sp.ureg < 0xE000) user_memory_data.word[sp.ureg>>1] = psw;
		sp.ureg-=2;	
		if(sp.ureg < 0xE000) user_memory_data.word[sp.ureg>>1] = pc;
		pc=iread_word(4);			//004
		psw=iread_word(6);
	} 
#endif
}

static inline unsigned short pop_data(void)
{
	unsigned short laddr=sp.ureg;
	sp.ureg+=2;	
	if(laddr < 0xE000) return(user_memory_data.word[laddr>>1]);
#if IO_TABLE == 1
	return (read_iow[(laddr & 0x1FFF) >> 1]());
#else
	return read_io_word(laddr);
#endif
}

