;测试0号中断类型码中断处理程序
assume cs:code

code segment
start:
	mov ax,1000H
	mov bl,1
	div bl
	
	mov ax,4C00H
	int 21H
code ends
end start