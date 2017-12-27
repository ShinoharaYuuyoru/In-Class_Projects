.586              ;Target processor.  Use instructions for Pentium class machines 
.MODEL FLAT, C    ;Use the flat memory model. Use C calling conventions 
.STACK            ;Define a stack segment of 1KB (Not required for this example) 
.DATA             ;Create a near data segment.  Local variables are declared after 
                  ;this directive (Not required for this example) 
.CODE             ;Indicates the start of a code segment.

main PROC

push    ebp 
mov     ebp,esp 
mov     edx, 80002418h 
xor     eax,eax 
mov     ecx,20h

SFT1: 
shr     edx,1 
jnc     LOOP1 
inc     eax

LOOP1: 
loop    SFT1 
pop     ebp 
ret

main ENDP 
END 
