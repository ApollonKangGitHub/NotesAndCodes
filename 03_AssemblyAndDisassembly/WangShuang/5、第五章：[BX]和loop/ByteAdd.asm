;2017年4月25日13:14:17
;Mail：mailbox_krj@163.com
;计算FFFF:0~FFFF:F的字节型数据的和，结果保存到DX中
assume cs:codeseg

codeseg segment

		mov bx,0
		mov ax,0FFFFH
		mov ds,ax
		
		mov dx,0
		mov cx,16
		mov ax,0		;高位必须清零，之后向AL存数据，所以只需清零一次
		
	addNumber:
		mov al,ds:[bx]	;字节型数据
		add dx,ax		;累加
		inc bx			;偏移地址移动一个字节<==>add bx,1
		loop addNumber	;条件(CX)减1
		
		mov ax,4C00H
		int 21H
	
codeseg ends

end