//###############################################################################
//#										#
//# universal microcontroller library						#
//#										#
//# copyright (c) 2010-2018 Joerg Wolfram (joerg@jcwolfram.de)			#
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
#include <stdint.h>

#define size_t unsigned long

//nop

typedef struct
{
	int quot;
	int rem;
} div_t;

typedef struct
{
	long quot;
	long rem;
} ldiv_t;

//pri

#define PORT_A		0
#define PORT_B		16
#define PORT_C		32
#define PORT_D		48
#define PORT_E		64
#define PORT_F		80
#define PORT_G		96
#define PORT_H		112

#define CLOCK_8_2	0x0208
#define CLOCK_8_4	0x0408
#define CLOCK_8_8	0x0808
#define CLOCK_8_16	0x1008
#define CLOCK_8_24	0x1808
#define CLOCK_8_32	0x2008
#define CLOCK_8_48	0x3008
#define CLOCK_8_64	0x4008

#define CLOCK_16_2	0x0210
#define CLOCK_16_4	0x0410
#define CLOCK_16_8	0x0810
#define CLOCK_16_16	0x1010
#define CLOCK_16_24	0x1810
#define CLOCK_16_32	0x2010
#define CLOCK_16_48	0x3010
#define CLOCK_16_64	0x4010

#define CLOCK_40_2	0x0228
#define CLOCK_40_4	0x0428
#define CLOCK_40_8	0x0828
#define CLOCK_40_16	0x1028
#define CLOCK_40_24	0x1828
#define CLOCK_40_32	0x2028
#define CLOCK_40_48	0x3028
#define CLOCK_40_64	0x4028

#define CLOCK_I_16	0x1000
#define CLOCK_I_8	0x0800
#define CLOCK_I_4	0x0400
#define CLOCK_I_2	0x0200

#define OUTPUT_UART0	send_uart0
#define OUTPUT_UART1	send_uart1
#define OUTPUT_SPI0	send_spi0
#define OUTPUT_SPI1	send_spi1
#define COMM_SPI0	comm_spi0
#define COMM_SPI1	comm_spi1

void unilib_outchar(unsigned char);

#define putc unilib_outchar

#define COLOR16_BLACK	0x0000
#define COLOR16_BLUE	0xf800
#define COLOR16_RED	0x001f
#define COLOR16_MAGENTA	0xf81f
#define COLOR16_GREEN	0x07e0
#define COLOR16_CYAN	0xffe0
#define COLOR16_YELLOW	0x07ff
#define COLOR16_WHITE	0xffff

#ifndef _UNILIB_CAN_FRAME
#define _UNILIB_CAN_FRAME
typedef struct _unilib_can_frame{
	unsigned long id;
	unsigned char mode;
	unsigned char len;
	unsigned char data[8];
	unsigned long timestamp;
}unilib_can_frame;
#endif

#ifndef _UNILIB_DATETIME
#define _UNILIB_DATETIME
typedef struct _unilib_date_time{
	unsigned short year;
	unsigned char month;
	unsigned char day;
	unsigned char hour;
	unsigned char min;
	unsigned char sec;
}unilib_date_time;
#endif

#ifndef _UNILIB_CAN_CLOCK
#define _UNILIB_CAN_CLOCK
#define	CANCLOCK_8_50k		0x09DB0006
#define	CANCLOCK_16_50k		0x13DB0006
#define	CANCLOCK_24_50k		0x1DDB0006
#define	CANCLOCK_32_50k		0x27DB0006
#define	CANCLOCK_48_50k		0x3BDB0006
#define	CANCLOCK_64_50k		0x4FDB0006
#define	CANCLOCK_80_50k		0x63DB0006
#define	CANCLOCK_96_50k		0x77DB0006
#define	CANCLOCK_120_50k	0x95DB0006

#define	CANCLOCK_8_100k		0x04DB0006
#define	CANCLOCK_16_100k	0x09DB0006
#define	CANCLOCK_24_100k	0x0EDB0006
#define	CANCLOCK_32_100k	0x13DB0006
#define	CANCLOCK_48_100k	0x1DDB0006
#define	CANCLOCK_64_100k	0x27DB0006
#define	CANCLOCK_80_100k	0x31DB0006
#define	CANCLOCK_96_100k	0x3BDB0006
#define	CANCLOCK_120_100k	0x4ADB0006

#define	CANCLOCK_8_125k		0x03DB0006
#define	CANCLOCK_16_125k	0x07DB0006
#define	CANCLOCK_24_125k	0x0BDB0006
#define	CANCLOCK_32_125k	0x0FDB0006
#define	CANCLOCK_48_125k	0x17DB0006
#define	CANCLOCK_64_125k	0x1FDB0006
#define	CANCLOCK_80_125k	0x27DB0006
#define	CANCLOCK_96_125k	0x2FDB0006
#define	CANCLOCK_120_125k	0x3BDB0006

#define	CANCLOCK_8_250k		0x01DB0006
#define	CANCLOCK_16_250k	0x03DB0006
#define	CANCLOCK_24_250k	0x05DB0006
#define	CANCLOCK_32_250k	0x07DB0006
#define	CANCLOCK_48_250k	0x0BDB0006
#define	CANCLOCK_64_250k	0x0FDB0006
#define	CANCLOCK_80_250k	0x13DB0006
#define	CANCLOCK_96_250k	0x17DB0006
#define	CANCLOCK_120_250k	0x1DDB0006

#define	CANCLOCK_8_500k		0x00DB0006
#define	CANCLOCK_16_500k	0x01DB0006
#define	CANCLOCK_24_500k	0x02DB0006
#define	CANCLOCK_32_500k	0x03DB0006
#define	CANCLOCK_48_500k	0x05DB0006
#define	CANCLOCK_64_500k	0x07DB0006
#define	CANCLOCK_80_500k	0x09DB0006
#define	CANCLOCK_96_500k	0x0BDB0006
#define	CANCLOCK_120_500k	0x0EDB0006

#define	CANCLOCK_8_1M		0x00490002
#define	CANCLOCK_16_1M		0x01490002
#define	CANCLOCK_24_1M		0x02490002
#define	CANCLOCK_32_1M		0x03490002
#define	CANCLOCK_48_1M		0x05490002
#define	CANCLOCK_64_1M		0x07490002
#define	CANCLOCK_80_1M		0x09490002
#define	CANCLOCK_96_1M		0x0B490002
#define	CANCLOCK_120_1M		0x0E490002
 
#endif


//---------------------------------------------------------------------------------------
// exports from src/hilevel_cc2500/src/hilevel_cc2500/cc2500.c
//---------------------------------------------------------------------------------------
//#define CC2500_PKT_BYTES 	33		// packet size 
//#######################################################################
//# init the CC2500 without communication setup				#
//#######################################################################
void CC2500_init_minimal(void);

//#######################################################################
//# init the CC2500 (250Kbit/s, compatibility mode with CC2541)		#
//#######################################################################
void CC2500_init_250k(PORT_TYPE cs_port, PORT_TYPE cs_pin);

//#######################################################################
//# init the CC2500 (50Kbit/s)						#
//#######################################################################
void CC2500_init_50k(PORT_TYPE cs_port, PORT_TYPE cs_pin);

//#######################################################################
//# init the CC2500 (2400 Bit/s)					#
//#######################################################################
void CC2500_init_2k4(PORT_TYPE cs_port, PORT_TYPE cs_pin);

//#######################################################################
//# send a packet							#
//#######################################################################
void CC2500_start_tx(unsigned char *txBuffer,unsigned char len,unsigned char addr);

//#######################################################################
//# start RX								#
//#######################################################################
void CC2500_start_rx(unsigned char len,unsigned char addr);

//#######################################################################
//# read a received packet						#
//#######################################################################
void CC2500_get_rxdata(unsigned char *rxBuffer,unsigned char len);

//#######################################################################
//#######################################################################
unsigned char CC2500_get_state(void);

//#######################################################################
//# set channel								#
//#######################################################################
void CC2500_set_channel(unsigned char channel);

//#######################################################################
//# get RSSI								#
//#######################################################################
unsigned char CC2500_get_rssi(void);

//#######################################################################
//# get partnumber							#
//#######################################################################
unsigned short CC2500_get_info(void);

//#######################################################################
//# goto IDLE mode							#
//#######################################################################
void CC2500_idle(void);

//#######################################################################
//# calibrate								#
//#######################################################################
void CC2500_calibrate(void);

//#######################################################################
//# detune								#
//#######################################################################
void CC2500_detune(unsigned long freq);

//#######################################################################
//# get calibration data						#
//#######################################################################
unsigned long CC2500_get_calibration(void);

//#######################################################################
//# set calibration data						#
//#######################################################################
void CC2500_set_calibration(unsigned long cal_val);

