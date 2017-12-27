.386  
.model flat, stdcall  
option casemap: none  
  
include windows.inc  
include kernel32.inc  
include user32.inc  
  
includelib kernel32.lib  
includelib user32.lib  
  
.data  
szCaption   db  "I'm a noob.", 0  
szText      db  "But you too!", 0  
  
.code  
  
main PROC  
    INVOKE MessageBox, NULL, addr szText, addr szCaption, MB_OK  
    INVOKE ExitProcess, 0  
main ENDP  
  
END main  