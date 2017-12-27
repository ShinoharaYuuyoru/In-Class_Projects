.386
.model flat, stdcall

;include	msvcrt.inc
includelib	msvcrt.lib

scanf	PROTO C	:dword, :vararg
printf	PROTO C	:dword, :vararg

.data
	szFmt	db	'%s', 0
	szOut	db	'%s', 0ah, 0

	FirNumM	db	'Please input the first number:'
	FirNum	db	255 dup(0)
	FirNumC	db	0
	FirNumP	dd	0
	SecNumM	db	'Please input the Second number:'
	SecNum	db	255 dup(0)
	SecNumC	db	0
	SecNumP	dd	0
	Result	db	65535 dup(0)
	ResultC	dd	0
	CutIn	dd	0

	OutputP	dd	65534
	OutCha	db	'%c', 0
	OutEnt	db	0ah, 0

.code
Check	PROC
	;First String Change
	mov	AL, [FirNum]					;EAX is Chara
	mov	EBX, offset FirNum				;EBX is Addr
	mov	CL, 0							;Counter
	.while	AL != 0
		sub	AL, 48						;-48
		mov	[EBX], AL					;Save
		inc	EBX							;Point to Next
		mov	AL, [EBX]					;Read next Num
		inc	CL							;Counter++
	.endw
	dec EBX
	mov	FirNumP, EBX
	mov	FirNumC, CL

	;Second String Change
	mov	AL, [SecNum]					;EAX is Chara
	mov	EBX, offset SecNum				;EBX is Addr
	mov	CL, 0							;Counter
	.while	AL != 0
		sub	AL, 48						;-48
		mov	[EBX], AL					;Save
		inc	EBX							;Point to Next
		mov	AL, [EBX]					;Read next Num
		inc	CL							;Counter++
	.endw
	dec	EBX
	mov	SecNumP, EBX
	mov	SecNumC, CL

	ret
Check	ENDP

Calculate	PROC
	mov	ECX, offset SecNum
	mov	EDX, SecNumP
	.while	EDX >= ECX
		mov	BL, [EDX]						;BL is the multiplicative number.

		push	ECX
		push	EDX
			mov	ECX, offset FirNum
			mov	EDX, FirNumP
			.while	EDX >= ECX				;ECX EDX in use
				push	EBX
					mov	AL, [EDX]			;AX in use.
					mul	BL

					cbw						;Convert Byte to Word
					mov	BL, 10
					div	BL					;The result number is in AL, and the ADD Number to next is in AH

					push	EDX
					push	ECX
						mov	ECX, offset Result	;ECX is the base addr of Result
						mov	EDX, CutIn
						inc	EDX
						mov	CutIn, EDX
						dec	EDX
						add	ECX, EDX			;ECX is now timing addr of Result

						push	EDX
						push	EBX
							mov	BL, [ECX]		;BL is the one of the Number of Result
							push	EAX
							push	ECX
								mov	AL, AH
								add	BL, AL		;Add this time'm result number and Result Number
								.while	1		;Confirm the next ADD Number and add them, and record final number.
									.if	BL > 9	
										sub	BL, 10
										mov	[ECX], BL
										inc	ECX
										mov	BL, [ECX]
										inc	BL
									.else
										mov	[ECX], BL
										.break
									.endif
								.endw
							pop	ECX
							pop	EAX

							inc	ECX				;Point to next Result Number

							mov	BL, [ECX]		;Add Result Number and this time's add number.
							push	EAX
							push	ECX
								add	BL, AL
								.while	1		;Confirm the next ADD Number and add them, and record final number.
									.if	BL > 9
										sub	BL, 10
										mov	[ECX], BL
										inc	ECX
										mov	BL, [ECX]
										inc	BL
									.else
										mov	[ECX], BL
										.break
									.endif
								.endw
							pop	ECX
							pop	EAX
						pop	EBX
						pop	EDX
					pop ECX
					pop	EDX

					dec	EDX
				pop	EBX
			.endw
			mov	EDX, ResultC
			inc	EDX
			mov	CutIn, EDX						;Set next position of Result Number, and ready to use in next ADD
			mov	ResultC, EDX					;Counter++
		pop	EDX
		pop	ECX

		dec	EDX
	.endw

	ret
Calculate	ENDP

Output	PROC
	mov	EAX, offset Result
	mov	EBX, OutputP
	add	EAX, EBX
	mov	CL, [EAX]

	mov	EBX, offset Result			;Get Position of the first number of Result Number
	.while	CL == 0
		dec	EAX
		mov	CL, [EAX]

		.if	EAX < EBX
			mov	EAX, EBX
			.break
		.endif
	.endw

	mov	EDX, offset Result
	.while	EAX >= EDX				;print
		mov	BL, [EAX]
		add	BL,	48
		mov	[EAX], BL
		push	EAX
		push	EBX
		push	ECX
		push	EDX
			invoke	printf, addr OutCha, BL
		pop	EDX
		pop	ECX
		pop	EBX
		pop	EAX
		dec	EAX
	.endw

	invoke	printf, addr OutEnt

	ret
Output ENDP

start PROC
	invoke	printf, addr szOut, addr FirNumM
	invoke	scanf, addr szFmt, addr FirNum
	;invoke	printf, addr szOut, addr FirNum

	invoke	printf, addr szOut, addr SecNumM
	invoke	scanf, addr szFmt, addr SecNum
	;invoke	printf, addr szOut, addr SecNum

	invoke	Check

	invoke	Calculate

	invoke	Output

	ret
start ENDP

end start