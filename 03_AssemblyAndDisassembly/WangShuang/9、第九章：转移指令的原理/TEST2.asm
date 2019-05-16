;在12，13行填入合适的内容，使得jmp指令执行以后CS:IP指向第一条指令：mov ax,data
assume cs:codeseg

data segment
	dd 12345678H
data ends
codeseg segment 
	start:
	mov ax,data
	mov ds,ax
	mov bx,0
	;mov [bx],__
	;mov [bx+2],__
	mov [bx+2],cs
	mov [bx],bx	;mov bx,0不符合要求，因为只能填第二个值，不能再前面加word ptr，所以借用bx即可
	mov [bx+2],cs
	jmp dword ptr ds:[0]
codeseg ends

end start