;计酸a的八个dw数据之和，存放到b的2个字中
assume cs:code

code segment
	a dw 1AH,23H,47H,0A5H,73H,12H,0FFH,0EAH
	b dd 0
start:
	mov si,0
	mov cx,8
	
	loop_add:
		mov ax,a[si]
		add a[16],ax
		adc a[18],0
		add si,2
	loop loop_add

mov ax,4C00H
int 21H
code ends
end start