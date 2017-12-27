.386
.model	flat, stdcall
option	casemap:none

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

WinMain		PROTO	:DWORD, :DWORD, :DWORD, :DWORD
CheckLegal	PROTO
ChangeToNum	PROTO
PLUS		PROTO
MINUS		PROTO
MULTIPLICATIVE	PROTO
DIVIDE		PROTO
CLEAR		PROTO
sprintf		PROTO C	:DWORD, :DWORD, :vararg


;****************************************

.data
	ClassName	DB	"SimpleWinClass", 0
	AppName	DB	"Calculator", 0
	MenuName	DB	"Menu", 0
	ButtonClassName	DB	"Button", 0
	EditClassName	DB	"Edit", 0

	plusBtnTxt	DB	"+", 0
	minusBtnTxt	DB	"-", 0
	multiBtnTxt	DB	"*", 0
	dividBtnTxt	DB	"/", 0
	clearBtnTxt	DB	"C", 0

	Num1		DD	0
	Num2		DD	0
	RstNum		DD	0	

	FirstNumCnt		DD	0				;Counter
	FirstNumEnd		DD	0				;End of Number
	SecondNumCnt	DD	0
	SecondNumEnd	DD	0
	ResultNumCnt	DD	0
	ResultNumEnd	DD	0
	LegalFlag		DD	0
	ErrorMsg		DB	"Input Error", 0

	szNumFmt		DB	"%d", 0

;----------------------------------------

.data?
	hInstance	HINSTANCE	?
	CommandLine	LPSTR	?
	FirstNum	HWND	?
	SecondNum	HWND	?
	ResultNum	HWND	?

	plusButton	HWND	?
	minusButton	HWND	?
	multiButton	HWND	?
	dividButton	HWND	?
	clearButton	HWND	?

	FirstNumBfr		DB	16	dup(?)
	SecondNumBfr	DB	16	dup(?)
	ResultNumBfr	DB	16	dup(?)

;----------------------------------------
.const
	ButtonID1	EQU	1
	ButtonID2	EQU	2
	ButtonID3	EQU	3
	ButtonID4	EQU	4
	ButtonID5	EQU	5

	EditID1	EQU	1
	EditID2	EQU	2
	EditID3	EQU	3

	IDM_PLUS	EQU	1
	IDM_MINUS	EQU	2
	IDM_MULTI	EQU	3
	IDM_DIVID	EQU	4
	IDM_CLEAR	EQU	5

;****************************************

.code
start:
	invoke	GetModuleHandle, NULL
	mov	hInstance, EAX
	invoke	GetCommandLine
	mov	CommandLine, EAX
	invoke	WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT		;Go into WinMain
	invoke	ExitProcess, EAX											;End

;--------------------Creat Window--------------------
WinMain	PROC	hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:DWORD
	LOCAL	wc:WNDCLASSEX
	LOCAL	msg:MSG
	LOCAL	hwnd:HWND
	mov	wc.cbSize, SIZEOF WNDCLASSEX
	mov	wc.style, CS_HREDRAW or CS_VREDRAW
	mov	wc.lpfnWndProc, OFFSET Calculate
	mov	wc.cbClsExtra, NULL
	mov	wc.cbWndExtra, NULL
	push	hInst
	pop		wc.hInstance
	mov	wc.hbrBackground, COLOR_BTNFACE + 1
	mov	wc.lpszMenuName, OFFSET MenuName
	mov	wc.lpszClassName, OFFSET ClassName
	invoke	LoadIcon, NULL, IDI_APPLICATION
	mov	wc.hIcon, EAX
	mov	wc.hIconSm, EAX
	invoke	LoadCursor, NULL, IDC_ARROW
	mov	wc.hCursor, EAX
	invoke	RegisterClassEx, addr wc
	invoke	CreateWindowEx, WS_EX_CLIENTEDGE, addr ClassName, addr AppName, \
			WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, \
			CW_USEDEFAULT, 640, 480, NULL, NULL, \					;Creat 640*480 window
			hInst, NULL
	mov	hwnd, EAX
	invoke	ShowWindow, hwnd, SW_SHOWNORMAL							;Show Window
	invoke	UpdateWindow, hwnd
	.while	TRUE													;Start listening message
		invoke	GetMessage, addr msg, NULL, 0, 0
		.break	.if(!EAX)											;Exit
		invoke	TranslateMessage, addr msg
		invoke	DispatchMessage, addr msg
	.endw
	mov	EAX, msg.wParam
	ret
WinMain	ENDP

