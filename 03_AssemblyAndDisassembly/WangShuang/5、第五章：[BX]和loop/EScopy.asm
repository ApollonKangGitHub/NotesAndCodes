;将FFFF:0~FFFF:F的字节型数据复制到0:200~020F中
;copy.asm
assume cs:codeseg

codeseg segment

		mov cx,16
		mov bx,0
		
		mov ax,0FFFFH
		mov ds,ax
		mov ax,0020H
		mov es,ax
	
	;用ES寄存器优化：
	copyNumber:
		mov dl,ds:[bx]
		mov es:[bx],dl	
		inc bx
		loop copyNumber
		
		mov ax,4C00H
		int 21H
	
codeseg ends

end