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
     ;������Ҫ�Լ�д������1==========================
     ;дLCR
	 mov dx,3fbh	;03fb,LCR
	 mov al,9ah	;1001 1010��DLAB=1,SB=0�޼����SP=0����У��λ��EPS=1żУ�飬PENʹ��У��λ��STB=0,ֹͣλ1λ��L1L0=10,�ַ�����7λ
	 out dx,al 
     ;д��Ƶϵ��
	 mov dx,3f8h	;�����ʳ����Ĵ����Ͱ�λDLL
	 mov al,07h	;0100 0000���÷�Ƶϵ��Ϊ64(Changed)����׼ʱ��/��������*64��=��Ƶϵ��,������4227*64,1843200/64/4227 = 7 = 07h
	 out dx,al
	 mov dx,3f9h	;�����ʳ����Ĵ����߰�λDLM
	 mov al,00h	;0000 0000
	 out dx,al
     ;�ڶ�д����ǰ��LCR�����λ����
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
	;������Ҫ�Լ�д������2====================
	;���Ͳ���
send:	mov dx,3fdh;LSR
		in al,dx
		;��������״̬�ж�
		test al,20h ;0010 0000���ͱ��ּĴ�������THRE=1�������Ѿ��ӷ��ͱ��ּĴ���ר������λ�Ĵ���
		;��ʾ���Է������ݣ����ԴӼ��̶���Ҫ���͵�����
		jz rece	;Ϊ�˱�֤����ѭ�����շ��ͣ����Ῠ���ڷ��ͻ����
		;����������
	    mov dl,0ffh	;���뷽ʽ��
   		mov ah,06h
   		int 21h         	;Ҫ������ַ�������AL
 		jz rece	;��������ת�����
		;����������
   		 mov dx,3f8h	;THR�����ͱ��ּĴ���
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
;�������Լ�д������3=======================
		;���ղ���
rece:	mov dx,3fdh	;LSR��·״̬�Ĵ���
		in al,dx
		;��������״̬�ж�
		test al,01h	;DR=1,���ջ���Ĵ����Ѿ��ӵ����ݣ�����û����
		jz send
		
		;����״̬�ж�
		test al,0eh	;FE=1��֡��ʽ����PE=1,��żУ�����;OE=1�����Ǵ������ݶ�ʧ
		jnz error
		mov dx,3f8h;RBR���ջ���Ĵ���
		in al,dx
		;��ʾ��
		
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
