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
#ifndef _STM32F107XC_H_
#define _STM32F107XC_H_
#include <stddef.h>
#include <stdint.h>

typedef volatile int8_t     vint8_t;        /**< Volatile signed 8 bits.    */
typedef volatile uint8_t    vuint8_t;       /**< Volatile unsigned 8 bits.  */
typedef volatile int16_t    vint16_t;       /**< Volatile signed 16 bits.   */
typedef volatile uint16_t   vuint16_t;      /**< Volatile unsigned 16 bits. */
typedef volatile int32_t    vint32_t;       /**< Volatile signed 32 bits.   */
typedef volatile uint32_t   vuint32_t;      /**< Volatile unsigned 32 bits. */

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
				vuint32_t PLL2ON:1;
				vuint32_t PLL2RDY:1;
				vuint32_t PLL3ON:1;
				vuint32_t PLL3RDY:1;
				  vuint32_t:2;
			} BIT;	
		} CR;

		//+04 RCC_CFGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t SW:2;
				vuint32_t SWS:2;
				vuint32_t HPRE:4;
				vuint32_t PPRE1:3;
				vuint32_t PPRE2:3;
				vuint32_t ADCPRE:2;
				vuint32_t PLLSRC:1;
				vuint32_t PLLXTPRE:1;
				vuint32_t PLLMUL:4;
				vuint32_t OTGFSPRE:1;
				  vuint32_t:1;
				vuint32_t MCO:4;
				  vuint32_t:4;
			} BIT;	
		} CFGR;

		//+08 RCC_CIR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LSIRDYF:1;
				vuint32_t LSERDYF:1;
				vuint32_t HSIRDYF:1;
				vuint32_t HSERDYF:1;
				vuint32_t PLLRDYF:1;
				vuint32_t PLL2RDYF:1;
				vuint32_t PLL3RDYF:1;
				vuint32_t CSSF:1;
				vuint32_t LSIRDYE:1;
				vuint32_t LSERDYE:1;
				vuint32_t HSIRDYE:1;
				vuint32_t HSERDYE:1;
				vuint32_t PLLRDYE:1;
				vuint32_t PLL2RDYE:1;
				vuint32_t PLL3RDYE:1;
				  vuint32_t:1;
				vuint32_t LSIRDYC:1;
				vuint32_t LSERDYC:1;
				vuint32_t HSIRDYC:1;
				vuint32_t HSERDYC:1;
				vuint32_t PLLRDYC:1;
				vuint32_t PLL2RDYC:1;
				vuint32_t PLL3RDYC:1;
				vuint32_t CSSC:1;
				  vuint32_t:8;
			} BIT;	
		} CIR;

		//+0C RCC_APB2RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t AFIORST:1;
				  vuint32_t:1;
				vuint32_t IOPARST:1;
				vuint32_t IOPBRST:1;
				vuint32_t IOPCRST:1;
				vuint32_t IOPDRST:1;
				vuint32_t IOPERST:1;
				  vuint32_t:2;
				vuint32_t ADC1RST:1;
				vuint32_t ADC2RST:1;
				vuint32_t TIM1RST:1;
				vuint32_t SPI1RST:1;
				  vuint32_t:1;
				vuint32_t USART1RST:1;
				  vuint32_t:17;
			} BIT;	
		} APB2RSTR;

		//+10 RCC_APB1RSTR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM2RST:1;
				vuint32_t TIM3RST:1;
				vuint32_t TIM4RST:1;
				vuint32_t TIM5RST:1;
				vuint32_t TIM6RST:1;
				vuint32_t TIM7RST:1;
				  vuint32_t:5;
				vuint32_t WWDGRST:1;
				  vuint32_t:2;
				vuint32_t SPI2RST:1;
				vuint32_t SPI3RST:1;
				  vuint32_t:1;
				vuint32_t USART2RST:1;
				vuint32_t USART3RST:1;
				vuint32_t UART4RST:1;
				vuint32_t UART5RST:1;
				vuint32_t I2C1RST:1;
				vuint32_t I2C2RST:1;
				  vuint32_t:2;
				vuint32_t CAN1RST:1;
				vuint32_t CAN2RST:1;
				vuint32_t BKBRST:1;
				vuint32_t PWRRST:1;
				vuint32_t DACRST:1;
				  vuint32_t:2;
			} BIT;	
		} APB1RSTR;

		//+14 RCC_AHPENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t DMA1EN:1;
				vuint32_t DMA2EN:1;
				vuint32_t SRAMEN:1;
				  vuint32_t:1;
				vuint32_t FLITFEN:1;
				  vuint32_t:1;
				vuint32_t CRCEN:1;
				  vuint32_t:5;
				vuint32_t OTGFSEN:1;
				  vuint32_t:1;
				vuint32_t ETHMACEN:1;
				vuint32_t ETHMACTXEN:1;
				vuint32_t ETHMACRXEN:1;
				  vuint32_t:15;
			} BIT;	
		} AHPENR;

		//+18 RCC_APB2ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t AFIOEN:1;
				  vuint32_t:1;
				vuint32_t IOPAEN:1;
				vuint32_t IOPBEN:1;
				vuint32_t IOPCEN:1;
				vuint32_t IOPDEN:1;
				vuint32_t IOPEEN:1;
				  vuint32_t:2;
				vuint32_t ADC1EN:1;
				vuint32_t ADC2EN:1;
				vuint32_t TIM1EN:1;
				vuint32_t SPI1EN:1;
				  vuint32_t:1;
				vuint32_t USART1EN:1;
				  vuint32_t:17;
			} BIT;	
		} APB2ENR;

		//+1C RCC_APB1ENR
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM2EN:1;
				vuint32_t TIM3EN:1;
				vuint32_t TIM4EN:1;
				vuint32_t TIM5EN:1;
				vuint32_t TIM6EN:1;
				vuint32_t TIM7EN:1;
				  vuint32_t:5;
				vuint32_t WWDGEN:1;
				  vuint32_t:2;
				vuint32_t SPI2EN:1;
				vuint32_t SPI3EN:1;
				  vuint32_t:1;
				vuint32_t USART2EN:1;
				vuint32_t USART3EN:1;
				vuint32_t UART4EN:1;
				vuint32_t UART5EN:1;
				vuint32_t I2C1EN:1;
				vuint32_t I2C2EN:1;
				  vuint32_t:2;
				vuint32_t CAN1EN:1;
				vuint32_t CAN2EN:1;
				vuint32_t BKBEN:1;
				vuint32_t PWREN:1;
				vuint32_t DACEN:1;
				  vuint32_t:2;
			} BIT;	
		} APB1ENR;

		//+20 RCC_BDCR
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

		//+24 RCC_CSR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LSION:1;
				vuint32_t LSIRDY:1;
				  vuint32_t:22;
				vuint32_t RMVF:1;
				  vuint32_t:1;
				vuint32_t PINRSTF:1;
				vuint32_t PORRSTF:1;
				vuint32_t SFTRSTF:1;
				vuint32_t IWDGRSTF:1;
				vuint32_t WWDGRSTF:1;
				vuint32_t LPWRSTF:1;
			} BIT;	
		} CSR;

		//+28 RCC_AHBSTR
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:12;
				vuint32_t OTGFRST:1;
				  vuint32_t:1;
				vuint32_t ETHMACRST:1;
				  vuint32_t:17;
			} BIT;	
		} AHBSTR;

		//+2C RCC_CFGR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t PREDIV1:4;
				vuint32_t PREDIV2:4;
				vuint32_t PLL2MUL:4;
				vuint32_t PLL3MUL:4;
				vuint32_t PREDIV1SRC:1;
				vuint32_t I2S2SRC:1;
				vuint32_t I2S3SRC:1;
				  vuint32_t:13;
			} BIT;	
		} CFGR2;
	};

