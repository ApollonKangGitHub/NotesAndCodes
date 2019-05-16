;2017年5月4日13:43:52
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1

;如何将数据段中的十进制数字以字符串的形式显示在屏幕上
assume cs:codeseg,ss:stackseg,ds:dataseg
dataseg segment
	dw 65535,12366,20121,30010,65534,60124,36524,18451
dataseg ends

data segment
	db 64 dup (0)
data ends

stackseg segment
	db 64 dup (0)
stackseg ends

codeseg segment
start:
	mov ax,dataseg
	mov es,ax
	mov ax,stackseg
	mov ss,ax
	mov ax,data
	mov ds,ax
	mov sp,64
	mov si,0
	
	mov di,0
	mov cx,8
	loop_change:
		mov ax,es:[di]
		call dtoc
		add di,2
	loop loop_change
	
	mov si,0
	mov dh,5
	mov dl,35*2
	mov al,10000000B
	mov cx,8
	loop_show:
		push cx
		inc al
		mov cl,al
		call show_str
		inc dh
		pop cx 
	loop loop_show
	
mov ax,4C00H
int 21H

;====================ASCII的数字+30H转字符，结果放在ds:[si]中以便输出===================
dtoc:
	push cx
	mov dx,0
	push dx
	
	mov bx,10
	dtoc_begin:
		mov dx,0	;高位用不上清零
		div bx
		add dx,30H		;余数数字转字符
		push dx
		mov cx,ax		
		jcxz dtoc_again	;商为0就结束数字->字符的转换
		jmp short dtoc_begin
		
	;由于按取余的顺序直接放入es:[si]开始的空间其顺序是反的，所以需要在转换成字符后先全部入栈，
	;再逐个出栈并按地址从小到大放到es:[si]开始的空间中去
	dtoc_again:
		pop cx
		mov ds:[si],cl
		inc si
		jcxz dtoc_over
		jmp short dtoc_again
	
	dtoc_over:
	pop cx
ret
;===================显示前的初始化与转化====================
show_str:
	push es
	push dx
	push ax
	
	mov ax,0B800H	;显卡起始位置B800H
	mov es,ax		;es不能以立即数赋值
	mov ax,160		;每一行的字节数
	mul dh			;乘以行数
	mov bx,ax		;将偏移值放到bx中
	mov dh,0
	mov di,dx		;将一行中的每个字符的动态偏移量放到di中
	
	call show_color
	
	pop ax
	pop dx
	pop es
ret
;==================将字母逐个显示在屏幕指定位置上=====================
show_color:
	mov ah,cl	;CX在jcxz中会用到，需要将cl的属性信息转存
	color_loop:
		mov ch,0
		mov cl,ds:[si]	;将需要显示的数据存到cl中
		
		mov es:[bx][di],cl	;低字节放ASCII
		mov es:[bx][di].1,ah	;高字节放属性
		inc si
		add di,2
		jcxz show_over	;遇到0就结束
	jmp short color_loop
show_over:
ret
codeseg ends
end start
