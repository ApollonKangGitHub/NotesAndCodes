;2017��5��4��12:51:17
;Mail:mailbox_krj@163.com
;Author:Kangruojin
;Version:v1.1

;��������Ľ������divdw����ʵ�֣�
;�ٲ���(parameters):
;(ax)=dword�ͱ������ĵ�16λ
;(dx)=dword�ͱ������ĸ�16λ
;(cx)=����
;�ڷ���ֵ(return value):
;(dx)=�̵ĸ�16λ
;(ax)=�̵ĵ�16λ
;(cx)=����
;��ʽ:X/N=int(H/N)*65535+[rem(H/N)*65535+L]/N
;X:������(dd��)��N����(dw��)��H�������ĸ�16λ��L�������ĵ�16λ��int()��ʾȡ����rem()��ʾȡ��
;X/N��������ֽ��ļ����������������

assume cs:codeseg,ss:stackseg

dataseg segment
	dd 0,0,0,0
dataseg ends

stackseg segment
	dd 0,0,0,0
stackseg ends

codeseg segment
start:
	mov ax,stackseg
	mov ss,ax
	mov sp,16
	
	mov dx,000FH	;H
	mov ax,4240H	;L
	mov cx,0AH		;N

	call divdw
mov ax,4C00H
int 21H
;=================���̵ķ������������===============
divdw:
	mov bx,dataseg
	mov ds,bx
	push ax
	mov ax,dx
	mov dx,0
	div cx	
	mov ds:[0],ax
	pop ax	
	div cx		
	mov cx,dx	;����rem([rem(H/N)*65535+L]/N),��������յ�����,�ŵ�cx�з���
	mov dx,ds:[0]	;����ֵ�̵ĸ�16λ,��16λ��ax��
ret

;========================ֻ��ջ���ö����dataseg========================
;======ע�⣺��ջ��ָ�������ƶ��󣬲��ٱ�֤�������������===============
divdw2:
	push ax
	mov ax,dx
	mov dx,0
	div cx
	mov bp,sp
	push ax
	mov ax,ss:[bp]
	div cx
	mov cx,dx
	pop dx
	pop bx	;���ڵ�ax���Ѿ��ù���
ret
codeseg ends
	
end start