//-----------------------------------------------------------------------------
// GPIO
//-----------------------------------------------------------------------------
	struct PORT_tag {
		union {
			vuint32_t REG;
			struct{
				vuint32_t MODE0:2;
				vuint32_t CNF0:2;
				vuint32_t MODE1:2;
				vuint32_t CNF1:2;
				vuint32_t MODE2:2;
				vuint32_t CNF2:2;
				vuint32_t MODE3:2;
				vuint32_t CNF3:2;
				vuint32_t MODE4:2;
				vuint32_t CNF4:2;
				vuint32_t MODE5:2;
				vuint32_t CNF5:2;
				vuint32_t MODE6:2;
				vuint32_t CNF6:2;
				vuint32_t MODE7:2;
				vuint32_t CNF7:2;
			} BIT;	
		} CRL;

		union {
			vuint32_t REG;
			struct{
				vuint32_t MODE8:2;
				vuint32_t CNF8:2;
				vuint32_t MODE9:2;
				vuint32_t CNF9:2;
				vuint32_t MODE10:2;
				vuint32_t CNF10:2;
				vuint32_t MODE11:2;
				vuint32_t CNF11:2;
				vuint32_t MODE12:2;
				vuint32_t CNF12:2;
				vuint32_t MODE13:2;
				vuint32_t CNF13:2;
				vuint32_t MODE14:2;
				vuint32_t CNF14:2;
				vuint32_t MODE15:2;
				vuint32_t CNF15:2;
			} BIT;	
		} CRH;

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

		union {
			vuint32_t REG;
			struct{
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
				  vuint32_t:16;
			} BIT;	
		} BRR;

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

				
	};				

