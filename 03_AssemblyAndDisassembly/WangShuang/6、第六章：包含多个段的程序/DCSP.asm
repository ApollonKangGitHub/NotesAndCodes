;DCSP:Data Code Stack programe
;对CDBS的改进
assume cs:code,ds:data,ss:stack

;数据段
data segment
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H
data ends
	
;栈段
stack segment
	dw 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0	;36个字节的栈
stack ends
;代码段
code segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,20H
	;设置数据段与栈段寄存器

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

