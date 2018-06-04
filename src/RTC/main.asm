;###############################################################################
;                                                                              #
; UNIX-RTC mit ATMEGA8/88      						       #
; (c)2016-2018 Jörg Wolfram   joerg@jcwolfram.de                               #
;                                                                              #
; Dieses Programm ist freie Software. Sie können es unter den Bedingungen      #
; der GNU General Public License, wie von der Free Software Foundation         #
; veröffentlicht, weitergeben und/oder modifizieren, entweder gemäss           #
; Version 3 der Lizenz oder (nach Ihrer Option) jeder späteren Version.        #
;                                                                              #
; Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, dass es       #
; Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, auch ohne die     #
; implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT FÜR EINEN          #
; BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License.      #
;                                                                              #
; Sie sollten ein Exemplar der GNU General Public License zusammen mit         #
; diesem Programm erhalten haben. Falls nicht, schreiben Sie an die Free       #
; Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110,    #
; USA.                                                                         #
;                                                                              #
; Jede Nutzung der Software/Informationen nonkonform zur GPL oder ausserhalb   #
; des Geltungsbereiches der GPL ist untersagt!                                 #
;                                                                              #
;###############################################################################

.include "/usr/local/include/avr/m88def.inc"

.def		const_0	=r2			;0x01 as constant
.def		const_1	=r3			;0x00 as constant

.equ		stack	= 0x3ff			;stack

.cseg
;###############################################################################
; jump to initialization
;###############################################################################
.org 0x00
		rjmp	init

;###############################################################################
; some interrupts
;###############################################################################
.org	INT0addr
			out	EIMSK,const_0		;disable this int
			rjmp	fsm


.org	OC2Aaddr
			dec	r17			;timeout counter
			brne	wx1
			clr	r18			;reset FSM
			cbi	DDRC,1
			cbi	PORTC,1			
wx1:			inc	r16			;precounter
			cpi	r16,0x08
			brne	int_end
			ldi	r16,0x00
			lds	r24,0x100
			add	r24,const_1
			sts	0x100,r24
			lds	r24,0x101
			adc	r24,const_0
			sts	0x101,r24
			lds	r24,0x102
			adc	r24,const_0
			sts	0x102,r24
			lds	r24,0x103
			adc	r24,const_0
			sts	0x103,r24
			sbi	PORTB,3			
			reti
	
int_end:		cbi	PORTB,3
			reti

		
;###############################################################################
; initialize
;###############################################################################
init:			cli			;disable interrupts
			ldi	XL,HIGH(stack)	;stack
			out	SPH,XL
			ldi	XL,LOW(stack)
			out	SPL,XL

			clr	r18			;FSM

			ldi	XL,0x00	
			mov	const_0,XL		;0-byte used as constant
			ldi	XL,0x01	
			mov	const_1,XL		;1-byte used as constant

			ldi	YL,0
			ldi	YH,1
			ldi	XL,64
init_1:			st	Y+,const_0
			dec	XL
			brne	init_1
		
			in	XL,MCUCR
			andi	XL,0xef			;enable pullups
			out	MCUCR,XL
calibration:		ldi	XL,0x5C
			sts	OSCCAL,XL

;-------------------------------------------------------------------------------
; port configuration
;-------------------------------------------------------------------------------
			ldi	XL,0xff		;outputs 
			out	DDRB,XL		;port B direction
			ldi	XL,0x00
			out	PORTB,XL	;set 

			ldi	XL,0xfc		;outputs
			out	DDRC,XL		;port C direction
			ldi	XL,0x00
			out	PORTC,XL	;set

			ldi	XL,0xfb		;PD2 is input
			out	DDRD,XL
			ldi	XL,0x04		;enable Pull-up
			out	PORTD,XL
	
			sts	EICRA,const_0	;INT at low level
			out	EIMSK,const_1	;activate INT1

