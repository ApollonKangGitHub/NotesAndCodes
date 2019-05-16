;对TEST3进行改进
;用普通数据段存放临时值显得不太方便，当临时值比较多时，可能还原时会混乱
;改为用栈存储显得更好一点(栈一般用来存储临时数据)

assume cs:codeseg,ds:dataseg,ss:stackseg

dataseg segment
	db 'ibm             '	;16个字符
	db 'dec             '
	db 'dos             '
	db 'vax             '
dataseg ends

stackseg segment
	dw 0,0,0,0,0,0,0,0
stackseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	mov ax,stackseg
	mov ss,ax
	mov sp,16
	
	mov bx,0
	mov cx,4
	mov al,0DFH
	
	change_one:
		push cx
		mov si,0
		mov cx,3
		change_two:
			and [bx][si],al
			inc si
		loop change_two
		pop cx
		add bx,16
	loop change_one
	
	mov ax,4C00H
	int 21H
codeseg ends
end start