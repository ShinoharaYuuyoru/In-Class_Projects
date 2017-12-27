.386
.model	flat, stdcall

include	user32.inc
include	kernel32.inc
include	msvcrt.inc

includelib	user32.lib
includelib	kernel32.lib
includelib	msvcrt.lib

.data
	len		db	0
	str1	db	'a','b','c',0
	str2	db	255 dup('x')

.code
start	PROC
	;strcpy
	mov	CL, 0
	mov	EBX, offset str1
	.while	1
		mov	AL, [EBX]
		.if AL == 0
			.break
		.endif
		inc	EBX
		inc	CL
	.endw

	mov	EAX, offset str1
	mov	EBX, offset str2
	mov	DL, 0
	.while DL <= CL
		push	EDX
			mov	DL, [EAX]
			mov	[EBX], DL
		pop	EDX
		inc	EAX
		inc	EBX
		inc	DL
	.endw

	ret
start	ENDP
END	start