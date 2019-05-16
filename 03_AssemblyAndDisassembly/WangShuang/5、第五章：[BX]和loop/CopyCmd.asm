;复制mov ax,4C00H指令之前的所有指令到0:200中
assume cs:codeseg

codeseg segment

	mov ax,cs	;直接获取代码段寄存器
	mov ds,ax
	mov ax,0020H
	
	mov es,ax
	mov bx,0
	mov cx,17H	;总共复制的字节数，mov ax,4C00H之前23个字节，可以查看CopyCmd.LST文件
	
	s:
	mov al,[bx]
	mov es:[bx],al
	inc bx
	loop s
	
	mov ax,4C00H
	int 21H

codeseg ends

end