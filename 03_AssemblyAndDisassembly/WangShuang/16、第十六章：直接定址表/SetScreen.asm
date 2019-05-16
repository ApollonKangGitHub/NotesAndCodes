assume cs:code,ss:stack

stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	;设置前景色
	mov ah,1
	mov al,1	;蓝色前景
	call SetScreen
	call Delay
	
	;设置背景色
	mov ah,2
	mov al,7	;白色背景
	call SetScreen
	call Delay
	
	;整体上移一行
	mov ah,3
	mov al,0
	call SetScreen
	call Delay
	
	;最后清屏
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
		jne loopdelay	;内存循环
		cmp dx,0
	jne loopdelay	;外层循环
	
	pop dx
	pop ax
ret
;====================================
SetScreen:
	jmp short SetBegin
	table dw Set_ClearScreen,Set_ForegroundColor,Set_BackgroundColor,Set_ScollUpOneLine
SetBegin:
	push bx
	;ah传递功能号码
	cmp ah,3
	ja SetScreenRet	;大于3的传递功能号非法
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
		and byte ptr es:[bx],11111000B	;前景色值为0(黑)
		or es:[bx],al		;al传递颜色
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
	shl al,cl	;al传递颜色不分前景背景，但是我们要区分
	mov bx,0B800H
	mov es,bx
	mov bx,1
	mov cx,2000
	Loop_BackgroundColor:
		and byte ptr es:[bx],10001111B	;前景色值为0(黑)
		or es:[bx],al		;al传递颜色
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
	
	;下一行复制到上一行
	Loop_ScollUpOneLine:
		push cx
		mov cx,160
		rep movsb
		pop cx
	loop Loop_ScollUpOneLine
	;最后一行清空
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