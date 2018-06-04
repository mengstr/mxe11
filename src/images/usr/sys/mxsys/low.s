/ low core

/ parameters to be set to include various drivers
/ as well as eis  and dump capability.

eis = 0
dump = 0
rf = 0
rk = 1
rp = 0
hp = 0
tc = 0
tm = 0
lp = 0
fltvect = 1
dl = 1
dc = 0
dh = 0
dhdm = 0
dn = 0
dp = 0

reset = 5

br4 = 200
br5 = 240
br6 = 300
br7 = 340

. = 0^.
	br	1f
	4

/ trap vectors
	trap; br7+0		/ bus error
.if eis
	trap; br7+1
.endif
.if eis-1
	.globl	trapem
	trapem; br7+1		/ illegal instruction
.endif
	trap; br7+2		/ bpt-trace trap
	trap; br7+3		/ iot trap
	trap; br7+4		/ power fail
	trap; br7+5		/ emulator trap
	trap; br7+6		/ system entry

. = 040^.
.globl	start, _dump, _panic
1:	jmp	start
	jmp	_dump

. = 060^.
	klin; br5
	klou; br5

. = 100^.
	kwlp; br6
	kwlp; br6

.if lp
. = 200^.
	lpou; br4
.endif

.if rf
. = 204^.
	rfio; br5
.endif

.if tc
. = 214^.
	tcio; br6
.endif

.if rk
. = 220^.
	rkio; br5
.endif

.if tm
. = 224^.
	tmio; br5
.endif

.if rp
. = 254^.
	rpio; br5
.endif

.if hp
. = 254^.
	hpio; br5
.endif

/ floating vectors go here

.if fltvect
. = 300^.
.endif
.if dl
	klin; br5+1
	klou; br5+1
.endif
.if dc
	dcin; br5+0
	dcou; br5+0
	dcin; br5+1
	dcou; br5+1
.endif
.if dhdm
	dmin; br4
.endif

.if dh
	dhin; br5
	dhou; br5
.endif

.if dp
	dpin; br6
	dpou; br6
.endif

.if dn
	dnou; br5
.endif

//////////////////////////////////////////////////////
/ interface code to C

.globl	call, trap
.globl	_clock
kwlp:
	jsr	r0,call; _clock

.if lp
.globl	_lpint
lpou:
	jsr	r0,call; _lpint
.endif

.if rf
.globl	_rfintr
rfio:
	jsr	r0,call; _rfintr
.endif

.if rk
.globl	_rkintr
rkio:
	jsr	r0,call; _rkintr
.endif

.if rp
.globl	_rpintr
rpio:
	jsr	r0,call; _rpintr
.endif

.if hp
.globl	_hpintr
hpio:
	jsr	r0,call; _hpintr
.endif

.if tc
.globl	_tcintr
tcio:
	jsr	r0,call; _tcintr
.endif

.if tm
.globl	_tmintr
tmio:
	jsr	r0,call; _tmintr
.endif

.globl	_klrint
klin:
	jsr	r0,call; _klrint

.globl	_klxint
klou:
	jsr	r0,call; _klxint

.if dc
.globl	_dcrint
dcin:
	jsr	r0,call; _dcrint

.globl	_dcxint
dcou:
	jsr	r0,call; _dcxint
.endif

.if dhdm
.globl	_dmint
dmin:
	jsr	r0,call; _dmint
.endif

.if dh
.globl	_dhrint
dhin:
	jsr	r0,call; _dhrint

.globl	_dhxint
dhou:
	jsr	r0,call; _dhxint
.endif

.if dp
.globl	_dprint
dpin:
	jsr	r0,call; _dprint

.globl	_dpxint
dpou:
	jsr	r0,call; _dpxint
.endif

.if dn
.globl	_dnint
dnou:
	jsr	r0,call; _dnint
.endif

/ save registers and dump memory


_panic:
_dump:
.if dump
	reset
	mov	r0,*$4
	mov	$6,r0
	mov	r1,(r0)+
	mov	r2,(r0)+
	mov	r3,(r0)+
	mov	r4,(r0)+
	mov	r5,(r0)+
	mov	sp,(r0)+
rkda = 177412
rkcs = 177404
1:
	tstb	*$rkcs
	bge	1b
	mov	$rkda+2,r1
	mov	$[396.\<4]+8.,-(r1)
	clr	-(r1)
	mov	$-28.*1024.,-(r1)
	mov	$3,-(r1)
1:
	tstb	(r1)
	bge	1b
	jmp	*$173010
.endif
.if dump-1
	br	.
.endif

.if rk
.globl _rkaddr

_rkaddr:
	mov	r2,-(sp)
	mov	$dvtab,r2
	mov	4(sp),r0
	bic	$!7,r0
	swab	r0
	asl	r0
	mov	6(sp),r1
0:
	sub	(r2),r1
	bmi	1f
	add	2(r2),r0
	br	0b
1:
	add	(r2),r1
	cmp	(r2)+,(r2)+
	cmp	r2,$dvtab+12.
	blo	0b
	asl	r0
	asl	r0
	asl	r0
	asl	r0
	bis	r1,r0
	mov	(sp)+,r2
	rts	pc

dvtab:
	1200.
	100.
	120.
	10.
	12.
	1.
.endif
