;2017��5��4��17:21:46
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1

;����0��β�����ݶε��ַ�������ָ��λ��ָ��������ʾ
;�ӳ�������ʾ
;�����������һ������(cl���)��һ��λ��(��dh,��dl)
;ds:[si]ָ���ַ����׵�ַ
assume cs:codeseg

dataseg segment
	db 'Welcome to masm!',0
dataseg ends

codeseg segment

start:
	mov ax,dataseg
	mov ds,ax
	mov si,0
	
	mov cl,11110101B	;�׵�������˸������
	mov dh,13			;����
	mov dl,30*2			;����ʼλ��
	
	call show_str
	
mov ax,4C00H
int 21H
;===================��ʾǰ�ĳ�ʼ����ת��====================
show_str:
	push es
	push di
	
	call show_init
	call show_color
	
	pop di
	pop es
ret

show_init:
	mov ax,0B800H	;�Կ���ʼλ��B800H
	mov es,ax		;es��������������ֵ
	mov ax,160		;ÿһ�е��ֽ���
	mul dh			;��������
	mov bx,ax		;��ƫ��ֵ�ŵ�bx��
	mov dh,0
	mov di,dx		;��һ���е�ÿ���ַ��Ķ�̬ƫ�����ŵ�di��
ret
;==================����ĸ�����ʾ����Ļָ��λ����=====================
show_color:
	push cx
	push si
	mov ah,cl	;CX��jcxz�л��õ�����Ҫ��cl��������Ϣת��
	mov si,0
	color_loop:
		mov ch,0
		mov cl,ds:[si]	;����Ҫ��ʾ�����ݴ浽cl��
		jcxz show_over	;����0�ͽ���
		
		mov es:[bx][di],cl	;���ֽڷ�ASCII
		mov es:[bx][di].1,ah	;���ֽڷ�����
		inc si
		add di,2
	jmp short color_loop
show_over:
	pop si
	pop cx
ret
	
codeseg ends
end start