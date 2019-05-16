;将FFFF:0~FFFF:2F的字节型数据复制到0:200~020F中
;copy.asm
assume cs:codeseg

codeseg segment

		mov cx,16
		mov bx,0
	
	copyNumber:
		mov ax,0FFFFH
		mov ds,ax
		mov al,ds:[bx]
		
		mov ax,0020H	;0020*10:0==0:200
		mov ds,ax
		mov ds:[bx],al
	
		inc bx
		loop copyNumber
		
		mov ax,4C00H
		int 21H
	
codeseg ends

end