
		SR = 0177570
		CC = 0177776
		NOP = 0240
		HALT = 0
		HLT = 0104000		/EMT
		SCOPE = 0104400		/TRAP
		BUFF = FIN
		BEL = 0240
		TWA = 0125252
		TWB = 052525
		CCC = 0257
		SCC = 0277
		PSW = 0177776
		SLR = 0177774
		PIRQ = 0177772

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word PRINT	//trap entrance
		.word 0		//trapped to previous location

		.word SCOPEC	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word .+2	//trap entrance
		.word 0		//trapped to previous location

		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		
		.word 0		

		/ binary instructions
		/ index, and indirect test
BEGIN:		mov	$FIN,sp		
		mov	$BEGIN,RETURN
		mov	$04000,ICOUNT
		SCOPE
		
		/test compare instruction indexed
		mov	$-010,r0
		cmp	A(0),$TWA
		beq	.+4
		HLT
		SCOPE

		mov	$-010,r0
		cmp	$TWA,A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmp	A(r0),$TWB
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmp	$TWB,A(r0)
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		cmp	A(r0),A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmp	A(r0),A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$-010,r0
		mov	$004,r1
		cmp	A(r0),A(r1)
		beq	.+4
		HLT
		SCOPE

		cmp	A(r1),A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$-4,r0
		mov	$010,r1
		cmp	A(r0),A(r1)
		beq	.+4
		HLT
		SCOPE

		mov	$-4,r0
		mov	$010,r1
		cmp	A(r1),A(r0)
		beq	.+4
		HLT
		SCOPE


PAGE03:
		/test move instruction for index
		mov	$-010,r0
		mov	A(r0),TEMP
		cmp	TEMP,$TWA				
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		mov	A(r0),TEMP
		cmp	TEMP,$TWB				
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		mov	$TWA,TEMP(r0)
		cmp	C,$TWA				
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		mov	$TWB,TEMP(r0)
		cmp	TEMP+010,$TWB				
		beq	.+4
		HLT
		SCOPE



		/test bic instruction for indexing
		mov	$-1,TEMP
		mov	$-010,r0
		bic	A(r0),TEMP
		cmp	TEMP,$TWB
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		bic	A(r0),TEMP
		cmp	TEMP,$TWA
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP+010
		mov	$010,r0
		bic	$TWA,TEMP(r0)
		cmp	TEMP+010,$TWB
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		mov	$-001,TEMP-010
		bic	$TWB,TEMP-010
		cmp	TEMP-010,$TWA
		beq	.+4
		HLT
		SCOPE


PAGE04:
		/test substract instruction for indexing
		mov	$TWA,TEMP
		mov	$-010,r0
		sub	A(r0),TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		mov	$-010,r0
		sub	B,TEMP+010(r0)
		beq	.+4
		HLT
		SCOPE
		
		mov	$TWB,TEMP
		mov	$010,r0
		sub	A(r0),TEMP
		beq	.+4
		HLT
		SCOPE
		
		mov	$TWB,TEMP
		mov	$010,r0
		sub	A+010,C(r0)
		beq	.+4
		HLT
		SCOPE

		/test unarys indexed
		mov	$-1,TEMP
		mov	$-010,r0
		clr	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		clr	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-010,r0
		com	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		com	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

PAGE05:
		mov	$-1,TEMP
		mov	$-010,r0
		inc	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		inc	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$-010,r0
		dec	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		dec	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$-010,r0
		neg	D(r0)
		cmp	$-1,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		neg	C(r0)
		cmp	$-1,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-010,r0
		sec
		adc	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		sec
		adc	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE


