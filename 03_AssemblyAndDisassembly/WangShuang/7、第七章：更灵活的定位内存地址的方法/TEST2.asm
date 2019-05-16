;将代码段的每个单词的小写字母均改为大写

assume cs:codeseg,ds:dataseg

dataseg segment
	db 'ibm             '	;16个字符
	db 'dec             '
	db 'dos             '
	db 'vax             '
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov cx,4
	mov bx,0
	mov si,0
	
	ChangeAll_LTB:
		mov al,0DFH
		and [bx][si+0],al
		and [bx][si+1],al
		and [bx][si+2],al
		add bx,16
	loop ChangeAll_LTB
	
	mov ax,4C00H
	int 21H
	
	
codeseg ends
end start