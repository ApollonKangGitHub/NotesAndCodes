;ret与retf
assume cs:codeseg

stack segment
	db 16 dup (0)
stack ends
codeseg segment
	mov ax,4C00H
	int 21H
	start:
	mov ax,stack
	mov ss,ax
	mov sp,16
	mov ax,0
	;push cs
	push ax
	mov bx,0
	ret	;retf
codeseg ends
end start