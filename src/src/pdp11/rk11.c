//#############################################################################[[D##
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

#include "board.h"
#include "cpu.h"
#include "xvars.h"
#if LOAD_TEST == 1
	#include "itest1_data.h"
#endif
unsigned short rkds,rker,rkcs,rkwc,rkba,rkda;
extern volatile unsigned short tx_cap;

extern unsigned short cycle_type;
unsigned long rk11_state;
unsigned short rk11_cmd,rk11_drive,buf_addr,buf_words;
unsigned short rk11_act_sector,rk11_num_sectors;


//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
unsigned char SDCARD_SPI_COMM(unsigned char x)
{
	return DEFAULT_SPI_COMM(x);
}
#endif
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
unsigned char DATAFLASH_SPI_COMM(unsigned char x)
{
	return DEFAULT_SPI_COMM(x);
}
#endif


//###############################################################################
// get position of next sector 
//###############################################################################
int next_sector(void)
{
	rkda++;		//increment sector

	if((rkda & 0x000F) == 12)	//beyond last sector?
	{
		rkda+=4;			//increment surface / cylinder
	}

	rk11_act_sector=(rkda & 0x0f) + ((rkda >> 4) & 0x1FF) * 12;	

	if(rk11_act_sector > 4871) 
	{ 
#if MCU < 9
		printf("!!! SECTOR OVERFLOW (%04X)!!!\n",rkda);
#endif
		return 0x4000;	//overflow disk
	}

	//calculate the new phys. sector
	rk11_act_sector=rk11_drive * 4872 + rk11_act_sector;

	return 0;
}

//###############################################################################
// initialise the drive 
//###############################################################################
void rk11_init(void)
{
	int i;
	
	rkds = 0x08C0;
	rker = 0x0000;
	rkcs = 0x0080;
	rkwc = 0x0000;
	rkba = 0x0000;
	rkda = 0x0000;
	rk11_state=0;
	for(i=0;i<MAX_CACHE;i++) rk11_disk_cache_entry[i]=0xFFFF;	//unused
	rk11_disk_cache_pointer=0;

//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
	SDCARD_SPI_INIT_SLOW	
	if(sdcard_init(SDCARD_CSPORT,SDCARD_CSPIN) != 0)
	{
		//no card -> drive LED flashes fast
		KPRINTF("\r\nMXE11: NO DRIVE\r\n",0);
		while(1)
		{
			set_portpin_one(DRIVE_LED);
			unilib_pause_ms(200);
			set_portpin_zero(DRIVE_LED);
			unilib_pause_ms(200);
		}
	}
	SDCARD_SPI_INIT
	set_portpin_zero(DRIVE_LED);
#endif
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
	DATAFLASH_SPI_INIT
	i=dataflash_init(DATAFLASH_CSPORT,DATAFLASH_CSPIN);
	
	if(i != 5)
	{
		//no card -> drive LED flashes fast
		KPRINTF("\r\nMXE11: NO DRIVE (%02x)\r\n",i);
		while(1)
		{
			set_portpin_one(DRIVE_LED);
			unilib_pause_ms(200);
			set_portpin_zero(DRIVE_LED);
			unilib_pause_ms(200);
		}
	}
	set_portpin_zero(DRIVE_LED);
#endif
	
}

//###############################################################################
// write bootcode to memory
//###############################################################################
void rk11_bootsetup(void)
{
#if LOAD_TEST == 1
	int i;
	for(i=0;i<((sizeof(itest1_data)>>1)-8);i++)
	{
		user_memory_data.word[i]=itest1_data[i+8];
	}
	pc=0x80;		//set PC to start
	KPRINTF("TEST SETUP...\r\n");
#else
	user_memory_data.word[0x100]=0012700;	
	user_memory_data.word[0x101]=0177406;	
	user_memory_data.word[0x102]=0012710;	
	user_memory_data.word[0x103]=0177400;	
	user_memory_data.word[0x104]=0012740;	
	user_memory_data.word[0x105]=0000005;	
	user_memory_data.word[0x106]=0105710;	
	user_memory_data.word[0x107]=0100376;	
	user_memory_data.word[0x108]=0005007;
	pc=0x200;		//set PC to start
#endif
}

