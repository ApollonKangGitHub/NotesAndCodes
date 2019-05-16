;CBBA:change data by AX
;通过中间寄存器将0:0~0:F的值覆盖到cs:0~cs:F(数据段)的位置
;本来cs:0开始的位置为代码段的指令，但是dw的数据将该段内存占用，故CS:0即数据段开头
assume cs:codeseg
codeseg segment
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H
	
	start:
	mov ax,0
	mov ds,ax
	mov bx,0
	mov cx,8

	loop_change:
	mov ax,ds:[bx]
	mov cs:[bx],ax
	add bx,2
	loop loop_change
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start