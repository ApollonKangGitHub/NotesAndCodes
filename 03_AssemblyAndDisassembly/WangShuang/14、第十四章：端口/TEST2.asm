;用移位指令与加法指令计算:
;n*10 = n*2 + n*8
;shl:逻辑左移，最后移出的一位放到CF中，右边补0	<==> 乘以2
;shr:逻辑右移，最后移出的一位放到CF中，左边补0	<==> 除以2
;当移位数大于1时，移位位数需要放到cl中
;注意是逻辑移位而不是算数移位
assume cs:code

code segment
	start:
	;eg:计算188*10
		mov al,188
		mov ah,0
		shl ax,1
		mov bx,ax
		
		mov cl,2
		shl ax,cl
		
		add ax,bx
	mov ax,4C00H
	int 21H
code ends
end start