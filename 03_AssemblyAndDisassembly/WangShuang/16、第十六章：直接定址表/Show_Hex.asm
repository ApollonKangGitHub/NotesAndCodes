;写一个子程序，用ah传参数，显示一个字节的十六进制数据
assume cs:code,ds:data

data segment
	table db '0123456789ABCDEF'
data ends
	
code segment
start:
	mov ax,data
	mov ds,ax
	mov al,0BFH;
	
	call ShowHex
mov ax,4C00H
int 21H
;==============================
ShowHex:
	push bx
	push es
	push cx
	
	mov cl,4
	mov ah,al
	shr ah,cl
	and al,0FH
	
	mov bl,ah
	mov bh,0
	mov ah,table[bx]	;定址
	
	mov bl,al
	mov al,table[bx]	;定址
	
	mov bx,0B800H
	mov es,bx
	mov bx,160*12+40*2
	mov es:[bx],ah
	mov es:[bx+2],al
	
	pop cx
	pop es
	pop bx
ret
code ends
end start