PAGE06:
		mov	$1,TEMP
		mov	$-010,r0
		sec
		sbc	D(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		sec
		sbc	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE
	
		/ test jmp indexed
		mov	$010,r0
		jmp	RJMP1-010(r0)
RJMP1:		NOP
		SCOPE

		mov	$-010,r0
		jmp	RJMP2+010(r0)
		HLT
RJMP2:		NOP
		SCOPE
		
PAGE07:	
		/test indirect addressing
		/test compare instruction
		cmp	*$B,$TWA
		beq	.+4
		HLT
		SCOPE

		cmp	$TWA,*$B
		beq	.+4
		HLT
		SCOPE

		cmp	*$B,*$B
		beq	.+4
		HLT
		SCOPE

		/test move insatructions
		mov	*$B,r0
		cmp	$TWA,r0
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,*$TEMP
		cmp	B,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	*$B,*$C
		cmp	B,C
		beq	.+4
		HLT
		SCOPE

PAGE08:		
		/test bic instruction indirect
		mov	$-1,r0
		bic	*$B,r0
		cmp	r0,$TWB
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		bic	$TWA,*$TEMP
		cmp	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,C
		bic	*$B,*$C
		cmp	C,$TWB
		beq	.+4
		HLT
		SCOPE
			
		/test substract instruction					
		mov	$TWA,r0
		sub	*$B,r0
		cmp	r0,$0
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		sub	B,*$TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		sub	*$B,TEMP
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

PAGE09:		
		/test add indirect
		clr	r0
		add	*$B,r0
		cmp	$TWA,r0				
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		add	$TWA,*$TEMP
		cmp	$TWA,TEMP
		beq	.+4
		HLT

		mov	$TWA,TEMP
		add	*A+6,*$TEMP
		cmp	TEMP,$-1
		beq	.+4
		HLT
		SCOPE

PAGE10:
		/test unarys indirect
		mov	$-1,TEMP
		clr	*$TEMP
		tst	TEMP
		beq	.+4
		HLT
		SCOPE
		
		mov	$TWA,TEMP
		com	*$TEMP
		cmp	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		inc	*$TEMP
		cmp	$1,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		dec	*$TEMP
		cmp	TEMP,$-1
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		neg	*$TEMP
		cmp	$-1,TEMP
		beq	.+4
		HLT
		SCOPE

		/test indirect addressing with indexing
		/test compare instruction
		
		cmp	*B+2,$TWA
		beq	.+4
		HLT
		SCOPE

		cmp	$TWA,*B+2
		beq	.+4
		HLT
		SCOPE

		cmp	*B+2,*B+2
		beq	.+4
		HLT
		SCOPE
		
PAGE11:
		/test move instructions
		mov	*B+2,r0
		cmp	$TWA,r0
		beq	.+4
		HLT
		SCOPE
		
		mov	$TWA,*TEMP+2
		cmp	B,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	*B+2,*C+2
		cmp	B,C
		beq	.+4
		HLT
		SCOPE
		
		/test bic instruction indirect with indexing
		mov	$-1,r0
		bic	*B+2,r0
		cmp	r0,$TWB
		beq	.+4
		HLT
		SCOPE
		
		mov	$-1,TEMP
		bic	$TWA,*TEMP+2
		cmp	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,C
		bic	*B+2,*C+2
		cmp	A+10,C
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,r0
		sub	*B+2,r0
		cmp	r0,$0
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		sub	B,*TEMP+2
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		sub	*B+2,*TEMP+2
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

PAGE12:
		/test add indirect with indexing
		clr	r0
		add	*B+2,r0
		cmp	$TWA,r0
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		add	$TWA,*TEMP+2
		cmp	$TWA,TEMP
		beq	.+4
		HLT

		mov	$TWA,TEMP
		add	*A+6,*TEMP+2
		cmp	TEMP,$-1
		beq	.+4
		HLT
		SCOPE
		
		/test unarys indirect with indexing
		mov	$-1,TEMP
		clr	*TEMP+2
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		com	*TEMP+2
		cmp	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		inc	*TEMP+2
		cmp	$1,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		dec	*TEMP+2
		cmp	TEMP,$-1
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		neg	*TEMP+2
		cmp	$-1,TEMP
		beq	.+4
		HLT
		SCOPE
		
PAGE13:		
		mov	$-1,TEMP
		sec
		adc	*TEMP+2
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		sec
		sbc	*TEMP+2
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		/test of combined indexing and indirect
		mov	$-6,r0
		cmp	*A(r0),$TWA
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		cmp	$TWA,*A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		mov	$2,r1
		cmp	*A(r0),*A(r1)
		beq	.+4
		HLT
		SCOPE
	
		/test bic instruction		
		mov	$+6,r0
		mov	$-1,TEMP
		bic	*A(r0),TEMP
		cmp	$TWA,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		mov	$-1,C
		bic	$TWA,*TEMP(r0)
		cmp	C,$TWB
		beq	.+4
		HLT
		SCOPE
		
PAGE14:		
		mov	$-1,C
		mov	$-6,r0
		mov	$-6,r1
		bic	*A(r0),*TEMP(r1)
		cmp	$TWB,C
		beq	.+4
		HLT
		SCOPE
		
		/binary instructions
		mov	$-010,r0
		cmpb	A(r0),$000252
		beq	.+4
		HLT
		SCOPE

		mov	$-010,r0
		cmpb	$000252,A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmpb	A(r0),$000125
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmpb	$000125,A(r0)
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		cmpb	A(r0),A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		cmpb	A(r0),A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$-010,r0
		mov	$004,r1
		cmpb	A(r0),A(r1)
		beq	.+4
		HLT
		SCOPE
		
		cmpb	A(r1),A(r0)
		beq	.+4
		HLT
		SCOPE
		
		mov	$-4,r0
		mov	$010,r1
		cmpb	A(r0),A(r1)
		beq	.+4
		HLT

		mov	$-4,r0
		mov	$010,r1
		cmpb	A(r1),A(r0)
		beq	.+4
		HLT
		SCOPE
				
PAGE15:
		/test move instruction for index
		mov	$-010,r0
		movb	A(r0),TEMP
		cmpb	TEMP,$000252
		beq	.+4
		HLT
		SCOPE

		mov	$010,r0
		movb	A(r0),TEMP
		cmpb	TEMP,$000125
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		movb	$TWA,TEMP(r0)
		cmpb	C,$TWA
		beq	.+4
		HLT
		SCOPE
		
		mov	$010,r0
		movb	$TWB,TEMP(r0)
		cmpb	TEMP+010,$TWB
		beq	.+4
		HLT
		SCOPE
		
		/test bic instruction for indexing		
		mov	$-1,TEMP
		mov	$-010,r0
		bicb	A(0),TEMP
		cmpb	TEMP,$0177525		
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		bicb	A(0),TEMP
		cmpb	TEMP,$07652		
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP+010
		mov	$010,r0
		bicb	$TWA,TEMP(r0)
		cmpb	TEMP+010,$02525		
		beq	.+4
		HLT
		SCOPE
		
		mov	$-010,r0
		mov	$-1,TEMP-010
		bicb	$TWB,TEMP-010
		cmpb	TEMP-010,$TWA
		beq	.+4
		HLT
		SCOPE
				
PAGE16:		
		/test unarys indexed
		mov	$-1,TEMP
		mov	$-010,r0
		clrb	D(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-010,r0
		clrb	D(r0)
		cmp	TEMP,$0177400
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-007,r0
		clrb	D(r0)
		cmp	TEMP,$000377
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$+010,r0
		clrb	C(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-010,r0
		comb	D(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		comb	C(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE


PAGE17:

		mov	$-1,TEMP
		mov	$-010,r0
		incb	D(r0)
		tstb	TEMP
		beq	.+4
		HLT
		cmp	TEMP,$0177400
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		incb	C(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$-010,r0
		decb	D(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		decb	C(r0)
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$-010,r0
		negb	D(r0)
		cmp	TEMP,$0377
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		negb	C(r0)
		cmp	TEMP,$0377
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$-010,r0
		sec
		adcb	D(r0)
		cmp	TEMP,$0177400
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		mov	$010,r0
		sec
		adcb	C(r0)
		cmp	TEMP,$0177400
		beq	.+4
		HLT
		SCOPE



PAGE18:		

		
		mov	$0401,TEMP
		mov	$-07,r0
		sec
		sbcb	D(r0)
		cmp	$1,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		mov	$010,r0
		sec
		sbcb	C(r0)
		tst	TEMP
		beq	.+4
		HLT
		SCOPE

		
PAGE19:
		/test indirect addressing + compare
		cmpb	*$B,$000252
		beq	.+4
		HLT
		SCOPE

		cmpb	*$B+1,$000252
		beq	.+4
		HLT
		SCOPE

		cmpb	$TWA,*$B
		beq	.+4
		HLT
		SCOPE

		cmpb	*$B,*$B
		beq	.+4
		HLT
		SCOPE

		/test move instructions
		movb	*$B,r0
		cmpb	$000252,r0
		beq	.+4
		HLT
		SCOPE
		
		movb	$TWA,*$TEMP
		cmpb	B,TEMP
		beq	.+4
		HLT
		SCOPE

		movb	*$B,*$C
		cmpb	B,C
		beq	.+4
		HLT
		SCOPE
		
PAGE20:		
		/test unarys indirect		
		mov	$-1,TEMP
		clrb	*$TEMP
		cmp	TEMP,$0177400
		beq	.+4
		HLT
		SCOPE
		
		mov	$TWA,TEMP
		comb	*$TEMP
		cmp	$0125125,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$TWA,TEMP
		comb	*$TEMP+1
		cmp	$052652,TEMP
		beq	.+4
		HLT
		SCOPE
		
		clr	TEMP
		incb	*$TEMP+1
		cmp	$0400,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		decb	*TEMP+2
		cmp	TEMP,$0377
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		movb	$1,TEMP+1
		negb	*$TEMP+1
		cmp	$0177400,TEMP
		beq	.+4
		HLT
		SCOPE
		
		/test indirect addressing with indexing + compare
		cmpb	*B+2,$TWA
		beq	.+4
		HLT
		SCOPE

		cmpb	$TWA,*B+2
		beq	.+4
		HLT
		SCOPE

		cmpb	*B+2,*B+2
		beq	.+4
		HLT
		SCOPE
		
PAGE21:
		/test move instructions
		movb	*B+2,r0
		cmpb	$TWA,r0
		beq	.+4
		HLT
		SCOPE

		movb	$TWA,*TEMP+2
		cmpb	B,TEMP
		beq	.+4
		HLT
		SCOPE
		
		movb	*B+2,*C+2
		cmpb	B,C
		beq	.+4
		HLT
		SCOPE
		
		/test bic instruction indirect with indexing
		mov	$-1,r0
		bicb	*B+2,r0
		cmpb	r0,$TWB		
		beq	.+4
		HLT
		SCOPE

		mov	$-1,TEMP
		bicb	$TWA,*TEMP+2
		cmpb	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-1,C
		bicb	*B+2,*C+2
		cmpb	A+10,C
		beq	.+4
		HLT
		SCOPE

PAGE22:
		/test unarys indirect with indexing
		mov	$-1,TEMP
		clrb	*TEMP+2
		tstb	TEMP
		beq	.+4
		HLT
		SCOPE
	
		mov	$TWA,TEMP
		comb	*TEMP+2
		cmpb	$TWB,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		incb	*TEMP+2
		cmpb	$1,TEMP
		beq	.+4
		HLT
		SCOPE

		clr	TEMP
		decb	*TEMP+2
		cmpb	TEMP,$-1
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		negb	*TEMP+2
		cmpb	$-1,TEMP
		beq	.+4
		HLT
		SCOPE

PAGE23:
		/test of combined indexing and indirect
		mov	$-1,TEMP
		sec
		adcb	*TEMP+2
		cmp	$0177400,TEMP
		beq	.+4
		HLT
		tstb	TEMP		
		beq	.+4
		HLT
		SCOPE

		mov	$1,TEMP
		sec
		decb	*TEMP+2
		tstb	TEMP		
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		cmpb	*A(r0),$TWA
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		cmpb	$TWA,*A(r0)
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		mov	$2,r1
		cmpb	*A(r0),*A(r1)
		beq	.+4
		HLT
		SCOPE

		/test bic instruction		
		mov	$+6,r0
		mov	$-1,TEMP
		bicb	*A(r0),TEMP
		cmpb	$TWA,TEMP
		beq	.+4
		HLT
		SCOPE

		mov	$-6,r0
		mov	$-1,C
		bicb	$TWA,*TEMP(r0)
		cmpb	C,$000125
		beq	.+4
		HLT
		SCOPE
		
		mov	$B+2,r0
		cmp	*(r0)+,B
		beq	.+4
		HLT
		SCOPE

		mov	$B+4,r0
		cmp	*-(r0),B
		beq	.+4
		HLT
		SCOPE

		mov	$B+4,r0
		cmpb	*-(r0),B
		beq	.+4
		HLT
		SCOPE

		mov	$C+4,r0
		mov	$-1,C
		clrb	*-(r0)
		cmp	C,$0177400
		beq	.+4
		HLT
PAGE24:

		mov	$-1,C
		mov	$-6,r0
		mov	$-6,r1
		bicb	*A(r0),*TEMP(r1)
		cmp	$0177525,C
		beq	.+4
		HLT
		SCOPE
		mov	$TWB,r0		/to be checked at end of prog
		SCOPE
				
		/test jsr instruction
		jsr	pc,TJSR2
TJSR1:		br	TJSR3
TJSR2:		cmp	*sp,$TJSR1
		beq	.+4
		HLT
		rts	pc

TJSR3:		SCOPE

		/test of jsr and rts5 levels
		clr	FLAG
		jsr	pc,SUBR5
		bmi	.+4
		HLT
		SCOPE
		clr	FLAG
		jsr	pc,SUBR6
		tst	FLAG
		bmi	.+4
		HLT
		SCOPE
		.word	0257		/ccc
		clr	FLAG
		jsr	pc,SUBR6
		bmi	.+4
		HLT
		bne	.+4
		HLT
		bvc	.+4
		HLT
		bcs	.+4
		HLT
		SCOPE
		.word	0277		/scc
		clr	FLAG
		jsr	pc,SUBR6
		bmi	.+4
		HLT
		bne	.+4
		HLT
		bvc	.+4
		HLT
		bcs	.+4
		HLT
		SCOPE


/---------------------------- DZQKC ----------------------------------------
		/check branches
PX01:		CCC			/ccc
		bcs	CC0
		bvs	CC0
		beq	CC0
		bmi	CC0
		blt	CC0
		ble	CC0
		blos	CC0
		bhi	.+4
CC0:		HLT

		sen
		bpl	CC1
		bge	CC1
		bgt	CC1
		blt	.+4
CC1:		HLT

		sev
		bvc	CC2
		blt	CC2
		ble	CC2
		bge	.+4
CC2:		HLT

		sec
		bcc	CC3
		blt	CC3
		ble	CC3
		bge	.+4
CC3:		HLT

		sez
		bne	CC4
		bgt	CC4
		bhi	CC4
		ble	.+4
CC4:		HLT
		SCOPE

		/test unary condition codes
		
		SCC			
		clz
		clr	r1
		bcs	CLR0
		bvs	CLR0
		bne	CLR0
		bmi	CLR0
		ble	.+4
CLR0:		HLT

		SCC
		tst	r1
		bcs	TST0
		bvs	TST0
		bne	TST0
		bmi	TST0
		blos	.+4
TST0:		HLT

		CCC
		.word	0266		/sez+sev
		com	r1
		bcc	COM0
		bvs	COM0
		beq	COM0
		bpl	COM0
		blt	.+4
COM0:		HLT

		sec
		adc	r1
		bcc	ADC0
		bvs	ADC0
		bne	ADC0
		bge	.+4
ADC0:		HLT

		sec
		ror	r1
		bcs	ROR0
		bvc	ROR0
		beq	ROR0
		bpl	ROR0
		bgt	.+4
ROR0:		HLT


		SCC
		clv
		dec	r1
		bcc	DEC0
		bvc	DEC0
		beq	DEC0
		bmi	DEC0
		ble	.+4
DEC0:		HLT

		CCC
		inc	r1
		bcs	INC0
		bvc	INC0
		beq	INC0
		bpl	INC0
		bgt	.+4
INC0:		HLT

		SCC
		clv
		neg	r1
		bcc	NEG0
		bvc	NEG0
		beq	NEG0
		bge	.+4
NEG0:		HLT

		sec
		asl	r1
		bcc	ASL0
		bvc	ASL0
		bne	ASL0
		bmi	ASL0
		blos	.+4
ASL0:		HLT

		rol	r1
		bcs	ROL0
		ble	ROL0
		bge	.+4
ROL0:		HLT
		
		asr	r1
		bcc	ASR0
		bvc	ASR0
		bne	ASR0
		blt	.+4
ASR0:		HLT

		SCC
		sbc	r1
		bcc	SBC0
		bvs	SBC0
		blt	.+4
SBC0:		HLT
		
		neg	r1
		swab	r1
		bcs	SWAB0
		bvs	SWAB0
		bne	SWAB0
		bge	.+4
SWAB0:		HLT
		SCOPE
		
		/check register selection
		clr	r0
		SCC
		rol	r0
		mov	r0,r2
		asl	r2
		mov	r2,r3
		asl	r3
		mov	r3,r4
		asl	r4
		mov	r4,r5
		asl	r5
		mov	r5,-(sp)
		bis	r4,(sp)
		bis	r3,(sp)
		bis	r2,(sp)
		bis	r0,(sp)
		cmp	$037,(sp)+
		beq	.+4
		HLT
		bis	r4,(sp)
				
		/check all bits
		CCC
		movb	$0377,r0
S1:		rol	r0
		bcs	S1
		inc	r0
		beq	.+4
		HLT
		
		mov	$16,r0
		clr	r2
S2:		sec
		ror	r2
		dec	r0
		bne	S2
		com	r2
		beq	.+4
		HLT
		
		mov	$0100000,r3
S3:		asr	r3
		bcc	S3
		inc	r3
		beq	.+4
		HLT
		
		movb	$0177401,r4
S4:		add	r4,r4
		bcc	S4
		tst	r4
		beq	.+4
		HLT

		mov	$1,r5
S5:		asl	r5
		bvc	S5
		asl	r5
		bcc	S6
		tst	r5
		beq	.+4
S6:		HLT

		/check register volitility
		clr	r2
		com	r2
		mov	r2,r3
		CCC
		ror	r2
		asr	r2
S7:		mov	r3,r4
		dec	r2
		bne	S7
		inc	r3
		bne	S8
		inc	r4
		beq	.+4
S8:		HLT
						
		/check transfer
GSTST:		bit	$20,*$PSW
		bne	SA7
		mov	r1,-(sp)
		mov	sp,(pc)+
SA1:		.word 	0
		mov	pc,(pc)+
SA2:		.word	0
						
		inc	SA2
SA3:		mov	SA2,r0
		mov	r0,r1
		mov	r1,r2
		mov	r2,r3
		mov	r3,r4
		mov	r4,r5
		bisb	$0340,*$PSW
		mov	r5,sp
		mov	sp,(pc)+
SA4:		.word	0
		mov	SA1,sp		
		bicb	$0340,*$PSW
		cmp	SA4,r0
		bne	SA5
		asl	SA2
		bne	SA3
		br	SA6
		
SA5:		mov	r0,-(sp)
		mov	r1,-(sp)
		mov	r2,-(sp)
		mov	r3,-(sp)
		mov	r4,-(sp)
		mov	r5,-(sp)
		HLT
		
		mov	SA1,sp
SA6:		mov	(sp)+,r1
SA7:		SCOPE
			
		/test unary word instructions	
		br	.+4
		.word	0
		mov	pc,r2
		sub	$4,r2
		clr	(r2)
		
		sec
		ror	(r2)
		blos	ROR1
		bpl	ROR1
		bge	.+4
ROR1:		HLT

		.word 0257
		sec
		dec	(r2)
		bcc	DEC1
		ble	.+4
DEC1:		HLT

		.word 0257
		sec
		adc	(r2)
		bcs	ADC1
		bvc	ADC1
		bpl	ADC1
		bne	.+4
ADC1:		HLT
		
		rol	(r2)
		bcc	ROL1
		bvc	ROL1
		bne	ROL1
		bpl	.+4
ROL1:		HLT

		rol	(r2)
		blos	ROL1A
		bvs	ROL1A
		bpl	.+4
ROL1A:		HLT

		asr	(r2)
		bcc	ASR1
		bvc	ASR1
		bne	ASR1
		bpl	.+4
ASR1:		HLT

		ror	(r2)
		bcs	ROR1A
		bvc	ROR1A
		beq	ROR1A
		bmi	.+4
ROR1A:		HLT

		sec
		inc	(r2)
		bcc	INC1
		bvs	INC1
		beq	INC1
		bmi	.+4
INC1:		HLT

		sbc	(r2)
		bcs	SBC1
		bvs	SBC1
		beq	SBC1
		bmi	.+4
SBC1:		HLT

		
		sec
		sbc	(r2)
		bcs	SBC1A
		bvc	SBC1A
		beq	SBC1A
		bpl	.+4
SBC1A:		HLT

		sec
		adc	(r2)
		bmi	.+4
		HLT
		
		sec
		asl	(r2)
		bcc	ASL1
		bvc	ASL1
		bne	ASL1
		bpl	.+4
ASL1:		HLT

		com	(r2)
		bcc	COM1
		bvs	COM1
		bmi	.+4
COM1:		HLT

		cln
		tst	(r2)
		bcs	TST1
		bvs	TST1
		bpl	TST1
		bne	.+4
TST1:		HLT
		
		sev
		neg	(r2)
		bcc	NEG1
		bvs	NEG1
		bne	.+4
NEG1:		HLT

		dec	(r2)
		bcc	DEC1A
		beq	.+4
DEC1A:		HLT
		SCOPE
		
		/check unary byte instructions
		br	.+4
		.word	0
		mov	pc,r3
		sub	$4,r3
		mov	r3,r4
		inc	r4
		clr	(r3)
		
SB1:		sec
		adcb	(r3)
		bmi	SB2
		incb	(r4)
		br	SB1
SB2:		bvs	.+4
		HLT
		clv
		incb	(r4)
		bcs	INCB1
		bvc	INCB1
		bmi	.+4
INCB1:		HLT

		rolb	(r4)
		bcc	ROLB1
		bvc	ROLB1
		beq	.+4
ROLB1:		HLT

		sbcb	(r4)
		bcc	SBCB1
		bvs	SBCB1
		bmi	.+4
SBCB1:		HLT

		aslb	(r3)
		bcc	ASLB1
		bvc	ASLB1
		beq	.+4
ASLB1:		HLT

		negb	(r3)
		bcs	NEGB1
		bvs	NEGB1
		beq	.+4
NEGB1:		HLT

		SCC
		decb	(r3)		
		bcc	DECB1
		bvs	DECB1
		bne	.+4
DECB1:		HLT
		
		clc
		rorb	(r3)
		bcc	RORB1
		bvc	RORB1
		bpl	.+4
RORB1:		HLT

		clc
		comb	(r4)
		bcc	COMB1
		bvs	COMB1
		beq	.+4
COMB1:		HLT
		
SC1:		asrb	(r3)
		bvc	SC2
		adcb	(r4)
		br	SC1
SC2:		bcs	ASRB1
		beq	.+4
ASRB1:		HLT

		asrb	(r4)
		asrb	(r4)
		bcc	ASRB1A
		bvc	ASRB1A
		bne	.+4
ASRB1A:		HLT

		decb	(r4)
		beq	.+4
		HLT
		
		sec
		rorb	(r4)
		bcs	RORB1A
		bvc	RORB1A
		bmi	.+4
RORB1A:		HLT

		clv
		decb	(r4)
		bvs	.+4
		HLT
		
		sec
		decb	(r3)
		bcc	DECB1A
		bvs	DECB1A
		bmi	.+4
DECB1A:		HLT

		SCC
		swab	(r3)
		bcs	SWAB1
		bvs	SWAB1
		bpl	.+4
SWAB1:		HLT

		tstb	(r4)
		bcs	TSTB1
		bvs	TSTB1
		bmi	.+4
TSTB1:		HLT

		clrb	(r4)
		beq	.+4
		HLT
		
		aslb	(r3)
		bcs	ASLB1A
		bvc	ASLB1A
		bmi	.+4
ASLB1A:		HLT

		comb	(r3)
		bcc	COMB1A
		bvs	COMB1A
		bpl	.+4
COMB1A:		HLT

		swab	(r3)
		beq	.+4
		HLT

		incb	(r3)
		sec
		sbcb	(r3)
		beq	.+4
		HLT
		cmp	$0400,(r3)
		beq	.+4
		HLT
		SCOPE
		
		/check unary word ops
		
		br	.+4
		.word	0
		mov	pc,r4
		sub	$4,r4
		mov	r4,r5
		clr	(r5)
		
		SCC
		clz
		tst	(r5)+
		bcs	TST2
		bvs	TST2
		beq	.+4
TST2:		HLT

		com	-(r5)
		bcc	COM4
		bmi	.+4
COM4:		HLT

		clc
		ror	(r4)+
		bcc	ROR2
		bvc	ROR2
		bpl	.+4
ROR2:		HLT
		
		CCC
		inc	-(r4)
		bvc	INC4
		beq	INC4
		bmi	.+4
INC4:		HLT

		sec
		swab	(r4)+
		bcs	SWAB2
		bmi	.+4
SWAB2:		HLT

		neg	(r5)+
		bcc	NEG2
		bmi	.+4
NEG2:		HLT

		clr	-(r4)
		beq	.+4
		HLT
		
		sec
		ror	-(r5)
		sec
		adc	(r5)+
		bvs	ADC2
		bmi	.+4
ADC2:		HLT

		sev
		asr	(r4)+
		bcc	ASR2
		bvs	ASR2
		bmi	.+4
ASR2:		HLT

		sev
		rol	-(r4)
		bcc	ROL4
		bvs	ROL4
		bmi	.+4
ROL4:		HLT

		sbc	-(r5)
		bcc	.+4
		HLT
		
		dec	(r5)+
		bcs	DEC2
		bvc	DEC2
		bpl	.+4
DEC2:		HLT

		asl	(r4)+
		bvs	.+4
		HLT
		asl	-(r4)
		bcc	ASL4
		bvs	ASL4
		beq	ASL4
		bmi	.+4
ASL4:		HLT

		cmp	$0177774,(r4)+
		beq	.+4
		HLT
		cmp	r4,r5
		beq	.+4
		HLT
		SCOPE
		
		/check unary byte ops
		br	.+4
		.word	0
		mov	pc,r5
		sub	$4,r5
		mov	r5,r0
		mov	r0,r2
		inc	r2
		clr	(r0)
		
		SCC
		clc
		comb	(r5)+
		bcc	COMB2
		bvs	COMB2
		bmi	.+4
COMB2:		HLT

		adcb	-(r2)
		beq	.+4
		HLT
		adcb	(r5)+
		bcs	ADCB2
		bne	.+4
ADCB2:		HLT

		.word	0263		/SEC+SEV
		rorb	-(r5)
		bcc	RORB4
		bvs	RORB4
		beq	RORB4
		bmi	.+4
RORB4:		HLT

		SCC
		rolb	(r2)+
		bcs	ROLB2
		bvs	ROLB2
		beq	ROLB2
		bpl	.+4
ROLB2:		HLT

		CCC
		asrb	(r5)+
		bcs	ASRB2
		bvc	ASRB2
		bmi	.+4
ASRB2:		HLT

		incb	-(r2)
		SCC
		asrb	(r2)+
		bcs	ASRB2A
		bvs	ASRB2A
		bpl	.+4
ASRB2A:		HLT

		.word	0266		/SEZ+SEV
		aslb	-(r5)
		bcc	ASLB4
		bvs	ASLB4
		bmi	.+4
ASLB4:		HLT

		decb	(r2)+
		bcc	DECB2
		bvc	DECB2
		bpl	.+4
DECB2:		HLT

		sbcb	-(r5)
		bcs	SBCB4
		bvs	SBCB4
		beq	.+4
SBCB4:		HLT

		negb	-(r2)
		bcc	NEGB4
		bvs	NEGB4
		bmi	.+4
NEGB4:		HLT

		tstb	(r5)+
		bcs	TSTB2
		beq	.+4
TSTB2:		HLT

		tstb	(r2)+
		beq	TSTB2A
		bmi	.+4
TSTB2A:		HLT

		sec
		swab	-(r2)
		bcs	SWAB4
		bmi	.+4
SWAB4:		HLT

		SCC
		incb	(r5)+
		bcc	INCB2
		bvs	INCB2
		beq	INCB2
		bpl	.+4
INCB2:		HLT

		cmp	(r2)+,$000601
		beq	.+4
		HLT
		cmp	r2,r5
		beq	.+4
		HLT
		SCOPE
		
		/check unary word ops mode 3+5
		br	.+6
		.word	0
		.word	0
		mov	pc,r3
		sub	$4,r3
		clr	(r3)
		mov	r3,r0
		tst	-(r3)
		mov	r0,(r3)
		mov	r3,r4
		
		CCC
		tst	*(r3)+
		beq	.+4
		HLT
		
		sec
		ror	*-(r3)
		bcs	ROR5
		bvc	ROR5
		bmi	.+4
ROR5:		HLT
		
		CCC
		asr	*(r4)+
		bvc	ASR3
		bmi	.+4
ASR3:		HLT

		cln
		asl	*(r3)+
		bcc	ASL3
		bvs	ASL3
		bmi	.+4
ASL3:		HLT

		SCC
		dec	*-(r4)
		bcc	DEC5
		bvc	DEC5
		beq	DEC5
		bpl	.+4
DEC5:		HLT
				
		neg	*-(r3)
		bcc	NEG5
		bvs	NEG5
		bmi	.+4
NEG5:		HLT

		sev
		com	*(r4)+
		bcc	COM3
		bvc	.+4
COM3:		HLT

		inc	*(r3)+
		bcc	INC3
		bpl	.+4
INC3:		HLT

		adc	*-(r4)
		bcs	ADC5
		bvc	ADC5
		bmi	.+4
ADC5:		HLT

		CCC
		rol	*(r4)+
		bcc	ROL3
		bvc	ROL3
		beq	.+4
ROL3:		HLT

		inc	*-(r3)
		sbc	*-(r4)
		bcs	SBC5
		beq	.+4
SBC5:		HLT
		SCOPE
		

		/check unary byte ops mode 3+5
		br	.+010
		.word	0
		.word	0
		.word	0
		mov	pc,r2
		tst	-(r2)
		tst	-(r2)
		mov	r2,r0
		clr	(r0)		
		tst	-(r2)
		tst	-(r2)
		mov	r0,(r2)+
		inc	r0
		mov	r0,(r2)+
		mov	r2,r0
		mov	r2,r5
		
		comb	*-(r2)
		bcc	COMB5
		bmi	.+4
COMB5:		HLT

		tstb	*-(r2)
		beq	.+4
		HLT
		
		sev
		asrb	*-(r5)
		bcc	ASRB5
		bvs	ASRB5
		bmi	.+4
ASRB5:		HLT

		incb	*(r2)+
		bcc	INCB3
		bpl	.+4
INCB3:		HLT

		clc
		rorb	*-(r5)
		bcc	RORB5
		bvc	RORB5
		bne	RORB5
		bpl	.+4
RORB5:		HLT

		aslb	*(r2)+
		bcc	ASLB3
		bvs	ASLB3
		bmi	.+4
ASLB3:		HLT

		adcb	*-(r2)
		bcs	ADCB5
		bmi	.+4
ADCB5:		HLT

		SCC
		rolb	*(r5)+
		blos	ROLB3
		bvs	ROLB3
		bpl	.+4
ROLB3:		HLT

		swab	*-(r2)
		bmi	.+4
		HLT
		
		sec
		sbcb	*(r5)+
		bcs	SBCB3
		beq	.+4
SBCB3:		HLT		
		
		negb	*(r2)+
		decb	*-(r2)
		bcc	DECB5
		beq	.+4
DECB5:		HLT
		SCOPE
		
		/check unary word ops mode 6
		clr	(pc)+
UWM6:		.word	0
		mov	pc,r0
		cmp	-(r0),-(r0)
		SCC
		rol	UWM6
		bcs	ROL6
		bvs	ROL6
		beq	ROL6
		bpl	.+4
ROL6:		HLT

		com	UWM6
		bcc	COM6
		bvs	COM6
		bmi	.+4
COM6:		HLT

		asr	UWM6
		bcs	ASR6
		bvc	ASR6
		bmi	.+4
ASR6:		HLT

		SCC
		neg	UWM6
		bcc	NEG6
		bvs	NEG6
		beq	NEG6
		bpl	.+4
NEG6:		HLT

		SCC
		ror	UWM6
		bcc	ROR6
		bvs	ROR6
		beq	ROR6
		bmi	.+4
ROR6:		HLT

		sbc	UWM6
		bcs	SBC6
		bvc	SBC6
		bpl	.+4
SBC6:		HLT

		clv
		inc	UWM6
		bcs	INC6
		bvc	INC6
		beq	INC6
		bmi	.+4
INC6:		HLT

		asr	UWM6
		sec
		asl	UWM6
		bcc	ASL6
		bvs	ASL6
		bmi	.+4
ASL6:		HLT

		dec	UWM6
		bcc	DEC6
		bvc	DEC6
		bpl	.+4
DEC6:		HLT

		adc	UWM6
		bcs	ADC6
		bvc	ADC6
		bmi	.+4
ADC6:		HLT

		clv
		swab	UWM6
		bmi	.+4
		HLT
		cmp	$0200,(r0)
		beq	.+4
		HLT
		SCOPE
				
		/check unary byte ops mode 6
		mov	$UBM6,r0
		add	*$FACTOR,r0
		clr	UBM6
		SCC
		clz
		tstb	UBM6
		bcs	TSTB6
		bvs	TSTB6
		bne	TSTB6
		bpl	.+4
TSTB6:		HLT

		CCC
		tstb	UBM6+1
		beq	.+4
		HLT
		
		sbcb	UBM6
		bcs	SBCB6
		bvs	SBCB6
		beq	.+4
SBCB6:		HLT

SD1:		sec
		incb	UBM6
		bmi	SD2
		adcb	UBM6+1
		br	SD1
SD2:		bcc	INCB6
		bvs	.+4
INCB6:		HLT

		aslb	UBM6
		bcc	ASLB6
		bvc	ASLB6
		bne	ASLB6
		bpl	.+4
ASLB6:		HLT

		clv
		adcb	UBM6+1
		bcs	ADCB6
		bvc	ADCB6
		bmi	.+4
ADCB6:		HLT

		sec
		rorb	UBM6+1
		bcs	RORB6
		bvc	RORB6
		bmi	.+4
RORB6:		HLT

		comb	UBM6
		bcc	COMB6
		bvs	COMB6
		bmi	.+4
COMB6:		HLT

		sev
		negb	UBM6+1
		bcc	NEGB6
		bvs	NEGB6
		bpl	.+4
NEGB6:		HLT
		
		rolb	UBM6+1
		bcs	ROLB6
		bvc	ROLB6
		bmi	.+4
ROLB6:		HLT

		asrb	UBM6
		bcc	ASRB6
		bvs	ASRB6
		bmi	.+4
ASRB6:		HLT

		incb	UBM6
		bcc	INCB6A
		bvs	INCB6A
		beq	.+4
INCB6A:		HLT

		decb	UBM6+1
		bcc	DECB6A
		bvs	DECB6A
		beq	DECB6A
		bmi	.+4
DECB6A:		HLT

		swab	UBM6
		bcs	SWAB6
		bmi	.+4
SWAB6:		HLT

		rolb	UBM6
		bcc	ROLB6A
		bvc	ROLB6A
		beq	.+4
ROLB6A:		HLT

		tst	UBM6
		bcs	TST6
		bvs	TST6
		beq	.+4
TST6:		HLT
	
		br	.+4
UBM6:		.word	0
		SCOPE
		
		/check binary ops
		
		SCC
		mov	pc,r0
		bcc	MOV0
		bvs	MOV0
		bne	.+4
MOV0:		HLT						
		
		mov	r0,r2
		sev
		sub	r0,r2
		bcs	SUB0
		bvs	SUB0
		beq	.+4
SUB0:		HLT

		clz
		mov	r2,r3
		bcs	MOV0A
		beq	.+4
MOV0A:		HLT

		CCC
		.word	0272		/set V+N
		cmp	r2,r3
		bcs	CMP0
		bvs	CMP0
		bne	CMP0
		bpl	.+4
CMP0:		HLT

		mov	r0,r2
		mov	r2,r3
		add	r2,r3
		asl	r2
		cmp	r2,r3
		beq	.+4
		HLT
		SCOPE
		
		clr	r2
		inc	r2
		br	SE2
SE1:		asl	r2
		bmi	SE4
SE2:		mov	r2,r5
		SCC
		bit	r2,r5
		bcc	SE3
		bvs	SE3
		bne	SE1
SE3:		HLT
SE4:		mov	r2,r5
		CCC
		bit	r2,r5
		bmi	.+4
		HLT
		
		clr	r2
		SCC
		bis	r0,r2
		bcc	BIS0
		bvs	BIS0
		bne	.+4
BIS0:		HLT

		mov	r2,r3
		SCC
		clz
		bic	r0,r3
		bcc	BIC0
		bvs	BIC0
		bne	BIC0
		bpl	.+4
BIC0:		HLT

		mov	r0,r4
		com	r4
		bic	r0,r4
		com	r4
		cmp	r0,r4
		beq	.+4
		HLT
		
		mov	r0,r4
		com	r4
		mov	r4,r3
		bis	r0,r3
		bcc	BIS0A
		bmi	.+4
BIS0A:		HLT

		inc	r3
		beq	.+4
		HLT
		mov	r3,r4
		com	r3
		sec
		ror	r4
		add	r3,r4
		bcc	ADD0
		bvc	ADD0
		beq	ADD0
		bpl	.+4
ADD0:		HLT
		
		mov	pc,r0
		cmp	(r0)+,(r0)+
		cmp	r0,pc
		beq	.+4
		HLT
		
		mov	pc,r0
		add	$010,r0
		mov	r0,r2
		cmp	pc,r0
		bne	CMP0A
		beq	.+4
CMP0A:		HLT
		SCOPE
		
		/check binary byte ops
		mov	$0125252,r3
		mov	r3,r4
		bicb	r3,r4
		cmp	$0125000,r4
		beq	.+4
		HLT
		
		clr	r4
		bisb	r3,r4
		cmp	$0252,r4
		beq	.+4
		HLT
		
		movb	r4,r4
		cmp	$0177652,r4
		beq	.+4
		HLT
		
		bitb	$0177525,r4
		beq	.+4
		HLT
			
		comb	r4
		movb	r4,r4
		cmp	$0125,r4	
		beq	.+4
		HLT
		
		bisb	r3,r4
		incb	r4
		tst	r4
		beq	.+4
		HLT
		SCOPE
		
		/check jump instructions
		
		mov	pc,r0
		add	$012,r0
		SCC
		jmp	(r0)
		br	.+6
		cln	
		br	.+4
		bcc	JMP1
		bvc	JMP1
		bne	JMP1
		bpl	.+4
JMP1:		HLT

		clr	r2
		mov	pc,r3
		br	.+4
		.word	0
		tst	(r3)+
		mov	r3,(r3)
		mov	r3,r0
		add	$022,(r3)
		mov	r3,r0
		jmp	*(r3)+
		br	.+6
		com	r2
		br	.-4
		inc	r2
		bne	JMP3
		tst	(r0)+
		cmp	r0,r3
		beq	.+4
JMP3:		HLT

		clr	r2
		mov	pc,r4
		mov	r4,r0
		br	SF1
		com	r2
		br	SF2
SF1:		cmp	(r4)+,(r4)+
		tst	(r4)+
		jmp	-(r4)
SF2:		inc	r2
		bne	JMP4
		cmp	(r0)+,(r0)+
		cmp	r0,r4
		beq	.+4
JMP4:		HLT

		mov	pc,r3
		br	.+4
SG1:		.word	0
		tst	(r3)+
		mov	r3,(r3)
		add	$016,(r3)+
		mov	r3,r0
		br	SG3
SG2:		com	r2
		br	SG4
SG3:		jmp	*-(r3)		
SG4:		inc	r2
		bne	JMP5
		tst	-(r0)
		cmp	r0,r3
		beq	.+4
JMP5:		HLT

		br	SH2
SH1:		com	r2
		br	SH3
SH2:		jmp	SH1
SH3:		inc	r2
		beq	.+4
JMP6:		HLT

		
		/check JSR
JSRTST:				
		
/---------------------------- END DZQKC ------------------------------------

XOR1:		mov	$010,r2		
		mov	$TWB,r1
		mov	$-1,TEMP
		xor	r1,C(r2)
		cmp	$TWA,TEMP
		beq	XOR1A
		HLT
XOR1A:		SCOPE
		
		mov	$TWA,r3
		mov	$010,r4
		mov	$Y,X+010
		mov	$-1,Y
		xor	r3,*X(r4)
		cmp	$TWB,Y
		beq	XOR1B
		HLT
XOR1B:		SCOPE
		
		/test SOB
		
SOB0:		br	SOB1
SOB2:		br	SOB3
SOB1:		mov	$010,r1
		sob	r1,SOB2
		HLT
SOB3:		br	SOB4
SOB5:		HLT
SOB4:		mov	$1,r1
		sob	r1,SOB5
		SCOPE						
		
MA0:		mov	$SPOINT,sp	/SP=N
		clr	r1
		mov	$7,-(sp)	/SP=n-2
		mov	$1,-(sp)	/SP=n-4
		mov	$06402,-(sp)	/SP=n-6
		mov	sp,r5		/R5=SP-6
		jsr	pc,MARK0	/SP=n-8
		br	MARK0A
MARK0:		mov	2(r5),r1
		rts	r5		/SP=N-6
MARK0A:		cmp	$1,r1
		beq	MA2
		HLT
MA2:		cmp	$SPOINT,sp
		beq	MA3
		HLT
MA3:		cmp	$7,r5
		beq	MA4
		HLT
MA4:		

SXT1:		mov	$010,r2
		clr	TEMP
		mov	$-1,TEMP
		CCC
		sxt	C(r2)
		tst	TEMP
		beq	SXT2
		HLT
		
SXT2:		clr	TEMP
		SCC
		sxt	TEMP
		cmp	$-1,TEMP
		beq	MUL1
		HLT


MUL1:		clr	r3
		mov	$5,r2
		clr	PLIER
		mov	$2,PLIER
		SCC
		mul	PLIER,r2
		bmi	MUL1E
		blos	MUL1E
		bvc	MUL1A
MUL1E:		HLT
MUL1A:		cmp	$012,r3
		beq	MUL1B
		HLT
MUL1B:		tst	r2
		beq	MUL2
		HLT
		
MUL2:		clr	r3
		clr	PLIER
		mov	$TWA,r2
		mov	$2,PLIER
		mul	PLIER,r2
		bcc	MUL2E
		bpl	MUL2E
		bvs	MUL2E
		bne	MUL2A
MUL2E:		HLT
MUL2A:		cmp	$-1,r2
		beq	MUL2B
		HLT
MUL2B:		cmp	$052524,r3
		beq	ASH1
		HLT
		
ASH1:		clr	PLIER
		mov	$1,PLIER
		mov	$TWA,r2
		CCC
		.word 0264
		.word 0270
		ash	PLIER,r2
		bmi	ASH1E
		beq	ASH1E
		bvc	ASH1E
		bcs	ASH1B
ASH1E:		HLT
ASH1B:		cmp	$052524,r2
		beq	ASH2
		HLT
		
ASH2:		clr	PLIER
		mov	$-1,PLIER
		mov	$TWB,r1
		ash	PLIER,r1
		cmp	r1,$025252
		beq	ASHC1
		HLT
		
ASHC1:		clr	r2
		clr	PLIER
		mov	$020,PLIER
		mov	$TWA,r3
		CCC
		sez
		sec
		ashc	PLIER,r2
		bpl	ASHC1E	
		beq	ASHC1E	
		bvc	ASHC1E	
		bcc	ASHC1B
ASHC1E:		HLT
ASHC1B:		cmp	$TWA,r2
		beq	ASHC1C
		HLT
ASHC1C:		tst	r3
		beq	ASHC2
		HLT
		
ASHC2:		clr	r3
		clr	PLIER
		mov	$-020,PLIER
		mov	$TWA,r2
		cln
		sez
		sev
		sec
		ashc	PLIER,r2
		bpl	ASHC2E	
		blos	ASHC2E	
		bvc	ASHC2B
ASHC2E:		HLT
ASHC2B:		cmp	$-1,r2
		beq	ASHC2C
		HLT
ASHC2C:		cmp	$TWA,r3
		beq	DIV1
		HLT
		
DIV1:		mov	$4,r1
		clr	r2
		mov	$TWB,r3
		SCC
		div	B(r1),r2
		bmi	DIV1E
		blos	DIV1E
		bvc	DIV1B
DIV1E:		HLT
DIV1B:		cmp	r2,$1
		beq	DIV1C
		HLT
DIV1C:		tst	r3
		beq	DIV2
		HLT
		
DIV2:		clr	PLIER
		mov	$0157777,r4
		mov	$0100001,r5
		mov	$0100000,PLIER
		SCC
		div	PLIER,r4
		bmi	DIV2E
		blos	DIV2E
		bvc	DIV2B
DIV2E:		HLT
DIV2B:		cmp	r4,$040000
		beq	DIV2C
		HLT
DIV2C:		cmp	r5,$0100001
		beq	DIV2X
		HLT
DIV2X:

		


			
		
		
		
		
		


/---------------------------- END EIS --------------------------------------

/		cmp	r0,$TWB
/		beq	.+4
/		HLT
		
		/power fail setup
		mov	$PFAIL,024
		mov	$0340,026
		
PAGE26:		
		/bell on pass complete
		mov	$052,*$0177566
		tstb	*$0177564
		bpl	.-4
		mov	$012,*$0177566
		tstb	*$0177564
		bpl	.-4
		
		/routine to check for trace trap
TRTRAP:		bit	$10000,SR
		beq	YESTR
		tst	YESTR1
		beq	TRPA
		mov	YESTR1,014
		mov	YESTR2,016
		bic	$020,CC
TRPA:		jmp	BEGIN
TRPB:		.word 0

		/save old contents
YESTR:		mov	014,YESTR1
		mov	016,YESTR2
		mov	$YESRT,014
		clr	016
		com	TRPB
		bmi	.+010
		bis	$020,CC
		jmp	BEGIN
		
YESTR1:		.word 0
YESTR2:		.word 0
YESRT:		rti
		HALT
		
PRINT:		bit	SR,$020000
		beq	.+4
		rti
		mov	(sp)+,SAVPC
		mov	(sp)+,SAVCC
		cmp	-(sp),-(sp)
		mov	$0215,*TDBR
		tstb	*TCSR
		bpl	.-4
		mov	$0212,*TDBR
		tstb	*TCSR
		bpl	.-4
		mov	r2,SAVR2
		mov	r3,SAVR3
		mov	r4,SAVR4
		mov	SAVPC,r2
		jsr	pc,PRTAB
		mov	$0240,*TDBR
		tstb	*TCSR
		bpl	.-4
		mov	SAVCC,r2
		jsr	pc,PRTAB
		mov	SAVR2,r2
		mov	SAVR3,r3
		mov	SAVR4,r4
		tst	SR
		bpl	.+4
		HALT
		rti

PAGE27:

SAVR2:		.word 0
SAVR3:		.word 0
SAVR4:		.word 0
TDBR:		.word 0177566
TCSR:		.word 0177564
SAVPC:		.word 0
SAVCC:		.word 0

PRTAB:		clr	BINCT
		clr	WGTCT
		mov	$LIST,r4
		bicb	$0177,*TCSR
		mov	$05,ASCNT
		mov	$07,SEVEN
		mov	$01,DECML
WAIT1:		tstb	*TCSR
		bpl	WAIT1
		tst	r2
		bmi	MINUS
		mov	$0260,*TDBR
		br	START
MINUS:		mov	$0261,*TDBR
START:		mov	SEVEN,r3
		mov	r2,TOODLE
		com	TOODLE
		bic	TOODLE,r3
		beq	WRTOC
MKNUM:		add	DECML,WGTCT
		inc	BINCT
		cmp	WGTCT,r3
		bne	MKNUM
WRTOC:		add	$0260,BINCT
		mov	BINCT,(r4)+
		add	SEVEN,DECML	
		clr	WGTCT
		clr	BINCT
		dec	ASCNT
		beq	XLIST
		mov	$3,r3
MOADD:		add	SEVEN,SEVEN
		dec	r3
		bne	MOADD
		br	START
		
XLIST:		mov	$5,ASCNT
WAIT2:		tstb	*TCSR
		bpl	WAIT2
		mov	-(r4),*TDBR
		dec	ASCNT
		beq	HDFHM
		br	WAIT2		

HDFHM:		tstb	*TCSR
		bpl	.-4
		rts	pc
TOODLE:		.word 0
SEVEN:		.word 0
DECML:		.word 0
WGTCT:		.word 0
BINCT:		.word 0
ASCNT:		.word 0
LIST:		.word 0
		.word 0
		.word 0
		.word 0
		.word 0

		/scope loop routine entered by user trap
SCOPEA:		bit	$40000,SR
		bne	SCOPEB
		mov	*sp,RETURN
		rti
		
SCOPEB:		cmp 	(sp)+,sp
		mov	(sp)+,CC
		jmp	*RETURN
		
		/scope and/or iteration loop for each test 4000 times
SCOPEC:		bit	$40000,SR
		bne	SCOPEB
		bit	$40000,SR
		bne	SCOPEG
		cmp	SCOPEF,$100
		beq	SCOPEG
		inc	SCOPEF
		br	SCOPEB
SCOPEG:		clr	SCOPEF
		mov	*sp,RETURN
		rti
		
ICOUNT:		.word 0400
SCOPEF:		.word 0
RETURN:		BEGIN
		jmp	0200
		
		/group of nested subroutines
SUBR1:		rts	pc
SUBR2:		com	FLAG
		rts	pc
SUBR3:		jsr	pc,SUBR2
		rts	pc
SUBR4:		jsr	pc,SUBR3
		rts	pc
SUBR5:		jsr	pc,SUBR4
		rts	pc
SUBR6:		jsr	pc,SUBR5
		rts	pc

FLAG:		.word 0

		/enter here on power down or power fail
PFAIL:		mov	r0,-(sp)
		mov	r1,-(sp)
		mov	r2,-(sp)
		mov	r3,-(sp)
		mov	r4,-(sp)
		mov	r5,-(sp)
		mov	024,-(sp)
		mov	sp,SAVR6
		mov	$RESTART,024
		HALT
SAVR6:		.word 0

		/enter here on auto recovery of power fail
RESTART:	mov	SAVR6,sp
		mov	(sp)+,024
		mov	(sp)+,r5
		mov	(sp)+,r4
		mov	(sp)+,r3
		mov	(sp)+,r2
		mov	(sp)+,r1
		mov	(sp)+,r0
		rti		

FACTOR:		.word 0		


B:		.word TWA
		.word B
		.word TWB
		
		.word 0			/filling

A:		.word 0177777
		.word A+004		
		.word TWA
		.word A+010		
		.word TWB
		
C:		.word 0
		.word C

		.word 0			/filling
		.word 0			/filling
		
TEMP:		.word 0
		.word TEMP

		.word 0			/filling
		.word 0			/filling

D:		.word 0		

Y:		.word 0
X:		.word 0

		.=.+0100

FIN:		.word 0
		.word 1
		
PLIER:		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
		.word 0
SPOINT:		.word 0			
		
		
		