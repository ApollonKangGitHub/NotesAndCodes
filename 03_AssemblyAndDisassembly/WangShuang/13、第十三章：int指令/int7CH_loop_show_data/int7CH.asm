;2017��5��7��16:37:05
;ʵ�֡�int 7CH������jmp near ptr sָ��Ĺ��ܣ�ʵ����ָ��λ������ַ���
;��bx����λ��
assume cs:code 

code segment
	start:
		mov ax,cs
		mov ds,ax
		mov si,offset doint7CH
		mov ax,0
		mov es,ax
		mov di,0200H
		
		mov cx,offset doint7CH_end - offset doint7CH
		cld
		rep movsb
		
		;�޸�������
		mov ax,0
		mov es,ax
		mov word ptr es:[7CH*4],200H
		mov word ptr es:[7CH*4+2],0
		
	mov ax,4C00H
	int 21H
;=============jmp near ptr sֻ�޸�IP���ɣ�=====================
doint7CH:
	push bp	;�����ֵ
	mov bp,sp
	add ss:[bp+2],bx	;jmp near ptr sΪƫ��16λ��ֵ
	over:
		pop bp
		iret
doint7CH_end:nop
;==================================
code ends
end start
