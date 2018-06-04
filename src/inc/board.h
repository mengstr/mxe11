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

#define SINTRO "\f\fFor setup press SPACE twice..." 

#define INTRO "\f\fMXE11 V1.71 (c)2017-2018 Joerg Wolfram\r\n--------------------------------------\r\n\r\r" 

//1=SD card, 2=AT45DB642
#define PREFERRED_MEDIA_TYPE 1

	//PC
#if MCU == 0
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <string.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define TERMINAL_RCHECK sim_uart_rcheck
	#define TERMINAL_TCHECK sim_uart_tcheck
	#define TERMINAL_GET sim_uart_get
	#define TERMINAL_PUT sim_uart_put
	#define	HAVE_TERM9 0
	#define DEBUG_PRINTF printf
	#define KPRINTF printf
	#define ERROR_PUT TERMINAL_PUT
	#define SERIAL_BUFFER_SIZE 256
	#define MAX_CACHE 64
	#define MEDIA_TYPE 0

	extern unsigned char TERMINAL_RCHECK();
	extern unsigned char TERMINAL_TCHECK();
	extern unsigned char TERMINAL_GET();
	extern void TERMINAL_PUT(unsigned char);
	extern void uxprintf(const char *,...);
#endif

	//PC+SDL
#if MCU == 1
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <string.h>
	#include "SDL.h"
	
	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define TERMINAL_RCHECK sim_uart_rcheck
	#define TERMINAL_TCHECK sim_uart_tcheck
	#define TERMINAL_GET sim_uart_get
	#define TERMINAL_PUT sim_uart_put
	#define	HAVE_TERM9 0

	#define DEBUG_PRINTF printf
	#define KPRINTF uxprintf
	#define ERROR_PUT TERMINAL_PUT
	#define SERIAL_BUFFER_SIZE 256
	#define MAX_CACHE 64
	#define MEDIA_TYPE 0

	extern unsigned char TERMINAL_RCHECK();
	extern unsigned char TERMINAL_TCHECK();
	extern unsigned char TERMINAL_GET();
	extern void TERMINAL_PUT(unsigned char);
	extern void uxprintf(const char *,...);
#endif


	//PC+SDL (320x240 simulation)
#if MCU == 2
	#include <stdarg.h>
	#include <stdio.h>
	#include <stdint.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sys/stat.h>
	#include <sys/types.h>
	#include <string.h>
	#include "SDL.h"
	
	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define TERMINAL_RCHECK sim_uart_rcheck
	#define TERMINAL_TCHECK sim_uart_tcheck
	#define TERMINAL_GET sim_uart_get
	#define TERMINAL_PUT sim_uart_put
	#define	HAVE_TERM9 0

	#define DEBUG_PRINTF printf
	#define KPRINTF uxprintf
	#define ERROR_PUT TERMINAL_PUT
	#define SERIAL_BUFFER_SIZE 256
	#define MAX_CACHE 20
	#define MEDIA_TYPE 0

	extern unsigned char TERMINAL_RCHECK();
	extern unsigned char TERMINAL_TCHECK();
	extern unsigned char TERMINAL_GET();
	extern void TERMINAL_PUT(unsigned char);
	extern void uxprintf(const char *,...);
#endif


	//SPC56EL60
#if MCU == 10
	#include <spc56el60.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_BIG_ENDIAN
	#define LOBYTE 1
	#define HIBYTE 0
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_C,14			//status LED
	#define DRIVE_LED PORT_C,13			//drive LED

	#define RTC_CLOCK PORT_B,5			//RTC clock pin
	#define RTC_DATA PORT_B,4			//RTC data pin

	#define CLOCK_SETTING CLOCK_16_120
	#define KHZ 120000
	#define TICK 16000				//7500HZ INT
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 3125		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART0
	#define TERM9_UART_INIT enable_uart0
	#define TERM9_OUTPUT OUTPUT_UART0
	#define TERM9_BAUD_DIVIDER 3125			//38K4
	#define TERM9_PUT send_uart0_nonblock
	#define TERM9_GET get_uart0
	#define TERM9_RCHECK check_uart0_rx
	#define TERM9_TCHECK check_uart0_tx

	#define DEFAULT_SPI_COMM comm_spi0
	#define SDCARD_SPI_INIT enable_spi0_master(2,0,PORT_C,4);
	#define SDCARD_SPI_INIT_SLOW enable_spi0_master(8,0,PORT_C,4);
	#define SDCARD_CSPORT PORT_C
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi0_master(2,0,PORT_C,4);
	#define DATAFLASH_CSPORT PORT_C
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 64
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif


