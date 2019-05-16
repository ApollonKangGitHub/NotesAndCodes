;利用jcxz指令实现在内存2000H段中查找第一个值为0的字节找到后将他的偏移地址存放在dx中。
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
	jcxz ok	;当找到的值存到cx中，找到0，存入CX的也为0，那么会自动跳到ok处
	inc bx
	jmp short again
	
	;找到后跳到该处将地址放到DX中
	ok:
	mov dx,bx
	
	mov ax,4C00H
	int 21H
codeseg ends
end start