;将data段中第一组数据的三次方计算结果存放到第二组相对应的位置中
assume cs:codeseg

data segment 
	dw 10,20,30,40,50,60,70,80
	dd 0,0,0,0,0,0,0,0
data ends

codeseg segment
	start:
		mov ax,data
		mov ds,ax
		
		mov si,0
		mov di,16
		
		mov cx,8
		loop_calc:
			mov bx,[si]
			call cube	;BX传递参数、AX与DX传递返回值
			mov [di],ax
			mov [di].2,dx
			add si,2
			add di,4
		loop loop_calc
		
	mov ax,4C00H
	int 21H
	
	cube:
		mov ax,bx
		mul bx
		mul bx
	ret
	
codeseg ends
end start