;将data_a的前八个字型数据逆序存放到data_b中
assume cs:code
data_a segment
	dw 1,2,3,4,5,6,7,8,0AH,0BH,0CH,0EH,0FH,0FFH
data_a ends

data_b segment
	dw 0,0,0,0,0,0,0,0
data_b ends

code segment
	start:
	mov ax,data_a
	mov ds,ax
	mov ax,data_b
	mov ss,ax
	mov sp,16	;data_b有16字节，(16/16+1)*16
		
		;DS:076A
		;SS:076C
		;CS:076D
	
	mov cx,8
	mov bx,0
	
	doagain:
		push ds:[bx]
		add bx,2
	loop doagain
	
	mov ax,4C00H
	int 21H
		
code ends
end start