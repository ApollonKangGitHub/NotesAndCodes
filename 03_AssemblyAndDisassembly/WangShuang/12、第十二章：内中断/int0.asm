;修改0号中断的中断处理程序为在屏幕中央打印"overflow"
assume cs:code

code segment
start:
	;将do0的程序复制到0000:0200H处的内存
	mov ax,cs
	mov ds,ax
	mov si,offset do0
	
	mov ax,0
	mov es,ax
	mov di,0200H
	
	mov cx,offset do0end - offset do0 
	cld
	rep movsb	
	
	;修改中断向量表
	mov ax,0
	mov es,ax
	mov word ptr es:[0],200H
	mov word ptr es:[2],0
	
mov ax,4C00H
int 21H
;=====================================
do0:
	jmp short do0start
	db 'overflow!'	;0000:0202
	do0start:
		mov ax,cs
		mov ds,ax
		mov si,202H
		
		mov ax,0B800H
		mov es,ax
		mov di,12*160+36*2
		mov cx,9
		s:
			mov al,ds:[si]
			mov es:[di],al
			inc si
			add di,2
		loop s
		
		;除法溢出后的值没有意义不必再继续执行，用不着用iret返回
		mov ax,4C00H	
		int 21H
do0end:nop
;========================================
code ends
end start