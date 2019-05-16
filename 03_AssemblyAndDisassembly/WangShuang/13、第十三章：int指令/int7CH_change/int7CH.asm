;编写、安装中断7ch的中断例程实现以0结尾的字符串的大写转换
;参数：ds:[0]指向字符串首字节

assume cs:code 

code segment
	start:
		mov ax,cs
		mov ds,ax
		mov si,offset doint7CH
		mov ax,0
		mov es,ax
		mov di,0200H
		
		mov cx,offset doint7CH_end - offset doint7CH
		cld
		rep movsb
		
		;修改向量表
		mov ax,0
		mov es,ax
		mov word ptr es:[7CH*4],200H
		mov word ptr es:[7CH*4+2],0
		
	mov ax,4C00H
	int 21H
;==================================
doint7CH:
	push cx
	push si
	change:
		mov ch,0
		mov cl,ds:[si]
		jcxz ok
		cmp byte ptr ds:[si],'a'
			jb over
		cmp byte ptr ds:[si],'z'
			ja over
		and byte ptr ds:[si],11011111B
		over:
			inc si
	jmp short change
	ok:
		pop si
		pop cx
	iret
doint7CH_end:nop
;==================================
code ends
end start
