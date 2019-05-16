;完成数据段向其后面空间的拷贝
;优化
assume cs:codeseg,ds:dataseg

dataseg segment
	db 'Welcome to MASM!'	;16个字节
	db '................'	;赋复制到该内存区域
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov si,0
	mov cx,8
	
	copydata:
		mov ax,[si]
		mov 16[si],ax
		add si,2
	loop copydata
	
	mov ax,4C00H
	int 21H
codeseg ends

end start