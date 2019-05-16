;在屏幕中间依次显示‘a’~‘z’
;以此显示就要考虑到延时问题，因为不延时很快就会被刷新
assume cs:code

code segment
	start:
	mov ax,0B800H
	mov es,ax
	mov bx,160*12+40*2
	mov al,'a'
	show:
		mov es:[bx],al
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