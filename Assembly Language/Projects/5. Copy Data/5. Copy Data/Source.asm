.386
.model	flat, stdcall

include	kernel32.inc
includelib	msvcrt.lib

printf	PROTO C	:dword, :vararg

.data
	needSolve	dd	262144	dup(69681965)
	solvedData	dd	262144	dup(0)
	dataSize	dd	1048576
	startTime	dd	0
	endTime		dd	0
	useTime		dd	0

	Output1		db	'%s%d', 0
	Output2		db	'%s', 0ah, 0
	Msg1		db	'Used ', 0
	Msg2		db	'ms.', 0

.code
start	PROC
	invoke	GetTickCount
	mov	startTime, EAX

	;mov	DS, needSolve
	mov	ESI, OFFSET	needSolve
	;mov	ES,	solvedData
	mov	EDI, OFFSET	solvedData
	mov	ECX, dataSize
	rep	movsb

	invoke	GetTickCount
	mov	endTime, EAX

	mov	ECX, startTime
	mov	EDX, endTime
	sub	EDX, ECX
	mov	useTime, EDX
	
	invoke	printf, offset Output1, offset Msg1, useTime
	invoke	printf, offset Output2, offset Msg2

	ret
start	ENDP
END	start