;--------------------Calculate--------------------
Calculate	PROC	hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	.if	uMsg == WM_DESTROY
		invoke	PostQuitMessage, NULL
	.elseif	uMsg == WM_CREATE
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, addr EditClassName, NULL, \
				WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or ES_AUTOHSCROLL, \
				40, 50, 240, 25, hWnd, EditID1, hInstance, NULL
		mov	FirstNum, EAX									;Set First Number editText
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, addr EditClassName, NULL, \
				WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or ES_AUTOHSCROLL, \
				360, 50, 240, 25, hWnd, EditID2, hInstance, NULL
		mov	SecondNum, EAX									;Set Second Number editText
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, addr EditClassName, NULL, \
				WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or ES_AUTOHSCROLL, \
				100, 360, 440, 25, hWnd, EditID3, hInstance, NULL
		mov	ResultNum, EAX									;Set Result Number editText
		invoke	SetFocus, FirstNum							;Set cursor on First Number editText

		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr plusBtnTxt, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				32, 150, 64, 64, hWnd, ButtonID1, hInstance, NULL
		mov	plusButton, EAX									;Set Plus Button
		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr minusBtnTxt, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				160, 150, 64, 64, hWnd, ButtonID2, hInstance, NULL
		mov	minusButton, EAX								;Set Minus Button
		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr multiBtnTxt, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				288, 150, 64, 64, hWnd, ButtonID3, hInstance, NULL
		mov	multiButton, EAX								;Set Multiplication Button
		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr dividBtnTxt, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				416, 150, 64, 64, hWnd, ButtonID4, hInstance, NULL
		mov	dividButton, EAX								;Set Divide Button
		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr clearBtnTxt, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				544, 150, 64, 64, hWnd, ButtonID5, hInstance, NULL
		mov	clearButton, EAX								;Set Clear Button
;----------------------------------------UI OVER----------------------------------------
	.elseif	uMsg == WM_COMMAND
		mov	EAX, wParam
		.if	lParam == 0
			.if	AX == IDM_PLUS
				invoke	GetWindowText, FirstNum, addr FirstNumBfr, 512
				invoke	GetWindowText, SecondNum, addr SecondNumBfr, 512
				invoke	CheckLegal
				mov	EAX, LegalFlag
				.if	EAX == 1					;Input Error
					invoke	MessageBox, NULL , addr ErrorMsg, addr AppName, MB_OK
					invoke	CLEAR				;If illegal, Clear
				.else
					invoke	PLUS				;Else, go Plus
				.endif
				invoke	sprintf, addr ResultNumBfr, addr szNumFmt, RstNum		;sprintf to ResultNumBfr
				invoke	SetWindowText, ResultNum, addr ResultNumBfr				;Set Text to Result editText
				invoke	SendMessage, ResultNum, WM_KEYDOWN, VK_END, NULL		;Send Message

			.elseif	AX == IDM_MINUS
				invoke	GetWindowText, FirstNum, addr FirstNumBfr, 512
				invoke	GetWindowText, SecondNum, addr SecondNumBfr, 512
				invoke	CheckLegal
				mov	EAX, LegalFlag
				.if	EAX == 1
					invoke	MessageBox, NULL , addr ErrorMsg, addr AppName, MB_OK
					invoke	CLEAR
				.else
					invoke	MINUS
				.endif
				invoke	sprintf, addr ResultNumBfr, addr szNumFmt, RstNum
				invoke	SetWindowText, ResultNum, addr ResultNumBfr
				invoke	SendMessage, ResultNum, WM_KEYDOWN, VK_END, NULL

			.elseif	AX == IDM_MULTI
				invoke	GetWindowText, FirstNum, addr FirstNumBfr, 512
				invoke	GetWindowText, SecondNum, addr SecondNumBfr, 512
				invoke	CheckLegal
				mov	EAX, LegalFlag
				.if	EAX == 1
					invoke	MessageBox, NULL , addr ErrorMsg, addr AppName, MB_OK
					invoke	CLEAR
				.else
					invoke	MULTIPLICATIVE
				.endif
				invoke	sprintf, addr ResultNumBfr, addr szNumFmt, RstNum
				invoke	SetWindowText, ResultNum, addr ResultNumBfr
				invoke	SendMessage, ResultNum, WM_KEYDOWN, VK_END, NULL

			.elseif	AX == IDM_DIVID
				invoke	GetWindowText, FirstNum, addr FirstNumBfr, 512
				invoke	GetWindowText, SecondNum, addr SecondNumBfr, 512
				invoke	CheckLegal
				mov	EAX, LegalFlag
				.if	EAX == 1
					invoke	MessageBox, NULL , addr ErrorMsg, addr AppName, MB_OK
					invoke	CLEAR
				.else
					invoke	DIVIDE								;If divide number is 0, also illegal
					mov	EAX, LegalFlag
					.if	EAX == 1
					invoke	MessageBox, NULL , addr ErrorMsg, addr AppName, MB_OK
					invoke	CLEAR
					.else
						invoke	sprintf, addr ResultNumBfr, addr szNumFmt, RstNum
						invoke	SetWindowText, ResultNum, addr ResultNumBfr
						invoke	SendMessage, ResultNum, WM_KEYDOWN, VK_END, NULL
					.endif
				.endif

			.elseif	AX == IDM_CLEAR
				invoke	CLEAR
			.else
				invoke	DestroyWindow, hWnd
			.endif
		.else
			.if AX == ButtonID1
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_PLUS, 0
				.endif
			.endif

			.if AX == ButtonID2
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_MINUS, 0
				.endif
			.endif

			.if AX == ButtonID3
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_MULTI, 0
				.endif
			.endif

			.if AX == ButtonID4
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_DIVID, 0
				.endif
			.endif

			.if AX == ButtonID5
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_CLEAR, 0
				.endif
			.endif
		.endif
	.else
		invoke	DefWindowProc, hWnd, uMsg, wParam, lParam
		ret
	.endif
	xor	EAX, EAX
	ret
