;��FFFF:0~FFFF:F���ֽ������ݸ��Ƶ�0:200~020F��
;copy.asm
assume cs:codeseg

codeseg segment

		mov cx,16
		mov bx,0
		
		mov ax,0FFFFH
		mov ds,ax
		mov ax,0020H
		mov es,ax
	
	;��ES�Ĵ����Ż���
	copyNumber:
		mov dl,ds:[bx]
		mov es:[bx],dl	
		inc bx
		loop copyNumber
		
		mov ax,4C00H
		int 21H
	
codeseg ends

end