//###############################################################################
// this is called if rk is called from main loop
//###############################################################################
void rk11_task(void)
{	
	int i;
#if MEDIA_TYPE == 0
	unsigned long offset;
#endif
#if MEDIA_TYPE == 2
	unsigned short j;
#endif
	//stop current action on error
	if(rker != 0)
	{
		rkcs=(rkcs & 0xFFFE);			//clear GO
		if(rkcs & 0x0040) cycle_type |= (0x04 << SHIFT_CYCLE);	//interrupt
		rk11_state=0;				//clear state
		cycle_type &= ~(0x10 << SHIFT_CYCLE);	//disable RK11 task
#if MCU > 9
		set_portpin_zero(DRIVE_LED);
#endif
		return;
	}
	//all done
	if(rk11_state == 0xE000)
	{
		rkcs=(rkcs & 0xFFFE) | 0x80;		//clear GO and set READY
		if(rkcs & 0x0040) cycle_type |= (0x04 << SHIFT_CYCLE);	//interrupt
		rk11_state=0;				//clear state
		cycle_type &= ~(0x10 << SHIFT_CYCLE);	//disable RK11 task
#if MCU > 9
		set_portpin_zero(DRIVE_LED);
#endif
		return;		
	}

//--------- read cycle, sector start --------------------------------------------------
 	if(rk11_state == 0x1000)
	{
#if MCU > 9
		set_portpin_one(DRIVE_LED);
#else
//		show_mem(0,8);
//		printf("READ SECTOR %d TO %x\r\n",rk11_act_sector,rkba);
#endif
		//check if sector is cached
		for(i=0;i<MAX_CACHE;i++)
		{
			if(rk11_disk_cache_entry[i]==rk11_act_sector)
			{
//				printf("SECTOR %d IS CACHED (%i)\n",rk11_act_sector,i);
				memcpy(&user_memory_data.byte[rkba],rk11_disk_cache[i],512);
				rkba+=512;
				rkwc+=256;
				rker=next_sector();
				if(rkwc == 0) rk11_state=0xE000;
				return;			
			}	
		}	
		rk11_state = 0x1100;
	}
	
	//sector is not in cache, prepare sector read from disk
	if(rk11_state == 0x1100)
	{
				
//-------------------------------------------- PC - FILE ----------------------------------
#if MEDIA_TYPE == 0
		offset=rk11_act_sector*512;
		i=open("image.bin",O_RDWR);
		if(i<1) printf("NO IMAGE\n");
		lseek(i,offset,SEEK_SET);
		read(i,&user_memory_data.byte[rkba],512);	
		close(i);
		rk11_state = 0x1F00;
		return;
#endif		
//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
		if(sdcard_read_status() == 0) return;
		sdcard_read_sector_ww(	&user_memory_data.word[rkba>>1],
					rk11_act_sector);
		rk11_state = 0x1F00;
		return;
#endif		
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
		if(dataflash_read_status() == 0) return;
		i=dataflash_read_page_ww(	&user_memory_data.word[rkba>>1],
						rk11_act_sector >> 1,
						(rk11_act_sector & 1) << 8,
						256);
//		KPRINTF("MXE11: READ (%04x) -> %d\r\n",rk11_act_sector,i);
		rk11_state = 0x1F00;
		return;
#endif		
//-----------------------------------------------------------------------------------------
	}
	
	//read_cycle end
	if(rk11_state == 0x1F00)
	{
//		show_mem(0,8);
		rkba+=512;
		rkwc+=256;
		rker=next_sector();
		rk11_state = 0x1000;
		if(rkwc == 0) rk11_state=0xE000;
		return;
	}

//--------- write cycle sector start ----------------------------------------------
	if(rk11_state == 0x2000)
	{
#if MCU > 9
		set_portpin_one(DRIVE_LED);
#endif
		//check if sector is cached and then overwrite
		for(i=0;i<(MAX_CACHE-1);i++)
		{
			if(rk11_disk_cache_entry[i]==rk11_act_sector)
			{
//				printf("OVERWRITE SECTOR %d IN CACHE (%d)\n",rk11_act_sector,i);
				memcpy(rk11_disk_cache[i],&user_memory_data.byte[rkba],512);
				rkba+=512;
				rkwc+=256;
				rker=next_sector();
				if(rkwc == 0) rk11_state=0xE000;
				return;			
			}	
		}	
		//we take the next entry because of no free entry
		rk11_disk_cache_pointer++;
		if(rk11_disk_cache_pointer == MAX_CACHE) rk11_disk_cache_pointer = 0;
		rk11_state = 0x2100;
		return;			
	}
			
					
	//write cycle flush cache
	if(rk11_state == 0x2100)
	{
		
		if(rk11_disk_cache_entry[rk11_disk_cache_pointer] == 0xFFFF)
		{
			rk11_state = 0x2F00;	//entry is empty			
			return;
		}

//-------------------------------------------- PC - FILE ----------------------------------
#if MEDIA_TYPE == 0
		offset=rk11_disk_cache_entry[rk11_disk_cache_pointer]*512;			
		i=open("image.bin",O_RDWR);
		lseek(i,offset,SEEK_SET);
		write(i,rk11_disk_cache[rk11_disk_cache_pointer],512);	
		close(i);
		rk11_state = 0x2F00;			
		return;
#endif
//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
		if(sdcard_read_status() == 0) return;
		sdcard_write_sector_ww(	rk11_disk_cache[rk11_disk_cache_pointer],
					rk11_disk_cache_entry[rk11_disk_cache_pointer]);
		rk11_state = 0x2F00;
		return;
#endif		
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
		if(dataflash_read_status() == 0) return;
		dataflash_load_page(	0,
					rk11_disk_cache_entry[rk11_disk_cache_pointer] >> 1,
					0);
		rk11_state = 0x2C00;
		return;
#endif		
	}		

#if MEDIA_TYPE == 2
	//now write buffer
	if(rk11_state == 0x2C00)
	{
		if(dataflash_read_status() == 0) return;

		dataflash_write_buffer_ww(	0,
						rk11_disk_cache[rk11_disk_cache_pointer],
						(rk11_disk_cache_entry[rk11_disk_cache_pointer] & 1) << 8,
						256);
		dataflash_prog_page(	0,
					rk11_disk_cache_entry[rk11_disk_cache_pointer] >> 1,
					0);
		rk11_state = 0x2F00;
		return;			
	}
#endif
//-----------------------------------------------------------------------------------------

	//now write new data into cache	
	if(rk11_state == 0x2F00)
	{
//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
		if(sdcard_read_status() == 0) return;
#endif		
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
		if(dataflash_read_status() == 0) return;
#endif

		memcpy(rk11_disk_cache[rk11_disk_cache_pointer],&user_memory_data.byte[rkba],512);
		rk11_disk_cache_entry[rk11_disk_cache_pointer]=rk11_act_sector;
		rkba+=512;
		rkwc+=256;
		rker=next_sector();
		rk11_state = 0x2000;
		if(rkwc == 0) rk11_state=0xE000;
		return;
	}


	if(rk11_state == 1)	//first active
	{
		rk11_cmd = rkcs & 0x0e;		//get command 
		rk11_drive = rkda >> 13;	//get drive
		rkcs &= 0xFF7F;			//clear ready
		
		rker=0;
		if((rkda & 0xE000) > 0x4000) rker = 0x0080;	//NO DISK
		if((rkda & 0x000F) > 11) rker = 0x0020;		//NO SECTOR
		if((rkda & 0x1FE0) > 6464) rker = 0x0040;	//NO CYLINDER DISK 0		

		if(rker != 0) 
		{
#if MCU < 9
			printf("SECTOR %04X OUT OF RANGE !!!\n",rkda);
#endif
			return;
		}
		
		//read
		if((rk11_cmd == 4) && (rker == 0))
		{
			rk11_state=0x1000;
			rk11_act_sector=(rkda & 0x0f) + ((rkda >> 4) & 0x1FF) * 12;	
			rk11_num_sectors= ~rkwc >> 8;
			rk11_act_sector=rk11_drive * 4872 + rk11_act_sector;
			return;
		}	
			
		//write	
		if((rk11_cmd == 2) && (rker == 0))
		{
			rk11_state=0x2000;
			rk11_act_sector=(rkda & 0x0f) + ((rkda >> 4) & 0x1FF) * 12;	
			rk11_num_sectors= ~rkwc >> 8;
			rk11_act_sector=rk11_drive * 4872 + rk11_act_sector;
			return;
		}

		rkcs=(rkcs & 0xFFFE) | 0x80;	//clear GO and set READY
		//interrupt
		if(rkcs & 0x0040) cycle_type |= (0x04 << SHIFT_CYCLE);			
	}	
}

