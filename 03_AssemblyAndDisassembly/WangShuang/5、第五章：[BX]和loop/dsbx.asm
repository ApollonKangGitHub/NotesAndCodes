assume cs:codeseg

codeseg segment

	mov ax,1000H
	mov ds,ax

	mov bx,0
	mov ax,ds:[bx]
	mov bx,2
	mov ax,ds:[bx]
	
	mov bx,4
	mov ax,ds:[bx]
	mov bx,6
	mov ax,ds:[bx]
	
	mov bx,8
	mov ax,ds:[bx]
	mov bx,10
	mov ax,ds:[bx]

	mov ax,4C00H
	int 21H

codeseg ends

end
