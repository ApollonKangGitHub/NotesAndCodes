assume cs:codeseg

codeseg segment 
	start:
	mov ax,2000H
	jmp ax
	;jmp 2000H
	
	mov ax,4C00H
	int 21H
codeseg ends
	
end start