;2017年5月4日17:21:46
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1

;将以0结尾的数据段的字符串按照指定位置指定属性显示
;子程序负责显示
;主程序负责给定一个属性(cl存放)和一个位置(行dh,列dl)
;ds:[si]指向字符串首地址
assume cs:codeseg

dataseg segment
	db 'Welcome to masm!',0
dataseg ends

codeseg segment

start:
	mov ax,dataseg
	mov ds,ax
	mov si,0
	
	mov cl,11110101B	;白底紫字闪烁不高亮
	mov dh,13			;行数
	mov dl,30*2			;列起始位置
	
	call show_str
	
mov ax,4C00H
int 21H
;===================显示前的初始化与转化====================
show_str:
	push es
	push di
	
	call show_init
	call show_color
	
	pop di
	pop es
ret

show_init:
	mov ax,0B800H	;显卡起始位置B800H
	mov es,ax		;es不能以立即数赋值
	mov ax,160		;每一行的字节数
	mul dh			;乘以行数
	mov bx,ax		;将偏移值放到bx中
	mov dh,0
	mov di,dx		;将一行中的每个字符的动态偏移量放到di中
ret
;==================将字母逐个显示在屏幕指定位置上=====================
show_color:
	push cx
	push si
	mov ah,cl	;CX在jcxz中会用到，需要将cl的属性信息转存
	mov si,0
	color_loop:
		mov ch,0
		mov cl,ds:[si]	;将需要显示的数据存到cl中
		jcxz show_over	;遇到0就结束
		
		mov es:[bx][di],cl	;低字节放ASCII
		mov es:[bx][di].1,ah	;高字节放属性
		inc si
		add di,2
	jmp short color_loop
show_over:
	pop si
	pop cx
ret
	
codeseg ends
end start