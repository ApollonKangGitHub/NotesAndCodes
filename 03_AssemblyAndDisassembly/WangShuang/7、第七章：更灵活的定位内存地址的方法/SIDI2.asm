;������ݶ��������ռ�Ŀ���
;�Ż�
assume cs:codeseg,ds:dataseg

dataseg segment
	db 'Welcome to MASM!'	;16���ֽ�
	db '................'	;�����Ƶ����ڴ�����
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov si,0
	mov cx,8
	
	copydata:
		mov ax,[si]
		mov 16[si],ax
		add si,2
	loop copydata
	
	mov ax,4C00H
	int 21H
codeseg ends

end start