;将第一条指令复制到start_two的两个字节的位置
assume cs:codeseg

codeseg segment
	start:
	mov ax,bx
	mov si,offset start
	mov di,offset start_two
	mov dx,cs:[si]
	mov cs:[di],dx
	
	start_two:
	nop
	nop
	
	mov ax,4C00H
	int 21H
codeseg ends
end start