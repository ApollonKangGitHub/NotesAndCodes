;在数据段给定入合适的值，使得jmp指令执行后，CS:IP指向第一条指令
assume cs:codeseg

data segment
	db 16 dup (0)
data ends
codeseg segment 
	start:
	mov ax,data
	mov ds,ax
	mov bx,0
	jmp word ptr [bx+1]	;读取ds:[1]与ds:[2]放到IP中，那么IP就变为0，从第一条指令重新开始
codeseg ends

end start