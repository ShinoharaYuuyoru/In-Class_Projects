.386
.model	flat, stdcall
option	casemap: none

;****************************************

include	windows.inc
include	shell32.inc
include	user32.inc
include	comctl32.inc
include	masm32.inc
include	kernel32.inc
include	msvcrt.inc

includelib	user32.lib
includelib	comctl32.lib
includelib	masm32.lib
includelib	kernel32.lib
includelib	shell32.lib
includelib	msvcrt.lib

;****************************************

fopen	PROTO C	:DWORD, :DWORD
feof	PROTO C	:DWORD
fgets	PROTO C	:DWORD, :DWORD, :DWORD
fclose	PROTO C	:DWORD
printf	PROTO C	:DWORD, :vararg

MainPro		PROTO
FileRead	PROTO
GetLine		PROTO
Check		PROTO
CloseFile	PROTO

;****************************************

.data
dfrtLineCtr	DD	0
dfrtLineNum	DD	0
sameFlag	DD	0
lsFlag		DD	0				;Long Short Flag - 0:same length 1:File1.txt is shorter 2:File2.txt is shorter

;----------------------------------------

.data?
file1Ptr	DD	?
file2Ptr	DD	?
file1EOFPtr	DD	?
file2EOFPtr	DD	?
file1Buffer	DB	1024	dup(?)
file2Buffer	DB	1024	dup(?)

;----------------------------------------

.const
stringFmt	DB	"%s", 0
intFmt		DB	"%d", 0
readMode	DB	"rb", 0
file1Name	DB	"File1.txt", 0
file2Name	DB	"File2.txt", 0
markLine	DB	"Line: ", 0
insertEnt	DB	0ah, 0
insertDot	DB	".", 0ah, 0
unsameMsg1	DB	"File1.txt and File2.txt are different. ", 0ah, "There are ", 0
unsameMsg2	DB	" different line(s) between two files.", 0ah, 0
unsameMsg3	DB	"The different line(s) are as mentioned above.", 0ah, 0
sameMsg		DB	"In the same line, File1.txt and File2.txt are the same.", 0ah, 0
file1StrMsg	DB	"***Warning: File1.txt has less line(s) than File2.txt.***", 0ah, 0
file1EndMsg	DB	"File1.txt ends at Line: ", 0
file2StrMsg	DB	"***Warning: File2.txt has less line(s) than File1.txt.***", 0ah, 0
file2EndMsg	DB	"File2.txt ends at Line: ", 0

sizeofBfr	DD	1024
charaPtr	DD	0

;****************************************

.code
start:
	invoke	MainPro

	ret

	MainPro		PROC
	invoke	FileRead
	.while	1
		invoke	GetLine

		.if	(file1EOFPtr != 0) && (file2EOFPtr != 0)	;EOF
			.if	sameFlag == 0
				invoke	printf, offset stringFmt, offset sameMsg
			.else
				invoke	printf, offset stringFmt, offset unsameMsg1
				invoke	printf, offset intFmt, dfrtLineCtr
				invoke	printf, offset stringFmt, offset unsameMsg2
				invoke	printf, offset stringFmt, offset unsameMsg3
			.endif

			.break
		.endif

		invoke	Check

		.if	lsFlag == 1
			invoke	printf, offset stringFmt, offset file1StrMsg
			invoke	printf, offset stringFmt, offset file1EndMsg
			invoke	printf, offset intFmt, dfrtLineNum
			invoke	printf, offset stringFmt, offset insertDot

			.if	sameFlag == 0
				invoke	printf, offset stringFmt, offset sameMsg
			.else
				invoke	printf, offset stringFmt, offset unsameMsg1
				invoke	printf, offset intFmt, dfrtLineCtr
				invoke	printf, offset stringFmt, offset unsameMsg2
				invoke	printf, offset stringFmt, offset unsameMsg3
			.endif

			.break
		.endif
		.if	lsFlag == 2
			invoke	printf, offset stringFmt, offset file2StrMsg
			invoke	printf, offset stringFmt, offset file2EndMsg
			invoke	printf, offset intFmt, dfrtLineNum
			invoke	printf, offset stringFmt, offset insertDot

			.if	sameFlag == 0
				invoke	printf, offset stringFmt, offset sameMsg
			.else
				invoke	printf, offset stringFmt, offset unsameMsg1
				invoke	printf, offset intFmt, dfrtLineCtr
				invoke	printf, offset stringFmt, offset unsameMsg2
				invoke	printf, offset stringFmt, offset unsameMsg3
			.endif

			.break
		.endif
	.endw

	invoke	CloseFile

	ret
	MainPro		ENDP

	FileRead	PROC
		invoke	fopen, offset file1Name, offset readMode
		mov	file1Ptr, EAX
		invoke	fopen, offset file2Name, offset readMode
		mov	file2Ptr, EAX

		ret
	FileRead	ENDP

	GetLine	PROC
		invoke	fgets, offset file1Buffer, sizeofBfr, file1Ptr
		invoke	fgets, offset file2Buffer, sizeofBfr, file2Ptr

		invoke	feof, file1Ptr
		mov	file1EOFPtr, EAX
		invoke	feof, file2Ptr
		mov	file2EOFPtr, EAX
		mov	EAX, file1EOFPtr
		mov	EBX, file2EOFPtr
		.if	EAX != 0
			.if	EBX != 0				;ALL set to EOF line.
				mov	lsFlag, 0
			.else						;File1.txt is shorter.
				mov	lsFlag, 1
			.endif
		.else
			.if	EBX != 0				;File2,txt is shorter.
				mov	lsFlag, 2
			.else						;ALL NOT set to EOF line.
				mov	lsFlag, 0
			.endif
		.endif

		inc	dfrtLineNum

		ret
	GetLine	ENDP

	Check	PROC
		mov	EAX, charaPtr
		mov	EBX, offset file1Buffer
		mov	ECX, offset file2Buffer
		.while 1
			push	EAX
			push	EBX
			push	ECX
			add	EBX, EAX
			add	ECX, EAX

			mov	BL, [EBX]
			mov	CL, [ECX]
			.if	(BL == 0) && (CL == 0)
				pop		ECX
				pop		EBX
				pop		EAX
				.break
			.endif
			.if	BL != CL
				mov	sameFlag, 1
				invoke	printf, offset stringFmt, offset markLine
				invoke	printf, offset intFmt, dfrtLineNum
				invoke	printf, offset stringFmt, offset insertEnt
				inc	dfrtLineCtr

				pop		ECX
				pop		EBX
				pop		EAX
				.break
			.endif
			pop		ECX
			pop		EBX
			pop		EAX

			inc	EAX
		.endw

		ret
	Check	ENDP

	CloseFile	PROC
		invoke	fclose, file1Ptr
		invoke	fclose, file2Ptr

		ret
	CloseFile	ENDP

end	start