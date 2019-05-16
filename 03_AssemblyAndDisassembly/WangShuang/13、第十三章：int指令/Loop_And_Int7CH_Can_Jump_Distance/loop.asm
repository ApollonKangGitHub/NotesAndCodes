;测试int 7CH的跳转范围与loop的跳转范围
assume cs:code

code segment
	start:
	mov ax,0B800H
	mov es,ax
	mov di,160*12
	
	mov bx,offset sbegin - offset send
	mov cx,80
	
	sbegin:
		mov byte ptr es:[di],'!'
		add di,2
		;db 119 dup (0)
	;loop sbegin
		db 65400 dup (0)
		int 7CH
	send:nop
	
	mov ax,4C00H
	int 21H
code ends
end start