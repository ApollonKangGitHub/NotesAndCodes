;2017-5-6 20:22:30
;Mail:mailbox_krj@163.com
;Author:Kangruojin
;Version:v1.1
;ͳ�����ݶ��У�ֵ��8�Ĺ�ϵ��
;��ֵΪ8�ĸ�����ŵ�ax��
;��ֵ����8�ĸ�����ŵ�bx��
;��ֵС��8�ĸ�����ŵ�dx��
assume cs:code

data segment
	db 8,12,8,4,7,8,2,8,9,8,3,1,8,16,8,15
data ends

code segment
start:
	mov ax,data
	mov ds,ax
	
	call compare_eight
mov ax,4C00H
int 21H
;==============================
compare_eight:
	mov si,0
	mov ax,0
	mov bx,0
	mov dx,0
	
	mov cx,16
	again:
		cmp byte ptr ds:[si],8
		jne notequal	;������������ax�Լ�
		inc ax	;ͳ�Ƶ���8�ĸ���
		jmp short over	;�ò�ͳ���˾�ֱ������over��������һ��
		notequal:
			jnb notless
			inc bx	;ͳ��С��8�ĸ���
			jmp short over	;�ò�ͳ���˾�ֱ������over��������һ��
		notless:
			inc dx	;ͳ�ƴ���8�ĸ���
		over:
			inc si
	loop again
ret
code ends
end start