//###############################################################################
// flus all buffers
//###############################################################################
void rk11_flush(void)
{	
	int i;
#if MEDIA_TYPE == 0
	unsigned long offset;
	int f;
	printf("\r\nCleanup cache ");
#endif
	
	KPRINTF("\r\nCleanup cache ");
	for(i=0;i<MAX_CACHE;i++)
	{
		if(rk11_disk_cache_entry[i]!=0xFFFF)
		{
			if(!(i & 3)) KPRINTF(".");
#if MEDIA_TYPE == 0
			if(!(i & 3)) printf(".");
			offset=rk11_disk_cache_entry[i]*512;			
			f=open("image.bin",O_RDWR);
			lseek(f,offset,SEEK_SET);
			write(f,rk11_disk_cache[i],512);	
			close(f);
#endif
//-------------------------------------------- SD - CARD ----------------------------------
#if MEDIA_TYPE == 1
			while(sdcard_read_status() == 0);
			sdcard_write_sector_ww(	rk11_disk_cache[i],
						rk11_disk_cache_entry[i]);
#endif		
//-------------------------------------------- DATAFLASH ----------------------------------
#if MEDIA_TYPE == 2
			while(dataflash_read_status() == 0);
			dataflash_load_page(0,rk11_disk_cache_entry[i] >> 1,1);
			dataflash_write_buffer_ww(	0,
							rk11_disk_cache[i],
							(rk11_disk_cache_entry[i] & 1) << 8,256);
			dataflash_prog_page(0,rk11_disk_cache_entry[i] >> 1,1);
#endif		
//-----------------------------------------------------------------------------------------
		}	
	}
#if MEDIA_TYPE == 0
	printf("\r\n");
#endif
}


//###############################################################################
// view status (for debugging)
//###############################################################################
void show_rk11(void)
{
#if MCU < 9
	printf("RKCS %04X\n",rkcs);
	printf("RKDA %04X\n",rkda);
	printf("RKBA %04X\n",rkba);
	printf("RKWC %04X\n",rkwc);
#endif
}