;-------------------------------------------------------------------------------
; timer2 configuration
;-------------------------------------------------------------------------------
			ldi	XL,0x03		;/4
			sts	OCR2A,XL

			ldi	XL,0x02		;CTC
			sts	TCCR2A,XL

			ldi	XL,0x07		;CTC, f/1024
			sts	TCCR2B,XL

			ldi	XL,0x02		;OC2A int enabled
			sts	TIMSK2,XL
		
			ldi	XL,0x20		;osc enabled
			sts	ASSR,XL
		
			ldi	ZL,0
			ldi	ZH,0
wx2:			sbiw	ZL,1
			brne	wx2

;-------------------------------------------------------------------------------
; switch off all unneeded
;-------------------------------------------------------------------------------
			ldi	XH,0x60		;disable BOD
			ldi	XL,0x40
			out	MCUCR,XH
			out	MCUCR,XL
		
			ldi	XL,0xAF		;power reduction except timer 2
			sts	PRR,XL
		
;-------------------------------------------------------------------------------
; the main loop
;-------------------------------------------------------------------------------
			ldi	XL,0x07		;07 power-save, sleep enabled
			out	SMCR,XL
			sei

loop:			ldi	XL,0x07		;07 power-save, sleep enabled
			out	SMCR,XL

			ldi	ZL,80		;wait a little bit before sleep again
wx0:			dec	ZL
			brne	wx0

			cbi	PORTC,0		;disable PU
			sleep			;wait for INT
			rjmp	loop
			
			
;-------------------------------------------------------------------------------
; the r/w FSM
;-------------------------------------------------------------------------------
fsm:			ldi	r17,0x04	;reset timeout
			mov	XL,r18
			andi	XL,0xE0
			brne	fsm_40
			cpi	r18,0x00
			brne	fsm_01
			clr	YL
			sbic	PINC,1		;skip if bit=0
			inc	YL
			inc	r18
			rjmp	fsm_end

fsm_01:			cpi	r18,0x4
			brne	fsm_02
			ldi	r18,0x80	;write
			sbic	PINC,1		;skip if read
			rjmp	fsm_end
			ldi	r18,0x40	;read
			;get current value
			lsl	YL
			lsl	YL
			ldi	YH,1
			ld	r20,Y+
			ld	r21,Y+
			ld	r22,Y+
			ld	r23,Y+
			rjmp	fsm_end		;OK, done
			
fsm_02:			lsl	YL
			sbic	PINC,1		;skip if bit=0
			inc	YL
			inc	r18
			rjmp	fsm_end
			
			
fsm_40:			cpi	XL,0x40		;read shift
			brne	fsm_60
			sbi	DDRC,1		;output
			sbrc	r23,7		;set data line
			sbi	PORTC,1
			sbrs	r23,7
			cbi	PORTC,1	
			lsl	r20		;prepare next bit
			rol	r21
			rol	r22
			rol	r23
			inc	r18		;clear FSM
			rjmp	fsm_end		;OK, done
			
fsm_60:			cpi	XL,0x60		;read shift end
			brne	fsm_80
			cbi	DDRC,1		;input
			cbi	PORTC,1		;no pull
			clr	r18
			rjmp	fsm_end		;OK, done
			
fsm_80:			cpi	XL,0x80		;write shift
			brne	fsm_A0
			sbi	PORTB,3			
			lsl	r20
			rol	r21
			rol	r22
			rol	r23
			sbic	PINC,1
			ori	r20,1
			inc	r18
			rjmp	fsm_end		;OK, done
		
fsm_A0:			cpi	XL,0xA0		;write shift end
			brne	fsm_end
;			cbi	PORTB,3			
			lsl	YL
			lsl	YL
			ldi	YH,1
			st	Y+,r20
			st	Y+,r21
			st	Y+,r22
			st	Y+,r23
			clr	r18		;clear FSM

fsm_end:		sei			;re-enable interrupts
		
fsm_end_1:		sbis	PIND,2		;wait until clock inactive
			rjmp	fsm_end_1	
			out	EIFR,const_1	;clear int
			out	EIMSK,const_1	;enable exint
			reti			;exit
			