;DCSP:Data Code Stack programe
;��CDBS�ĸĽ�
assume cs:code,ds:data,ss:stack

;���ݶ�
data segment
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H
data ends
	
;ջ��
stack segment
	dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	;36���ֽڵ�ջ
stack ends
;�����
code segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,20H
	;�������ݶ���ջ�μĴ���

	mov bx,0
	mov cx,8
	
	mov ax,0
	mov es,ax
	
	push_pop_loop:
		push es:[bx]
		pop ds:[bx]
		add bx,2
	loop push_pop_loop
	
	mov ax,4C00H
	int 21H
code ends
end start