//-----------------------------------------------------------------------------
// AFIO
//-----------------------------------------------------------------------------
	struct AFIO_tag {
		//00 EVCR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PIN:3;
				vuint32_t PORT:3;
				vuint32_t EVOE:1;
				 vuint32_t:25;
			} BIT;	
		} EVCR;
		//04 MAPR
		union {
			vuint32_t REG;
			struct{
				vuint32_t SPI1_REMAP:1;
				vuint32_t I2C1_REMAP:1;
				vuint32_t USART1_REMAP:1;
				vuint32_t USART2_REMAP:1;
				vuint32_t USART3_REMAP:2;
				vuint32_t TIM1_REMAP:2;
				vuint32_t TIM2_REMAP:2;
				vuint32_t TIM3_REMAP:2;
				vuint32_t TIM4_REMAP:1;
				vuint32_t CAN1_REMAP:2;
				vuint32_t PD01_REMAP:1;
				vuint32_t TIM5CH4_IREMAP:1;
				vuint32_t ADC1_ETRGINJ_REMAP:1;
				vuint32_t ADC1_ETRGREG_REMAP:1;
				vuint32_t ADC2_ETRGINJ_REMAP:1;
				vuint32_t ADC2_ETRGREG_REMAP:1;
				vuint32_t ETH_REMAP:1;
				vuint32_t CAN2_REMAP:1;
				vuint32_t MII_RMII_SEL:1;
				vuint32_t SWJ_CFG:3;
				  vuint32_t:1;
				vuint32_t SPI3_REMAP:1;
				vuint32_t TIM2ITR1_IREMAP:1;
				vuint32_t PTP_PPS_REMAP:1;
				  vuint32_t:1;
			} BIT;	
		} MAPR;
		//08 EXTICR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t EXTI0:4;
				vuint32_t EXTI1:4;
				vuint32_t EXTI2:4;
				vuint32_t EXTI3:4;
				  vuint32_t:16;
			} BIT;	
		} EXTICR1;
		//0C EXTICR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t EXTI4:4;
				vuint32_t EXTI5:4;
				vuint32_t EXTI6:4;
				vuint32_t EXTI7:4;
				  vuint32_t:16;
			} BIT;	
		} EXTICR2;
		//10 EXTICR3
		union {
			vuint32_t REG;
			struct{
				vuint32_t EXTI8:4;
				vuint32_t EXTI9:4;
				vuint32_t EXTI10:4;
				vuint32_t EXTI11:4;
				  vuint32_t:16;
			} BIT;	
		} EXTICR3;
		//14 EXTICR4
		union {
			vuint32_t REG;
			struct{
				vuint32_t EXTI12:4;
				vuint32_t EXTI13:4;
				vuint32_t EXTI14:4;
				vuint32_t EXTI15:4;
				  vuint32_t:16;
			} BIT;	
		} EXTICR4;

		vuint32_t RESERVED1;

		//1C MAPR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t TIM15_REMAP:1;
				vuint32_t TIM16_REMAP:1;
				vuint32_t TIM17_REMAP:1;
				vuint32_t CEC_REMAP:1;
				vuint32_t TIM1_DMA_REMAP:1;
				vuint32_t TIM9_REMAP:1;
				vuint32_t TIM10_REMAP:1;
				vuint32_t TIM11_REMAP:1;
				vuint32_t TIM13_REMAP:1;
				vuint32_t TIM14_REMAP:1;
				vuint32_t FSMC_NADV:1;
				vuint32_t TIM67_DAC_DMA_REMAP:1;
				vuint32_t TIM12_REMAP:1;
				vuint32_t MISC_REMAP:1;
				  vuint32_t:8;
			} BIT;	
		} MAPR2;
	};

