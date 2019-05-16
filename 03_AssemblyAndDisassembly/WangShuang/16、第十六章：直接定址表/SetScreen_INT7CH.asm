;说明： 
;在进行这个实验时，安装程序习惯采用下面图1安装结构
;assume cs:code 
;code segment 
;	start: 
;		安装程序 
;-------------------------- 
;		被安装代码 
;-------------------------- 
;code ends 
;end start 
;==   图1   == 
;会出问题，问题有两个: 
;1：table dw Set_ClearScreen……中Set_ClearScreen存放的应该是子程序的偏移地址，这个偏移地址是相对于中断程序入口的，
;而此时Sub1中存放的是相对于安装程序入口的地址。所以应该将被安装代码放到code段标号Start前边。 
;2：中断程序被调用时，table[bx]默认的段存器为cs，所以在安装程序中设置中断向量表时，应设：cs=200h(20H)，ip=0，而不是cs=0，ip=200h
assume cs:code

code segment
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
iret
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
	push ax
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
	pop ax
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
start:	
	mov ax,cs
	mov ds,ax
	mov si,offset SetScreen
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	;复制
	mov cx,offset start - offset SetScreen
	cld
	rep movsb

	;安装
	cli
	mov word ptr es:[7CH*4],0
	mov word ptr es:[7CH*4+2],20H	;CS:IP=20:0=0000:200H
	sti
	
mov ax,4C00H
int 21H
;====================================
code ends
end start