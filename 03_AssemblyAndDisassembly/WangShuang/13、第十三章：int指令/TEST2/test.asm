;≤‚ ‘≥Ã–Ú
assume cs:code

code segment
	start:
	mov ax,0B800H
	mov es,ax
	mov di,160*12
	mov bx,offset s - offset se
	mov cx,80
	
	s:
		mov byte ptr es:[di],'!'
		add di,2
		int 7CH
	se:nop
	
	mov ax,4C00H
	int 21H
code ends
end start