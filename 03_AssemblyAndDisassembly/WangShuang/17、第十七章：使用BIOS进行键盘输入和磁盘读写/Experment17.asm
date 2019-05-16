;2017��5��14��11:42:29
;Mail:mailbox_krj@163.com
;Author:KangRuoJin
;Version:v1.1

;��װһ���µ�int 7CH�ж����̣�ʵ��ͨ���߼������Ŷ����̽��ж�д
;(��������Ҫʱ���߼������ŵ�int 13H������ת��)

;ah���ݹ��ܺţ�0��ʾ����1��ʾд
;dx����Ҫ��д���߼�������
;es:bxָ������̽������ڴ���

;���(dh)=(bx)/1440
;�ŵ���(ch)=((bx)%1440)/18)
;������(cl)=((bx)%1440)%18)+1
assume cs:code

stack segment
	db 128 dup (0)
stack ends
code segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	call copy_newint7CH	;����
	call install		;��װ
	
	;����
	mov dx,1439+80*18
	mov ah,1	;д
	mov al,5	;������
	int 7CH
	
	mov ax,4C00H
	int 21H
;==================================
copy_newint7CH:
	mov ax,cs
	mov ds,ax
	mov si,offset INT_7CH
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	mov cx,offset INT_7CH_end - offset INT_7CH
	cld 
	rep movsb
ret
;==================================
install:
	cli 
	mov word ptr es:[7CH*4],200H
	mov word ptr es:[7CH*4+2],0
	cld
ret
;==================================
INT_7CH:
	push ax
	push bx
	push cx
	push dx
	
	call calc_physic_number
	add ah,2		;0+2=2(��),1+2=3(д)
	;ת������Ժ�Ϳ��Ե���int 13H
	int 13H
	
	pop dx
	pop cx
	pop bx
	pop ax
iret
;==============================
calc_physic_number:	
	push ax
	push bx
	
	;DX��Ϊ������DXAX������,AX�̣�DX����
	mov ax,dx
	mov dx,0
	mov bx,1440
	div bx
	
	;AX��������AL�̣�AH����
	push dx	
	mov dh,al	;���(��ͷ��)
	pop ax	
	mov bl,18
	div bl
	
	inc ah
	mov ch,al	;�ŵ���
	mov cl,ah	;������
	mov dl,0 	;��������
	
	pop bx
	pop ax
ret
INT_7CH_end:nop
;==============================
code ends
end start