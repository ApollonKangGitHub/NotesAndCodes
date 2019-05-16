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
	
	BigToLittle:
		;mov al,ds:[bx]
		;or al,00100000B		;or al,20H
		;mov ds:[bx],al
		
		mov al,20H
		or ds:[bx],al
		inc bx
	loop BigToLittle
		
	mov cx,26	;BX不用变，CX要变
	
	LittleToBig:
		;mov al,ds:[bx]
		;and al,11011111B	;and al,DlFH
		;mov ds:[bx],al
		
		mov al,0DFH
		and ds:[bx],al
		inc bx
	loop LittleToBig
	
	mov ax,4C00H
	int 21H
	
code ends

end start