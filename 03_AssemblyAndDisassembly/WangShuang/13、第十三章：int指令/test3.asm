;2017��5��7��21:56:35
;����Ļ��2468�зֱ�д�ľ�ʫ
assume cs:code

code segment
	s1:	db 'Good,better,best,','$'
	s2:	db 'Never let it rest,','$'
	s3:	db 'Till good is better,','$'
	s4:	db 'And better,best.','$'
	s:	dw offset s1,offset s2,offset s3,offset s4
	row:db 2,4,6,8

	start:
	mov ax,0B800H
	mov ds,ax
	mov cx,80*25
	mov si,0
	begin:
		mov word ptr ds:[si],0700H
		add si,2
	loop begin
	;����

	mov ax,cs
	mov ds,ax
	mov bx,offset s
	mov si,offset row
	mov cx,4
	;���û�ȡ���ݵ�ַ
	ok:
	mov bh,0
	mov dh,ds:[si]
	mov dl,0
	mov ah,2
	int 10H	
	;���ù��
	
	mov dx,ds:[bx]
	mov ah,9
	int 21H
	inc si
	add bx,2
	;���괦д�ַ���
	loop ok
	
	mov ax,4C00H
	int 21H
code ends
end start