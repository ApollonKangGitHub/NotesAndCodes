;change data by stack
;通过栈将0:0~0:F的值覆盖到cs:0~cs:F(数据段)的位置
assume cs:codeseg
codeseg segment
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H
	dw 0,0,0,0,0,0,0,0,0,0
	
	start:
	mov ax,0
	mov ds,ax
	mov ax,cs
	mov ss,ax
	mov sp,36H
	
	mov bx,0
	mov cx,8

	loop_change:
		push ds:[bx]
		pop cs:[bx]
		add bx,2
	loop loop_change

	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start