#if MCU == 11
	#include <spc56el60.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_BIG_ENDIAN
	#define LOBYTE 1
	#define HIBYTE 0
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 3
	#define IO_TABLE 1

	#define STAT_LED PORT_C,14			//status LED
	#define DRIVE_LED PORT_C,13			//drive LED

	#define RTC_CLOCK PORT_B,5			//RTC clock pin
	#define RTC_DATA PORT_B,4			//RTC data pin

	#define CLOCK_SETTING CLOCK_16_120
	#define KHZ 120000
	#define TICK 16000				//7500HZ INT
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 3125		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART0
	#define TERM9_UART_INIT enable_uart0
	#define TERM9_OUTPUT OUTPUT_UART0
	#define TERM9_BAUD_DIVIDER 3125			//38K4
	#define TERM9_PUT send_uart0_nonblock
	#define TERM9_GET get_uart0
	#define TERM9_RCHECK check_uart0_rx
	#define TERM9_TCHECK check_uart0_tx

	#define DEFAULT_SPI_COMM comm_spi0
	#define SDCARD_SPI_INIT enable_spi0_master(2,0,PORT_C,4);
	#define SDCARD_SPI_INIT_SLOW enable_spi0_master(8,0,PORT_C,4);
	#define SDCARD_CSPORT PORT_C
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi0_master(2,0,PORT_C,4);
	#define DATAFLASH_CSPORT PORT_C
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 64
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif


	//STM32F103VE
#if MCU == 20
	#include <stm32f103xe.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_C,13			//status LED
	#define DRIVE_LED PORT_A,0			//drive LED

	#define RTC_CLOCK PORT_B,3			//RTC clock pin
	#define RTC_DATA PORT_B,4			//RTC data pin

	//72 MHz setup
	#define CLOCK_SETTING CLOCK_8_72
	#define KHZ 72000
	#define TICK 9600
	#define KL11_FACTOR 125

	//120MHz setup
	#define F1_OVERCLOCKING
	#define CLOCK_SETTING2 0x784e0d
	#define KHZ2 120000
	#define TICK2 16000
	#define TERMINAL_BAUD_DIVIDER2 3125		//38K4
	#define TERM9_BAUD_DIVIDER2 3125		//38K4

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 1875		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART2
	#define TERM9_UART_INIT enable_uart2
	#define TERM9_OUTPUT OUTPUT_UART2
	#define TERM9_BAUD_DIVIDER 1875			//38K4
	#define TERM9_PUT send_uart2_nonblock
	#define TERM9_GET get_uart2
	#define TERM9_RCHECK check_uart2_rx
	#define TERM9_TCHECK check_uart2_tx

	#define DEFAULT_SPI_COMM comm_spi1
#ifdef F1_OVERCLOCKING
	#define SDCARD_SPI_INIT enable_spi1_master(2,0,PORT_A,4);	//for 120MHz
#else
	#define SDCARD_SPI_INIT enable_spi1_master(3,0,PORT_A,4);	//for 72MHz
