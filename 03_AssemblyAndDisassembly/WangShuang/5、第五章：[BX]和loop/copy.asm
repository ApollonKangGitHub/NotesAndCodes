;��FFFF:0~FFFF:2F���ֽ������ݸ��Ƶ�0:200~020F��
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