Calculate	ENDP

CheckLegal	PROC
	;--------------------First Number Check--------------------
	mov	AL, [FirstNumBfr]				;EAX is Chara
	mov	EBX, offset FirstNumBfr			;EBX is Addr
	mov	ECX, 0							;Counter
	.while	AL != 0
		.if	AL >= 48
			.if	AL <= 57
				sub	AL, 48						;-48
				mov	[EBX], AL					;Save
				inc	ECX							;Counter++
				inc	EBX							;Point to Next
				mov	AL, [EBX]					;Read next Num
			.else
				inc	LegalFlag

				ret
			.endif
		.else
			inc	LegalFlag

			ret
		.endif
	.endw
	dec EBX
	mov	FirstNumEnd, EBX
	mov	FirstNumCnt, ECX

	;--------------------Second Number Check--------------------
	mov	AL, [SecondNumBfr]					;EAX is Chara
	mov	EBX, offset SecondNumBfr			;EBX is Addr
	mov	ECX, 0								;Counter
	.while	AL != 0
		.if	AL >= 48
			.if	AL <= 57
				sub	AL, 48						;-48
				mov	[EBX], AL					;Save
				inc	ECX							;Counter++
				inc	EBX							;Point to Next
				mov	AL, [EBX]					;Read next Num
			.else
				inc	LegalFlag

				ret
			.endif
		.else
			inc	LegalFlag

			ret
		.endif
	.endw
	dec EBX
	mov	SecondNumEnd, EBX
	mov	SecondNumCnt, ECX

	ret
CheckLegal	ENDP

ChangeToNum	PROC
	mov	EAX, 0
	mov	EBX, 0
	mov	ECX, FirstNumCnt
	.while	EBX < ECX					;From 0, multiplicarive 10, and add the number. Next time, multiplicative this sum.
		mov	EDX, 10
		mul	EDX
		push	ECX
			mov	ECX, offset FirstNumBfr
			add	ECX, EBX
			add	AL, [ECX]
		pop		ECX

		inc	EBX
	.endw
	mov	Num1, EAX

	mov	EAX, 0
	mov	EBX, 0
	mov	ECX, SecondNumCnt
	.while	EBX < ECX
		mov	EDX, 10
		mul	EDX
		push	ECX
			mov	ECX, offset SecondNumBfr
			add	ECX, EBX
			add	AL, [ECX]
		pop		ECX

		inc	EBX
	.endw
	mov	Num2, EAX

	ret
ChangeToNum	ENDP

PLUS	PROC
	invoke	ChangeToNum
	mov	EAX, Num1
	mov	EBX, Num2
	add	EAX, EBX
	mov	RstNum, EAX

	ret
PLUS	ENDP

MINUS	PROC
	invoke	ChangeToNum
	mov	EAX, Num1
	mov	EBX, Num2
	sub	EAX, EBX
	mov	RstNum, EAX

	ret
MINUS	ENDP

MULTIPLICATIVE	PROC
	invoke	ChangeToNum
	mov	EAX, Num1
	mov	EBX, Num2
	mul	EBX
	mov	RstNum, EAX

	ret
MULTIPLICATIVE	ENDP

DIVIDE	PROC
	invoke	ChangeToNum
	mov	EAX, Num1
	mov	EBX, Num2
	.if	EBX == 0
		mov	LegalFlag, 1
		
		ret
	.endif
	div	EBX
	mov	RstNum, EAX

	ret
DIVIDE	ENDP

CLEAR	PROC
	invoke	SetWindowText, FirstNum, NULL
	invoke	SetWindowText, SecondNum, NULL
	invoke	SetWindowText, ResultNum, NULL

	mov	Num1, 0
	mov	Num2, 0
	mov	RstNum, 0
	mov	FirstNumCnt, 0
	mov	FirstNumEnd, 0
	mov	SecondNumCnt, 0
	mov	SecondNumEnd, 0
	mov	ResultNumCnt, 0
	mov	ResultNumEnd, 0
	mov	LegalFlag, 0

	ret
CLEAR	ENDP

end	start