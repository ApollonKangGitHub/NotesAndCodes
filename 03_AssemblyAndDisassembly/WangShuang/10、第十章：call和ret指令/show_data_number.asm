;2017��5��4��13:43:52
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1

;��ν����ݶ��е�ʮ�����������ַ�������ʽ��ʾ����Ļ��
assume cs:codeseg,ss:stackseg,ds:dataseg
dataseg segment
	dw 65535,12366,20121,30010,65534,60124,36524,18451
dataseg ends

data segment
	db 64 dup (0)
data ends

stackseg segment
	db 64 dup (0)
stackseg ends

codeseg segment
start:
	mov ax,dataseg
	mov es,ax
	mov ax,stackseg
	mov ss,ax
	mov ax,data
	mov ds,ax
	mov sp,64
	mov si,0
	
	mov di,0
	mov cx,8
	loop_change:
		mov ax,es:[di]
		call dtoc
		add di,2
	loop loop_change
	
	mov si,0
	mov dh,5
	mov dl,35*2
	mov al,10000000B
	mov cx,8
	loop_show:
		push cx
		inc al
		mov cl,al
		call show_str
		inc dh
		pop cx 
	loop loop_show
	
mov ax,4C00H
int 21H

;====================ASCII������+30Hת�ַ����������ds:[si]���Ա����===================
dtoc:
	push cx
	mov dx,0
	push dx
	
	mov bx,10
	dtoc_begin:
		mov dx,0	;��λ�ò�������
		div bx
		add dx,30H		;��������ת�ַ�
		push dx
		mov cx,ax		
		jcxz dtoc_again	;��Ϊ0�ͽ�������->�ַ���ת��
		jmp short dtoc_begin
		
	;���ڰ�ȡ���˳��ֱ�ӷ���es:[si]��ʼ�Ŀռ���˳���Ƿ��ģ�������Ҫ��ת�����ַ�����ȫ����ջ��
	;�������ջ������ַ��С����ŵ�es:[si]��ʼ�Ŀռ���ȥ
	dtoc_again:
		pop cx
		mov ds:[si],cl
		inc si
		jcxz dtoc_over
		jmp short dtoc_again
	
	dtoc_over:
	pop cx
ret
;===================��ʾǰ�ĳ�ʼ����ת��====================
show_str:
	push es
	push dx
	push ax
	
	mov ax,0B800H	;�Կ���ʼλ��B800H
	mov es,ax		;es��������������ֵ
	mov ax,160		;ÿһ�е��ֽ���
	mul dh			;��������
	mov bx,ax		;��ƫ��ֵ�ŵ�bx��
	mov dh,0
	mov di,dx		;��һ���е�ÿ���ַ��Ķ�̬ƫ�����ŵ�di��
	
	call show_color
	
	pop ax
	pop dx
	pop es
ret
;==================����ĸ�����ʾ����Ļָ��λ����=====================
show_color:
	mov ah,cl	;CX��jcxz�л��õ�����Ҫ��cl��������Ϣת��
	color_loop:
		mov ch,0
		mov cl,ds:[si]	;����Ҫ��ʾ�����ݴ浽cl��
		
		mov es:[bx][di],cl	;���ֽڷ�ASCII
		mov es:[bx][di].1,ah	;���ֽڷ�����
		inc si
		add di,2
		jcxz show_over	;����0�ͽ���
	jmp short color_loop
show_over:
ret
codeseg ends
end start
