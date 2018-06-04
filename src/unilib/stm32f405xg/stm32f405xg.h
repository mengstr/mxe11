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
#ifndef _STM32F405XG_H_
#define _STM32F405XG_H_
#include <stddef.h>
#include <stdint.h>

typedef volatile int8_t     vint8_t;        /**< Volatile signed 8 bits.    */
typedef volatile uint8_t    vuint8_t;       /**< Volatile unsigned 8 bits.  */
typedef volatile int16_t    vint16_t;       /**< Volatile signed 16 bits.   */
typedef volatile uint16_t   vuint16_t;      /**< Volatile unsigned 16 bits. */
typedef volatile int32_t    vint32_t;       /**< Volatile signed 32 bits.   */
typedef volatile uint32_t   vuint32_t;      /**< Volatile unsigned 32 bits. */


//-----------------------------------------------------------------------------
// CM4 core
//-----------------------------------------------------------------------------	
	struct STK_tag {
		//+00 CTRL
		union {
			vuint32_t REG;
			struct{
				vuint32_t ENABLE:1;
				vuint32_t TICKINT:1;
				vuint32_t CLKSOURCE:1;
				  vuint32_t:13;
				vuint32_t COUNTFLAG:1;
				  vuint32_t:15;			
			} BIT;	
		} CTRL;

		//+04 RELOAD
		union {
			vuint32_t REG;
			struct{
				vuint32_t RELOAD:24;
				  vuint32_t:8;
			} BIT;	
		} LOAD;

		//+08 CURRENT
		union {
			vuint32_t REG;
			struct{
				vuint32_t CURRENT:24;
				  vuint32_t:8;
			} BIT;	
		} VAL;

		//+0C CALIB
		union {
			vuint32_t REG;
			struct{
				vuint32_t TENMS:24;
				  vuint32_t:8;
			} BIT;	
		} CALIB;
	};
	

	struct NVIC_tag {
		//+00 ISER
		union {
			vuint32_t REG[3];
			struct{
				vuint32_t SETENA:1;

			} BIT[96];	
		} ISER;

		vuint32_t RESERVED0[29];

		//+80 ICER
		union {
			vuint32_t REG[3];
			struct{
				vuint32_t CLRENA:1;

			} BIT[96];	
		} ICER;

		vuint32_t RESERVED1[29];

		//+100 SETPEND
		union {
			vuint32_t REG[3];
			struct{
				vuint32_t SETPEND:1;

			} BIT[96];	
		} ISPR;

		vuint32_t RESERVED2[29];

		//+180 CLRPEND
		union {
			vuint32_t REG[3];
			struct{
				vuint32_t CLRPEND:1;

			} BIT[96];	
		} ICPR;

		vuint32_t RESERVED3[29];

		//+200 IABR
		union {
			vuint32_t REG[3];
			struct{
				vuint32_t ACTIVE:1;

			} BIT[96];	
		} IABR;

		vuint32_t RESERVED4[61];

		//+300 IPR
		union {
			vuint32_t REG[33];
			struct{
				vuint32_t IP:8;

			} BIT[132];	
		} IPR;
	};

	struct SCB_tag {
		//+00 CPUID
		union {
			vuint32_t REG;
			struct{
				vuint32_t Revision:4;
				vuint32_t PartNo:12;
				vuint32_t Constant:4;
				vuint32_t Variant:4;
				vuint32_t Implementer:8;
				
			} BIT;	
		} CPUID;

		//+04 ICSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t VECTACTIVE:9;
				  vuint32_t:2;
				vuint32_t RETOBASE:1;
				vuint32_t VECTPENDING:10;
				vuint32_t ISPENDING:1;
				  vuint32_t:2;				
				vuint32_t PENDSTCLR:1;
				vuint32_t PENDSTSET:1;
				vuint32_t PENDSVCLR:1;
				vuint32_t PENDSVSET:1;
				  vuint32_t:2;				
				vuint32_t NMIPENDSET:1;				
			} BIT;	
		} ICSR;

		//+08 VTOR
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:9;				
				vuint32_t TBLOFF:21;
				  vuint32_t:2;				
			} BIT;	
		} VTOR;

		//+0C AIRCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t VECTRESET:1;
				vuint32_t VECTCLRACTIVE:1;
				vuint32_t SYSRESETREQ:1;
				  vuint32_t:5;				
				vuint32_t PRIGROUP:3;
				  vuint32_t:4;				
				vuint32_t ENDIANESS:1;
				vuint32_t VECTKEY:16;
			} BIT;	
		} AIRCR;

		//+10 SCR
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:1;				
				vuint32_t SLEEPONEXIT:1;
				vuint32_t SLEEPDEEP:1;
				  vuint32_t:1;				
				vuint32_t SEVONPEND:1;
				  vuint32_t:27;				
			} BIT;	
		} SCR;

		//+14 CCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t NONBASETHRDENA:1;
				vuint32_t USERSETMPEND:1;
				  vuint32_t:1;				
				vuint32_t UNALIGN_TRP:1;
				vuint32_t DIV_0_TRP:1;
				  vuint32_t:3;				
				vuint32_t BFHFNMIGN:1;
				vuint32_t STKALIGN:1;
				  vuint32_t:22;				
			} BIT;	
		} CCR;

		//+18 SHPR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t PRI_4:8;
				vuint32_t PRI_5:8;
				vuint32_t PRI_6:8;
				  vuint32_t:8;				
			} BIT;	
		} SHPR1;

		//+1C SHPR2
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:24;				
				vuint32_t PRI_11:8;
			} BIT;	
		} SHPR2;

		//+20 SHPR3
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:16;				
				vuint32_t PRI_14:8;
				vuint32_t PRI_15:8;
			} BIT;	
		} SHPR3;

		//+24 SHCRS
		union {
			vuint32_t REG;
			struct{
				vuint32_t MEM_FAULT_ACT:1;
				vuint32_t BUS_FAULT_ACT:1;
				  vuint32_t:1;
				vuint32_t USG_FAULT_ACT:1;
				  vuint32_t:3;
				vuint32_t SV_CALL_ACT:1;
				vuint32_t MONITOR_ACT:1;
				  vuint32_t:1;
				vuint32_t PENDSV:1;
				vuint32_t SYS_TICK_ACT:1;
				vuint32_t USG_FAULT_PENDED:1;
				vuint32_t MEM_FAULT_PENDED:1;
				vuint32_t BUS_FAULT_PENDED:1;
				vuint32_t SV_CALL_PENDED:1;
				vuint32_t USG_FAULT_ENA:1;
				vuint32_t MEM_FAULT_ENA:1;
				vuint32_t BUS_FAULT_ENA:1;
				  vuint32_t:13;				
			} BIT;	
		} SHCRS;

		//+28 CFSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t MMFSR:8;
				vuint32_t BFSR:8;
				vuint32_t UFSR:16;
			} BIT;	
		} CFSR;

		//+2C HFSR
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:1;
				vuint32_t VECTTBL:1;
				  vuint32_t:28;
				vuint32_t FORCED:1;
				vuint32_t DEBUG_VT:1;
			} BIT;	
		} HFSR;

		//+30 reserved
		vuint32_t RESERVED1;

		//+34 MMAR
		union {
			vuint32_t REG;
			struct{
				vuint32_t MMAR:32;
			} BIT;	
		} MMAR;

		//+38 BFAR
		union {
			vuint32_t REG;
			struct{
				vuint32_t BFAR:32;
			} BIT;	
		} BFAR;

		//+3C AFSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t IMPDEF:32;
			} BIT;	
		} AFSR;
	};

