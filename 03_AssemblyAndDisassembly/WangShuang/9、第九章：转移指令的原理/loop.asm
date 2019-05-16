;利用loop指令实现在内存2000H段中查找第一个值为0的字节找到后将他的偏移地址存放在dx中。
assume cs:codeseg

codeseg segment
	start:
	mov ax,2000H
	mov ds,ax
	mov bx,0
	;寻找单字节值为0的地址
	again:
	mov cx,0
	mov cl,ds:[bx]
	inc cx	;当cx为0时，自加一次为1，在loop时自减一次为0就结束循环
	inc bx
	loop again
	
	;找到后跳到该处将地址放到DX中
	ok:
	dec bx;与inc指令作用相反，自减：(bx)=(bx)-1
	mov dx,bx
	
	mov ax,4C00H
	int 21H
codeseg ends
end start