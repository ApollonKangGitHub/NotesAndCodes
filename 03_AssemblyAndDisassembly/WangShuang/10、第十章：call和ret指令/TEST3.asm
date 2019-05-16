;¼ì²âµã10.5(2)
;AX=1,BX=0
assume cs:codeseg

data segment
	dw 8 dup (0)
data ends
codeseg segment
	start:
	mov ax,data
	mov ss,ax
	mov sp,16
	mov word ptr ss:[0],offset s
	mov ss:[2],cs
	call dword ptr ss:[0]
	nop
	s:
	mov ax,offset s
	sub ax,ss:[0CH]
	mov bx,cs
	sub bx,ss:[0EH]
	
	mov ax,4C00H
	int 21H
codeseg ends
end start