//-----------------------------------------------------------------------------
// GPIO
//-----------------------------------------------------------------------------
	struct PORT_tag {

		//+00 MODER
		union {
			vuint32_t REG;
			struct{
				vuint32_t MODER0:2;
				vuint32_t MODER1:2;
				vuint32_t MODER2:2;
				vuint32_t MODER3:2;
				vuint32_t MODER4:2;
				vuint32_t MODER5:2;
				vuint32_t MODER6:2;
				vuint32_t MODER7:2;
				vuint32_t MODER8:2;
				vuint32_t MODER9:2;
				vuint32_t MODER10:2;
				vuint32_t MODER11:2;
				vuint32_t MODER12:2;
				vuint32_t MODER13:2;
				vuint32_t MODER14:2;
				vuint32_t MODER15:2;
			} BIT;	
		} MODER;

		//+04 OTYPER
		union {
			vuint32_t REG;
			struct{
				vuint32_t OT0:1;
				vuint32_t OT1:1;
				vuint32_t OT2:1;
				vuint32_t OT3:1;
				vuint32_t OT4:1;
				vuint32_t OT5:1;
				vuint32_t OT6:1;
				vuint32_t OT7:1;
				vuint32_t OT8:1;
				vuint32_t OT9:1;
				vuint32_t OT10:1;
				vuint32_t OT11:1;
				vuint32_t OT12:1;
				vuint32_t OT13:1;
				vuint32_t OT14:1;
				vuint32_t OT15:1;
				  vuint32_t:16;
			} BIT;	
		} OTYPER;

		//+08 OSPEEDR
		union {
			vuint32_t REG;
			struct{
				vuint32_t OSPEEDR0:2;
				vuint32_t OSPEEDR1:2;
				vuint32_t OSPEEDR2:2;
				vuint32_t OSPEEDR3:2;
				vuint32_t OSPEEDR4:2;
				vuint32_t OSPEEDR5:2;
				vuint32_t OSPEEDR6:2;
				vuint32_t OSPEEDR7:2;
				vuint32_t OSPEEDR8:2;
				vuint32_t OSPEEDR9:2;
				vuint32_t OSPEEDR10:2;
				vuint32_t OSPEEDR11:2;
				vuint32_t OSPEEDR12:2;
				vuint32_t OSPEEDR13:2;
				vuint32_t OSPEEDR14:2;
				vuint32_t OSPEEDR15:2;
			} BIT;	
		} OSPEEDR;

		//+0C PUPDR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PUPDR0:2;
				vuint32_t PUPDR1:2;
				vuint32_t PUPDR2:2;
				vuint32_t PUPDR3:2;
				vuint32_t PUPDR4:2;
				vuint32_t PUPDR5:2;
				vuint32_t PUPDR6:2;
				vuint32_t PUPDR7:2;
				vuint32_t PUPDR8:2;
				vuint32_t PUPDR9:2;
				vuint32_t PUPDR10:2;
				vuint32_t PUPDR11:2;
				vuint32_t PUPDR12:2;
				vuint32_t PUPDR13:2;
				vuint32_t PUPDR14:2;
				vuint32_t PUPDR15:2;
			} BIT;	
		} PUPDR;

		//+10 IDR
		union {
			vuint32_t REG;
			struct{
				vuint32_t IDR0:1;
				vuint32_t IDR1:1;
				vuint32_t IDR2:1;
				vuint32_t IDR3:1;
				vuint32_t IDR4:1;
				vuint32_t IDR5:1;
				vuint32_t IDR6:1;
				vuint32_t IDR7:1;
				vuint32_t IDR8:1;
				vuint32_t IDR9:1;
				vuint32_t IDR10:1;
				vuint32_t IDR11:1;
				vuint32_t IDR12:1;
				vuint32_t IDR13:1;
				vuint32_t IDR14:1;
				vuint32_t IDR15:1;
				  vuint32_t:16;
			} BIT;	
		} IDR;

		//+14 ODR
		union {
			vuint32_t REG;
			struct{
				vuint32_t ODR0:1;
				vuint32_t ODR1:1;
				vuint32_t ODR2:1;
				vuint32_t ODR3:1;
				vuint32_t ODR4:1;
				vuint32_t ODR5:1;
				vuint32_t ODR6:1;
				vuint32_t ODR7:1;
				vuint32_t ODR8:1;
				vuint32_t ODR9:1;
				vuint32_t ODR10:1;
				vuint32_t ODR11:1;
				vuint32_t ODR12:1;
				vuint32_t ODR13:1;
				vuint32_t ODR14:1;
				vuint32_t ODR15:1;
				  vuint32_t:16;
			} BIT;	
		} ODR;

		//+18 BSRR
		union {
			vuint32_t REG;
			struct{
				vuint32_t BS0:1;
				vuint32_t BS1:1;
				vuint32_t BS2:1;
				vuint32_t BS3:1;
				vuint32_t BS4:1;
				vuint32_t BS5:1;
				vuint32_t BS6:1;
				vuint32_t BS7:1;
				vuint32_t BS8:1;
				vuint32_t BS9:1;
				vuint32_t BS10:1;
				vuint32_t BS11:1;
				vuint32_t BS12:1;
				vuint32_t BS13:1;
				vuint32_t BS14:1;
				vuint32_t BS15:1;

				vuint32_t BR0:1;
				vuint32_t BR1:1;
				vuint32_t BR2:1;
				vuint32_t BR3:1;
				vuint32_t BR4:1;
				vuint32_t BR5:1;
				vuint32_t BR6:1;
				vuint32_t BR7:1;
				vuint32_t BR8:1;
				vuint32_t BR9:1;
				vuint32_t BR10:1;
				vuint32_t BR11:1;
				vuint32_t BR12:1;
				vuint32_t BR13:1;
				vuint32_t BR14:1;
				vuint32_t BR15:1;
			} BIT;	
		} BSRR;

		//+1C LCKR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LCK0:1;
				vuint32_t LCK1:1;
				vuint32_t LCK2:1;
				vuint32_t LCK3:1;
				vuint32_t LCK4:1;
				vuint32_t LCK5:1;
				vuint32_t LCK6:1;
				vuint32_t LCK7:1;
				vuint32_t LCK8:1;
				vuint32_t LCK9:1;
				vuint32_t LCK10:1;
				vuint32_t LCK11:1;
				vuint32_t LCK12:1;
				vuint32_t LCK13:1;
				vuint32_t LCK14:1;
				vuint32_t LCK15:1;
				vuint32_t LCKK;
				  vuint32_t:15;
			} BIT;	
		} LCKR;

		//+20 AFRL
		union {
			vuint32_t REG;
			struct{
				vuint32_t AFRL0:4;
				vuint32_t AFRL1:4;
				vuint32_t AFRL2:4;
				vuint32_t AFRL3:4;
				vuint32_t AFRL4:4;
				vuint32_t AFRL5:4;
				vuint32_t AFRL6:4;
				vuint32_t AFRL7:4;
			} BIT;	
		} AFRL;

		//+24 AFRH
		union {
			vuint32_t REG;
			struct{
				vuint32_t AFRH8:4;
				vuint32_t AFRH9:4;
				vuint32_t AFRH10:4;
				vuint32_t AFRH11:4;
				vuint32_t AFRH12:4;
				vuint32_t AFRH13:4;
				vuint32_t AFRH14:4;
				vuint32_t AFRH15:4;
			} BIT;	
		} AFRH;
				
	};				


