.name 		"Lydeka"
.comment	"Tuturuu ~"

start:
	ld		%0, r10
	zjmp	%:fall

def:
	live	%0
	zjmp	%:def

fill:
	st		r2, -512
	st		r2, -506
	st		r2, -500
	st		r2, -494
	st		r2, -488
	st		r2, -482
	st		r2, -476
	st		r2, -470
	zjmp	%:fill


evenmorefill:
	st		r2, -464
	st		r2, -458
	st		r2, -452
	st		r2, -446
	st		r2, -440
	st		r2, -434
	st		r2, -428
	st		r2, -422
	zjmp	%:evenmorefill

affspam:
	ld		%84, r10		# T
	ld		%117, r11		# u
	ld		%116, r12		# t
	ld		%114, r13		# r
	ld		%126, r14		#	~
	aff		r10
	aff		r11
	aff		r12
	aff		r11
	aff		r13
	aff		r11
	aff		r11
	aff		r14
	aff		r10
	aff		r10
	aff		r11
	aff		r12
	aff		r11
	aff		r13
	aff		r11
	aff		r11
	aff		r14
	aff		r10
	aff		r11
	aff		r12
	aff		r11
	aff		r13
	aff		r11
	aff		r11
	aff		r14
	aff		r10
	aff		r11
	aff		r12
	aff		r11
	aff		r13
	aff		r11
	aff		r11
	aff		r14
	live	%0
	zjmp	%:affspam

fall:
	st		r1, :start
	fork	%:def
	live	%0
	fork	%:forkmore

minizork:
	live	%0

raindown:
	fork	%:minizork
	live	%0
    fork    %:storm
    or      r2, %32, r2

forkmore:
	live	%0
	fork	%:effect

rain:
    live    %2
    fork    %:tsunami
    or      r2, %4, r2

storm:
    live    %2
    fork    %:hail
    or      r2, %16, r2

hail:
    live    %2
    fork    %:rain
    or      r2, %8, r2

tsunami:
    ldi     %:effect, r2, r16
    ld      %0, r15

effect:
    live    %0
    sti     r16, %354, r2
    sti     r16, %402, r2
    sti     r16, %448, r2
    zjmp    %442
    live    %0
    zjmp	%:raindown
