;计算2的三次方
assume cs:codeseg

codeseg segment 
	start:
	mov ax,1
	mov cx,3
	call s
	mov bx,ax
	mov ax,4C00H
	int 21H
;===========子程序=================
	s:
	add ax,ax
	loop s
	ret
codeseg ends
end start