//-----------------------------------------------------------------------------
// Reset + clock
//-----------------------------------------------------------------------------
	struct RCC_tag {
		//+00 RCC_CR
		union {
			vuint32_t REG;
			struct{
				vuint32_t HSION:1;
				vuint32_t HSIRDY:1;
				  vuint32_t:1;
				vuint32_t HSITRIM:5;
				vuint32_t HSICAL:8;
				vuint32_t HSEON:1;
				vuint32_t HSERDY:1;
				vuint32_t HSEBYP:1;
				vuint32_t CSSON:1;
				  vuint32_t:4;
				vuint32_t PLLON:1;
				vuint32_t PLLRDY:1;
				vuint32_t PLLI2SON:1;
				vuint32_t PLLI2SRDY:1;
				  vuint32_t:4;
			} BIT;	
		} CR;

		//+04 RCC_PLLCFGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PLLM:6;
				vuint32_t PLLN:9;
				  vuint32_t:1;
				vuint32_t PLLP:2;
				  vuint32_t:4;
				vuint32_t PLLSRC:1;
				  vuint32_t:1;
				vuint32_t PLLQ:4;
				  vuint32_t:4;
			} BIT;	
		} PLLCFGR;

		//+08 RCC_CFGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t SW:2;
				vuint32_t SWS:2;
				vuint32_t HPRE:4;
				  vuint32_t:2;
				vuint32_t PPRE1:3;
				vuint32_t PPRE2:3;
				vuint32_t RTCPRE:5;
				vuint32_t MCO1:2;
				vuint32_t I2SSRC:1;
				vuint32_t MCO1PRE:3;
				vuint32_t MCO2PRE:3;
				vuint32_t MCO2:2;
			} BIT;	
		} CFGR;

		//+0C RCC_CIR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LSIRDYF:1;
				vuint32_t LSERDYF:1;
				vuint32_t HSIRDYF:1;
				vuint32_t HSERDYF:1;
				vuint32_t PLLRDYF:1;
				vuint32_t PLLI2SRDYF:1;
				  vuint32_t:1;
				vuint32_t CSSF:1;
				vuint32_t LSIRDYE:1;
				vuint32_t LSERDYE:1;
				vuint32_t HSIRDYE:1;
				vuint32_t HSERDYE:1;
				vuint32_t PLLRDYE:1;
				vuint32_t PLLI2SRDYE:1;
				  vuint32_t:2;
				vuint32_t LSIRDYC:1;
				vuint32_t LSERDYC:1;
				vuint32_t HSIRDYC:1;
				vuint32_t HSERDYC:1;
				vuint32_t PLLRDYC:1;
				vuint32_t PLLI2SRDYC:1;
				  vuint32_t:1;
				vuint32_t CSSC:1;
				  vuint32_t:8;
			} BIT;	
		} CIR;

		//+10 RCC_AHB1RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t GPIOARST:1;
				vuint32_t GPIOBRST:1;
				vuint32_t GPIOCRST:1;
				vuint32_t GPIODRST:1;
				vuint32_t GPIOERST:1;
				vuint32_t GPIOFRST:1;
				vuint32_t GPIOGRST:1;
				vuint32_t GPIOHRST:1;
				vuint32_t GPIOIRST:1;
				  vuint32_t:3;
				vuint32_t CRCRST:1;
				  vuint32_t:8;
				vuint32_t DMA1RST:1;
				vuint32_t DMA2RST:1;
				  vuint32_t:2;
				vuint32_t ETHMACRST:1;
				  vuint32_t:3;
				vuint32_t OTGHSRST:1;
				  vuint32_t:2;
			} BIT;	
		} AHB1RSTR;

		//+14 RCC_AHB2RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DCMIRST:1;
				  vuint32_t:3;
				vuint32_t CRYPRST:1;
				vuint32_t HASHRST:1;
				vuint32_t RNGRST:1;
				vuint32_t OTGFSRST:1;
				  vuint32_t:24;
			} BIT;	
		} AHB2RSTR;

		//+18 RCC_AHB3RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FSMCRST:1;
				  vuint32_t:31;
			} BIT;	
		} AHB3RSTR;


		//+1C reserved
		vuint32_t RESERVED1;

		//+20 RCC_APB1RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM2RST:1;
				vuint32_t TIM3RST:1;
				vuint32_t TIM4RST:1;
				vuint32_t TIM5RST:1;
				vuint32_t TIM6RST:1;
				vuint32_t TIM7RST:1;
				vuint32_t TIM12RST:1;
				vuint32_t TIM13RST:1;
				vuint32_t TIM14RST:1;
				  vuint32_t:2;
				vuint32_t WWDGRST:1;
				  vuint32_t:2;
				vuint32_t SPI2RST:1;
				vuint32_t SPI3RST:1;
				  vuint32_t:1;
				vuint32_t UART2RST:1;
				vuint32_t UART3RST:1;
				vuint32_t UART4RST:1;
				vuint32_t UART5RST:1;
				vuint32_t I2C1RST:1;
				vuint32_t I2C2RST:1;
				vuint32_t I2C3RST:1;
				  vuint32_t:1;
				vuint32_t CAN1RST:1;
				vuint32_t CAN2RST:1;
				  vuint32_t:1;
				vuint32_t PWRRST:1;
				vuint32_t DACRST:1;
				  vuint32_t:2;
			} BIT;	
		} APB1RSTR;

		//+24 RCC_APB2RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM1RST:1;
				vuint32_t TIM8RST:1;
				  vuint32_t:2;
				vuint32_t UART1RST:1;
				vuint32_t UART6RST:1;
				  vuint32_t:2;
				vuint32_t ADCRST:1;
				  vuint32_t:2;
				vuint32_t SDIORST:1;
				vuint32_t SPI1RST:1;
				  vuint32_t:1;
				vuint32_t SYSCFGRST:1;
				  vuint32_t:1;
				vuint32_t TIM9RST:1;
				vuint32_t TIM10RST:1;
				vuint32_t TIM11RST:1;
				  vuint32_t:13;
			} BIT;	
		} APB2RSTR;

		//+28 reserved
		vuint32_t RESERVED2;

		//+2C reserved
		vuint32_t RESERVED3;

		//+30 RCC_AHB1ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t GPIOAEN:1;
				vuint32_t GPIOBEN:1;
				vuint32_t GPIOCEN:1;
				vuint32_t GPIODEN:1;
				vuint32_t GPIOEEN:1;
				vuint32_t GPIOFEN:1;
				vuint32_t GPIOGEN:1;
				vuint32_t GPIOHEN:1;
				vuint32_t GPIOIEN:1;
				  vuint32_t:3;
				vuint32_t CRCEN:1;
				  vuint32_t:5;
				vuint32_t BKPSRAMEN:1;
				  vuint32_t:1;
				vuint32_t CCMDATARAMEN:1;
				vuint32_t DMA1EN:1;
				vuint32_t DMA2EN:1;
				  vuint32_t:2;
				vuint32_t ETHMACEN:1;
				vuint32_t ETHMACTXEN:1;
				vuint32_t ETHMACRXEN:1;
				vuint32_t ETHMACPTPEN:1;
				vuint32_t OTGHSEN:1;
				vuint32_t OTGHSULPIEN:1;
				  vuint32_t:1;
			} BIT;	
		} AHB1ENR;

		//+34 RCC_AHB2ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DCMIEN:1;
				  vuint32_t:3;
				vuint32_t CRYPEN:1;
				vuint32_t HASHEN:1;
				vuint32_t RNGEN:1;
				vuint32_t OTGFSEN:1;
				  vuint32_t:24;
			} BIT;	
		} AHB2ENR;

		//+38 RCC_AHB3ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FSMCEN:1;
				  vuint32_t:31;
			} BIT;	
		} AHB3ENR;


		//+3C reserved
		vuint32_t RESERVED4;


		//+40 RCC_APB1ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM2EN:1;
				vuint32_t TIM3EN:1;
				vuint32_t TIM4EN:1;
				vuint32_t TIM5EN:1;
				vuint32_t TIM6EN:1;
				vuint32_t TIM7EN:1;
				vuint32_t TIM12EN:1;
				vuint32_t TIM13EN:1;
				vuint32_t TIM14EN:1;
				  vuint32_t:2;
				vuint32_t WWDGEN:1;
				  vuint32_t:2;
				vuint32_t SPI2EN:1;
				vuint32_t SPI3EN:1;
				  vuint32_t:1;
				vuint32_t UART2EN:1;
				vuint32_t UART3EN:1;
				vuint32_t UART4EN:1;
				vuint32_t UART5EN:1;
				vuint32_t I2C1EN:1;
				vuint32_t I2C2EN:1;
				vuint32_t I2C3EN:1;
				  vuint32_t:1;
				vuint32_t CAN1EN:1;
				vuint32_t CAN2EN:1;
				  vuint32_t:1;
				vuint32_t PWREN:1;
				vuint32_t DACEN:1;
				  vuint32_t:2;
			} BIT;	
		} APB1ENR;

		//+44 RCC_APB2ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM1EN:1;
				vuint32_t TIM8EN:1;
				  vuint32_t:2;
				vuint32_t UART1EN:1;
				vuint32_t UART6EN:1;
				  vuint32_t:2;
				vuint32_t ADC1EN:1;
				vuint32_t ADC2EN:1;
				vuint32_t ADC3EN:1;
				vuint32_t SDIOEN:1;
				vuint32_t SPI1EN:1;
				  vuint32_t:1;
				vuint32_t SYSCFGEN:1;
				  vuint32_t:1;
				vuint32_t TIM9EN:1;
				vuint32_t TIM10EN:1;
				vuint32_t TIM11EN:1;
				  vuint32_t:13;
			} BIT;	
		} APB2ENR;

		//+48 reserved
		vuint32_t RESERVED5;

		//+4C reserved
		vuint32_t RESERVED6;

		//+50 RCC_AHB1LPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t GPIOALPEN:1;
				vuint32_t GPIOBLPEN:1;
				vuint32_t GPIOCLPEN:1;
				vuint32_t GPIODLPEN:1;
				vuint32_t GPIOELPEN:1;
				vuint32_t GPIOFLPEN:1;
				vuint32_t GPIOGLPEN:1;
				vuint32_t GPIOHLPEN:1;
				vuint32_t GPIOILPEN:1;
				  vuint32_t:3;
				vuint32_t CRCLPEN:1;
				  vuint32_t:2;
				vuint32_t FLITFLPEN:1;
				vuint32_t SRAM1LPEN:1;
				vuint32_t SRAM2LPEN:1;
				vuint32_t BKPSRAMLPEN:1;
				  vuint32_t:2;
				vuint32_t DMA1LPEN:1;
				vuint32_t DMA2LPEN:1;
				  vuint32_t:2;
				vuint32_t ETHMACLPEN:1;
				vuint32_t ETHMACTXLPEN:1;
				vuint32_t ETHMACRXLPEN:1;
				vuint32_t ETHMACPTPLPEN:1;
				vuint32_t OTGHSLPEN:1;
				vuint32_t OTGHSULPILPEN:1;
				  vuint32_t:1;
			} BIT;	
		} AHB1LPENR;

		//+54 RCC_AHB2LPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DCMILPEN:1;
				  vuint32_t:3;
				vuint32_t CRYPLPEN:1;
				vuint32_t HASHLPEN:1;
				vuint32_t RNGLPEN:1;
				vuint32_t OTGFSLPEN:1;
				  vuint32_t:24;
			} BIT;	
		} AHB2LPENR;

		//+58 RCC_AHB3LPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FSMCLPEN:1;
				  vuint32_t:31;
			} BIT;	
		} AHB3LPENR;


		//+5C reserved
		vuint32_t RESERVED7;

		//+60 RCC_APB1LPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM2LPEN:1;
				vuint32_t TIM3LPEN:1;
				vuint32_t TIM4LPEN:1;
				vuint32_t TIM5LPEN:1;
				vuint32_t TIM6LPEN:1;
				vuint32_t TIM7LPEN:1;
				vuint32_t TIM12LPEN:1;
				vuint32_t TIM13LPEN:1;
				vuint32_t TIM14LPEN:1;
				  vuint32_t:2;
				vuint32_t WWDGLPEN:1;
				  vuint32_t:2;
				vuint32_t SPI2LPEN:1;
				vuint32_t SPI3LPEN:1;
				  vuint32_t:1;
				vuint32_t UART2LPEN:1;
				vuint32_t UART3LPEN:1;
				vuint32_t UART4LPEN:1;
				vuint32_t UART5LPEN:1;
				vuint32_t I2C1LPEN:1;
				vuint32_t I2C2LPEN:1;
				vuint32_t I2C3LPEN:1;
				  vuint32_t:1;
				vuint32_t CAN1LPEN:1;
				vuint32_t CAN2LPEN:1;
				  vuint32_t:1;
				vuint32_t PWRLPEN:1;
				vuint32_t DACLPEN:1;
				  vuint32_t:2;
			} BIT;	
		} APB1LPENR;

		//+64 RCC_APB2LPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM1LPEN:1;
				vuint32_t TIM8LPEN:1;
				  vuint32_t:2;
				vuint32_t UART1LPEN:1;
				vuint32_t UART6LPEN:1;
				  vuint32_t:2;
				vuint32_t ADC1LPEN:1;
				vuint32_t ADC2LPEN:1;
				vuint32_t ADC3LPEN:1;
				vuint32_t SDIOLPEN:1;
				vuint32_t SPI1LPEN:1;
				  vuint32_t:1;
				vuint32_t SYSCFGLPEN:1;
				  vuint32_t:1;
				vuint32_t TIM9LPEN:1;
				vuint32_t TIM10LPEN:1;
				vuint32_t TIM11LPEN:1;
				  vuint32_t:13;
			} BIT;	
		} APB2LPENR;

		//+68 reserved
		vuint32_t RESERVED8;

		//+6C reserved
		vuint32_t RESERVED9;

		//+70 RCC_BDCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LSEON:1;
				vuint32_t LSERDY:1;
				vuint32_t LSEBYP:1;
				  vuint32_t:5;
				vuint32_t RTCSEL:2;
				  vuint32_t:5;
				vuint32_t RTCEN:1;
				vuint32_t BDRST:1;
				  vuint32_t:15;
			} BIT;	
		} BDCR;

		//+74 RCC_CSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LSION:1;
				vuint32_t LSIRDY:1;
				  vuint32_t:22;
				vuint32_t RMVF:1;
				vuint32_t BORRSTF:1;
				vuint32_t PADRSTF:1;
				vuint32_t PORRSTF:1;
				vuint32_t SFTRSTF:1;
				vuint32_t WDGRSTF:1;
				vuint32_t WWDGRSTF:1;
				vuint32_t LPWRSTF:1;
			} BIT;	
		} CSR;

		//+78 reserved
		vuint32_t RESERVED10;

		//+7C reserved
		vuint32_t RESERVED11;

		//+80 RCC_SSCGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t MODPER:13;
				vuint32_t INCSTEP:15;
				  vuint32_t:2;
				vuint32_t SPREADSEL:1;
				vuint32_t SSCGEN:1;
			} BIT;	
		} SSCGR;

		//+84 RCC_PLLI2SCFGR
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:6;
				vuint32_t PLLI2SN:9;
				 vuint32_t:13;
				vuint32_t PLLI2SR:3;
				  vuint32_t:1;
			} BIT;	
		} PLLI2SCFGR;
	};


