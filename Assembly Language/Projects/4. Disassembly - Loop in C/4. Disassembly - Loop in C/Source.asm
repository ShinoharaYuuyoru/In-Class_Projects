.386
.model	flat, stdcall

includelib	msvcrt.lib

.data
CounterA	dd	0
CounterB	dd	0
SignA		dd	100
SignB		dd	0

.code
start	PROC
	mov	EBX, dword ptr [CounterB]
	.while	EBX < 10
		push	EBX
			mov	EDX, dword ptr [SignB]
			inc	EDX
			mov	dword ptr [SignB], EDX					;SignB++

			mov	EAX, dword ptr [CounterA]
			.while	EAX < 10
				push	EAX
					mov	ECX, dword ptr [SignA]
					dec	ECX
					mov	dword ptr [SignA], ECX			;SignA--
				pop	EAX
				inc	EAX									;CounterA++
			.endw
		pop	EBX
		inc	EBX											;CounterB++
	.endw
	mov	dword ptr [CounterA], EAX
	mov	dword ptr [CounterB], EBX

	ret
start	ENDP
END	start