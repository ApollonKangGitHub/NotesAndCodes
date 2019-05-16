;用栈做
;牵扯到中间转换的均可用压栈出栈代替
assume cs:codeseg

data segment
	;年份:0~84
	db '1975','1976','1977','1978','1979','1980','1981'
	db '1982','1983','1984','1985','1986','1987','1988'
	db '1989','1990','1991','1992','1993','1994','1995'
	;公司收入:84~168
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514,345980
	dd 590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
	;员工人数:168~210
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793
	dw 4037,5635,8226,11542,14430,15257,17800
data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

stack segment
	dd 0,0,0,0
stack ends

codeseg segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,table
	mov es,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	
	mov bx,0
	mov bp,0
	mov cx,21
	mov di,0
	loop_one:
		push ds:[bp].0	;年份复制,注意：要通过寄存器复制
		pop es:[bx].0
		push ds:[bp].2
		pop es:[bx].2
		
		mov dx,ds:[bp].86	;公司总收入复制
		mov ax,ds:[bp].84
		mov es:[bx].5,ax	;总收入的低16位
		mov es:[bx].7,dx	;总收入的高16位
			
		push ds:168[di]
		pop es:[bx].10;员工人数

		div word ptr es:[bx].10		;进行除法运算计算工资,word ptr指定被除数在AX与DX寄存器中
		mov es:[bx].13,ax			;将商移动到最终平均工资的内存中
		
		add di,2
		add bp,4
		add bx,16	;bx自加进行下一年度运算
	loop loop_one
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start