//-----------------------------------------------------------------------------
// UART
//-----------------------------------------------------------------------------

	struct UART_tag {
		//+00 SR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PE:1;
				vuint32_t FE:1;
				vuint32_t NE:1;
				vuint32_t ORE:1;
				vuint32_t IDLE:1;
				vuint32_t RXNE:1;
				vuint32_t TC:1;
				vuint32_t TXE:1;
				vuint32_t LBD:1;
				vuint32_t CTS:1;
				  vuint32_t:22;
			} BIT;	
		} SR;

		//+04 DR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DR:9;
				  vuint32_t:23;
			} BIT;	
		} DR;

		//+08 BRR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DIV_FRACTION:4;
				vuint32_t DIV_MANTISSA:12;
				  vuint32_t:16;		
			} BIT;	
		} BRR;

		//+0C CR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t SBK:1;
				vuint32_t RWU:1;
				vuint32_t RE:1;
				vuint32_t TE:1;
				vuint32_t IDLEIE:1;
				vuint32_t RXNEIE:1;
				vuint32_t TCIE:1;
				vuint32_t TXEIE:1;
				vuint32_t PEIE:1;
				vuint32_t PS:1;
				vuint32_t PCE:1;
				vuint32_t WAKE:1;
				vuint32_t M:1;
				vuint32_t UE:1;
				  vuint32_t:1;
				vuint32_t OVER8:1;
				  vuint32_t:16;
			} BIT;	
		} CR1;

		//+10 CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t ADD:4;
				  vuint32_t:1;
				vuint32_t LBDL:1;
				vuint32_t LBDIE:1;
				  vuint32_t:1;
				vuint32_t LBCL:1;
				vuint32_t CPHA:1;
				vuint32_t CPOL:1;
				vuint32_t CLKEN:1;
				vuint32_t STOP:2;
				vuint32_t LINEN:1;
				  vuint32_t:17;
			} BIT;	
		} CR2;

		//+14 CR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t EIE:1;
				vuint32_t IREN:1;
				vuint32_t IRLP:1;
				vuint32_t HDSEL:1;
				vuint32_t NACK:1;
				vuint32_t SCEN:1;
				vuint32_t DMAR:1;
				vuint32_t DMAT:1;
				vuint32_t RTSE:1;
				vuint32_t CTSE:1;
				vuint32_t CTSIE:1;
				vuint32_t ONEBIT:1;
				  vuint32_t:20;
			} BIT;	
		} CR3;

		//+18 GTPR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PSC:8;
				vuint32_t GT:8;
				  vuint32_t:16;
			} BIT;	
		} GTPR;
	};
	
	