//-----------------------------------------------------------------------------
// FLASH
//-----------------------------------------------------------------------------
	struct FLASH_tag {
		//+00 FLASH_ACR
		union {
			vuint32_t REG;
			struct{
				vuint32_t LATENCY:3;
				vuint32_t HLFCYA:1;
				vuint32_t PRFTBE:1;
				vuint32_t PRFTBS:1;
				  vuint32_t:26;
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
				vuint32_t BSY:1;
				  vuint32_t:1;
				vuint32_t PGERR:1;
				  vuint32_t:1;
				vuint32_t WRPRTERR:1;
				vuint32_t EOP:1;
				  vuint32_t:26;
			} BIT;	
		} SR;

		//+10 FLASH_CR
		union {
			vuint32_t REG;
			struct{
				vuint32_t PG:1;
				vuint32_t PER:1;
				vuint32_t MER:1;
				  vuint32_t:1;
				vuint32_t OPTPG:1;
				vuint32_t OPTER:1;
				vuint32_t STRT:1;
				vuint32_t LOCK:1;
				  vuint32_t:1;
				vuint32_t OPTWRE:1;
				vuint32_t ERRIE:1;
				  vuint32_t:1;
				vuint32_t EOPIE:1;
				  vuint32_t:19;
			} BIT;	
		} CR;

		//+14 FLASH_AR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FAR:32;
			} BIT;	
		} AR;

		vuint32_t RESERVED1;

		//+1C FLASH_OBR
		union {
			vuint32_t REG;
			struct{
				vuint32_t OPTERR:1;
				vuint32_t RDPRT:1;
				vuint32_t WDG_SW:1;
				vuint32_t nRST_STOP:1;
				vuint32_t nRST_STDBY:1;
				vuint32_t BFB2:1;
				  vuint32_t:4;
				vuint32_t DATA0:8;
				vuint32_t DATA1:8;
				  vuint32_t:6;
			} BIT;	
		} OBR;

		//+20 FLASH_WRPR
		union {
			vuint32_t REG;
			struct{
				vuint32_t WRP:32;
			} BIT;	
		} WRPR;

		vuint32_t RESERVED2[8];

		//+44 FLASH_KEYR
		union {
			vuint32_t REG;
			struct{
				vuint32_t FKEYR:32;
			} BIT;	
		} KEYR2;

		vuint32_t RESERVED3;

		//+4C FLASH_SR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t BSY:1;
				  vuint32_t:1;
				vuint32_t PGERR:1;
				  vuint32_t:1;
				vuint32_t WRPRTERR:1;
				vuint32_t EOP:1;
				  vuint32_t:26;
			} BIT;	
		} SR2;

		//+50 FLASH_CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t PG:1;
				vuint32_t PER:1;
				vuint32_t MER:1;
				  vuint32_t:1;
				vuint32_t OPTPG:1;
				vuint32_t OPTER:1;
				vuint32_t STRT:1;
				vuint32_t LOCK:1;
				  vuint32_t:1;
				vuint32_t OPTWRE:1;
				vuint32_t ERRIE:1;
				  vuint32_t:1;
				vuint32_t EOPIE:1;
				  vuint32_t:19;
			} BIT;	
		} CR2;

		//+54 FLASH_AR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t FAR:32;
			} BIT;	
		} AR2;


		
	};
	
	

//-----------------------------------------------------------------------------
// SYSTEM TIMER
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
				  vuint32_t:6;
				vuint32_t SKEW:1;
				vuint32_t NOREF:1;
			} BIT;	
		} CALIB;
	};
	

//-----------------------------------------------------------------------------
// NVIC
//-----------------------------------------------------------------------------
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
			vuint32_t REG[21];
			struct{
				vuint32_t IP:8;

			} BIT[84];	
		} IPR;
	};


