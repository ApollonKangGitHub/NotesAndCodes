;王爽《汇编语言·第三版》实验七-P172
;将data中分开的：年份、公司收入、员工人数按照先后顺序写入table表段
;年份(4B)+(空格1B)+收入(4B)+(空格1B)+员工人数(2B)+(空格1B)+平均工资(2B)+(空格1B)
;总共16B即在Debug中一年的信息记录，占一行，21年共占21行
;员工平均工资=收入/员工人数(取整)
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

codeseg segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,table
	mov es,ax

	mov bx,0
	mov bp,0
	mov cx,21
	mov di,0
	
	loop_one:
		mov ax,cx
		
		mov cx,2
		mov si,0
		loop_two:
			mov dx,ds:[bp].0[si]	;年份复制,注意：要通过寄存器复制
			mov es:[bx].0[si],dx
			mov dx,ds:[bp].84[si]	;公司总收入复制
			mov es:[bx].5[si],dx
			add si,2
		loop loop_two
		mov cx,ax	;提前转回来，因为后面要用到ax
		
		mov dx,ds:168[di]
		mov es:[bx].10,dx;员工人数

		mov dx,es:[bx].7		;总收入的高16位
		mov ax,es:[bx].5		;总收入的低16位
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