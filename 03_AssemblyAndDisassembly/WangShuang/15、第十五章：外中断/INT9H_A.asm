;2017��5��8��19:57:10
;��װ�µ�int 9����DOS�°�A���󣬳��ǲ����ɿ���һ���ɿ�����ʾȫ����A
;��С����ν
;0040:17�ĵ�Ԫ�洢����״̬�֣�
;7			6			5			4			3		2		1			0
;Insert		CapsLock	NumLock		ScrollLock	Alt		Ctrl	LeftShift	RightShift

assume cs:code 

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
	mov si,offset new_int9H
	
	mov ax,0
	mov es,ax
	mov di,204H
	
	mov cx,offset new_int9H_end - offset new_int9H
	cld
	rep movsb
	
	push es:[9*4]
	pop es:[200H]
	push es:[9*4+2]
	pop es:[202H]
	
	cli
	mov word ptr es:[9*4],204H
	mov word ptr es:[9*4+2],0
	sti
	
mov ax,4C00H
int 21H
;===============================
new_int9H:
	push ax
	push bx
	push cx
	push es
	push ds
	
	in al,60H
	
	pushf
	call dword ptr cs:[200H]
	
	;��һ�����жϴ�Сд��������˵����a�ļ�������˵���Ǵ�A�������ж�CapsLock������Shift�ı�־λ�Ƿ�Ϊ1
	;���������ж����ɲ����Ͻ�:��CapsLock��Shiftͬʱ��Чʱ����ʾ����Сд��ĸ(����ȥϸϸ������)
	mov bx,0040H
	mov ds,bx
	mov bl,ds:[17H]
	and bl,01000011B	;����CapsLock������Shift
	cmp bl,0
	je new_int9H_ret	;����0˵�����Ǵ�дA
	
	cmp al,1EH+80H
	jne new_int9H_ret	;����A�Ķ����ֱ�ӽ���
	
	;��ʾ����A
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov cx,2000
	ShowA:
		mov byte ptr es:[bx],'A'
		add bx,2
	loop ShowA
	
new_int9H_ret:
	pop ds
	pop es
	pop cx
	pop bx
	pop ax
iret
new_int9H_end:nop	
code ends
end start