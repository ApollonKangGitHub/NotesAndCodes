;��data���е���ĸת���ɴ�д�����Ż�
assume cs:codeseg

data segment
	db 'conversation',0
	db 'conversation',0
	db 'conversation',0
	db 'conversation',0
	db 'conversation',0
data ends

stack segment
	db 16 dup (0)
stack ends

codeseg segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	
	mov si,0
	mov bx,0
	mov cx,5
	
	loop_change:
		mov si,bx
		call change
		add bx,13
	loop loop_change
	
	mov ax,4C00H
	int 21H
;***************************Сд��ĸת���ɴ�д��ĸ****************************
;**********ע�⣺���εļĴ���������ջ,���磺������/�˷���AX��DX�Ĵ���***********
	change:
		push cx
		push si
	change_char:
		mov ch,0
		mov cl,ds:[si]
		jcxz ok
		and byte ptr ds:[si],11011111B
		inc si
		jmp short change_char
	ok:
		pop si
		pop cx
		ret
;====================================================================end change
codeseg ends
end start