//-----------------------------------------------------------------------------
// SCB
//-----------------------------------------------------------------------------
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
				vuint32_t TBLOFF:30;
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


	};


//-----------------------------------------------------------------------------
// USART
//-----------------------------------------------------------------------------
	struct USART_tag {
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
				  vuint32_t:18;
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
				  vuint32_t:21;
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
// SPI
//-----------------------------------------------------------------------------	
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
				vuint32_t CRCL:1;
				vuint32_t CRCNEXT:1;
				vuint32_t CRCEN:1;
				vuint32_t BIDIOE:1;
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
				vuint32_t NSSP:1;
				vuint32_t FRF:1;
				vuint32_t ERRIE:1;
				vuint32_t RXNEIE:1;
				vuint32_t TXEIE:1;
				vuint32_t DS:4;
				vuint32_t FRXTH:1;
				vuint32_t LDMA_RX:1;
				vuint32_t LDMA_TX:1;
				  vuint32_t:17;
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
				vuint32_t TBSY:1;
				vuint32_t FRE:1;
				vuint32_t FRLVL:2;
				vuint32_t FTLVL:2;
				  vuint32_t:19;
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

		//+14 RXCRCR
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
				  vuint32_t:27;
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
				vuint32_t DUALMOD:4;
				  vuint32_t:2;
				vuint32_t AWDEN:1;
				vuint32_t JAWDEN:1;
				  vuint32_t:8;
			} BIT;	
		} CR1;
		//+08 CR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t ADON:1;
				vuint32_t CONT:1;
				vuint32_t CAL:1;
				vuint32_t RSTCAL:1;
				  vuint32_t:4;
				vuint32_t DMA:1;
				  vuint32_t:2;
				vuint32_t ALIGN:1;
				vuint32_t JEXTSE:3;
				vuint32_t JEXTTRIG:1;
				  vuint32_t:1;
				vuint32_t EXTSEL:3;
				vuint32_t EXTTRIG:1;			
				vuint32_t JSWSTART:1;
				vuint32_t SWSTART:1;
				vuint32_t TSVREFE:1;
				  vuint32_t:8;
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
				  vuint32_t:8;
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

