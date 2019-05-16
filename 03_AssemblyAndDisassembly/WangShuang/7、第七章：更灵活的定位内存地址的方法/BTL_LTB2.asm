assume cs:code,ds:data

data segment
	db 'AbCdEfGhIjKlMnOpQrStUvWxYz'
	db 'aBcDeFgHiJkLmNoPqRsTuVwXyZ'
data ends

code segment
	start:
	mov ax,data
	mov ds,ax
	
	mov bx,0
	mov cx,26
	
	BTL_LTB:
		mov al,20H
		or ds:0[bx],al		;or ds:[bx].0¡¢or ds:[bx+0],ah
		mov al,0DFH
		and ds:26[bx],al	;ans ds:[bx].26,al¡¢and ds:[bx+26],al
		inc bx
	loop BTL_LTB
	
	mov ax,4C00H
	int 21H
	
code ends

end start