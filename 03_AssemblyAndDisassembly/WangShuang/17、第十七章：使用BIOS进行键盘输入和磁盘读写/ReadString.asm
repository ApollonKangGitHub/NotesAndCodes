;(ah)��Ź��ܺţ�0��ʾ��ջ��1��ʾ��ջ��2��ʾ��ʾ
;ds:siָ���ַ�ջ�ռ�
;0�Ź���:(al)=��ջ�ַ�
;1�Ź���:(al)=�����ַ�
;2�Ź���:(dh)=�С�(dl)=��
;top����ɾ������ջ�ķ��ʷ�ʽ(�Ƚ������ɾ����ʽ)�������ڱ�����ʾʱ���ڶ��еķ��ʷ�ʽ(�Ƚ��ȷ�����ʾ)��
assume cs:code

data segment
	db 256 dup (0)
data ends

code segment
	start:
	call getstr
mov ax,4C00H
int 21H	
;=============���ղ���������ж�==============
getstr:
	push ax
	push ds
	
	mov ax,data
	mov ds,ax
getstrs:
	mov ah,0
	int 16H
	cmp al,20H	;ASCII��С��20H˵�������ַ�
	jb nochar
	mov ah,0	;�ַ���ջ
	call charstack
	mov ah,2	;��ʾջ���ַ�
	call charstack	
	jmp getstrs
nochar:
	cmp ah,0EH	;�˸�ͨ��
	je BackspaceKey
	cmp ah,1CH	;�س�ͨ��
	je EnterKey
	jmp getstrs
BackspaceKey:
	mov ah,1
	call charstack
	mov ah,2
	call charstack
	jmp getstrs
EnterKey:
	mov al,0
	mov ah,0
	call charstack	;�������룬0��ջ
	mov ah,2		;��ʾջ���ַ�
	call charstack
	
	pop ax
	pop ds
ret
;==============�ַ���ջ����ջ����ʾ=============
charstack:
	jmp short charstart
table	dw charpush,charpop,charshow
top 	dw 0
charstart:	;��ȡ(al)���ܺŲ��ж�
	push bx
	push dx
	push di
	push es
	
	cmp ah,2	;����2�����
	ja sret
	mov bl,ah
	mov bh,0
	add bx,bx
	jmp word ptr table[bx]	;��ַ
charpush:
	mov bx,top
	mov ds:[si][bx],al	;��ջ��al�����ַ�
	inc top				;ջ��ָ������һ���ֽ�
	jmp sret			;��ջ���
charpop:
	cmp top,0
	je sret			;ջΪ��ʱ���ó�ջֱ�ӽ���
	dec top			;���ƶ�ָ��
	mov bx,top		;�ٳ�ջ
	mov al,ds:[si][bx]	;al���س�ջ�ַ�
	jmp sret			;��ջ�����
charshow:
	mov bx,0B800H	;����esָ���Կ���0���ֽ�
	mov es,bx
	mov al,160
	mov ah,0
	mul dh
	mov di,ax
	add dl,dl
	mov dh,0
	add di,dx	;���㣺�к�*160+��=((dh)*160+(dl)*2)=(di)
	mov bx,0
charshows:
	cmp bx,top		;�Ƿ�ջ��
	jne noempty		;û��ջ���ͼ������
	mov byte ptr es:[di],' '	
	;�þ���������ڣ�ÿ�����ʱ����һ����Ч�ַ����ᱻ���
	;��ôɾ��һ���������ʱ�����ַ��ѳ�Ϊ��һ����Ч�ַ������ո񸲸ǵ����ٴ����ʱ������ӹ���
	;�µ������̲��Ḳ��ԭ����ɾ����λ�ã�����ԭ����δ��ɾ�����ַ�������ʾ����Ļ�ϣ�������Ч��
	jmp sret
noempty:
	mov al,ds:[si][bx]
	mov es:[di],al
	mov byte ptr es:[di+2],' '
	inc bx
	add di,2
	jmp charshows	;ѭ���ж���һ���Ƿ�ջ��
sret:
	pop es
	pop di
	pop dx
	pop bx
ret
;================================
code ends
end start