//-----------------------------------------------------------------------------
// DAC
//-----------------------------------------------------------------------------
	struct DAC_tag {
		//+00 CR
		union {
			vuint32_t REG;
			struct{
				vuint32_t EN1:1;
				vuint32_t BOFF1:1;
				vuint32_t TEN1:1;
				vuint32_t TSEL1:3;
				vuint32_t WAVE1:2;
				vuint32_t MAMP1:4;
				vuint32_t DMAEN1:1;
				  vuint32_t:3;
				vuint32_t EN2:1;
				vuint32_t BOFF2:1;
				vuint32_t TEN2:1;
				vuint32_t TSEL2:3;
				vuint32_t WAVE2:2;
				vuint32_t MAMP2:4;
				vuint32_t DMAEN2:1;
				  vuint32_t:3;
			} BIT;	
		} CR;
		//+04 SWTRIGR
		union {
			vuint32_t REG;
			struct{
				vuint32_t SWTRIG1:1;
				vuint32_t SWTRIG2:1;
				  vuint32_t:30;
			} BIT;	
		} SWTRIGR;
		//+08 DHR12R1
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC1DHR:12;
				  vuint32_t:20;
			} BIT;	
		} DHR12R1;
		//+0C DHR12L1
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:4;
				vuint32_t DACC1DHR:12;
				  vuint32_t:16;
			} BIT;	
		} DHR12L1;
		//+10 DHR8R1
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC1DHR:8;
				  vuint32_t:24;
			} BIT;	
		} DHR8R1;
		//+14 DHR12R2
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC2DHR:12;
				  vuint32_t:20;
			} BIT;	
		} DHR12R2;
		//+18 DHR12L2
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:4;
				vuint32_t DACC2DHR:12;
				  vuint32_t:16;
			} BIT;	
		} DHR12L2;
		//+1C DHR8R2
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC2DHR:8;
				  vuint32_t:24;
			} BIT;	
		} DHR8R2;
		//+20 DHR12RD
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC1DHR:12;
				  vuint32_t:4;
				vuint32_t DACC2DHR:12;
				  vuint32_t:4;
			} BIT;	
		} DHR12RD;
		//+24 DHR12LD
		union {
			vuint32_t REG;
			struct{
				  vuint32_t:4;
				vuint32_t DACC1DHR:12;
				  vuint32_t:4;
				vuint32_t DACC2DHR:12;
			} BIT;	
		} DHR12LD;
		//+28 DHR8R2
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC1DHR:8;
				  vuint32_t:8;
				vuint32_t DACC2DHR:8;
				  vuint32_t:8;
			} BIT;	
		} DHR8RD;
		//+2C DOR1
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC1DOR:12;
				  vuint32_t:20;
			} BIT;	
		} DOR1;
		//+30 DOR2
		union {
			vuint32_t REG;
			struct{
				vuint32_t DACC2DOR:12;
				  vuint32_t:20;
			} BIT;	
		} DOR2;
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
				vuint32_t ADD:7;
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
				  vuint32_t:2;
				vuint32_t CC2E:1;
				vuint32_t CC2P:1;
				  vuint32_t:2;
				vuint32_t CC3E:1;
				vuint32_t CC3P:1;
				  vuint32_t:2;
				vuint32_t CC4E:1;
				vuint32_t CC4P:1;
				  vuint32_t:2;
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
		vuint32_t RESERVED1;
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
		vuint32_t RESERVED2;
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
// block addresses
//-----------------------------------------------------------------------------
#define GPIOA (*(volatile struct PORT_tag *) 0x40010800UL)
#define GPIOB (*(volatile struct PORT_tag *) 0x40010C00UL)
#define GPIOC (*(volatile struct PORT_tag *) 0x40011000UL)
#define GPIOD (*(volatile struct PORT_tag *) 0x40011400UL)
#define GPIOE (*(volatile struct PORT_tag *) 0x40011800UL)
#define GPIOF (*(volatile struct PORT_tag *) 0x40011C00UL)
#define GPIOG (*(volatile struct PORT_tag *) 0x40012000UL)
#define AFIO (*(volatile struct AFIO_tag *) 0x40010000UL)

#define RCC (*(volatile struct RCC_tag *) 0x40021000UL)
#define FLASH (*(volatile struct FLASH_tag *) 0x40022000UL)

#define USART1 (*(volatile struct USART_tag *) 0x40013800UL)
#define USART2 (*(volatile struct USART_tag *) 0x40004400UL)
#define USART3 (*(volatile struct USART_tag *) 0x40004800UL)
#define USART4 (*(volatile struct USART_tag *) 0x40004C00UL)
#define USART5 (*(volatile struct USART_tag *) 0x40005000UL)

#define SPI1 (*(volatile struct SPI_tag *) 0x40013000UL)
#define SPI2 (*(volatile struct SPI_tag *) 0x40003800UL)

#define TIM2 (*(volatile struct TIMX_tag *) 0x40000000UL)
#define TIM3 (*(volatile struct TIMX_tag *) 0x40000400UL)

#define ADC1 (*(volatile struct ADC_tag *) 0x40012400UL)
#define ADC2 (*(volatile struct ADC_tag *) 0x40012800UL)
#define DAC1 (*(volatile struct DAC_tag *) 0x40007400UL)

#define I2C1 (*(volatile struct I2C_tag *) 0x40005400UL)
#define I2C2 (*(volatile struct I2C_tag *) 0x40005800UL)

#define STK (*(volatile struct STK_tag *) 0xE000E010UL)
#define NVIC (*(volatile struct NVIC_tag *) 0xE000E100UL)
#define SCB (*(volatile struct SCB_tag *) 0xE000ED00UL)

