.386
.model	flat, stdcall

includelib	msvcrt.lib
printf	PROTO C :dword, :vararg

.data
	Xn		dd	0
	Numm	dd	0
	Numa	dd	0
	Numc	dd	0

	OutInt	db	'%d', 0ah, 0

.code
start	PROC
	mov	EAX, 1
	mov	Xn,	EAX				;seed

	mov	EAX, 1
	shl	EAX, 31
	mov	Numm, EAX			;set m

	mov	EAX, 1103515245
	mov	Numa, EAX			;set a

	mov	EAX, 12345
	mov	Numc, EAX			;set c

	mov	EDX, 1
	.while	EDX <= 100
		push	EDX
			mov	EAX, Xn
			mov	EBX, Numm
			mov	ECX, Numa

			mul	ECX
			mov	ECX, Numc
			add	EAX, ECX

			div	EBX

			mov	Xn, EDX

			invoke	printf, offset OutInt, Xn
		pop	EDX
		inc	EDX
	.endw

	ret
start	ENDP
END	start