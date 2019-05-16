;在屏幕满屏依次显示‘a’~‘z’
;以此显示就要考虑到延时问题，因为不延时很快就会被刷新
assume cs:code

code segment
	start:
	mov ax,0B800H
	mov es,ax
	mov al,'a'
	show:
		mov bx,0
		mov cx,80*25
		mov si,0
		loop_char:
			mov es:[bx+si],al
			mov byte ptr es:[bx+si+1],00001010B
			add si,2
		loop loop_char
		inc al
		call Delay
		cmp al,'z'
	jna show
	
	mov ax,4C00H
	int 21H
;=====================延时函数:空循环==============
Delay:
	push ax
	push dx
	
	mov dx,10H
	mov ax,0
	loopdelay:
			sub ax,1
			sbb dx,0	;(dx)=(dx)-0-CF
			cmp ax,0
		jne loopdelay	;内存循环
		cmp dx,0
	jne loopdelay	;外层循环
	
	pop dx
	pop ax
ret
code ends
end start