assume cs:codeseg

codeseg segment
	
	mov ax,2000H
	mov ss,ax
	mov sp,0H
	add sp,10H
	
	mov ax,1111H
	mov bx,2222H
	mov cx,3333H
	mov dx,4444H
	
	push ax
	push bx
	push cx
	push dx
	
	mov ax,1000H
	mov ds,ax
	
	pop ds:[0]
	pop ds:[2]
	pop ds:[4]
	pop ds:[6]
	
	mov ax,4C00H
	int 21H

codeseg ends

end

	