;-d 2000:1000
;00 00 00 00 00 00 00 00--00 00 00 00 00 00 00 00
 
assume cs:codeseg

codeseg segment

	mov ax,2000H
	mov ds,ax
	mov bx,1000H
	
	mov dx,00BEH	;注意不要写成“mov dl,BEH”,即使写成“mov dl,190”
	mov [bx],dl		;21000H BE 	给21000H设置初始值
	
	mov ax,[bx]		;AX=00BEH 	用21000H的字为AX设置初始值
	inc bx
	inc bx
	
	mov [bx],ax		;21002H BE	用AX给21002设置字型数据
	inc bx
	inc bx
	
	mov [bx],ax		;21004H	BE 	用AX给21004设置字型数据
	inc bx
	mov [bx],al		;21005H BE	用AX给21005设置字节型数据
	inc bx
	mov [bx],al		;21006H BE	用AX给21006设置字节型数据
	
	mov ax,4C00H
	int 21H
	
codeseg ends

end

;编译->连接->装载->运行后，结果为：
;-d 2000:1000
;BE 00 EE 00 EE EE EE 00--00 00 00 00 00 00 00 00