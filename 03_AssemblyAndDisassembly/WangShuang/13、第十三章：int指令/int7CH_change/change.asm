assume cs:code

data segment
	db 'conversation',0
data ends

code segment
start:
	mov ax,data
	mov ds,ax
	mov si,0
	
	int 7CH
	
mov ax,4C00H
int 21H	
code ends
end start 