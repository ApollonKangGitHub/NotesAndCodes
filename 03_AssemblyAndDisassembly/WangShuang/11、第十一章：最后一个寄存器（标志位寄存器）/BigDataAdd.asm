;�����ӷ�������128λ���ݽ������
;2017��5��6��15:51:04
;Author:Kangruojin
;Version:v1.1
;Mail:mailbox_krj@163.com
;���򣺽�ds:siָ���һ�����Ĵ洢��Ԫ��ds:diָ��ڶ������Ĵ洢��Ԫ
;�ɵ͵�ַ���ߵ�ַ��Ԫ���δ��128λ�����ɵ͵��ߵĸ�����(�ܹ�8����)��
;���������ڵ�һ�����Ĵ洢�ռ���

assume cs:code

data segment
	db 0FEH,0EDH,0A2H,0C3H,0D4H,0E5H,0F6H,0CCH,0CFH,0EDH,012H,064H,0FFH,01DH,0AAH,033H
	;db 16 dup (0FFH)	;ds:[0]��ʼ�洢��һ��������2^128-1
	dw 0				;�����յĽ�λ
	db 0FFH,01DH,0AAH,033H,0CFH,0EDH,012H,064H,0D4H,0E5H,0F6H,0CCH,0FEH,0EDH,0A2H,0C3H
	;db 16 dup (0FFH)	;ds:[130]��ʼ�洢�ڶ���������2^128-1
data ends

code segment
start:
	mov ax,data
	mov ds,ax

	call add_128bit

mov ax,4C00H
int 21H
;========================================
add_128bit:
	mov si,0
	mov di,18
	
	sub ax,ax	;��CF����Ϊ0
	mov cx,8
	add_loop:
		mov ax,ds:[si]
		adc ax,ds:[di]
		mov ds:[si],ax
		inc si
		inc si
		inc di
		inc di	;ע�⣺���ܽ�����inc di������inc si�ϲ�Ϊһ��add si,2��add di,2.��Ϊ���ֲ������CF����Ӱ��
	loop add_loop
	mov ax,0
	adc ax,0	;�����һ����Ҫ�������п��ܴ��ڵĽ�λOF��������
	mov ds:[si],ax
ret
code ends
end start