#define _IS_STM32F1_ 1
#define _CONN_LINE
#define CLOCK_8_8	0x080500	// HSE
#define CLOCK_8_16	0x100E12	// PLL / 2 * 4
#define CLOCK_8_20	0x140E13	// PLL / 2 * 5
#define CLOCK_8_24	0x180E14	// PLL / 2 * 6
#define CLOCK_16_8		0x080E72	// PLL / 8 * 4
#define CLOCK_16_16	0x100500	// HSE
#define CLOCK_16_20	0x140E33	// PLL / 4 * 5
#define CLOCK_16_24	0x180E34	// PLL / 4 * 6
#define CLOCK_I_8	0x080000	// HSI
#define CLOCK_I_16	0x100A02	// PLL 4M x 4
#define CLOCK_I_20	0x140A03	// PLL 4M x 5
#define CLOCK_I_24	0x180A04 	// PLL 4M x 6
#define CLOCK_8_32	0x200E16	// PLL / 2 * 8
#define CLOCK_8_36	0x240E17	// PLL / 2 * 9
#define CLOCK_16_32	0x200E36	// PLL / 4 * 8
#define CLOCK_16_36	0x240E37	// PLL / 4 * 9
#define CLOCK_I_32	0x200A06	// PLL 4M x 8
#define CLOCK_I_36	0x240A07	// PLL 4M x 9
#define CLOCK_8_40	0x284E03	// PLL / 1 * 5
#define CLOCK_8_48	0x304E04	// PLL / 1 * 6
#define CLOCK_16_40	0x284E13	// PLL / 2 * 5
#define CLOCK_16_48	0x314E14	// PLL / 2 * 6
#define CLOCK_25_20	0x140E42	// PLL / 5 * 4
#define CLOCK_25_25	0x190500	// HSE
#define CLOCK_25_40	0x284E46	// PLL / 5 * 8
#define CLOCK_8_64	0x404E06	// PLL / 1 * 8
#define CLOCK_8_72	0x484E07	// PLL / 1 * 9
#define CLOCK_16_64	0x404E16	// PLL / 2 * 8
#define CLOCK_16_72	0x484E17	// PLL / 2 * 9
#define CLOCK_25_50	0x324E36	// PLL / 4 * 8
#define CLOCK_25_75	0x4B4E27	// PLL / 3 * 9
#define	PORT_A 0x40010800
#define	PORT_B 0x40010c00
#define	PORT_C 0x40011000
#define	PORT_D 0x40011400
#define	PORT_E 0x40011800
#define	PORT_F 0x40011c00
#define	PORT_G 0x40012000
#define	PORT_AL 0x40010802
#define	PORT_BL 0x40010c02
#define	PORT_CL 0x40011002
#define	PORT_DL 0x40011402
#define	PORT_EL 0x40011802
#define	PORT_FL 0x40011c02
#define	PORT_GL 0x40012002
#define	PORT_AH 0x40010803
#define	PORT_BH 0x40010c03
#define	PORT_CH 0x40011003
#define	PORT_DH 0x40011403
#define	PORT_EH 0x40011803
#define	PORT_FH 0x40011c03
#define	PORT_GH 0x40012003
#define	HAVE_UART1 1
#define	OUTPUT_UART1 send_uart1
#define	UART1_PORT PORT_A
#define	UART1_TX_PIN 9
#define	UART1_RX_PIN 10
#define	HAVE_UART2 1
#define	OUTPUT_UART2 send_uart2
#define	UART2_PORT PORT_A
#define	UART2_TX_PIN 2
#define	UART2_RX_PIN 3
#define	UART3_PORT PORT_C
#define	UART3_TX_PIN 10
#define	UART3_RX_PIN 11
#define	HAVE_UART3 1
#define	OUTPUT_UART3 send_uart3
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
#define	I2C1_SCL_PIN 6
#define	I2C1_SDA_PIN 7
#define	HAVE_OTG 1
#define	USB_PORT PORT_A
#define	USBDP_PIN 12
#define	USBDM_PIN 11
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
#define	ADC0_PORT PORT_A
#define	ADC0_PIN 0
#define	ADC0_CHANNEL 0
#define	ADC1_PORT PORT_A
#define	ADC1_PIN 1
#define	ADC1_CHANNEL 1
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
#define	ADC5_CHANNEL 10
#define	ADC6_PORT PORT_C
#define	ADC6_PIN 2
#define	ADC6_CHANNEL 10
#define	ADC7_PORT PORT_C
#define	ADC7_PIN 3
#define	ADC7_CHANNEL 10
#define	UNILIB_PAUSE_MS 202
#define EESIZE   340
#define EESTART  0x0803F000
#define EE_PSIZE 2048
#define EE_PAGES 1
#define RAMSIZE 65536
typedef unsigned long PORT_TYPE;
#endif
