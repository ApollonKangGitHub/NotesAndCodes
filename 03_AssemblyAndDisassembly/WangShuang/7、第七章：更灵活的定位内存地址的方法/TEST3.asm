;TEST2�ĸ�����
;������ѭ�����ڴ��ʼ��CX��ʱ�򣬽�����CX�ݴ��ڼĴ������ڴ���
;���ǼĴ����������ޣ������ݴ����ڴ��и���

assume cs:codeseg,ds:dataseg
dataseg segment
	db 'ibm             '	;16���ַ�
	db 'dec             '
	db 'dos             '
	db 'vax             '
	dw 0	;�ݴ�CX�Ĵ�����ֵ
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov cx,4
	mov bx,0
	mov al,0DFH
	change_one:
		mov ds:[40H],cx	;�ݴ�CX
		mov si,0
		mov cx,3
		change_two:
			and [bx][si],al 
			inc si
		loop change_two
		add bx,16
		mov cx,ds:[40H]	;ȡ�����ѭ��ֵ
	loop change_one
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start