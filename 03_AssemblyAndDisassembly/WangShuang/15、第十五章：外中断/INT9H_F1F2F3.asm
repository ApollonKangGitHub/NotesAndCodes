;2017��5��8��18:37:00
assume cs:code,ss:stack

stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128

	mov ax,cs
	mov ds,ax
	mov si,offset new_int9
	
	mov ax,0
	mov es,ax
	mov di,0204H
	
	;�����µ�int 9�����̴���ε�������Ŀ��пռ���
	mov cx,offset new_int9_over - offset new_int9
	cld
	rep movsb
	
	;����ɵ�int 9���̵ĵ�ַ
	push es:[9*4]
	pop es:[200H]
	push es:[9*4+2]
	pop es:[202H]
	
	;�����µ�int 9���̵ĵ�ַ����������
	cli 
	mov word ptr es:[9*4],204H
	mov word ptr es:[9*4+2],0
	sti
	
mov ax,4C00H
int 21H
;=========================================
new_int9:
	push ax
	push bx
	push cx
	push es
	
	in al,60H		;��ȡ�����ж�
	pushf
	call dword ptr cs:[200H]	;��ʱcsΪ0
	
	mov bx,0B800H
	mov es,bx
	mov cx,2000
	mov bx,1
	
	;�ж��Ƿ���F1��������
	new_int9_F1:	;д�ϴ˱����Ϊ��ͳһ
		cmp al,3BH
		jne new_int9_F2
		change_F1:
			mov byte ptr es:[bx],01110001B	;��F1�޸�Ϊ��������
			add bx,2
		loop change_F1
	;�ж��Ƿ���F2��������
	new_int9_F2:
		cmp al,3CH
		jne new_int9_F3
		change_F2:
			mov byte ptr es:[bx],00001010B	;��F2�޸�Ϊ��������
			add bx,2
		loop change_F2
	;�ж��Ƿ���F3��������	
	new_int9_F3:
		cmp al,3DH
		jne new_int9_ret
		change_F3:
			mov byte ptr es:[bx],01010111B	;��F3�޸�Ϊ��������
			add bx,2
		loop change_F3
		
new_int9_ret:
	pop es
	pop cx
	pop bx
	pop ax
iret
new_int9_over:nop
code ends
end start
