;TEST2的改良：
;用两层循环，内存初始化CX的时候，将外层的CX暂存于寄存器或内存中
;但是寄存器数量有限，所有暂存于内存中更好

assume cs:codeseg,ds:dataseg
dataseg segment
	db 'ibm             '	;16个字符
	db 'dec             '
	db 'dos             '
	db 'vax             '
	dw 0	;暂存CX寄存器的值
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov cx,4
	mov bx,0
	mov al,0DFH
	change_one:
		mov ds:[40H],cx	;暂存CX
		mov si,0
		mov cx,3
		change_two:
			and [bx][si],al 
			inc si
		loop change_two
		add bx,16
		mov cx,ds:[40H]	;取回外层循环值
	loop change_one
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start