#endif
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(2,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 4
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif

	//STM32F107VC
#if MCU == 25
	#include <stm32f107xc.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_C,6			//status LED
	#define DRIVE_LED PORT_C,7			//drive LED

	#define RTC_CLOCK PORT_C,14			//RTC clock pin
	#define RTC_DATA PORT_C,15			//RTC data pin

	//72 MHz setup
	#define CLOCK_SETTING CLOCK_8_72
	#define KHZ 72000
	#define TICK 9600
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART3
	#define TERMINAL_UART_INIT enable_uart3_alt
	#define TERMINAL_OUTPUT OUTPUT_UART3
	#define TERMINAL_BAUD_DIVIDER 1875		//38K4
	#define TERMINAL_PUT send_uart3_nonblock
	#define ERROR_PUT send_uart3
	#define TERMINAL_GET get_uart3
	#define TERMINAL_RCHECK check_uart3_rx
	#define TERMINAL_TCHECK check_uart3_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART2
	#define TERM9_UART_INIT enable_uart2
	#define TERM9_OUTPUT OUTPUT_UART2	
	#define TERM9_BAUD_DIVIDER 1875			//38K4
	#define TERM9_PUT send_uart2_nonblock
	#define TERM9_GET get_uart2
	#define TERM9_RCHECK check_uart2_rx
	#define TERM9_TCHECK check_uart2_tx

	#define DEFAULT_SPI_COMM comm_spi1
#ifdef F1_OVERCLOCKING
	#define SDCARD_SPI_INIT enable_spi1_master(3,0,PORT_A,4);	//for 120MHz
#else
	#define SDCARD_SPI_INIT enable_spi1_master(2,0,PORT_A,4);	//for 72MHz
#endif
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(1,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 4
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif

	//STM32F411VE
#if MCU == 30
	#include <stm32f411xe.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_D,12			//status LED
	#define DRIVE_LED PORT_D,13			//drive LED

	#define RTC_CLOCK PORT_C,14			//RTC clock pin
	#define RTC_DATA PORT_C,13			//RTC data pin

	//96 MHz setup
	#define CLOCK_SETTING CLOCK_8_96
	#define KHZ 96000
	#define TICK 12800
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1_alt
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 2500		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define TERM9_UART UART2
	#define TERM9_UART_INIT enable_uart2
	#define TERM9_OUTPUT OUTPUT_UART2
	
	#define TERM9_BAUD_DIVIDER 2500			//38K4
	#define TERM9_PUT send_uart2_nonblock
	#define TERM9_GET get_uart2
	#define TERM9_RCHECK check_uart2_rx
	#define TERM9_TCHECK check_uart2_tx

	#define DEFAULT_SPI_COMM comm_spi1
	#define SDCARD_SPI_INIT enable_spi1_master(2,0,PORT_A,4);	//for 100MHz
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(2,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 64
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif


	//STM32F411VE
#if MCU == 31
	#include <stm32f411xe.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_D,12			//status LED
	#define DRIVE_LED PORT_D,13			//drive LED

	#define RTC_CLOCK PORT_C,14			//RTC clock pin
	#define RTC_DATA PORT_C,13			//RTC data pin

	//96 MHz setup
	#define CLOCK_SETTING CLOCK_8_96
	#define KHZ 96000
	#define TICK 12800
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1_alt
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 2500		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART2
	#define TERM9_UART_INIT enable_uart2
	#define TERM9_OUTPUT OUTPUT_UART2
	#define TERM9_BAUD_DIVIDER 2500			//38K4
	#define TERM9_PUT send_uart2_nonblock
	#define TERM9_GET get_uart1
	#define TERM9_RCHECK check_uart2_rx
	#define TERM9_TCHECK check_uart2_tx

	#define DEFAULT_SPI_COMM comm_spi1
	#define SDCARD_SPI_INIT enable_spi1_master(2,0,PORT_A,4);	//for 100MHz
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(2,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 64
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif



	//STM32F405VG
#if MCU == 35
	#include <stm32f405xg.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_C,10			//status LED
	#define DRIVE_LED PORT_C,12			//drive LED

	#define RTC_CLOCK PORT_C,14			//RTC clock pin
	#define RTC_DATA PORT_C,13			//RTC data pin

	//168 MHz setup
	#define CLOCK_SETTING CLOCK_16_168
	#define KHZ 168000
	#define TICK 22400
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 4375		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART6
	#define TERM9_UART_INIT enable_uart6
	#define TERM9_OUTPUT OUTPUT_UART6
	#define TERM9_BAUD_DIVIDER 4375			//38K4
	#define TERM9_PUT send_uart6_nonblock
	#define TERM9_GET get_uart6
	#define TERM9_RCHECK check_uart6_rx
	#define TERM9_TCHECK check_uart6_tx

	#define DEFAULT_SPI_COMM comm_spi1
	#define SDCARD_SPI_INIT enable_spi1_master(3,0,PORT_A,4);	//for 168MHz
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(2,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 120
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif

	//STM32L475RG
#if MCU == 40
	#include <stm32l475xg.h>
	#include <unilib.h>
	#include <stdarg.h>

	#define IS_LITTLE_ENDIAN
	#define LOBYTE 0
	#define HIBYTE 1
	#define USE_STACKLIMIT 0
	#define CHECK_FETCH 1
	#define LOAD_TEST 0
	#define SHIFT_CYCLE 0
	#define IO_TABLE 1

	#define STAT_LED PORT_C,10			//status LED
	#define DRIVE_LED PORT_C,12			//drive LED

	#define RTC_CLOCK PORT_C,14			//RTC clock pin
	#define RTC_DATA PORT_C,13			//RTC data pin

	//78 MHz setup
	#define CLOCK_SETTING CLOCK_16_78
	#define KHZ 78000
	#define TICK 10400
	#define KL11_FACTOR 125

	#define TERMINAL_UART UART1
	#define TERMINAL_UART_INIT enable_uart1
	#define TERMINAL_OUTPUT OUTPUT_UART1
	#define TERMINAL_BAUD_DIVIDER 2031		//38K4
	#define TERMINAL_PUT send_uart1_nonblock
	#define ERROR_PUT send_uart1
	#define TERMINAL_GET get_uart1
	#define TERMINAL_RCHECK check_uart1_rx
	#define TERMINAL_TCHECK check_uart1_tx
	#define SERIAL_BUFFER_SIZE 256

	#define	HAVE_TERM9 1
	#define TERM9_UART UART3
	#define TERM9_UART_INIT enable_uart3
	#define TERM9_OUTPUT OUTPUT_UART3
	#define TERM9_BAUD_DIVIDER 2031			//38K4
	#define TERM9_PUT send_uart3_nonblock
	#define TERM9_GET get_uart3
	#define TERM9_RCHECK check_uart3_rx
	#define TERM9_TCHECK check_uart3_tx

	#define DEFAULT_SPI_COMM comm_spi1
	#define SDCARD_SPI_INIT enable_spi1_master(2,0,PORT_A,4);	//for 78MHz
	#define SDCARD_SPI_INIT_SLOW enable_spi1_master(7,0,PORT_A,4);
	#define SDCARD_CSPORT PORT_A
	#define SDCARD_CSPIN 4

	#define DATAFLASH_SPI_INIT enable_spi1_master(2,0,PORT_A,4);
	#define DATAFLASH_CSPORT PORT_A
	#define DATAFLASH_CSPIN 4

	#define MAX_CACHE 62
	#define MEDIA_TYPE PREFERRED_MEDIA_TYPE
	#define DEBUG_PRINTF uxprintf
	#define KPRINTF uxprintf
#endif
