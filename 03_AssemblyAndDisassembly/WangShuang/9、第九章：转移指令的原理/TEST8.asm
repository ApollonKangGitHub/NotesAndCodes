;下面的程序能否正常结束？
assume cs:codeseg 

codeseg segment
	mov ax,4C00H
	int 21H
	
	start:
	mov ax,0
	s:
	nop
	nop
	
	mov di,offset s
	mov si,offset s2
	mov ax,cs:[si]
	mov cs:[di],ax
	
	s0:
	jmp short s
	
	s1:
	mov ax,0
	int 21H
	mov ax,0
	
	s2:
	jmp short s1
	nop
	
codeseg ends
end start