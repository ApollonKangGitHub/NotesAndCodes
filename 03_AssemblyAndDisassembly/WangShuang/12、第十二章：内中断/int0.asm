;�޸�0���жϵ��жϴ������Ϊ����Ļ�����ӡ"overflow"
assume cs:code

code segment
start:
	;��do0�ĳ����Ƶ�0000:0200H�����ڴ�
	mov ax,cs
	mov ds,ax
	mov si,offset do0
	
	mov ax,0
	mov es,ax
	mov di,0200H
	
	mov cx,offset do0end - offset do0 
	cld
	rep movsb	
	
	;�޸��ж�������
	mov ax,0
	mov es,ax
	mov word ptr es:[0],200H
	mov word ptr es:[2],0
	
mov ax,4C00H
int 21H
;=====================================
do0:
	jmp short do0start
	db 'overflow!'	;0000:0202
	do0start:
		mov ax,cs
		mov ds,ax
		mov si,202H
		
		mov ax,0B800H
		mov es,ax
		mov di,12*160+36*2
		mov cx,9
		s:
			mov al,ds:[si]
			mov es:[di],al
			inc si
			add di,2
		loop s
		
		;����������ֵû�����岻���ټ���ִ�У��ò�����iret����
		mov ax,4C00H	
		int 21H
do0end:nop
;========================================
code ends
end start