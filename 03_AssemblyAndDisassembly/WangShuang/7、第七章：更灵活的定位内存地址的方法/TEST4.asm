;��TEST3���иĽ�
;����ͨ���ݶδ����ʱֵ�Եò�̫���㣬����ʱֵ�Ƚ϶�ʱ�����ܻ�ԭʱ�����
;��Ϊ��ջ�洢�Եø���һ��(ջһ�������洢��ʱ����)

assume cs:codeseg,ds:dataseg,ss:stackseg

dataseg segment
	db 'ibm             '	;16���ַ�
	db 'dec             '
	db 'dos             '
	db 'vax             '
dataseg ends

stackseg segment
	dw 0,0,0,0,0,0,0,0
stackseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	mov ax,stackseg
	mov ss,ax
	mov sp,16
	
	mov bx,0
	mov cx,4
	mov al,0DFH
	
	change_one:
		push cx
		mov si,0
		mov cx,3
		change_two:
			and [bx][si],al
			inc si
		loop change_two
		pop cx
		add bx,16
	loop change_one
	
	mov ax,4C00H
	int 21H
codeseg ends
end start