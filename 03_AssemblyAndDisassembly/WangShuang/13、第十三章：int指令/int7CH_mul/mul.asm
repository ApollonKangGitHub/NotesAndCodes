;≤‚ ‘int124
assume cs:code

code segment
	start:
	mov ax,3456
	int 7CH
	
	add ax,ax
	adc dx,dx
	
	mov ax,4C00H
	int 21H
code ends
end start