//-----------------------------------------------------------------------------
// I2C
//-----------------------------------------------------------------------------
	struct I2C_tag {
		//+00 CR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t PE:1;
				vuint32_t SMBUS:1;
				  vuint32_t:1;
				vuint32_t SMBTYPE:1;
				vuint32_t ENARP:1;
				vuint32_t ENPEC:1;
				vuint32_t ENGC:1;
				vuint32_t NOSTRETCH:1;
				vuint32_t START:1;
				vuint32_t STOP:1;
				vuint32_t ACK:1;
				vuint32_t POS:1;
				vuint32_t PEC:1;
				vuint32_t ALERT:1;
				  vuint32_t:1;
				vuint32_t SWRST:1;
				  vuint32_t:16;
			} BIT;	
		} CR1;
		//+04 CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t FREQ:6;
				  vuint32_t:2;
				vuint32_t ITERREN:1;
				vuint32_t ITEVTEN:1;
				vuint32_t ITBUFEN:1;
				vuint32_t DMAEN:1;
				vuint32_t LAST:1;
				  vuint32_t:19;
			} BIT;	
		} CR2;
		//+08 OAR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t ADD0:1;
				vuint32_t ADD:9;
				  vuint32_t:5;
				vuint32_t ADDMODE:1;
				  vuint32_t:16;
			} BIT;	
		} OAR1;
		//+0C OAR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t ENDUAL:1;
				vuint32_t ADD2:7;
				  vuint32_t:24;
			} BIT;	
		} OAR2;
		//+10 DR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DR:8;
				  vuint32_t:24;
			} BIT;	
		} DR;
		//+14 SR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t SB:1;
				vuint32_t ADDR:1;
				vuint32_t BTF:1;
				vuint32_t ADD10:1;
				vuint32_t STOPF:1;
				  vuint32_t:1;
				vuint32_t RXNE:1;
				vuint32_t TXE:1;
				vuint32_t BERR:1;
				vuint32_t ARLO:1;
				vuint32_t AF:1;
				vuint32_t OVR:1;
				vuint32_t PECERR:1;
				  vuint32_t:1;
				vuint32_t TIMEOUT:1;
				vuint32_t SMBALERT:1;
				  vuint32_t:16;
			} BIT;	
		} SR1;
		//+18 SR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t MSL:1;
				vuint32_t BUSY:1;
				vuint32_t TRA:1;
				  vuint32_t:1;
				vuint32_t GENCALL:1;
				vuint32_t SMBDEFAULT:1;
				vuint32_t SMBHOST:1;
				vuint32_t DUALF:1;
				vuint32_t PEC:8;
				  vuint32_t:16;
			} BIT;	
		} SR2;
		//+1C CCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t CCR:12;
				  vuint32_t:2;
				vuint32_t DUTY:1;
				vuint32_t F_S:1;
				  vuint32_t:16;
			} BIT;	
		} CCR;

		//+20 TRISE
		union {
			vuint32_t REG;
			struct{
				vuint32_t TRISE:6;
				  vuint32_t:26;
			} BIT;	
		} TRISE;

		//+24 FLTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DNF:4;
				vuint32_t ANOFF:1;
				  vuint32_t:27;
			} BIT;	
		} FLTR;
	};


//----------------------------------------------------------------------------------------------
// SPI
//----------------------------------------------------------------------------------------------
	struct SPI_tag {
		//+00 CR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t CPHA:1;
				vuint32_t CPOL:1;
				vuint32_t MSTR:1;
				vuint32_t BR:3;
				vuint32_t SPE:1;
				vuint32_t LSBFIRST:1;
				vuint32_t SSI:1;
				vuint32_t SSM:1;
				vuint32_t RXONLY:1;
				vuint32_t DFF:1;
				vuint32_t CRCNEXT:1;
				vuint32_t CRCEN:1;
				vuint32_t BDIOE:1;
				vuint32_t BIDIMODE:1;
				  vuint32_t:16;
			} BIT;	
		} CR1;

		//+04 CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t RXDMAEN:1;
				vuint32_t TXDMAEN:1;
				vuint32_t SSOE:1;
				  vuint32_t:1;
				vuint32_t FRF:1;
				vuint32_t ERRIE:1;
				vuint32_t RXNEIE:1;
				vuint32_t TXEIE:1;
				  vuint32_t:24;
			} BIT;	
		} CR2;

		//+08 SR
		union {
			vuint32_t REG;
			struct{
				vuint32_t RXNE:1;
				vuint32_t TXE:1;
				vuint32_t CHSIDE:1;
				vuint32_t UDR:1;
				vuint32_t CRCERR:1;
				vuint32_t MODF:1;
				vuint32_t OVR:1;
				vuint32_t BSY:1;
				vuint32_t FRE:1;
				  vuint32_t:23;
			} BIT;	
		} SR;

		//+0C DR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DR:16;
				  vuint32_t:16;
			} BIT;	
		} DR;

		//+10 CRCPR
		union {
			vuint32_t REG;
			struct{
				vuint32_t CRCPOLY:16;
				  vuint32_t:16;
			} BIT;	
		} CRCPR;

		//+14 CRXCRCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t RXCRC:16;
				  vuint32_t:16;
			} BIT;	
		} RXCRCR;

		//+18 TXCRCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TXCRC:16;
				  vuint32_t:16;
			} BIT;	
		} TXCRCR;

		//+1C I2SCFGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t CHLEN:1;
				vuint32_t DATLEN:2;
				vuint32_t CKPOL:1;
				vuint32_t I2SSTD:2;
				  vuint32_t:1;
				vuint32_t PCMSYNC:1;
				vuint32_t I2SCFG:2;
				vuint32_t I2SE:1;
				vuint32_t I2SMOD:1;
				  vuint32_t:20;
			} BIT;	
		} I2SCFGR;

		//+20 I2SPR
		union {
			vuint32_t REG;
			struct{
				vuint32_t I2SDIV:8;
				vuint32_t ODD:1;
				vuint32_t MCKOE:1;
				  vuint32_t:22;
			} BIT;	
		} I2SPR;
	};


