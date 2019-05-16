;修改每个单词的前4个字母为大写

assume cs:codeseg,ds:dataseg,ss:stackseg

dataseg segment
	db '1. display      '	;16个字符
	db '2. brows        '
	db '3. replace      '
	db '4. modify       '
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
	
	mov cx,4
	mov bx,0
	mov al,0DFH
	change_one:
		push cx
		mov cx,4
		mov si,0
		change_two:
			and [bx][si+3],al
			inc si
		loop change_two
		pop cx
		add bx,16
	loop change_one
	
	mov ax,4C00H
	int 21H
codeseg ends
end start