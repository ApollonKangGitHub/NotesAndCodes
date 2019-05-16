;检测点10.5(1),AX最终的值，Debug单步跟踪结果不代表CPU执行结果
;debug单步调试不行，但是Debug一步运行完毕(CPU的执行结果)是可以的
assume cs:codeseg

stack segment
	dw 8 dup (0)
stack ends
codeseg segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,16
	mov ds,ax
	mov ax,0
	call word ptr ds:[0EH]
	inc ax
	inc ax
	inc ax
	
	mov ax,4C00H
	int 21H
codeseg ends
end start