//-----------------------------------------------------------------------------
// TIMER 2-3
//-----------------------------------------------------------------------------
	struct TIMX_tag {
		//+00 CR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t CEN:1;
				vuint32_t UDIS:1;
				vuint32_t URS:1;
				vuint32_t OPM:1;
				vuint32_t DIR:1;
				vuint32_t CMS:2;
				vuint32_t ARPE:1;
				vuint32_t CKD:2;
				  vuint32_t:22;
			} BIT;	
		} CR1;

		//+04 CR2
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:3;
				vuint32_t CCDS:1;
				vuint32_t MMS:3;
				vuint32_t T11S:1;
				  vuint32_t:24;
			} BIT;	
		} CR2;

		//+08 SMCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t SMS:3;
				  vuint32_t:1;
				vuint32_t TS:3;
				vuint32_t MSM:1;
				vuint32_t ETF:4;
				vuint32_t ETPS:2;
				vuint32_t ECE:1;
				vuint32_t ETP:1;
				  vuint32_t:16;
			} BIT;	
		} SMCR;

		//+0C DIER
		union {
			vuint32_t REG;
			struct{
				vuint32_t UIE:1;
				vuint32_t CC1IE:1;
				vuint32_t CC2IE:1;
				vuint32_t CC3IE:1;
				vuint32_t CC4IE:1;
				  vuint32_t:1;
				vuint32_t TIE:1;
				  vuint32_t:1;
				vuint32_t UDE:1;
				vuint32_t CC1DE:1;
				vuint32_t CC2DE:1;
				vuint32_t CC3DE:1;
				vuint32_t CC4DE:1;
				vuint32_t COMDE:1;
				vuint32_t TDE:1;
				  vuint32_t:17;
			} BIT;	
		} DIER;

		//+10 SR
		union {
			vuint32_t REG;
			struct{
				vuint32_t UIF:1;
				vuint32_t CC1IF:1;
				vuint32_t CC2IF:1;
				vuint32_t CC3IF:1;
				vuint32_t CC4IF:1;
				  vuint32_t:1;
				vuint32_t TIF:1;
				  vuint32_t:2;
				vuint32_t CC1OF:1;
				vuint32_t CC2OF:1;
				vuint32_t CC3OF:1;
				vuint32_t CC4OF:1;
				  vuint32_t:19;
			} BIT;	
		} SR;

		//+14 EGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t UG:1;
				vuint32_t CC1G:1;
				vuint32_t CC2G:1;
				vuint32_t CC3G:1;
				vuint32_t CC4G:1;
				  vuint32_t:1;
				vuint32_t TG:1;
				  vuint32_t:25;
			} BIT;	
		} EGR;

		//+18 CCMR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t CC1S:2;
				vuint32_t OC1FE:1;
				vuint32_t OC1PE:1;
				vuint32_t OC1M:3;
				vuint32_t OC1CE:1;
				vuint32_t CC2S:2;
				vuint32_t OC2FE:1;
				vuint32_t OC2PE:1;
				vuint32_t OC2M:3;
				vuint32_t OC2CE:1;
				  vuint32_t:16;
			} BIT_OC;
			struct{
				vuint32_t CC1S:2;
				vuint32_t IC1PSC:2;
				vuint32_t IC1F:4;
				vuint32_t CC2S:2;
				vuint32_t IC2PSC:2;
				vuint32_t IC2F:4;
				  vuint32_t:16;
			} BIT_IC;		
		} CCMR1;

		//+1C CCMR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t CC3S:2;
				vuint32_t OC3FE:1;
				vuint32_t OC3PE:1;
				vuint32_t OC3M:3;
				vuint32_t OC3CE:1;
				vuint32_t CC4S:2;
				vuint32_t OC4FE:1;
				vuint32_t OC4PE:1;
				vuint32_t OC4M:3;
				vuint32_t OC4CE:1;
				  vuint32_t:16;
			} BIT_OC;
			struct{
				vuint32_t CC3S:2;
				vuint32_t IC3PSC:2;
				vuint32_t IC3F:4;
				vuint32_t CC4S:2;
				vuint32_t IC4PSC:2;
				vuint32_t IC4F:4;
				  vuint32_t:16;
			} BIT_IC;		
		} CCMR2;

		//+20 CCER
		union {
			vuint32_t REG;
			struct{
				vuint32_t CC1E:1;
				vuint32_t CC1P:1;
				  vuint32_t:1;
				vuint32_t CC1NP:1;
				vuint32_t CC2E:1;
				vuint32_t CC2P:1;
				  vuint32_t:1;
				vuint32_t CC2NP:1;
				vuint32_t CC3E:1;
				vuint32_t CC3P:1;
				  vuint32_t:1;
				vuint32_t CC3NP:1;
				vuint32_t CC4E:1;
				vuint32_t CC4P:1;
				  vuint32_t:1;
				vuint32_t CC4NP:1;
				  vuint32_t:16;
			} BIT;	
		} CCER;

		//+24 CNT
		union {
			vuint32_t REG;
			struct{
				vuint32_t CNT:16;
				  vuint32_t:16;
			} BIT;	
		} CNT;

		//+28 PSC
		union {
			vuint32_t REG;
			struct{
				vuint32_t PSC:16;
				  vuint32_t:16;
			} BIT;	
		} PSC;

		//+2C ARR
		union {
			vuint32_t REG;
			struct{
				vuint32_t ARR:16;
				  vuint32_t:16;
			} BIT;	
		} ARR;
		
		//+30 RESERVED
		vuint32_t RESERVED30;

		//+34 CCR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t CCR1:16;
				  vuint32_t:16;
			} BIT;	
		} CCR1;

		//+38 CCR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t CCR2:16;
				  vuint32_t:16;
			} BIT;	
		} CCR2;

		//+3C CCR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t CCR3:16;
				  vuint32_t:16;
			} BIT;	
		} CCR3;

		//+40 CCR4
		union {
			vuint32_t REG;
			struct{
				vuint32_t CCR4:16;
				  vuint32_t:16;
			} BIT;	
		} CCR4;

		//+44 RESERVED
		vuint32_t RESERVED44;
		
		//+48 DCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DBA:5;
				  vuint32_t:3;
				vuint32_t DBL:5;
				  vuint32_t:3;
				  vuint32_t:16;
			} BIT;	
		} DCR;
		
		//+4C DMAR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DMAB:16;
				  vuint32_t:16;
			} BIT;	
		} DMAR;
		
	};



//-----------------------------------------------------------------------------
// ADC
//-----------------------------------------------------------------------------
	struct ADC_tag {
		//+00 SR
		union {
			vuint32_t REG;
			struct{
				vuint32_t AWD:1;
				vuint32_t EOC:1;
				vuint32_t JEOC:1;
				vuint32_t JSTRT:1;
				vuint32_t STRT:1;
				vuint32_t OVR:1;
				  vuint32_t:26;
			} BIT;	
		} SR;
		//+04 CR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t AWDCH:5;
				vuint32_t EOCIE:1;
				vuint32_t AWDIE:1;
				vuint32_t JEOCIE:1;
				vuint32_t SCAN:1;
				vuint32_t AWDSGL:1;
				vuint32_t JAUTO:1;
				vuint32_t DISCEN:1;
				vuint32_t JDISCEN:1;
				vuint32_t DISCNUM:3;
				  vuint32_t:6;
				vuint32_t JAWDEN:1;
				vuint32_t AWDEN:1;
				vuint32_t RES:2;
				vuint32_t OVRIE:1;
				  vuint32_t:5;
			} BIT;	
		} CR1;
		//+08 CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t ADON:1;
				vuint32_t CONT:1;
				  vuint32_t:6;
				vuint32_t DMA:1;
				vuint32_t DDS:1;
				vuint32_t EOCS:1;
				vuint32_t ALIGN:1;
				  vuint32_t:4;
				vuint32_t JEXTSEL:4;
				vuint32_t JEXTEN:2;
				vuint32_t JSWSTART:1;
				  vuint32_t:1;
				vuint32_t EXTSEL:4;
				vuint32_t EXTEN:2;
				vuint32_t SWSTART:1;
				  vuint32_t:1;
			} BIT;	
		} CR2;
		//+0C SMPR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t SMP10:3;
				vuint32_t SMP11:3;
				vuint32_t SMP12:3;
				vuint32_t SMP13:3;
				vuint32_t SMP14:3;
				vuint32_t SMP15:3;
				vuint32_t SMP16:3;
				vuint32_t SMP17:3;
				vuint32_t SMP18:3;
				  vuint32_t:5;
			} BIT;	
		} SMPR1;
		//+10 SMPR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t SMP0:3;
				vuint32_t SMP1:3;
				vuint32_t SMP2:3;
				vuint32_t SMP3:3;
				vuint32_t SMP4:3;
				vuint32_t SMP5:3;
				vuint32_t SMP6:3;
				vuint32_t SMP7:3;
				vuint32_t SMP8:3;
				vuint32_t SMP9:3;
				  vuint32_t:2;
			} BIT;	
		} SMPR2;
		//+14 JOFR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t JOFFSET1:12;
				  vuint32_t:20;				
			} BIT;	
		} JOFR1;
		//+18 JOFR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t JOFFSET2:12;
				  vuint32_t:20;				
			} BIT;	
		} JOFR2;
		//+1C JOFR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t JOFFSET3:12;
				  vuint32_t:20;				
			} BIT;	
		} JOFR3;
		//+20 JOFR4
		union {
			vuint32_t REG;
			struct{
				vuint32_t JOFFSET4:12;
				  vuint32_t:20;				
			} BIT;	
		} JOFR4;
		//+24 HTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t HT:12;
				  vuint32_t:20;				
			} BIT;	
		} HTR;
		//+28 LTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LT:12;
				  vuint32_t:20;				
			} BIT;	
		} LTR;
		//+2C SQR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t SQ13:5;
				vuint32_t SQ14:5;
				vuint32_t SQ15:5;
				vuint32_t SQ16:5;
				vuint32_t L:4;
				  vuint32_t:8;				
			} BIT;	
		} SQR1;
		//+30 SQR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t SQ7:5;
				vuint32_t SQ8:5;
				vuint32_t SQ9:5;
				vuint32_t SQ10:5;
				vuint32_t SQ11:5;
				vuint32_t SQ12:5;
				  vuint32_t:2;				
			} BIT;	
		} SQR2;
		//+34 SQR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t SQ1:5;
				vuint32_t SQ2:5;
				vuint32_t SQ3:5;
				vuint32_t SQ4:5;
				vuint32_t SQ5:5;
				vuint32_t SQ6:5;
				  vuint32_t:2;				
			} BIT;	
		} SQR3;
		//+38 JSQR
		union {
			vuint32_t REG;
			struct{
				vuint32_t JSQ1:5;
				vuint32_t JSQ2:5;
				vuint32_t JSQ3:5;
				vuint32_t JSQ4:5;
				vuint32_t JL:2;
				  vuint32_t:10;				
			} BIT;	
		} JSQR;
		//+3C JDR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t JDATA:16;
				  vuint32_t:16;				
			} BIT;	
		} JDR1;
		//+40 JDR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t JDATA:16;
				  vuint32_t:16;				
			} BIT;	
		} JDR2;
		//+44 JDR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t JDATA:16;
				  vuint32_t:16;				
			} BIT;	
		} JDR3;
		//+48 JDR4
		union {
			vuint32_t REG;
			struct{
				vuint32_t JDATA:16;
				  vuint32_t:16;				
			} BIT;	
		} JDR4;
		//+4C DR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DATA:16;
				vuint32_t ADC2DATA:16;
			} BIT;	
		} DR;		
	};

	struct ADC_COMMON_tag {
		
		//+04 CSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t AWD1:1;
				vuint32_t EOC1:1;
				vuint32_t JEOC1:1;
				vuint32_t JSTRT1:1;
				vuint32_t STRT1:1;
				vuint32_t OVR1:1;
				  vuint32_t:2;

				vuint32_t AW2:1;
				vuint32_t EOC2:1;
				vuint32_t JEOC2:1;
				vuint32_t JSTRT2:1;
				vuint32_t STRT2:1;
				vuint32_t OVR2:1;
				  vuint32_t:2;

				vuint32_t AWD3:1;
				vuint32_t EOC3:1;
				vuint32_t JEOC3:1;
				vuint32_t JSTRT3:1;
				vuint32_t STRT3:1;
				vuint32_t OVR3:1;
				  vuint32_t:10;
			} BIT;	
		} CSR;
		
		//+04 CCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t MULTI:5;
				  vuint32_t:3;
				vuint32_t DELAY:4;
				  vuint32_t:1;
				vuint32_t DDS:1;
				vuint32_t DMA:2;
				vuint32_t ADCPRE:2;
				  vuint32_t:4;
				vuint32_t VBATE:1;
				vuint32_t TSVREFE:1;
				  vuint32_t:8;
			} BIT;	
		} CCR;

		//+08 CDR
		union {
			vuint32_t REG;
			struct{
				vuint16_t DATA1;
				vuint16_t DATA2;
			} WORD;	
		} CDR;
	};
	
