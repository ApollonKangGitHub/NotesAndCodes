;����Ļ�м�������ʾ��a��~��z��
;�Դ���ʾ��Ҫ���ǵ���ʱ���⣬��Ϊ����ʱ�ܿ�ͻᱻˢ��
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
;=====================��ʱ����:��ѭ��==============
Delay:
	push ax
	push dx
	
	mov dx,10H
	mov ax,0
	loopdelay:
			sub ax,1
			sbb dx,0	;(dx)=(dx)-0-CF
			cmp ax,0
		jne loopdelay	;�ڴ�ѭ��
		cmp dx,0
	jne loopdelay	;���ѭ��
	
	pop dx
	pop ax
ret
code ends
end start