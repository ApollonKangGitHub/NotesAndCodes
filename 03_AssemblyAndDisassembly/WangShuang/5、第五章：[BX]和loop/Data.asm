assume cs:codeseg

codeseg segment

	mov ax,20H
	mov ds,ax	;ES is OK,too
	mov bx,0
	mov cx,64
	
	copy:
	mov ds:[bx],bl
	inc bx
	loop copy
	
	mov ax,4C00H
	int 21H

codeseg ends

end