//#######################################################################
//# st into power down mode						#
//#######################################################################
void CC2500_sleep(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_crc16/src/hilevel_crc16/crc16.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init crc16							#
//#									#
//#######################################################################
void init_crc16(unsigned short startvalue,unsigned short polynom, unsigned char invert);

//#######################################################################
//#									#
//#	update crc16 with byte						#
//#									#
//#######################################################################
void update_crc16(unsigned char val);

//#######################################################################
//#									#
//#	update crc16 with byte array					#
//#									#
//#######################################################################
void calculate_crc16(unsigned char *buffer, unsigned int len);

//#######################################################################
//#									#
//#	get crc16 value							#
//#									#
//#######################################################################
unsigned short get_crc16(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_crypt/src/hilevel_crypt/aes.c
//---------------------------------------------------------------------------------------
//############################################################################
//#                                                                          #
//# encrypt with AES128 (data is little endian)                              #
//#                                                                          #
//############################################################################
void encrypt_aes128(unsigned char* data, unsigned char* key);

//############################################################################
//#                                                                          #
//# decrypt with AES128 (data is little endian)                              #
//#                                                                          #
//############################################################################
void decrypt_aes128(unsigned char* data, unsigned char* key);

//############################################################################
//#                                                                          #
//# encrypt with AES256 (data is little endian)                              #
//#                                                                          #
//############################################################################
void encrypt_aes256(unsigned char* data, unsigned char* key);

//############################################################################
//#                                                                          #
//# decrypt with AES256 (data is little endian)                              #
//#                                                                          #
//############################################################################
void decrypt_aes256(unsigned char* data, unsigned char* key);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_crypt/src/hilevel_crypt/sha256.c
//---------------------------------------------------------------------------------------
//##############################################################################
//#                                                                            #
//# init the hash                                                              #
//#                                                                            #
//##############################################################################
void sha256_init(void);

//##############################################################################
//#                                                                            #
//# update the hash with data                                                  #
//#                                                                            #
//##############################################################################
void sha256_update(unsigned char *data, unsigned long len);

//##############################################################################
//#                                                                            #
//# output the hash                                                            #
//#                                                                            #
//##############################################################################
void sha256_final(unsigned char *hash);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_crypt/src/hilevel_crypt/xtea.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	xtea encrypt							#
//#									#
//#######################################################################
void encrypt_xtea (unsigned int num_cycles, unsigned char *data, unsigned char *key);

//#######################################################################
//#									#
//#	xtea decrypt							#
//#									#
//#######################################################################
void decrypt_xtea (unsigned int num_cycles, unsigned char *data, unsigned char *key);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_dataflash/src/hilevel_dataflash/dataflash.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char dataflash_checkid(void);

//#######################################################################
//# init the dataflash							#
//# ret: 	0=no dataflash						#
//# 	 	1=AT45DB041						#
//# 	 	2=AT45DB081						#
//# 	 	3=AT45DB161						#
//# 	 	4=AT45DB321						#
//# 	 	5=AT45DB642						#
//#######################################################################
unsigned char dataflash_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//# 1=ready, 0=busy							#
//#######################################################################
unsigned char dataflash_read_status(void);

//#######################################################################
//# wait for device is ready						#
//# 0=ready, 1=timeout							#
//#######################################################################
unsigned char dataflash_wait_ready(unsigned char timeout);

//#######################################################################
//# read from page (byte-wise)						#
//#######################################################################
unsigned char dataflash_read_page(unsigned char *buffer,unsigned short page, unsigned short start, unsigned short bytes);

//#######################################################################
//# read from page (word_wise)						#
//#######################################################################
unsigned char dataflash_read_page_ww(unsigned short *buffer,unsigned short page, unsigned short start, unsigned short words);

//#######################################################################
//# read from page (longword_wise)					#
//#######################################################################
unsigned char dataflash_read_page_lw(unsigned long *buffer,unsigned short page, unsigned short start, unsigned short longs);

//#######################################################################
//# read data from buffer (byte-wise)					#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_read_buffer(unsigned char bufnum,unsigned char *buffer, unsigned short start, unsigned short bytes);

//#######################################################################
//# read data from buffer (word-wise)					#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_read_buffer_ww(unsigned char bufnum,unsigned short *buffer, unsigned short start, unsigned short words);

//#######################################################################
//# read data from buffer (longword-wise)				#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_read_buffer_lw(unsigned char bufnum,unsigned long *buffer, unsigned short start, unsigned short longs);

//#######################################################################
//# write data to buffer (byte-wise)					#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_write_buffer(unsigned char bufnum,unsigned char *buffer,unsigned short start, unsigned short bytes);

//#######################################################################
//# write data to buffer (word-wise)					#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_write_buffer_ww(unsigned char bufnum,unsigned short *buffer,unsigned short start, unsigned short words);

//#######################################################################
//# write data to buffer (longword-wise)				#
//# 0 = buffer 1							#
//# 1 = buffer 2							#
//#######################################################################
unsigned char dataflash_write_buffer_lw(unsigned char bufnum,unsigned long *buffer,unsigned short start, unsigned short longs);

//#######################################################################
//# load buffer 1/2 from flash						#
//#######################################################################
unsigned char dataflash_load_page(unsigned char bufnum,unsigned short page,unsigned char blocked);

//#######################################################################
//# write buffer 1/2 to flash						#
//#######################################################################
unsigned char dataflash_prog_page(unsigned char bufnum,unsigned short page,unsigned char blocked);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_debounce/src/hilevel_debounce/debounce.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init debounce							#
//#									#
//#######################################################################
void enable_debounce(unsigned char s);

//#######################################################################
//#									#
//#	add a debounce pin						#
//#									#
//#######################################################################
unsigned char add_debounce(PORT_TYPE debounce_port,int debounce_pin);

//#######################################################################
//#									#
//#	get debounce pin value						#
//#									#
//#######################################################################
unsigned char get_debounced(unsigned char num);

//#######################################################################
//#									#
//#	this must be called periodicly (in interrupt)			#
//#									#
//#######################################################################
void serve_debounce(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_enc28j60/src/hilevel_enc28j60/enc28j60.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init ENC							#
//#									#
//#######################################################################
int enc28j60_init(unsigned char spi_port,int prescaler,PORT_TYPE sel_port,int sel_pin);

//#######################################################################
//#									#
//#	get a packet							#
//#									#
//#######################################################################
int enc28j60_receive_packet(unsigned char buffer[]);

//#######################################################################
//#									#
//#	send a packet							#
//#									#
//#######################################################################
int enc28j60_send_packet(unsigned char buffer[],int frame_length);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_glcd128128_color/src/hilevel_glcd128128_color/glcd128ca.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	set active window						#
//#									#
//#######################################################################
void glcd128ca_setwin(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2);

//#######################################################################
//#									#
//#	fill window						#
//#									#
//#######################################################################
void glcd128ca_fillwin(unsigned char dx,unsigned char dy,unsigned int color);

//#######################################################################
//#									#
//#	set background color						#
//#									#
//#######################################################################
void glcd128ca_set_bgcolor(unsigned int color);

//#######################################################################
//#									#
//#	set foreground color						#
//#									#
//#######################################################################
void glcd128ca_set_fgcolor(unsigned int color);

//#######################################################################
//#									#
//#	set background color						#
//#									#
//#######################################################################
void glcd128ca_set_bgcolor_rgb(unsigned char red,unsigned char green, unsigned char blue);

//#######################################################################
//#									#
//#	set foreground color						#
//#									#
//#######################################################################
void glcd128ca_set_fgcolor_rgb(unsigned char red,unsigned char green, unsigned char blue);

//#######################################################################
//#									#
//#	clear screen							#
//#									#
//#######################################################################
void glcd128ca_clrscr(void);

//#######################################################################
//#									#
//#	enable display							#
//#									#
//#######################################################################
void enable_glcd128ca(PORT_TYPE dataport,PORT_TYPE ctrlport,unsigned char wrpin,unsigned char rdpin,unsigned char cdpin,unsigned char cspin,unsigned char rspin);

//#######################################################################
//#									#
//#	set display contrast						#
//#									#
//#######################################################################
void glcd128ca_set_contrast(unsigned char contrast);

//#######################################################################
//#									#
//#	set screen position						#
//#									#
//#######################################################################
void glcd128ca_gotoxy(unsigned char x,unsigned char y);

//#######################################################################
//#									#
//#	new line							#
//#									#
//#######################################################################
void glcd128ca_newline(void);

//#######################################################################
//#									#
//#	output char (opaque)						#
//#									#
//#######################################################################
void glcd128ca_char(unsigned char c);

//#######################################################################
//#									#
//#	output big char (opaque)					#
//#									#
//#######################################################################
void glcd128ca_bchar(unsigned char c);

//#######################################################################
//#									#
//#	get current x coordinate					#
//#									#
//#######################################################################
unsigned int glcd128ca_get_drawpos_x(void);

//#######################################################################
//#									#
//#	get current y coordinate					#
//#									#
//#######################################################################
unsigned int glcd128ca_get_drawpos_y(void);

//#######################################################################
//#									#
//#	get current x coordinate					#
//#									#
//#######################################################################
unsigned int glcd128ca_get_textpos_x(void);

//#######################################################################
//#									#
//#	get current y coordinate					#
//#									#
//#######################################################################
unsigned int glcd128ca_get_textpos_y(void);

//#######################################################################
//#									#
//#	draw pixel							#
//#									#
//#######################################################################
void glcd128ca_plot(unsigned int x,unsigned int y);

//#######################################################################
//#									#
//#	draw line							#
//#									#
//#######################################################################
void glcd128ca_draw(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

//#######################################################################
//#									#
//#	draw line to							#
//#									#
//#######################################################################
void glcd128ca_drawto(unsigned int x2,unsigned int y2);

//#######################################################################
//#									#
//#	draw box							#
//#									#
//#######################################################################
void glcd128ca_box(unsigned int x1,unsigned int y1,unsigned int dx,unsigned int dy);

//#######################################################################
//#									#
//#	draw filled box							#
//#									#
//#######################################################################
void glcd128ca_fbox(unsigned char x1,unsigned char y1,unsigned char dx,unsigned char dy);

//#######################################################################
//#									#
//#	draw sprite							#
//#									#
//#######################################################################
void glcd128ca_draw_sprite(unsigned char x,unsigned char y,unsigned char dx,unsigned char dy,unsigned int *buffer);

//#######################################################################
//#									#
//#	draw 8x8 sprite with bg						#
//#									#
//#######################################################################
void glcd128ca_draw_sprite_bg(unsigned char x,unsigned char y,unsigned int transp,unsigned int *buffer,unsigned int *background);

//#######################################################################
//#									#
//#	undraw 8x8 sprite with bg					#
//#									#
//#######################################################################
void glcd128ca_undraw_sprite_bg(unsigned char x,unsigned char y,unsigned int *background);

//#######################################################################
//#									#
//#	undraw 8x8 sprite with bg					#
//#									#
//#######################################################################
void glcd128ca_set_bg(unsigned char x,unsigned char y,unsigned char dx,unsigned char dy,unsigned int *background);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_glcd_mono/src/hilevel_glcd_mono/glcd.c
//---------------------------------------------------------------------------------------
extern volatile unsigned char *unilib_glcd_sdata;

//#######################################################################
//#									#
//#	wait for screeen sync						#
//#									#
//#######################################################################
void glcd_waitsync(void);

//#######################################################################
//#									#
//#	clear screen							#
//#									#
//#######################################################################
void glcd_clrscr(void);

//#######################################################################
//#									#
//#	set screen position						#
//#									#
//#######################################################################
void glcd_gotoxy(unsigned char x,unsigned char y);

//#######################################################################
//#									#
//#	new line							#
//#									#
//#######################################################################
void glcd_newline(void);

//#######################################################################
//#									#
//#	set wrapmode							#
//#									#
//#######################################################################
void glcd_wrapmode(void);

//#######################################################################
//#									#
//#	set scrollmode							#
//#									#
//#######################################################################
void glcd_scrollmode(void);

//#######################################################################
//#									#
//#	set color normal						#
//#									#
//#######################################################################
void glcd_set_color(unsigned char color);

//#######################################################################
//#									#
//#	get maximal x coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_drawsize_x(void);

//#######################################################################
//#									#
//#	get maximal y coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_drawsize_y(void);

//#######################################################################
//#									#
//#	get maximal x coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_textsize_x(void);

//#######################################################################
//#									#
//#	get maximal y coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_textsize_y(void);

//#######################################################################
//#									#
//#	get current x coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_drawpos_x(void);

//#######################################################################
//#									#
//#	get current y coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_drawpos_y(void);

//#######################################################################
//#									#
//#	get current x coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_textpos_x(void);

//#######################################################################
//#									#
//#	get current y coordinate					#
//#									#
//#######################################################################
unsigned int glcd_get_textpos_y(void);

//#######################################################################
//#									#
//#	write char							#
//#									#
//#######################################################################
void glcd_char(unsigned char data);

//#######################################################################
//#									#
//#	write char (raw mode)						#
//#									#
//#######################################################################
void glcd_char_raw(unsigned char data);

//#######################################################################
//#									#
//#	draw pixel							#
//#									#
//#######################################################################
void glcd_plot(unsigned int x,unsigned int y);

//#######################################################################
//#									#
//#	draw line							#
//#									#
//#######################################################################
void glcd_draw(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2);

//#######################################################################
//#									#
//#	draw line to							#
//#									#
//#######################################################################
void glcd_drawto(unsigned int x2,unsigned int y2);

//#######################################################################
//#									#
//#	draw box							#
//#									#
//#######################################################################
void glcd_box(unsigned int x1,unsigned int y1,unsigned int dx,unsigned int dy);

//#######################################################################
//#									#
//#	draw filled box							#
//#									#
//#######################################################################
void glcd_fbox(unsigned int x1,unsigned int y1,unsigned int dx,unsigned int dy);

//#######################################################################
//#									#
//#	draw 8x8 sprite							#
//#									#
//#######################################################################
void glcd_sprite(unsigned int px,unsigned int py,unsigned char *sdata);

//#######################################################################
//#									#
//#	show flash image						#
//#									#
//#######################################################################
void glcd_flash_image(unsigned char *image_data);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_glcd_mono/src/hilevel_glcd_mono/glcd128a.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	enable GLCD (unipolar mode)					#
//#									#
//#######################################################################
void init_glcd128a(PORT_TYPE dataport,PORT_TYPE ctrlport,unsigned char cs1pin,unsigned char cs2pin,unsigned char dipin,unsigned char epin);

//#######################################################################
//#									#
//#	set display contrast						#
//#									#
//#######################################################################
void glcd128a_set_contrast(unsigned char contrast);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_glcd128a(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_glcd_mono/src/hilevel_glcd_mono/glcd128b.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init display					#
//#									#
//#######################################################################
void init_glcd128b(PORT_TYPE dataport,PORT_TYPE ctrlport,unsigned char resetpin,unsigned char cspin,unsigned char rspin,unsigned char wrpin,unsigned char rdpin);

//#######################################################################
//#									#
//#	init display (without cs/rd)					#
//#									#
//#######################################################################
void init_glcd128b_minimal(PORT_TYPE dataport,PORT_TYPE ctrlport,unsigned char resetpin,unsigned char rspin,unsigned char wrpin);

//#######################################################################
//#									#
//#	set display contrast						#
//#									#
//#######################################################################
void glcd128b_set_contrast(unsigned char contrast);

//#######################################################################
//#									#
//#	switch display on						#
//#									#
//#######################################################################
void glcd128b_on(void);

//#######################################################################
//#									#
//#	switch display off						#
//#									#
//#######################################################################
void glcd128b_off(void);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_glcd128b(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_glcd_mono/src/hilevel_glcd_mono/glcd128c.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD (positive CS)						#
//#									#
//#######################################################################
void init_glcd128c(PORT_TYPE dataport,PORT_TYPE ctrlport,unsigned char cs1pin,unsigned char cs2pin,unsigned char dipin,unsigned char epin);

//#######################################################################
//#									#
//#	set display contrast						#
//#									#
//#######################################################################
void glcd128c_set_contrast(unsigned char contrast);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_glcd128c(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_hamming/src/hilevel_hamming/hamm4.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	hamming encode							#
//#									#
//#######################################################################
unsigned int encode_hamm4 (unsigned char value);

//#######################################################################
//#									#
//#	hamming decode	(results error count in upper byte)		#
//#									#
//#######################################################################
unsigned int decode_hamm4 (unsigned int value);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c01.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c01_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c01_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c01_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c02.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c02_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c02_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c02_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c04.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c04_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c04_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c04_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c08.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c08_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c08_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c08_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c128.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c128_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c128_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c128_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c16.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c16_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c16_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c16_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c256.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c256_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c256_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c256_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c32.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c32_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c32_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c32_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c512.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c512_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c512_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c512_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_i2c_eeprom/src/hilevel_i2c_eeprom/gen24c64.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char gen_24c32_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char gen_24c32_read(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char gen_24c32_write(unsigned char *buffer,unsigned int addr, int len, unsigned char devaddr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_ickeybd/src/hilevel_ickeybd/ickeyb.c
//---------------------------------------------------------------------------------------
//##################################################################################
//#
//#	get current key or 0xff if none pressed
//#
//##################################################################################
unsigned char ickbd12_getkey(void);

//##################################################################################
//#
//#	wait for key pressed
//#
//##################################################################################
unsigned char ickbd12_waitkey(void);

//##################################################################################
//#
//#	wait for no key is pressed
//#
//##################################################################################
void ickbd12_waitnokey(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_iclcd/src/hilevel_iclcd/iclcd.c
//---------------------------------------------------------------------------------------
extern unsigned char _iclcd_font;

extern unsigned char _iclcd_lwidth;

//###############################################################################
//#										#
//#	test if display is available (0/1)					#
//#										#
//###############################################################################
int iclcd_test(void);

//###############################################################################
//#										#
//#	clear screen with actual background color				#
//#										#
//###############################################################################
void iclcd_clear(void);

//###############################################################################
//#										#
//#	set color (foregroundg, background)					#
//#										#
//###############################################################################
void iclcd_set_color(unsigned char fg, unsigned char bg);

//###############################################################################
//#										#
//#	set text position							#
//#										#
//###############################################################################
void iclcd_set_textpos(unsigned char row, unsigned char col);

//###############################################################################
//#										#
//#	set last point								#
//#										#
//###############################################################################
void iclcd_set_graphpos(unsigned char y, unsigned char x);

//###############################################################################
//#										#
//#	plot a point								#
//#										#
//###############################################################################
void iclcd_plot(unsigned char y, unsigned char x);

//###############################################################################
//#										#
//#	draw line								#
//#										#
//###############################################################################
void iclcd_draw(unsigned char y1, unsigned char x1,unsigned char y2, unsigned char x2);

//###############################################################################
//#										#
//#	draw line from last point						#
//#										#
//###############################################################################
void iclcd_drawto(unsigned char y, unsigned char x);

//###############################################################################
//#										#
//#	draw filled box								#
//#										#
//###############################################################################
void iclcd_fbox(unsigned char y1, unsigned char x1,unsigned char y2, unsigned char x2);

//###############################################################################
//#										#
//#	draw ellipse								#
//#										#
//###############################################################################
void iclcd_ellipse(unsigned char y, unsigned char x,unsigned char ry, unsigned char rx);

//###############################################################################
//#										#
//#	set lcd font size (0..3)						#
//#										#
//###############################################################################
void iclcd_set_font(unsigned char font);

//###############################################################################
//#										#
//#	set line width for drawing (1..3)					#
//#										#
//###############################################################################
void iclcd_set_linewidth(unsigned char width);

//###############################################################################
//#										#
//#	lcd wakeup (display and backlight on)					#
//#										#
//###############################################################################
void iclcd_wake(void);

//###############################################################################
//#										#
//#	lcd sleep (display and backlight off)					#
//#										#
//###############################################################################
void iclcd_sleep(void);

//###############################################################################
//#										#
//#	my little printf							#
//#										#
//###############################################################################
void iclcd_printf (const char *format, ...);

//###############################################################################
//#										#
//#	output packed greyscale data line from buffer				#
//#										#
//###############################################################################
void iclcd_greyline(unsigned char line_number,unsigned char *buffer);

//###############################################################################
//#										#
//#	output packed color data line from buffer				#
//#										#
//###############################################################################
void iclcd_colorline(unsigned char line_number,unsigned char *buffer);

//###############################################################################
//#										#
//#	output rgb data line							#
//#										#
//###############################################################################
void iclcd_rgbline(unsigned char line_number,unsigned char *buffer);

//###############################################################################
//#										#
//#	set tile pattern							#
//#										#
//###############################################################################
void iclcd_tile_set(unsigned char tile_number,unsigned char *buffer);

//###############################################################################
//#										#
//#	fill tile solid								#
//#										#
//###############################################################################
void iclcd_tile_set_solid(unsigned char tile_number,unsigned char color);

//###############################################################################
//#										#
//#	add pre-defined pattern to tile						#
//#										#
//###############################################################################
void iclcd_tile_add_pattern(unsigned char tile_number,unsigned char pattern,unsigned char color);

//###############################################################################
//#										#
//#	add character from charset to tile					#
//#										#
//###############################################################################
void iclcd_tile_add_char(unsigned char tile_number,unsigned char tchar,unsigned char color);

//###############################################################################
//#										#
//#	copy a tile								#
//#										#
//###############################################################################
void iclcd_tile_copy(unsigned char dst_tile,unsigned char src_tile);

//###############################################################################
//#										#
//#	X-mirror a tile								#
//#										#
//###############################################################################
void iclcd_tile_mirror_x(unsigned char tile);

//###############################################################################
//#										#
//#	Y-mirror a tile								#
//#										#
//###############################################################################
void iclcd_tile_mirror_y(unsigned char tile);

//###############################################################################
//#										#
//#	rotate a tile CW							#
//#										#
//###############################################################################
void iclcd_tile_rotate_cw(unsigned char tile);

//###############################################################################
//#										#
//#	rotate a tile CCW							#
//#										#
//###############################################################################
void iclcd_tile_rotate_ccw(unsigned char tile);

//###############################################################################
//#										#
//#	invert a tile (negative color)						#
//#										#
//###############################################################################
void iclcd_tile_invert(unsigned char tile);

//###############################################################################
//#										#
//#	draw a sprite								#
//#										#
//###############################################################################
void iclcd_sprite_draw(	unsigned char tile,unsigned char backup_tile,unsigned char posy,unsigned char posx,unsigned char transp_color);

//###############################################################################
//#										#
//#	undraw a sprite (restore background)					#
//#										#
//###############################################################################
void iclcd_sprite_restore(unsigned char backup_tile,unsigned char posy,unsigned char posx);

//###############################################################################
//#										#
//#										#
//#										#
//###############################################################################
void iclcd_bigsprite_draw(unsigned char tile,unsigned char backup_tile,unsigned char posy,unsigned char posx,unsigned char transp_color);

//###############################################################################
//#										#
//#										#
//#										#
//###############################################################################
void iclcd_bigsprite_restore(unsigned char backup_tile,unsigned char posy,unsigned char posx);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_mdfs/src/hilevel_mdfs/mdfs.c
//---------------------------------------------------------------------------------------
extern int mdfs_internal_image_size;

//#######################################################################
//#									#
//#	init the file system						#
//#									#
//#######################################################################
void mdfs_init(int (*readfunct)(unsigned short, unsigned char*),int (*writefunct)(unsigned short, unsigned char*),int image_size);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_mlx90363/src/hilevel_mlx90363/mlx90363.c
//---------------------------------------------------------------------------------------
void mlx90363_comm(void);

//#######################################################################
//# reboot cmd								#
//#######################################################################
void mlx90363_reboot(void);

//#######################################################################
//# reboot cmd								#
//#######################################################################
void mlx90363_sleep(void);

//#######################################################################
//# init the mlx90363							#
//#######################################################################
char MLX90363_init(PORT_TYPE cs_port, unsigned char cs_pin);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_mlx90363/src/hilevel_mlx90363/mlx90363_xyz.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# read data block							#
//#######################################################################
char MLX90363_get_xyz(short *xval,short *yval,short *zval);

//#######################################################################
//# read data block							#
//#######################################################################
char MLX90363_wait_xyz(short *xval,short *yval,short *zval);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_rfm12/src/hilevel_rfm12/rfm12.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# set channel								#
//#######################################################################
void rfm12_set_channel(int channel);

//#######################################################################
//# send a byte								#
//#######################################################################
void rfm12_byte_send(unsigned char data);

//#######################################################################
//# send a hamming coded byte						#
//#######################################################################
void rfm12_hamm_send(unsigned char data);

//#######################################################################
//# reveive a byte							#
//#######################################################################
unsigned char rfm12_byte_recv(void);

//#######################################################################
//# get hamming coded byte						#
//#######################################################################
unsigned char rfm12_hamm_recv(void);

//#######################################################################
//# init the RFM12 (default 869,4MHz)					#
//#######################################################################
void rfm12_init_433(unsigned char cs_port, unsigned char cs_pin);

//#######################################################################
//# init the RFM12 (default 869,4MHz)					#
//#######################################################################
void rfm12_init_868(unsigned char cs_port, unsigned char cs_pin);

//#######################################################################
//# send a packet							#
//#######################################################################
void rfm12_send(unsigned char *txBuffer,unsigned char len,unsigned char addr);

//#######################################################################
//# receive a packet							#
//#######################################################################
unsigned char rfm12_recv(unsigned char *rxBuffer,unsigned char len,unsigned char addr);

//#######################################################################
//# sleep								#
//#######################################################################
void rfm12_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
void rfm12_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_rtc/src/hilevel_rtc/convert.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# convert date/time structure to unix stamp				#
//#######################################################################
unsigned char get_max_day(unsigned short year, unsigned char month);

//#######################################################################
//# convert unix timestamp to date/time structure			#
//#######################################################################
void unix2date(unsigned long stamp, unilib_date_time *tr);

//#######################################################################
//# convert date/time structure to unix stamp				#
//#######################################################################
unsigned long date2unix(unilib_date_time *tr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_rtc/src/hilevel_rtc/pcf8583.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# ckeck presence							#
//#######################################################################
unsigned char pcf8583_check(unsigned char devaddr);

//#######################################################################
//# read bytes								#
//#######################################################################
unsigned char pcf8583_read(unsigned char *buffer,unsigned char addr, int len, unsigned char devaddr);

//#######################################################################
//# write bytes								#
//#######################################################################
unsigned char pcf8583_write(unsigned char *buffer,unsigned char addr, int len, unsigned char devaddr);

//#######################################################################
//# read seconds							#
//#######################################################################
int pcf8583_get_sec(unsigned char devaddr);

//#######################################################################
//# read minutes							#
//#######################################################################
int pcf8583_get_min(unsigned char devaddr);

//#######################################################################
//# read hour								#
//#######################################################################
int pcf8583_get_hour(unsigned char devaddr);

//#######################################################################
//# read day								#
//#######################################################################
int pcf8583_get_day(unsigned char devaddr);

//#######################################################################
//# read weekday							#
//#######################################################################
int pcf8583_get_wday(unsigned char devaddr);

//#######################################################################
//# read month								#
//#######################################################################
int pcf8583_get_month(unsigned char devaddr);

//#######################################################################
//# read month								#
//#######################################################################
int pcf8583_get_year(unsigned char devaddr);

//#######################################################################
//# set time								#
//#######################################################################
int pcf8583_set_sec(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set minutes								#
//#######################################################################
int pcf8583_set_min(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set hours								#
//#######################################################################
int pcf8583_set_hour(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set day								#
//#######################################################################
int pcf8583_set_day(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set weekday								#
//#######################################################################
int pcf8583_set_wday(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set month								#
//#######################################################################
int pcf8583_set_month(unsigned char devaddr, unsigned char val);

//#######################################################################
//# set year								#
//#######################################################################
int pcf8583_set_year(unsigned char devaddr, unsigned char val);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_rtc/src/hilevel_rtc/xrtc.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# init the RTC interface						#
//#######################################################################
void xrtc_init(PORT_TYPE cport,unsigned char cpin,PORT_TYPE dport,unsigned char dpin);

//#######################################################################
//# get current date/time						#
//# param: regnum (0-15)						#
//# result: 32 bit data							#
//#######################################################################
unsigned long xrtc_read_register(unsigned char reg);

//#######################################################################
//# write register value						#
//# param: regnum (0-15), 32 bit data					#
//#######################################################################
void xrtc_write_register(unsigned char reg,unsigned long value);

//#######################################################################
//# get current date/time						#
//# result: 32 bit timestamp						#
//#######################################################################
unsigned long xrtc_get_date(void);

//#######################################################################
//# set current date/time						#
//# param: 32 bit timestamp						#
//#######################################################################
void xrtc_set_date(unsigned long date);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_sdcard/src/hilevel_sdcard/sdcard.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# send a command							#
//#######################################################################
unsigned char sdcard_cmd(unsigned char cmd, unsigned long addr, unsigned char crc);

//#######################################################################
//# init the sdcard							#
//# this must be done with low speed					#
//# 0 = no card / failure						#
//# 
//#######################################################################
unsigned char sdcard_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read status								#
//# 0=busy, 1=ready							#
//#######################################################################
unsigned char sdcard_read_status(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char sdcard_read_sector(unsigned char *buffer,unsigned long sector);

//#######################################################################
//# read data block word wise						#
//#######################################################################
unsigned char sdcard_read_sector_ww(unsigned short *buffer,unsigned long sector);

//#######################################################################
//# read data block longword wise					#
//#######################################################################
unsigned char sdcard_read_sector_lw(unsigned long *buffer,unsigned long sector);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char sdcard_write_sector(unsigned char *buffer,unsigned long sector);

//#######################################################################
//# write data block word wise						#
//#######################################################################
unsigned char sdcard_write_sector_ww(unsigned short *buffer,unsigned long sector);

//#######################################################################
//# write data block word wise						#
//#######################################################################
unsigned char sdcard_write_sector_lw(unsigned long *buffer,unsigned long sector);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiflash/src/hilevel_spiflash/m25p16.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char m25p16_checkid(void);

//#######################################################################
//# init the m25p16							#
//#######################################################################
unsigned char m25p16_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//#######################################################################
unsigned char m25p16_read_status(void);

//#######################################################################
//# wait for device is ready						#
//#######################################################################
unsigned char m25p16_wait_ready(unsigned long timeout);

//#######################################################################
//# checx for ready (0=ready  1=busy)					#
//#######################################################################
unsigned char m25p16_check_ready(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char m25p16_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char m25p16_write_page(unsigned char *buffer,unsigned long addr,unsigned char blocked);

//#######################################################################
//# erase 64K sector							#
//#######################################################################
unsigned char m25p16_erase_sector(unsigned long addr, unsigned char blocked);

//#######################################################################
//# bulk erase								#
//#######################################################################
unsigned char m25p16_erase_bulk(unsigned char blocked);

//#######################################################################
//# sleep								#
//#######################################################################
unsigned char m25p16_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
unsigned char m25p16_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiflash/src/hilevel_spiflash/m25p32.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char m25p32_checkid(void);

//#######################################################################
//# init the m25p32							#
//#######################################################################
unsigned char m25p32_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//#######################################################################
unsigned char m25p32_read_status(void);

//#######################################################################
//# wait for device is ready						#
//#######################################################################
unsigned char m25p32_wait_ready(unsigned long timeout);

//#######################################################################
//# checx for ready (0=ready  1=busy)					#
//#######################################################################
unsigned char m25p32_check_ready(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char m25p32_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char m25p32_write_page(unsigned char *buffer,unsigned long addr,unsigned char blocked);

//#######################################################################
//# erase 64K sector							#
//#######################################################################
unsigned char m25p32_erase_sector(unsigned long addr, unsigned char blocked);

//#######################################################################
//# bulk erase								#
//#######################################################################
unsigned char m25p32_erase_bulk(unsigned char blocked);

//#######################################################################
//# sleep								#
//#######################################################################
unsigned char m25p32_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
unsigned char m25p32_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiflash/src/hilevel_spiflash/m25p64.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char m25p64_checkid(void);

//#######################################################################
//# init the m25p64							#
//#######################################################################
unsigned char m25p64_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//#######################################################################
unsigned char m25p64_read_status(void);

//#######################################################################
//# wait for device is ready						#
//#######################################################################
unsigned char m25p64_wait_ready(unsigned long timeout);

//#######################################################################
//# checx for ready (0=ready  1=busy)					#
//#######################################################################
unsigned char m25p64_check_ready(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char m25p64_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char m25p64_write_page(unsigned char *buffer,unsigned long addr,unsigned char blocked);

//#######################################################################
//# erase 64K sector							#
//#######################################################################
unsigned char m25p64_erase_sector(unsigned long addr, unsigned char blocked);

//#######################################################################
//# bulk erase								#
//#######################################################################
unsigned char m25p64_erase_bulk(unsigned char blocked);

//#######################################################################
//# sleep								#
//#######################################################################
unsigned char m25p64_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
unsigned char m25p64_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiflash/src/hilevel_spiflash/m25p80.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char m25p80_checkid(void);

//#######################################################################
//# init the m25p80							#
//#######################################################################
unsigned char m25p80_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//#######################################################################
unsigned char m25p80_read_status(void);

//#######################################################################
//# wait for device is ready						#
//#######################################################################
unsigned char m25p80_wait_ready(unsigned long timeout);

//#######################################################################
//# checx for ready (0=ready  1=busy)					#
//#######################################################################
unsigned char m25p80_check_ready(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char m25p80_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char m25p80_write_page(unsigned char *buffer,unsigned long addr,unsigned char blocked);

//#######################################################################
//# erase 64K sector							#
//#######################################################################
unsigned char m25p80_erase_sector(unsigned long addr, unsigned char blocked);

//#######################################################################
//# bulk erase								#
//#######################################################################
unsigned char m25p80_erase_bulk(unsigned char blocked);

//#######################################################################
//# sleep								#
//#######################################################################
unsigned char m25p80_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
unsigned char m25p80_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiflash/src/hilevel_spiflash/w25q128.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# check device ID							#
//#######################################################################
unsigned char w25q128_checkid(void);

//#######################################################################
//# init the w25q128							#
//#######################################################################
unsigned char w25q128_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read ststus byte							#
//#######################################################################
unsigned char w25q128_read_status(void);

//#######################################################################
//# wait for device is ready						#
//#######################################################################
unsigned char w25q128_wait_ready(unsigned long timeout);

//#######################################################################
//# checx for ready (0=ready  1=busy)					#
//#######################################################################
unsigned char w25q128_check_ready(void);

//#######################################################################
//# read data block							#
//#######################################################################
unsigned char w25q128_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
unsigned char w25q128_write_page(unsigned char *buffer,unsigned long addr,unsigned char blocked);

//#######################################################################
//# erase 64K sector							#
//#######################################################################
unsigned char w25q128_erase_sector(unsigned long addr, unsigned char blocked);

//#######################################################################
//# erase 4K sector							#
//#######################################################################
unsigned char w25q128_erase_sector4k(unsigned long addr, unsigned char blocked);

//#######################################################################
//# bulk erase								#
//#######################################################################
unsigned char w25q128_erase_bulk(unsigned char blocked);

//#######################################################################
//# sleep								#
//#######################################################################
unsigned char w25q128_sleep(void);

//#######################################################################
//# wakeup								#
//#######################################################################
unsigned char w25q128_wakeup(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_spiram/src/hilevel_spiram/xsram.c
//---------------------------------------------------------------------------------------
//#######################################################################
//# init the xsram							#
//#######################################################################
void xsram_init(PORT_TYPE cs_port, unsigned char cs_pin);

//#######################################################################
//# read data block							#
//#######################################################################
void xsram_read_block(unsigned char *buffer,unsigned long addr, unsigned long len);

//#######################################################################
//# write data block							#
//#######################################################################
void xsram_write_block(unsigned char *buffer,unsigned long addr, unsigned long len);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/abs.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# integer absolute value (magnitude)					#
//#									#
//#######################################################################
int abs (int i);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/atof.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# ascii to long							#
//#									#
//#######################################################################
float atof(const char *s);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/atoi.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# ascii to integer							#
//#									#
//#######################################################################
int atoi(const char *s);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/atol.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# ascii to long							#
//#									#
//#######################################################################
long atol(const char *s);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/div.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# divide two integers							#
//#									#
//#######################################################################

//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/index.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# search for character in string					#
//#									#
//#######################################################################
char * index(char *s1, int i);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/isalpha.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# check if char is a alphabetic letter				#
//#									#
//#######################################################################
int isalpha(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/isdigit.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# check if char is a digit						#
//#									#
//#######################################################################
int isdigit(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/islower.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# check if char is lowercase						#
//#									#
//#######################################################################
int islower(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/isspace.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# check if char is a whitespace					#
//#									#
//#######################################################################
int isspace(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/isupper.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# check if char is uppercase						#
//#									#
//#######################################################################
int isupper(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/itoa.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# integer to ascii							#
//#									#
//#######################################################################
char * itoa(int value, char *ptr, int base);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/ldiv.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# divide two long integers						#
//#									#
//#######################################################################

//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memccpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy memory regions with end-token check				#
//#									#
//#######################################################################
void * memccpy(void * dst0, const void * src0, int endchar0, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memchr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# find character in memory						#
//#									#
//#######################################################################
void * memchr(const void *ptr,int value,size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memcmp.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two memory areas						#
//#									#
//#######################################################################
int memcmp(void *ptr1,void *ptr2,size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memcpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy memory regions							#
//#									#
//#######################################################################
void * memcpy(void * dst0,const void * src0,size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memmove.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two strings							#
//#									#
//#######################################################################
void * memmove(void * dst0,const void * src0, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/memset.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# set an area of memory						#
//#									#
//#######################################################################
void * memset(void * ptr,int value,size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/rindex.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# reverse search for character in string				#
//#									#
//#######################################################################
char * rindex(char *s1, int i);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/stpcpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy string	and return a pointer to its end				#
//#									#
//#######################################################################
char* stpcpy(char *dst0, char *src0);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/stpncpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy string	and return a pointer to its end				#
//#									#
//#######################################################################
char* stpncpy(char *dst0, char *src0,size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcasecmp.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two strings and ignore case					#
//#									#
//#######################################################################
int strcasecmp(char *s1, char *s2);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcasestr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# find string segment and ignore case					#
//#									#
//#######################################################################
char * strcasestr(char *haystack, char *needle);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcat.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# concatenate two strings						#
//#									#
//#######################################################################
char * strcat(char *dst, const char *src);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strchr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# search for character in string					#
//#									#
//#######################################################################
char * strchr(const char *s1, int i);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcmp.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two strings							#
//#									#
//#######################################################################
int strcmp(const char *s1, const char *s2);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy string								#
//#									#
//#######################################################################
char* strcpy(char *dst0, const char *src0);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strcspn.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# count characters not in string					#
//#									#
//#######################################################################
size_t strcspn(const char *s1,const char *s2);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strlen.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# determine lenght of a string					#
//#									#
//#######################################################################
size_t strlen (const char *str);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strlwr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# force string to lowercase						#
//#									#
//#######################################################################
char * strlwr (char * s);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strncasecmp.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two strings and ignore case					#
//#									#
//#######################################################################
int strncasecmp(char *s1, char *s2, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strncat.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# concatenate two strings						#
//#									#
//#######################################################################
char * strncat(char *s1, const char *s2, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strncmp.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# compare two strings							#
//#									#
//#######################################################################
int strncmp(const char *s1, const char *s2, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strncpy.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# copy string								#
//#									#
//#######################################################################
char* strncpy(char *dst0, const char *src0, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strnlen.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# determine lenght of a string					#
//#									#
//#######################################################################
size_t strnlen (const char *str, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strpbrk.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# find characters in string						#
//#									#
//#######################################################################
char * strpbrk(const char *s1, const char *s2);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strrchr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# reverse search for character in string				#
//#									#
//#######################################################################
char * strrchr(const char *s1, int i);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strspn.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# find initial match							#
//#									#
//#######################################################################
size_t strspn(const char *s1, const char *s2);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strstr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# find string segment							#
//#									#
//#######################################################################
char * strstr(const char *haystack, const char *needle);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strtof.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# Convert a string to a float						#
//#									#
//#######################################################################
float strtof (const char *ptr, char** endptr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strtok.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# split string into tokens						#
//#									#
//#######################################################################
char * strtok(char *str, const char *delimiters);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strtol.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# Convert a string to a long integer.					#
//#									#
//#######################################################################
long strtol (const char *ptr, char** endptr);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/strupr.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# force string to uppercase						#
//#									#
//#######################################################################
char * strupr (char * s);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/swab.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# swap adjacent bytes							#
//#									#
//#######################################################################
void swab(void *src0, void *dst0, size_t num);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/tolower.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# convert char to lowercase						#
//#									#
//#######################################################################
char tolower(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/toupper.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# convert char to uppercase						#
//#									#
//#######################################################################
char toupper(char c);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stdlib/src/hilevel_stdlib/utoa.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# unsigned integer to string						#
//#									#
//#######################################################################
char * utoa(unsigned int value, char * str, int base);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_stepper/src/hilevel_stepper/stepper_unipolar.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	enable stepper (unipolar mode)					#
//#									#
//#######################################################################
void enable_stepper(int stepper,PORT_TYPE port,int pina,int pinb,int pinc,int pind);

//#######################################################################
//#									#
//#	reset stepper							#
//#									#
//#######################################################################
void reset_stepper(int stepper);

//#######################################################################
//#									#
//#	move stepper							#
//#									#
//#######################################################################
void move_stepper(int stepper,int stepper_steps,int stepper_scale);

//#######################################################################
//#									#
//#	wait for move end						#
//#									#
//#######################################################################
void wait_stepper(void);

//#######################################################################
//#									#
//#	check stepper (1=move0, 2=move1)				#
//#									#
//#######################################################################
int check_stepper(void);

//#######################################################################
//#									#
//#	this must be called periodicly (in interrupt)			#
//#									#
//#######################################################################
void serve_stepper(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	wait for screeen sync						#
//#									#
//#######################################################################
void tlcd_waitsync(void);

//#######################################################################
//#									#
//#	clear screen							#
//#									#
//#######################################################################
void tlcd_clrscr(void);

//#######################################################################
//#									#
//#	set screen position						#
//#									#
//#######################################################################
void tlcd_gotoxy(unsigned char x,unsigned char y);

//#######################################################################
//#									#
//#	new line							#
//#									#
//#######################################################################
void tlcd_newline(void);

//#######################################################################
//#									#
//#	set wrapmode							#
//#									#
//#######################################################################
void tlcd_wrapmode(void);

//#######################################################################
//#									#
//#	set scrollmode							#
//#									#
//#######################################################################
void tlcd_scrollmode(void);

//#######################################################################
//#									#
//#	get maximal x coordinate					#
//#									#
//#######################################################################
unsigned int tlcd_get_textsize_x(void);

//#######################################################################
//#									#
//#	get maximal y coordinate					#
//#									#
//#######################################################################
unsigned int tlcd_get_textsize_y(void);

//#######################################################################
//#									#
//#	get current x coordinate					#
//#									#
//#######################################################################
unsigned int tlcd_get_textpos_x(void);

//#######################################################################
//#									#
//#	get current y coordinate					#
//#									#
//#######################################################################
unsigned int tlcd_get_textpos_y(void);

//#######################################################################
//#									#
//#	write char							#
//#									#
//#######################################################################
void tlcd_char(unsigned char data);

//#######################################################################
//#									#
//#	write char (raw mode)						#
//#									#
//#######################################################################
void tlcd_user_char(unsigned char num,unsigned char* pixline);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_16_1.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd161(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd161(void);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd161b(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_16_2.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd162(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd162(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_16_4.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd164(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd164(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_20_2.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd202(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd202(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_20_4.c
//---------------------------------------------------------------------------------------
extern volatile unsigned char unilib_tlcd204_dpos;

//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd204(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd204(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_40_2.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd402(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd402(void);


//---------------------------------------------------------------------------------------
// exports from src/hilevel_tlcd/src/hilevel_tlcd/tlcd_40_4.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init LCD							#
//#									#
//#######################################################################
void init_tlcd404(PORT_TYPE dataport,unsigned char d4pin,unsigned char d5pin,unsigned char d6pin,unsigned char d7pin,PORT_TYPE ctrlport,unsigned char rspin,unsigned char epin1,unsigned char epin2);

//#######################################################################
//#									#
//#	service								#
//#									#
//#######################################################################
void serve_tlcd404(void);


//---------------------------------------------------------------------------------------
// exports from src/src_romtables/src/src_romtables/hamm4_rtable.c
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// exports from src/src_stdlib/src/src_stdlib/abort.c
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// exports from src/src_stdlib/src/src_stdlib/outchar.c
//---------------------------------------------------------------------------------------
extern unsigned char *memptr;

//#######################################################################
//#									#
//#	set printf channel						#
//#									#
//#######################################################################
void set_outchar_routine(void (*outfunc)(unsigned char));

//#######################################################################
//#									#
//#	dummy output							#
//#									#
//#######################################################################
void OUTPUT_NONE(unsigned char c);

//#######################################################################
//#									#
//#	memory output							#
//#									#
//#######################################################################
void OUTPUT_MEMORY(unsigned char c);

//#######################################################################
//#									#
//#	memory output							#
//#									#
//#######################################################################
void set_outchar_memory(unsigned char *c);


//---------------------------------------------------------------------------------------
// exports from src/src_stdlib/src/src_stdlib/uprintf.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	get printf channel						#
//#									#
//#######################################################################
void uprintf (const char *format, ...);


//---------------------------------------------------------------------------------------
// exports from src/src_stdlib/src/src_stdlib/uxprintf.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	get printf channel						#
//#									#
//#######################################################################
void uxprintf (const char *format, ...);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/rotate_buffer.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//# rotate 8x8 buffer for glcd						#
//#									#
//#######################################################################
void unilib_rotate_buffer8(unsigned char * src,unsigned char *dst);

//#######################################################################
//#									#
//# rotate 8x8 buffer for glcd						#
//#									#
//#######################################################################
void unilib_rotate_buffer8a(unsigned char * src,unsigned char *dst);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib.c
//---------------------------------------------------------------------------------------
extern int mylib_uart_stat;

extern volatile unsigned char unilib_cpu_freq;

extern volatile unsigned char unilib_this_core;

//#######################################################################
//#									#
//# init the unilib infrastructure					#
//#									#
//#######################################################################
void unilib_init(void);

//#######################################################################
//#									#
//# init the unilib infrastructure					#
//#									#
//#######################################################################
void unilib_init_core1(void);

//#######################################################################
//#									#
//# init the unilib infrastructure for core 2				#
//#									#
//#######################################################################
void unilib_init_core2(void);

//#######################################################################
//#									#
//# start core 2 and wait until its running				#
//#									#
//#######################################################################
void unilib_start_core2(void);

//#######################################################################
//#									#
//#	set FMPLL for 8/16M crystal					#
//#									#
//#######################################################################
void set_clock(unsigned int mode);

//#######################################################################
//#									#
//#	set clock							#
//#									#
//#######################################################################
void set_clock_core2(unsigned int mode);

//#######################################################################
//#									#
//#	trim int osc							#
//#									#
//#######################################################################
void trim_clock(int val);

//#######################################################################
//#									#
//#	wait n cycles							#
//#									#
//#######################################################################
void unilib_pause(long cycles);

//#######################################################################
//#									#
//#	wait n millisecs						#
//#									#
//#######################################################################
void unilib_pause_ms(unsigned int ms);

//#######################################################################
//#									#
//# enable interrupts global						#
//#									#
//#######################################################################
void enable_interrupts(void);

//#######################################################################
//#									#
//# disable interrupts global						#
//#									#
//#######################################################################
void disable_interrupts(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_adc.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init ADC (max 8 channels)					#
//#									#
//#######################################################################
void init_adc(unsigned char mask);

//#######################################################################
//#									#
//#	disable ADC							#
//#									#
//#######################################################################
void disable_adc(void);

//#######################################################################
//#									#
//#	disable tick interrupt						#
//#									#
//#######################################################################
unsigned int get_adc(unsigned char channel);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_extint0.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init SPI as master						#
//#									#
//#######################################################################
void enable_ext_int0(unsigned char mode,unsigned char pin);

//#######################################################################
//#									#
//#	init SPI as slave						#
//#									#
//#######################################################################
void disable_ext_int0(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_extint1.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init SPI as master						#
//#									#
//#######################################################################
void enable_ext_int0(unsigned char mode,unsigned char pin);

//#######################################################################
//#									#
//#	init SPI as slave						#
//#									#
//#######################################################################
void disable_ext_int0(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexcan0.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	enable CAN							#
//#									#
//#######################################################################
void enable_can0(unsigned long divider);

//#######################################################################
//#									#
//#	disable CAN							#
//#									#
//#######################################################################
void disable_can0(void);

//#######################################################################
//#									#
//#	transmitter check (0=empty, 1...=frame(s) pending)		#
//#									#
//#######################################################################
unsigned char tcheck_can0(void);

//#######################################################################
//#									#
//#	send frame							#
//#									#
//#	byte 0:		identifier LOW					#
//#	byte 1:		identifier HIGH					#
//#	byte 2:		type (normal=0, RTR=1)				#
//#	byte 3:		length						#
//#	byte 4..:	data						#
//#									#
//#######################################################################
unsigned char send_can0(unilib_can_frame txdata, unsigned int block);

//#######################################################################
//#									#
//#	abort								#
//#									#
//#######################################################################
void abort_can0(void);

//#######################################################################
//#									#
//#	set filter							#
//#									#
//#######################################################################
void setfilter_can0(unsigned int filter,unsigned long id, unsigned long mask, unsigned char mode);

//#######################################################################
//#									#
//#	receiver check (0=empty, 1=frame received)			#
//#									#
//#######################################################################
long rcheck_can0(void);

//#######################################################################
//#									#
//#	get frame							#
//#									#
//#	byte 0:		identifier LOW					#
//#	byte 1:		identifier HIGH					#
//#	byte 2:		type (normal=0, RTR=1)				#
//#	byte 3:		length						#
//#	byte 4..:	data						#
//#									#
//#######################################################################
unsigned char get_can0(unilib_can_frame *rxdata_in);

//#######################################################################
//#									#
//#	discard messages						#
//#									#
//#######################################################################
void discard_can0(void);

//#######################################################################
//#									#
//#	enable RX int							#
//#									#
//#######################################################################
void enable_can0_rxint(void);

//#######################################################################
//#									#
//#	enable RX int							#
//#									#
//#######################################################################
void reenable_can0_rxint(void);

//#######################################################################
//#									#
//#	disable RX int							#
//#									#
//#######################################################################
void disable_can0_rxint(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexcan1.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	enable CAN							#
//#									#
//#######################################################################
void enable_can1(unsigned long divider);

//#######################################################################
//#									#
//#	disable CAN							#
//#									#
//#######################################################################
void disable_can1(void);

//#######################################################################
//#									#
//#	transmitter check (0=empty, 1...=frame(s) pending)		#
//#									#
//#######################################################################
unsigned char tcheck_can1(void);

//#######################################################################
//#									#
//#	send frame							#
//#									#
//#	byte 0:		identifier LOW					#
//#	byte 1:		identifier HIGH					#
//#	byte 2:		type (normal=0, RTR=1)				#
//#	byte 3:		length						#
//#	byte 4..:	data						#
//#									#
//#######################################################################
unsigned char send_can1(unilib_can_frame txdata, unsigned int block);

//#######################################################################
//#									#
//#	abort								#
//#									#
//#######################################################################
void abort_can1(void);

//#######################################################################
//#									#
//#	set filter							#
//#									#
//#######################################################################
void setfilter_can1(unsigned int filter,unsigned long id, unsigned long mask, unsigned char mode);

//#######################################################################
//#									#
//#	receiver check (0=empty, 1=frame received)			#
//#									#
//#######################################################################
long rcheck_can1(void);

//#######################################################################
//#									#
//#	get frame							#
//#									#
//#	byte 0:		identifier LOW					#
//#	byte 1:		identifier HIGH					#
//#	byte 2:		type (normal=0, RTR=1)				#
//#	byte 3:		length						#
//#	byte 4..:	data						#
//#									#
//#######################################################################
unsigned char get_can1(unilib_can_frame *rxdata_in);

//#######################################################################
//#									#
//#	discard messages						#
//#									#
//#######################################################################
void discard_can1(void);

//#######################################################################
//#									#
//#	enable RX int							#
//#									#
//#######################################################################
void enable_can1_rxint(void);

//#######################################################################
//#									#
//#	enable RX int							#
//#									#
//#######################################################################
void reenable_can1_rxint(void);

//#######################################################################
//#									#
//#	disable RX int							#
//#									#
//#######################################################################
void disable_can1_rxint(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexpwm0_sub0.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm0(unsigned long scale);

//#######################################################################
//#									#
//#	enable PWM0 (A0)						#
//#									#
//#######################################################################
void enable_pwm0a(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1 (B0)						#
//#									#
//#######################################################################
void enable_pwm0b(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm0a(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm0b(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm0a(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm0b(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexpwm0_sub1.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm1(unsigned long scale);

//#######################################################################
//#									#
//#	enable PWM0 (A0)						#
//#									#
//#######################################################################
void enable_pwm1a(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1 (B0)						#
//#									#
//#######################################################################
void enable_pwm1b(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm1a(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm1b(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm1a(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm1b(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexpwm0_sub2.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm2(unsigned long scale);

//#######################################################################
//#									#
//#	enable PWM0 (A0)						#
//#									#
//#######################################################################
void enable_pwm2a(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1 (B0)						#
//#									#
//#######################################################################
void enable_pwm2b(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm2a(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm2b(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm2a(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm2b(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_flexpwm0_sub3.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm3(unsigned long scale);

//#######################################################################
//#									#
//#	enable PWM0 (A0)						#
//#									#
//#######################################################################
void enable_pwm3a(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1 (B0)						#
//#									#
//#######################################################################
void enable_pwm3b(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm3a(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm3b(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm3a(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm3b(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_i2c.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init I2C (0=slow, 1=fast)					#
//#									#
//#######################################################################
void enable_i2c_master(unsigned char mode);

//#######################################################################
//#									#
//#	disable I2C							#
//#									#
//#######################################################################
void disable_i2c(void);

//#######################################################################
//#									#
//#	send start condition						#
//#									#
//#######################################################################
unsigned char i2c_start(void);

//#######################################################################
//#									#
//#	repeated send start condition					#
//#									#
//#######################################################################
unsigned char i2c_rstart(void);

//#######################################################################
//#									#
//#	send stop condition						#
//#									#
//#######################################################################
unsigned char i2c_stop(void);

//#######################################################################
//#									#
//#	send data							#
//#									#
//#######################################################################
unsigned char i2c_master_send(unsigned char data);

//#######################################################################
//#									#
//#	read data							#
//#									#
//#######################################################################
unsigned char i2c_master_recv(unsigned char ack);

//#######################################################################
//#									#
//#	send address							#
//#									#
//#######################################################################
unsigned char i2c_master_addr(unsigned char address);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_interrupts.c
//---------------------------------------------------------------------------------------
extern volatile unsigned int unilib_tick_counter;


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_nvmdata.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	enable internal data storage					#
//#									#
//#######################################################################
unsigned int enable_nvmdata(void);

//#######################################################################
//#									#
//#	erase internal data storage					#
//#									#
//#######################################################################
void erase_nvmdata(void);

//#######################################################################
//#									#
//#	write long to eeprom						#
//#									#
//#######################################################################
void nvmdata_write(unsigned int addr, unsigned long data);

//#######################################################################
//#									#
//#	read long from eeprom						#
//#									#
//#######################################################################
unsigned long nvmdata_read(unsigned int addr);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_portio.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	set port to output						#
//#									#
//#######################################################################
void set_port_output(int port);

//#######################################################################
//#									#
//#	set port to to input without pullup				#
//#									#
//#######################################################################
void set_port_input_nopull(int port);

//#######################################################################
//#									#
//#	set port to to input without pullup				#
//#									#
//#######################################################################
void set_port_input_pullup(int port);

//#######################################################################
//#									#
//#	get port value							#
//#									#
//#######################################################################
unsigned short get_port_level(int port);

//#######################################################################
//#									#
//#	set port value							#
//#									#
//#######################################################################
void set_port_level(int port,unsigned int val);

//#######################################################################
//#									#
//#	set port bits							#
//#									#
//#######################################################################
void set_port_one(int port,unsigned short mask);

//#######################################################################
//#									#
//#	set port bits							#
//#									#
//#######################################################################
void set_port_ZERO(int port,unsigned short mask);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_portio_pin.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	set port pin to output						#
//#									#
//#######################################################################
void set_portpin_output(int port,int pin);

//#######################################################################
//#									#
//#	set port pin to input without pullup				#
//#									#
//#######################################################################
void set_portpin_input_nopull(int port,int pin);

//#######################################################################
//#									#
//#	set port pin to input with pullup				#
//#									#
//#######################################################################
void set_portpin_input_pullup(int port,int pin);

//#######################################################################
//#									#
//#	set port pin to one						#
//#									#
//#######################################################################
void set_portpin_one(int port,int pin);

//#######################################################################
//#									#
//#	set port pin to zero						#
//#									#
//#######################################################################
void set_portpin_zero(int port,int pin);

//#######################################################################
//#									#
//#	set port pin status						#
//#									#
//#######################################################################
void set_portpin_level(int port,int pin,int val);

//#######################################################################
//#									#
//#	get port pin value						#
//#									#
//#######################################################################
int get_portpin_level(int port,int pin);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_pwm0.c
//---------------------------------------------------------------------------------------
extern volatile unsigned int pwm_scale;

extern volatile unsigned int pwm_active;

//#######################################################################
//#									#
//#	scale PWM0-PWM3							#
//#									#
//#######################################################################
void scale_pwm03(unsigned int scale);

//#######################################################################
//#									#
//#	enable PWM0							#
//#									#
//#######################################################################
void enable_pwm0(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1							#
//#									#
//#######################################################################
void enable_pwm1(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM2							#
//#									#
//#######################################################################
void enable_pwm2(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM3							#
//#									#
//#######################################################################
void enable_pwm3(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm0(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm1(unsigned long value);

//#######################################################################
//#									#
//#	set PWM2 value							#
//#									#
//#######################################################################
void set_pwm2(unsigned long value);

//#######################################################################
//#									#
//#	set PWM3 value							#
//#									#
//#######################################################################
void set_pwm3(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm0(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm1(void);

//#######################################################################
//#									#
//#	disable PWM2							#
//#									#
//#######################################################################
void disable_pwm2(void);

//#######################################################################
//#									#
//#	disable PWM3							#
//#									#
//#######################################################################
void disable_pwm3(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_pwm0_flex.c
//---------------------------------------------------------------------------------------
extern volatile unsigned int pwm_scale;

extern volatile unsigned int pwm_active;

//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm03(unsigned int scale);

//#######################################################################
//#									#
//#	enable PWM0							#
//#									#
//#######################################################################
void enable_pwm0(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1							#
//#									#
//#######################################################################
void enable_pwm1(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM2							#
//#									#
//#######################################################################
void enable_pwm2(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM3							#
//#									#
//#######################################################################
void enable_pwm3(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm0(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm1(unsigned long value);

//#######################################################################
//#									#
//#	set PWM2 value							#
//#									#
//#######################################################################
void set_pwm2(unsigned long value);

//#######################################################################
//#									#
//#	set PWM3 value							#
//#									#
//#######################################################################
void set_pwm3(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm0(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm1(void);

//#######################################################################
//#									#
//#	disable PWM2							#
//#									#
//#######################################################################
void disable_pwm2(void);

//#######################################################################
//#									#
//#	disable PWM3							#
//#									#
//#######################################################################
void disable_pwm3(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_pwm0_flex1.c
//---------------------------------------------------------------------------------------
extern volatile unsigned int pwm_scale;

extern volatile unsigned int pwm_active;

extern volatile unsigned int pwm_prescale; 

//#######################################################################
//#									#
//#	scale pwm timer							#
//#									#
//#######################################################################
void scale_pwm(unsigned long scale);

//#######################################################################
//#									#
//#	enable PWM0 (A0)						#
//#									#
//#######################################################################
void enable_pwm0(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM1 (B0)						#
//#									#
//#######################################################################
void enable_pwm1(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM2 (X1)						#
//#									#
//#######################################################################
void enable_pwm2(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM3 (A1)						#
//#									#
//#######################################################################
void enable_pwm3(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM4 (B1)						#
//#									#
//#######################################################################
void enable_pwm4(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM5 (X2)						#
//#									#
//#######################################################################
void enable_pwm5(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM6 (A2)						#
//#									#
//#######################################################################
void enable_pwm6(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM7 (B2)						#
//#									#
//#######################################################################
void enable_pwm7(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM8 (X3)						#
//#									#
//#######################################################################
void enable_pwm8(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM9 (A3)						#
//#									#
//#######################################################################
void enable_pwm9(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	enable PWM10 (B3)						#
//#									#
//#######################################################################
void enable_pwm10(unsigned long scale, unsigned long value);

//#######################################################################
//#									#
//#	set PWM0 value							#
//#									#
//#######################################################################
void set_pwm0(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm1(unsigned long value);

//#######################################################################
//#									#
//#	set PWM2 value							#
//#									#
//#######################################################################
void set_pwm2(unsigned long value);

//#######################################################################
//#									#
//#	set PWM1 value							#
//#									#
//#######################################################################
void set_pwm3(unsigned long value);

//#######################################################################
//#									#
//#	set PWM4 value							#
//#									#
//#######################################################################
void set_pwm4(unsigned long value);

//#######################################################################
//#									#
//#	set PWM5 value							#
//#									#
//#######################################################################
void set_pwm5(unsigned long value);

//#######################################################################
//#									#
//#	set PWM6 value							#
//#									#
//#######################################################################
void set_pwm6(unsigned long value);

//#######################################################################
//#									#
//#	set PWM7 value							#
//#									#
//#######################################################################
void set_pwm7(unsigned long value);

//#######################################################################
//#									#
//#	set PWM8 value							#
//#									#
//#######################################################################
void set_pwm8(unsigned long value);

//#######################################################################
//#									#
//#	set PWM9 value							#
//#									#
//#######################################################################
void set_pwm9(unsigned long value);

//#######################################################################
//#									#
//#	set PWM10 value							#
//#									#
//#######################################################################
void set_pwm10(unsigned long value);

//#######################################################################
//#									#
//#	disable PWM0							#
//#									#
//#######################################################################
void disable_pwm0(void);

//#######################################################################
//#									#
//#	disable PWM1							#
//#									#
//#######################################################################
void disable_pwm1(void);

//#######################################################################
//#									#
//#	disable PWM2							#
//#									#
//#######################################################################
void disable_pwm2(void);

//#######################################################################
//#									#
//#	disable PWM3							#
//#									#
//#######################################################################
void disable_pwm3(void);

//#######################################################################
//#									#
//#	disable PWM4							#
//#									#
//#######################################################################
void disable_pwm4(void);

//#######################################################################
//#									#
//#	disable PWM5							#
//#									#
//#######################################################################
void disable_pwm5(void);

//#######################################################################
//#									#
//#	disable PWM6							#
//#									#
//#######################################################################
void disable_pwm6(void);

//#######################################################################
//#									#
//#	disable PWM7							#
//#									#
//#######################################################################
void disable_pwm7(void);

//#######################################################################
//#									#
//#	disable PWM8							#
//#									#
//#######################################################################
void disable_pwm8(void);

//#######################################################################
//#									#
//#	disable PWM9							#
//#									#
//#######################################################################
void disable_pwm9(void);

//#######################################################################
//#									#
//#	disable PWM10							#
//#									#
//#######################################################################
void disable_pwm10(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_sleep.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	sleep until extint event					#
//#									#
//#######################################################################
void unilib_sleep();

//#######################################################################
//#									#
//#	sleep for approx 10ms						#
//#									#
//#######################################################################
void unilib_sleep10();

//#######################################################################
//#									#
//#	sleep for approx 100ms						#
//#									#
//#######################################################################
void unilib_sleep100();

//#######################################################################
//#									#
//#	sleep for approx 1000ms						#
//#									#
//#######################################################################
void unilib_sleep1000();


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_sleeptick.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	wait a number of ticks						#
//#									#
//#######################################################################
void sleep_ticks(unsigned int ticks);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_spi0.c
//---------------------------------------------------------------------------------------
extern volatile unsigned char spi0_sso_port;

extern volatile unsigned char spi0_sso_pin;

//#######################################################################
//#									#
//#	init SPI as master						#
//#									#
//#######################################################################
void enable_spi0_master(unsigned char divider,unsigned char mode,unsigned char sso_port,unsigned char sso_pin);

//#######################################################################
//#									#
//#	init SPI as slave						#
//#									#
//#######################################################################
void enable_spi0_slave(unsigned char mode);

//#######################################################################
//#									#
//#	disable SPI							#
//#									#
//#######################################################################
void disable_spi0(void);

//#######################################################################
//#									#
//#	send/recv byte							#
//#									#
//#######################################################################
unsigned char comm_spi0(unsigned char data);

//#######################################################################
//#									#
//#	send byte							#
//#									#
//#######################################################################
void send_spi0(unsigned char data);

//#######################################################################
//#									#
//#	send/recv byte							#
//#									#
//#######################################################################
unsigned char comm_spi0_slave(unsigned char data);

//#######################################################################
//#									#
//#	select (SSO-pin=low)						#
//#									#
//#######################################################################
void select_spi0(void);

//#######################################################################
//#									#
//#	de-select (SSO-pin=high)					#
//#									#
//#######################################################################
void unselect_spi0(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_spi1.c
//---------------------------------------------------------------------------------------
extern volatile unsigned char spi1_sso_port;

extern volatile unsigned char spi1_sso_pin;

//#######################################################################
//#									#
//#	init SPI as master						#
//#									#
//#######################################################################
void enable_spi1_master(unsigned char divider,unsigned char mode,unsigned char sso_port,unsigned char sso_pin);

//#######################################################################
//#									#
//#	init SPI as slave						#
//#									#
//#######################################################################
void enable_spi1_slave(unsigned char mode);

//#######################################################################
//#									#
//#	disable SPI							#
//#									#
//#######################################################################
void disable_spi1(void);

//#######################################################################
//#									#
//#	send/recv byte							#
//#									#
//#######################################################################
unsigned char comm_spi1(unsigned char data);

//#######################################################################
//#									#
//#	send byte							#
//#									#
//#######################################################################
void send_spi1(unsigned char data);

//#######################################################################
//#									#
//#	select (SSO-pin=low)						#
//#									#
//#######################################################################
void select_spi1(void);

//#######################################################################
//#									#
//#	de-select (SSO-pin=high)					#
//#									#
//#######################################################################
void unselect_spi1(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_spi2.c
//---------------------------------------------------------------------------------------
extern volatile unsigned char spi2_sso_port;

extern volatile unsigned char spi2_sso_pin;

//#######################################################################
//#									#
//#	init SPI as master						#
//#									#
//#######################################################################
void enable_spi2_master(unsigned char divider,unsigned char mode,unsigned char sso_port,unsigned char sso_pin);

//#######################################################################
//#									#
//#	init SPI as slave						#
//#									#
//#######################################################################
void enable_spi2_slave(unsigned char mode);

//#######################################################################
//#									#
//#	disable SPI							#
//#									#
//#######################################################################
void disable_spi2(void);

//#######################################################################
//#									#
//#	send/recv byte							#
//#									#
//#######################################################################
unsigned char comm_spi2(unsigned char data);

//#######################################################################
//#									#
//#	send byte							#
//#									#
//#######################################################################
void send_spi2(unsigned char data);

//#######################################################################
//#									#
//#	select (SSO-pin=low)						#
//#									#
//#######################################################################
void select_spi2(void);

//#######################################################################
//#									#
//#	de-select (SSO-pin=high)					#
//#									#
//#######################################################################
void unselect_spi2(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_tick.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	wait a number of ticks						#
//#									#
//#######################################################################
void wait_ticks(unsigned int ticks);

//#######################################################################
//#									#
//#	wait a number of ticks						#
//#									#
//#######################################################################
void set_ticks(unsigned int ticks);

//#######################################################################
//#									#
//#	wait a number of ticks						#
//#									#
//#######################################################################
unsigned int get_ticks(void);

//#######################################################################
//#									#
//#	init tick/pwm timer						#
//#									#
//#######################################################################
void enable_tick(unsigned long scale);

//#######################################################################
//#									#
//#	disable tick interrupt						#
//#									#
//#######################################################################
void disable_tick(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_uart0.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init uart							#
//#									#
//#######################################################################
void enable_uart0(unsigned int divider);

//#######################################################################
//#									#
//#	disable UART							#
//#									#
//#######################################################################
void disable_uart0(void);

//#######################################################################
//#									#
//#	send serial byte						#
//#									#
//#######################################################################
void send_uart0(unsigned char data);

//#######################################################################
//#									#
//#	send serial byte						#
//#									#
//#######################################################################
void send_uart0_nonblock(unsigned char data);

//#######################################################################
//#									#
//#	read serial byte						#
//#									#
//#######################################################################
unsigned char get_uart0(void);

//#######################################################################
//#									#
//#	check uart receiver status (1=char)				#
//#									#
//#######################################################################
unsigned char check_uart0_rx(void);

//#######################################################################
//#									#
//#	check uart transmitter status (1=empty)				#
//#									#
//#######################################################################
unsigned char check_uart0_tx(void);

//#######################################################################
//#									#
//#	enable tx interrupt						#
//#									#
//#######################################################################
void enable_uart0_transmit_interrupt(void);

//#######################################################################
//#									#
//#	disable tx interrupt						#
//#									#
//#######################################################################
void disable_uart0_transmit_interrupt(void);

//#######################################################################
//#									#
//#	enable rx interrupt						#
//#									#
//#######################################################################
void enable_uart0_receive_interrupt(void);

//#######################################################################
//#									#
//#	disable rx interrupt						#
//#									#
//#######################################################################
void disable_uart0_receive_interrupt(void);


//---------------------------------------------------------------------------------------
// exports from src/src_unilib/src/src_unilib/unilib_uart1.c
//---------------------------------------------------------------------------------------
//#######################################################################
//#									#
//#	init uart							#
//#									#
//#######################################################################
void enable_uart1(unsigned int divider);

//#######################################################################
//#									#
//#	disable UART							#
//#									#
//#######################################################################
void disable_uart1(void);

//#######################################################################
//#									#
//#	send serial byte						#
//#									#
//#######################################################################
void send_uart1(unsigned char data);

//#######################################################################
//#									#
//#	send serial byte						#
//#									#
//#######################################################################
void send_uart1_nonblock(unsigned char data);

//#######################################################################
//#									#
//#	read serial byte						#
//#									#
//#######################################################################
unsigned char get_uart1(void);

//#######################################################################
//#									#
//#	check uart receiver status (1=char)				#
//#									#
//#######################################################################
unsigned char check_uart1_rx(void);

//#######################################################################
//#									#
//#	check uart transmitter status (1=empty)				#
//#									#
//#######################################################################
unsigned char check_uart1_tx(void);

//#######################################################################
//#									#
//#	enable tx interrupt						#
//#									#
//#######################################################################
void enable_uart1_transmit_interrupt(void);

//#######################################################################
//#									#
//#	disable tx interrupt						#
//#									#
//#######################################################################
void disable_uart1_transmit_interrupt(void);

//#######################################################################
//#									#
//#	enable rx interrupt						#
//#									#
//#######################################################################
void enable_uart1_receive_interrupt(void);

//#######################################################################
//#									#
//#	disable rx interrupt						#
//#									#
//#######################################################################
void disable_uart1_receive_interrupt(void);

