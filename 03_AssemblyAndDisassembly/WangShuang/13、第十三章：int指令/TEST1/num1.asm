;��2017��5��7��20:35:55
;int 7CH�ж����̣���ʾһ����0�������ַ������ж����̰�װ��0:200��
;(dh)=�к�,(dl)=�к�,(cl)=��ɫ,ds:[si]ָ���ַ����׵�ַ
assume cs:code

code segment
	start:
	mov ax,cs
	mov ds,ax
	mov si,offset doint7CH
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	mov cx,offset doint7CHend - offset doint7CH
	cld
	rep movsb
	
	mov ax,0
	mov es,ax
	mov word ptr es:[7CH*4],200H
	mov word ptr es:[7CH*4+2],0
	
	mov ax,4C00H
	int 21H
;===========================
doint7CH:
	;(dh)=�к�,(dl)=�к�,(cl)=��ɫ,ds:[si]ָ���ַ����׵�ַ
	push cx
	push ax
	push dx
	push es
	push di
	push si
	
	mov ax,0B800H
	mov es,ax
	mov al,160
	mul dh
	mov dh,0
	add dl,dl	;����2��������������
	add ax,dx
	mov di,ax
	
	showchar:
		mov al,ds:[si]
		cmp al,0
		je over
		mov es:[di],al
		mov es:[di+1],cl
		inc si
		add di,2
	jmp short showchar
	over:
		pop si
		pop di
		pop es
		pop dx
		pop ax
		pop cx
		iret
doint7CHend:nop
;===========================
code ends
end start