//-----------------------------------------------------------------------------
// Flash
//-----------------------------------------------------------------------------
	struct FLASH_tag {
		//+00 FLASH_ACR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LATENCY:3;
				  vuint32_t:5;
				vuint32_t PRFTEN:1;
				vuint32_t ICEN:1;
				vuint32_t DCEN:1;
				vuint32_t ICRST:1;
				vuint32_t DCRST:1;
				  vuint32_t:19;
			} BIT;	
		} ACR;
		
		//+04 FLASH_KEYR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FKEYR:32;
			} BIT;	
		} KEYR;

		//+08 FLASH_OPTKEYR
		union {
			vuint32_t REG;
			struct{
				vuint32_t OPTKEYR:32;
			} BIT;	
		} OPTKEYR;

		//+0C FLASH_SR
		union {
			vuint32_t REG;
			struct{
				vuint32_t EOP:1;
				vuint32_t OPERR:1;
				  vuint32_t:2;
				vuint32_t WRPERR:1;
				vuint32_t PGAERR:1;
				vuint32_t PGPERR:1;
				vuint32_t PGSERR:1;
				  vuint32_t:8;
				vuint32_t BSY:1;
				  vuint32_t:15;
			} BIT;	
		} SR;

		//+10 FLASH_CR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PG:1;
				vuint32_t PER:1;
				vuint32_t MER:1;
				vuint32_t SNB:3;
				  vuint32_t:1;
				vuint32_t PSIZE:2;
				  vuint32_t:6;
				vuint32_t STRT:1;
				  vuint32_t:7;
				vuint32_t EOPIE:1;
				  vuint32_t:6;
				vuint32_t LOCK:1;
			} BIT;	
		} CR;


		//+14 FLASH_OPTCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t OPTLOCK:1;
				vuint32_t OPTSTRT:1;
				vuint32_t BOR_LEV:2;
				  vuint32_t:1;
				vuint32_t WDG_SW:1;
				vuint32_t NRST_STOP:1;
				vuint32_t NRST_STDBY:1;
				vuint32_t RDP:8;
				vuint32_t NWRP:12;
				  vuint32_t:4;
			} BIT;	
		} OPTCR;		
	};
	

//-----------------------------------------------------------------------------
// block addresses
//-----------------------------------------------------------------------------
#define GPIOA (*(volatile struct PORT_tag *) 0x40020000UL)
#define GPIOB (*(volatile struct PORT_tag *) 0x40020400UL)
#define GPIOC (*(volatile struct PORT_tag *) 0x40020800UL)
#define GPIOD (*(volatile struct PORT_tag *) 0x40020C00UL)
#define GPIOE (*(volatile struct PORT_tag *) 0x40021000UL)
#define GPIOF (*(volatile struct PORT_tag *) 0x40021400UL)
#define GPIOG (*(volatile struct PORT_tag *) 0x40021800UL)
#define GPIOH (*(volatile struct PORT_tag *) 0x40021C00UL)
#define GPIOI (*(volatile struct PORT_tag *) 0x40022000UL)
#define GPIOJ (*(volatile struct PORT_tag *) 0x40022400UL)
#define GPIOK (*(volatile struct PORT_tag *) 0x40022800UL)
#define RCC (*(volatile struct RCC_tag *) 0x40023800UL)
#define FLASH (*(volatile struct FLASH_tag *) 0x40023C00UL)

#define UART1 (*(volatile struct UART_tag *) 0x40011000UL)
#define UART2 (*(volatile struct UART_tag *) 0x40004400UL)
#define UART3 (*(volatile struct UART_tag *) 0x40004800UL)
#define UART4 (*(volatile struct UART_tag *) 0x40004C00UL)
#define UART5 (*(volatile struct UART_tag *) 0x40005000UL)
#define UART6 (*(volatile struct UART_tag *) 0x40011400UL)

#define SPI1 (*(volatile struct SPI_tag *) 0x40013000UL)
#define SPI2 (*(volatile struct SPI_tag *) 0x40003800UL)
#define SPI3 (*(volatile struct SPI_tag *) 0x40003C00UL)

#define I2C1 (*(volatile struct I2C_tag *) 0x40015400UL)
#define I2C2 (*(volatile struct I2C_tag *) 0x40015800UL)

#define TIM2 (*(volatile struct TIMX_tag *) 0x40000000UL)
#define TIM3 (*(volatile struct TIMX_tag *) 0x40000400UL)

#define ADC1 (*(volatile struct ADC_tag *) 0x40012000UL)
#define ADC2 (*(volatile struct ADC_tag *) 0x40012100UL)
#define ADC3 (*(volatile struct ADC_tag *) 0x40012200UL)
#define ADC (*(volatile struct ADC_COMMON_tag *) 0x40012300UL)

#define STK (*(volatile struct STK_tag *) 0xE000E010UL)
#define NVIC (*(volatile struct NVIC_tag *) 0xE000E100UL)
#define SCB (*(volatile struct SCB_tag *) 0xE000ED00UL)

