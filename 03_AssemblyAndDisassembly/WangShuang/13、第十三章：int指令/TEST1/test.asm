;≤‚ ‘≥Ã–Ú
assume cs:code

data segment
	db "welcome to masm! ",0
data ends
code segment
	start:
	mov dh,10
	mov dl,10
	mov cl,2
	mov ax,data
	mov ds,ax
	mov si,0
	int 7CH
	
	mov ax,4C00H
	int 21H
code ends
end start