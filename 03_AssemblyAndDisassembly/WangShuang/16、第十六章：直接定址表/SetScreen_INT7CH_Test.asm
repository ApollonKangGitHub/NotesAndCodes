assume cs:code 

code segment 

start:
;������ǰ��ɫ�������ñ���ɫ�����Ź���һ�Σ��������
	mov ax,0101h
	int 7ch 
	call Delay
	mov ax,0207h
	int 7ch 
	call Delay
	mov ax,0300h
	int 7ch 
	call Delay
	mov ax,0000h
	int 7ch 
	call Delay
;==================================================
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
mov ax,4c00h 
int 21h 
code ends 

end start
