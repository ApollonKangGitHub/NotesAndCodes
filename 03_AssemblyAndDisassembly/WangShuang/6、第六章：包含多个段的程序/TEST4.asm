;将data_a与data_b中的数据依次相加并依次存入result段中
assume cs:code

data_a segment
	db 1,2,3,4,5,6,7,8	;db==>define Byte
data_a ends

data_b segment
	db 1,2,3,4,5,6,7,8
data_b ends

result segment
	db 0,0,0,0,0,0,0,0
result ends

code segment
	start:
	mov ax,data_a
	mov ds,ax
	mov ax,data_b
	mov es,ax
	
	mov ax,result
	mov ss,ax
	
	mov cx,8
	mov bx,0

	loop_begin:
		mov dx,0
		mov ax,0
		
		mov al,ds:[bx]
		add dx,ax
		mov al,es:[bx]
		add dx,ax
		
		mov ss:[bx],dx
		inc bx
	loop loop_begin
	
	mov ax,4C00H
	int 21H
	
code ends
end start