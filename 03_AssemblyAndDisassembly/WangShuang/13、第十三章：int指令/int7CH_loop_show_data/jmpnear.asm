;����int7CH
;ʵ�֡�int 7CH������jmp near ptr sָ��Ĺ��ܣ�ʵ����ָ��λ������ַ���
;��bx����λ��
assume cs:code

data segment
	db 'conversation!',0
data ends

code segment
	start:
	mov ax,data
	mov ds,ax
	mov si,0
	
	mov ax,0B800H
	mov es,ax
	mov di,160*12
	
	sbegin:
		cmp byte ptr ds:[si],0
		je over
		mov al,ds:[si]
		mov es:[di],al
		inc si
		add di,2
		
		mov bx,offset sbegin - offset over
		int 7CH
	over:
	mov ax,4C00H
	int 21H
code ends
end start