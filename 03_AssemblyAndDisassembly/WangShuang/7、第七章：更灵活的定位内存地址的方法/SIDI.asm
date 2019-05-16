;SI与DI的功能与BX相似:
;mov bx,0		mov si,0		mov di,0
;mov ax,[bx+16]	mov ax,[si+16]	mov ax,[di+16]
;mov cx,16[bx]	mov cx,16[si]	mov cx,16[di]

;完成数据段向其后面空间的拷贝
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
	mov di,16
	mov cx,8
	
	copydata:
		mov ax,[si]	;一次复制两个字节
		mov [di],ax
		add si,2
		add di,2
	loop copydata
	
	mov ax,4C00H
	int 21H
codeseg ends

end start