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

includelib	user32.lib
includelib	comctl32.lib
includelib	masm32.lib
includelib	kernel32.lib
includelib	shell32.lib

;****************************************

WinMain	PROTO	:DWORD, :DWORD, :DWORD, :DWORD

;****************************************

.data
	ClassName	DB	"SimpleWinClass", 0
	AppName	DB	"Calculator", 0
	MenuName	DB	"Menu", 0
	ButtonClassName	DB	"Button", 0
	ButtonText	DB	"Click", 0
	EditClassName	DB	"Edit", 0
	TestString	DB	"Ready", 0

;----------------------------------------

.data?
	hInstance	HINSTANCE	?
	CommandLine	LPSTR	?
	hwndEdit	HWND	?
	hwndButton	HWND	?
	buffer	DB	512	dup(?)

;----------------------------------------
.const
	ButtonID	EQU	1
	EditID	EQU	2
	IDM_HELLO	EQU	1
	IDM_CLEAR	EQU	2
	IDM_GETTEXT	EQU	3
	IDM_EXIT	EQU	4

;****************************************

.code
start:
	invoke	GetModuleHandle, NULL
	mov	hInstance, EAX
	invoke	GetCommandLine
	mov	CommandLine, EAX
	invoke	WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT
	invoke	ExitProcess, EAX

;----------------------------------------
;Create Window
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
			CW_USEDEFAULT, 300, 200, NULL, NULL, \
			hInst, NULL
	mov	hwnd, EAX
	invoke	ShowWindow, hwnd, SW_SHOWNORMAL
	invoke	UpdateWindow, hwnd
	.while	TRUE
		invoke	GetMessage, addr msg, NULL, 0, 0
		.break	.if(!EAX)
		invoke	TranslateMessage, addr msg
		invoke	DispatchMessage, addr msg
	.endw
	mov	EAX, msg.wParam
	ret
WinMain	ENDP

;----------------------------------------
;Calculate
Calculate	PROC	hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
	.if	uMsg == WM_DESTROY
		invoke	PostQuitMessage, NULL
	.elseif	uMsg == WM_CREATE
		invoke	CreateWindowEx, WS_EX_CLIENTEDGE, addr EditClassName, NULL, \
				WS_CHILD or WS_VISIBLE or WS_BORDER or ES_LEFT or ES_AUTOHSCROLL, \
				50, 35, 200, 25, hWnd, EditID, hInstance, NULL
		mov	hwndEdit, EAX
		invoke	SetFocus, hwndEdit
		invoke	CreateWindowEx, NULL, addr ButtonClassName, addr ButtonText, \
				WS_CHILD or WS_VISIBLE or BS_DEFPUSHBUTTON, \
				75, 70, 140, 25, hWnd, ButtonID, hInstance, NULL
		mov	hwndButton, EAX

	.elseif	uMsg == WM_COMMAND
		mov	EAX, wParam
		.if	lParam == 0
			.if	AX == IDM_HELLO
				invoke	SetWindowText, hwndEdit, addr TestString
				invoke	SendMessage, hwndEdit, WM_KEYDOWN, VK_END, NULL
			.elseif	AX == IDM_CLEAR
				invoke	SetWindowText, hwndEdit, NULL
			.elseif	AX == IDM_GETTEXT
				invoke GetWindowText, hwndEdit, addr buffer, 512
				invoke	MessageBox, NULL , addr buffer, addr AppName, MB_OK
			.else
				invoke	DestroyWindow, hWnd
			.endif
		.else
			.if AX == ButtonID
				shr	EAX, 16
				.if	AX == BN_CLICKED
					invoke	SendMessage, hWnd, WM_COMMAND, IDM_GETTEXT, 0
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

end	start