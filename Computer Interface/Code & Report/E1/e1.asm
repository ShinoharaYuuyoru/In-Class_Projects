   com1k equ 3fbh
   data segment
 p1 db"system ready!$"
 p3 db"communication error!$"
   data ends
   code segment
   assume cs:code,ds:data
main proc far
start:push ds
     xor ax,ax
     push ax
     mov ax,data
     mov ds,ax
     ;下面是要自己写的内容1==========================
     ;写LCR
	 mov dx,3fbh	;03fb,LCR
	 mov al,9ah	;1001 1010，DLAB=1,SB=0无间隔，SP=0设置校验位，EPS=1偶校验，PEN使用校验位，STB=0,停止位1位，L1L0=10,字符长度7位
	 out dx,al 
     ;写分频系数
	 mov dx,3f8h	;波特率除数寄存器低八位DLL
	 mov al,07h	;0100 0000设置分频系数为64(Changed)，基准时钟/（波特率*64）=分频系数,波特率4227*64,1843200/64/4227 = 7 = 07h
	 out dx,al
	 mov dx,3f9h	;波特率除数寄存器高八位DLM
	 mov al,00h	;0000 0000
	 out dx,al
     ;在读写操作前将LCR的最高位清零
   	 mov dx,3fbh	;03fb,LCR
	 mov al,1ah	;0001 1010
	 out dx,al

     ;1============================================
     mov dx,3fch
     mov al,03h
     out dx,al
     mov dx,3f9h
     mov al,0
     out dx,al
     
     call back
     mov dx,offset p1
     mov ah,9
     int 21h
	;下面是要自己写的内容2====================
	;发送部分
send:	mov dx,3fdh;LSR
		in al,dx
		;包括发送状态判断
		test al,20h ;0010 0000发送保持寄存器就绪THRE=1，数据已经从发送保持寄存器专向发送移位寄存器
		;表示可以发送数据，可以从键盘读入要发送的数据
		jz rece	;为了保证不断循环接收发送，不会卡死在发送或接收
		;读键盘输入
	    mov dl,0ffh	;读入方式？
   		mov ah,06h
   		int 21h         	;要传输的字符保存在AL
 		jz rece	;无输入则转向接收
		;有输入则发送
   		 mov dx,3f8h	;THR：发送保持寄存器
		 out dx,al
		 
		cmp al,0dh
		jne goonsend
		call back
goonsend:	 
;2==========================================
        cmp al,'*'
        jz stop
        mov bx,7
        mov ah,14
        int 10h
;下面是自己写的内容3=======================
		;接收部分
rece:	mov dx,3fdh	;LSR线路状态寄存器
		in al,dx
		;包括接收状态判断
		test al,01h	;DR=1,接收缓冲寄存器已经接到数据，否则没数据
		jz send
		
		;出错状态判断
		test al,0eh	;FE=1，帧格式错误；PE=1,奇偶校验错误;OE=1，覆盖错误，数据丢失
		jnz error
		mov dx,3f8h;RBR接收缓冲寄存器
		in al,dx
		;显示？
		
		cmp al,0dh
		jne goonrece
		call back
goonrece:
;3=======================================
        cmp al,'*'
        jz stop
        mov bx,7
        mov ah,14
        int 10h
        jmp send

   error:call back
         mov dx,offset p3
         mov ah,9
         int 21h
         jmp send
    stop:ret
         main endp

back proc near
        push ax
        push dx
        mov dl,0dh
        mov ah,2
        int 21h
        mov dl,0ah
        mov ah,2
        int 21h
        pop dx
        pop ax
        ret
   back endp
   code ends
        end start
