assume cs:code,ss:stack

stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	;����ǰ��ɫ
	mov ah,1
	mov al,1	;��ɫǰ��
	call SetScreen
	call Delay
	
	;���ñ���ɫ
	mov ah,2
	mov al,7	;��ɫ����
	call SetScreen
	call Delay
	
	;��������һ��
	mov ah,3
	mov al,0
	call SetScreen
	call Delay
	
	;�������
	mov ah,0
	mov al,0
	call SetScreen
	call Delay
mov ax,4C00H
int 21H
;=============================
Delay:
	push ax
	push dx
	
	mov dx,10H
	mov ax,0
	loopdelay:
			sub ax,1
			sbb dx,0	;(dx)=(dx)-0-CF
			cmp ax,0
		jne loopdelay	;�ڴ�ѭ��
		cmp dx,0
	jne loopdelay	;���ѭ��
	
	pop dx
	pop ax
ret
;====================================
SetScreen:
	jmp short SetBegin
	table dw Set_ClearScreen,Set_ForegroundColor,Set_BackgroundColor,Set_ScollUpOneLine
SetBegin:
	push bx
	;ah���ݹ��ܺ���
	cmp ah,3
	ja SetScreenRet	;����3�Ĵ��ݹ��ܺŷǷ�
	mov bl,ah
	mov bh,0
	add bx,bx
	
	call word ptr table[bx]
	
	SetScreenRet:
	pop bx
ret
;====================================
Set_ClearScreen:
	push bx
	push cx
	push es
	
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov cx,2000
	Loop_Set_ClearScreen:
		mov byte ptr es:[bx],' '
		add bx,2
	loop Loop_Set_ClearScreen
	
	pop es
	pop cx
	pop bx
ret
;====================================
Set_ForegroundColor:
	push bx
	push cx
	push es
	
	mov bx,0B800H
	mov es,bx
	mov bx,1
	mov cx,2000
	Loop_ForegroundColor:
		and byte ptr es:[bx],11111000B	;ǰ��ɫֵΪ0(��)
		or es:[bx],al		;al������ɫ
		add bx,2
	loop Loop_ForegroundColor
	
	pop es
	pop cx
	pop bx
ret
;====================================
Set_BackgroundColor:
	push bx
	push cx
	push es
	
	mov cl,4
	shl al,cl	;al������ɫ����ǰ����������������Ҫ����
	mov bx,0B800H
	mov es,bx
	mov bx,1
	mov cx,2000
	Loop_BackgroundColor:
		and byte ptr es:[bx],10001111B	;ǰ��ɫֵΪ0(��)
		or es:[bx],al		;al������ɫ
		add bx,2
	loop Loop_BackgroundColor
	
	pop es
	pop cx
	pop bx
ret
;====================================
Set_ScollUpOneLine:
	push cx
	push es
	push ds
	push si
	push di
	
	mov si,0B800H
	mov es,si
	mov ds,si
	mov si,160
	mov di,0
	
	cld
	mov cx,24
	
	;��һ�и��Ƶ���һ��
	Loop_ScollUpOneLine:
		push cx
		mov cx,160
		rep movsb
		pop cx
	loop Loop_ScollUpOneLine
	;���һ�����
	mov cx,80
	mov si,0
	Loop_Clrer_lastLine:
		mov byte ptr [160*24+si],' '
		add si,2
	loop Loop_Clrer_lastLine
	pop di
	pop si
	pop ds
	pop es
	pop cx
ret
;====================================
code ends
end start