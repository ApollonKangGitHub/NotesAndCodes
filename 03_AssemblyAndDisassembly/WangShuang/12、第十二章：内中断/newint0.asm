assume cs:code

code segment
start:
	;设置“rep movsb”循环的源与目的
	mov ax,cs
	mov ds,ax
	mov si,offset donewint0

	mov ax,0
	mov es,ax
	mov di,200H
	
	;循环复制
	mov cx,offset enddonewint0 - offset donewint0
	cld
	rep movsb
	
	;修改中断向量表
	mov ax,0
	mov ds,ax
	mov word ptr ds:[0],200H
	mov word ptr ds:[2],0
	
	mov ax,4C00H
	int 21H
;========================================	
donewint0:
	jmp short begin
	db 'divide error!'	;0000:202H

	begin:
		mov ax,0
		mov ds,ax
		mov si,202H
		
		mov ax,0B800H
		mov es,ax
		mov di,160*12+35*2
		mov cx,13
	show_error:
		mov al,ds:[si]
		mov es:[di],al
		inc si
		add di,2
	loop show_error
	mov ax,4C00H
	int 21H
enddonewint0:nop
;========================================
code ends
end start