#define _IS_STM32F405_ 1
#define CLOCK_8_8		0x08000500	// HSE
#define CLOCK_8_16		0x10403E24	// 16MHz, PLL / 8 * 128 / 8, OTG=32MHz
#define CLOCK_8_20		0x14503E24	// 20MHz, PLL / 8 * 160 / 8, OTG=40MHz
#define CLOCK_8_24		0x18603E24	// 24MHz, PLL / 8 * 192 / 8, OTG=48MHz
#define CLOCK_8_32		0x20401E24	// 32MHz, PLL / 8 * 128 / 4, OTG=32MHz
#define CLOCK_8_36		0x24481E23	// 36MHz, PLL / 8 * 144 / 4, OTG=48MHz
#define CLOCK_8_40		0x28501E24	// 40MHz, PLL / 8 * 160 / 4, OTG=40MHz
#define CLOCK_8_48		0x30601E24	// 48MHz, PLL / 8 * 192 / 4, OTG=48MHz
#define CLOCK_8_64		0x40400E24	// 64MHz, PLL / 8 * 128 / 2, OTG=32MHz
#define CLOCK_8_72		0x48480E23	// 72MHz, PLL / 8 * 144 / 2, OTG=48MHz
#define CLOCK_8_80		0x50500E24	// 80MHz, PLL / 8 * 160 / 2, OTG=40MHz
#define CLOCK_8_96		0x60600E24	// 96MHz, PLL / 8 * 192 / 2, OTG=48MHz
#define CLOCK_8_100	0x64640E25	// 100MHz, PLL / 8 * 200 / 2, OTG=40MHz
#define CLOCK_8_128	0x80800E28	// 128MHz, PLL / 8 * 256 / 2, OTG=32MHz
#define CLOCK_8_144	0x90900E26	// 144MHz, PLL / 8 * 288 / 2, OTG=48MHz
#define CLOCK_8_160	0xA0A00E28	// 160MHz, PLL / 8 * 320 / 2, OTG=40MHz
#define CLOCK_8_168	0xA8A80E28	// 168MHz, PLL / 8 * 320 / 2, OTG=42MHz
#define CLOCK_16_16	0x10000500	// HSE
#define CLOCK_16_20	0x14503E44	// 20MHz, PLL / 16 * 160 / 8, OTG=40MHz
#define CLOCK_16_24	0x18603E44	// 24MHz, PLL / 16 * 192 / 8, OTG=48MHz
#define CLOCK_16_32	0x20401E44	// 32MHz, PLL / 16 * 128 / 4, OTG=32MHz
#define CLOCK_16_36	0x24481E43	// 36MHz, PLL / 16 * 144 / 4, OTG=48MHz
#define CLOCK_16_40	0x28501E44	// 40MHz, PLL / 16 * 160 / 4, OTG=40MHz
#define CLOCK_16_48	0x30601E44	// 48MHz, PLL / 16 * 192 / 4, OTG=48MHz
#define CLOCK_16_64	0x40400E44	// 64MHz, PLL / 16 * 128 / 2, OTG=32MHz
#define CLOCK_16_72	0x48480E43	// 72MHz, PLL / 16 * 144 / 2, OTG=48MHz
#define CLOCK_16_80	0x50500E44	// 80MHz, PLL / 16 * 160 / 2, OTG=40MHz
#define CLOCK_16_96	0x60600E44	// 96MHz, PLL / 16 * 192 / 2, OTG=48MHz
#define CLOCK_16_100	0x64640E45	// 100MHz, PLL / 16 * 200 / 2, OTG=40MHz
#define CLOCK_16_128	0x80800E48	// 128MHz, PLL / 16 * 256 / 2, OTG=32MHz
#define CLOCK_16_144	0x90900E46	// 144MHz, PLL / 16 * 288 / 2, OTG=48MHz
#define CLOCK_16_160	0xA0A00E48	// 160MHz, PLL / 16 * 320 / 2, OTG=40MHz
#define CLOCK_16_168	0xA8A80E48	// 168MHz, PLL / 16 * 320 / 2, OTG=42MHz
#define CLOCK_I_16		0x10000500	// HSE
#define CLOCK_I_20		0x14503A44	// 20MHz, PLL / 16 * 160 / 8, OTG=40MHz
#define CLOCK_I_24		0x18603A44	// 24MHz, PLL / 16 * 192 / 8, OTG=48MHz
#define CLOCK_I_32		0x20401A44	// 32MHz, PLL / 16 * 128 / 4, OTG=32MHz
#define CLOCK_I_36		0x24481A43	// 36MHz, PLL / 16 * 144 / 4, OTG=48MHz
#define CLOCK_I_40		0x28501A44	// 40MHz, PLL / 16 * 160 / 4, OTG=40MHz
#define CLOCK_I_48		0x30601A44	// 48MHz, PLL / 16 * 192 / 4, OTG=48MHz
#define CLOCK_I_64		0x40400A44	// 64MHz, PLL / 16 * 128 / 2, OTG=32MHz
#define CLOCK_I_72		0x48480A43	// 72MHz, PLL / 16 * 144 / 2, OTG=48MHz
#define CLOCK_I_80		0x50500A44	// 80MHz, PLL / 16 * 160 / 2, OTG=40MHz
#define CLOCK_I_96		0x60600A44	// 96MHz, PLL / 16 * 192 / 2, OTG=48MHz
#define CLOCK_I_100	0x64640A45	// 100MHz, PLL / 16 * 200 / 2, OTG=40MHz
#define CLOCK_I_128	0x80800A48	// 128MHz, PLL / 16 * 256 / 2, OTG=32MHz
#define CLOCK_I_144	0x90900A46	// 144MHz, PLL / 16 * 288 / 2, OTG=48MHz
#define CLOCK_I_160	0xA0A00A48	// 160MHz, PLL / 16 * 320 / 2, OTG=40MHz
#define CLOCK_I_168	0xA8A80A48	// 168MHz, PLL / 16 * 320 / 2, OTG=42MHz
#define	APB_MAX_FREQ 84
#define	PORT_A 0x40020000
#define	PORT_B 0x40020400
#define	PORT_C 0x40020800
#define	PORT_D 0x40020C00
#define	PORT_E 0x40021000
#define	PORT_F 0x40021400
#define	PORT_G 0x40021800
#define	PORT_H 0x40021C00
#define	PORT_I 0x40022000
#define	PORT_J 0x40022400
#define	PORT_K 0x40022800
#define	HAVE_UART1 1
#define	OUTPUT_UART1 send_uart1
#define	UART1_PORT PORT_A
#define	UART1_TX_PIN 9
#define	UART1_RX_PIN 10
#define	UART1A_PORT PORT_B
#define	UART1A_TX_PIN 6
#define	UART1A_RX_PIN 7
#define	HAVE_UART2 1
#define	OUTPUT_UART1 send_uart1
#define	UART2_PORT PORT_A
#define	UART2_TX_PIN 2
#define	UART2_RX_PIN 3
#define	HAVE_UART3 3
#define	OUTPUT_UART3 send_uart3
#define	UART3_PORT PORT_C
#define	UART3_TX_PIN 6
#define	UART3_RX_PIN 7
#define	HAVE_SPI1 1
#define	OUTPUT_SPI1 send_spi1
#define	COMM_SPI1 comm_spi1
#define	SPI1_PORT PORT_A
#define	SPI1_SS_PIN 4
#define	SPI1_SCK_PIN 5
#define	SPI1_MISO_PIN 6
#define	SPI1_MOSI_PIN 7
#define	HAVE_SPI2 2
#define	OUTPUT_SPI2 send_spi2
#define	COMM_SPI2 comm_spi2
#define	SPI2_PORT PORT_B
#define	SPI2_SS_PIN 12
#define	SPI2_SCK_PIN 13
#define	SPI2_MISO_PIN 14
#define	SPI2_MOSI_PIN 15
#define	HAVE_I2C 1
#define	HAVE_I2C1 1
#define	I2C1_PORT PORT_B
#define	I2C1_SCL_PIN 8
#define	I2C1_SDA_PIN 9
#define	HAVE_I2C2 1
#define	HAVE_PWM2
#define	PWM21_PORT PORT_A
#define	PWM21_PIN 15
#define	PWM22_PORT PORT_B
#define	PWM22_PIN 3
#define	PWM23_PORT PORT_B
#define	PWM23_PIN 10
#define	PWM24_PORT PORT_B
#define	PWM24_PIN 11
#define	HAVE_PWM3
#define	PWM31_PORT PORT_C
#define	PWM31_PIN 6
#define	PWM32_PORT PORT_C
#define	PWM32_PIN 7
#define	PWM33_PORT PORT_C
#define	PWM33_PIN 8
#define	PWM34_PORT PORT_C
#define	PWM34_PIN 9
#define	HAVE_ADC 1
#define	ADC0_PORT PORT_C
#define	ADC0_PIN 4
#define	ADC0_CHANNEL 14
#define	ADC1_PORT PORT_C
#define	ADC1_PIN 5
#define	ADC1_CHANNEL 15
#define	ADC2_PORT PORT_B
#define	ADC2_PIN 0
#define	ADC2_CHANNEL 8
#define	ADC3_PORT PORT_B
#define	ADC3_PIN 1
#define	ADC3_CHANNEL 9
#define	ADC4_PORT PORT_C
#define	ADC4_PIN 0
#define	ADC4_CHANNEL 10
#define	ADC5_PORT PORT_C
#define	ADC5_PIN 1
#define	ADC5_CHANNEL 11
#define	ADC6_PORT PORT_C
#define	ADC6_PIN 2
#define	ADC6_CHANNEL 12
#define	ADC7_PORT PORT_C
#define	ADC7_PIN 3
#define	ADC7_CHANNEL 13
#define	UNILIB_PAUSE_MS 202
#define RAMSIZE 192
#define HAVE_LONGPORT 1
typedef unsigned long PORT_TYPE;
#endif
