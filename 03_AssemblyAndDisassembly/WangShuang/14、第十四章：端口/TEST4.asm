;TEST3的改良版
assume cs:code,ds:data

data segment
	time db 'yy/mm/dd hh:mm:ss','$'
	cmos db 9,8,7,4,2,0
data ends

code segment
start: 
	mov ax,data
	mov ds,ax
	again:
	mov bx,0
	mov si,0
	mov cx,6
	GetMessage:   
		push cx
		mov al,cmos[bx]
		
		out 70h,al    ;将al送入地址端口70h
		in al,71h ;从数据端口71h处读出单元内容
		mov ah,al
		mov cl,4
		shr al,cl ;右移4位
		and ah,0fh    ;al分成两个表示BCD码值的数据
		add ax,3030h  ;BCD码+30h=10进制数对应的ASCII码
		
		mov ds:[si],ax     ;ASCII码写入time段
		inc bx
		add si,3
		pop cx
	loop GetMessage
	;名称：BIOS中断(int 10h)
	;功能：(ah)=2置光标到屏幕指定位置、(ah)=9在光标位置显示字符
	;参数：(al)=字符、(bh)=页数、(dh)=行号、(dl)=例号、(bl)=颜色属性、(cx)=字符重复个数
	mov ah,2 ;置光标
	mov bh,0 ;第0页
	mov dh,13 ;dh中放行号
	mov dl,32 ;dl中放例号
	int 10h
	;名称：DOS中断(int 21h)
	;功能：(ah)=9显示用'$'结束的字符串、(ah)=4ch程序返回
	;参数：ds:dx指向字符串、(al)=返回值
	mov dx,0
	mov ah,9
	int 21h
	;一次显示结束
	loop again 	;循环显示
mov ax,4c00h
int 21h
code ends
end start

 
