assume cs:codeseg

codeseg segment

	mov ax,47120	;B810H
	mov ss,ax
	mov sp,0H
	add sp,90H
	
	mov ax,1
	push ax
	
	mov ax,4C00H
	int 21H
	
codeseg ends

end