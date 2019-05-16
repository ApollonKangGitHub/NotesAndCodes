assume cs:code,ds:table

stack segment
	db 128 dup (0)
stack ends

table segment
	change	db '00/00/00 00:00:00',0
	menu	db 'Weclome to System of Mr.Kang   ',0
			db '      (1) Reset PC             ',0
			db '      (2) Start System         ',0
			db '      (3) Clock                ',0
			db '      (4) Set Clock            ',0
			db 'Please Enter Your Choose(1~4): ',0
			
	time 	db 'YY/MM/DD hh:mm:ss',0
	cmos 	db 9,8,7,4,2,0
	clock1	db 'press F1 to change the color, press ESC to return',0
	clock2	db 'Please input Date and Time,(YY/MM/DD hh:mm:ss):',0
table ends

data segment
	db 256 dup (0)
data ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128

	call get_keyboard
mov ax,4C00H
int 21H
;================================
init_reg:
	mov ax,table
	mov ds,ax
	mov ax,0B800H
	mov es,ax
ret
;===============清屏与设置边框================
clear_screen:
	mov bx,0
	mov cx,2000
	clear:
		mov es:[bx],1F00H	;蓝屏白字
		add bx,2
	loop clear
	
	mov bx,6*160+10*2
	mov cx,60
	clear_showframe_UpandDown:
		mov byte ptr es:[bx],'#'
		mov byte ptr es:[bx+160*9],'#'
		add bx,2
	loop clear_showframe_UpandDown
	
	mov bx,7*160+10*2
	mov cx,8
	clear_showframe_LeftandRight:
		mov byte ptr es:[bx],'#'
		mov byte ptr es:[bx+59*2],'#'
		mov byte ptr es:[bx+2],'#'
		mov byte ptr es:[bx+59*2-2],'#'
		add bx,160
	loop clear_showframe_LeftandRight
	
ret
;================================
show_message:
	mov cx,6
	mov di,160*8+25*2	;从第8行开始显示
	mov si,offset menu
	loop_show:
		call show_diff_message	
		add di,160
		add si,32
	loop loop_show
ret
;================================
get_keyboard:
	push ax
get_keyboard_begin:
	call init_reg
	call clear_screen
	call show_message
	
	mov ah,0
	int 16H

	cmp al,'1'
	je ResetPC
	cmp al,'2'
	je StartSystem
	cmp al,'3'
	je ShowClock
	cmp al,'4'
	je SetClock
	jmp short get_keyboard_begin

ResetPC:
	;call ResetPC_Function
jmp get_keyboard_begin

StartSystem:
	;call StartSystem_Function
jmp get_keyboard_begin

ShowClock:
	call ShowClock_Function
jmp get_keyboard_begin
;设置时钟
SetClock:
	call SetClock_Function
jmp get_keyboard_begin

get_keyboard_over:
	pop ax
ret
;================================
SetClock_Function:
;设置显示提示信息的位置为18行15列开始
	mov di,160*18+15*2
	mov si,offset clock2
	call show_diff_message
	
	call clear_stack
	mov di,20*160+15*2		
	mov si,offset change
	call show_diff_message	;显示
	
	call getstr
	call WriteCMOSRAM
ret
;=============接收并处理键盘中断==============
getstr:
	push ax
getstrs:
	mov ah,0
	int 16H
	cmp al,20H	;ASCII码小于20H说明不是字符
	jb nochar
	mov ah,0	;字符入栈
	call charstack
	mov ah,2	;显示栈中字符
	call charstack	
	jmp getstrs
nochar:
	cmp ah,0EH	;退格通码
	je BackspaceKey
	cmp ah,1CH	;回车通码
	je EnterKey
	jmp getstrs
BackspaceKey:
	mov ah,1
	call charstack
	mov ah,2
	call charstack
	jmp getstrs
EnterKey:
	mov al,0
	mov ah,0
	call charstack	;结束输入，0入栈
	mov ah,2		;显示栈中字符
	call charstack
	pop ax
ret
;===============================================
clear_stack:
	push es
	push bx
	push cx
	
	mov bx,0
	mov cx,6
	loop_clear_stack:
		mov byte ptr ds:[bx],'0'
		mov byte ptr ds:[bx+1],'0'
		add bx,3
	loop loop_clear_stack
	
	mov bx,cs
	mov es,bx
	mov bx,offset top
	mov word ptr es:[bx],0
	
	pop cx
	pop bx
	pop es
ret
;===============================================
WriteCMOSRAM:
	push ax
	push bx
	push cx
	push dx
	push si
	push di	
	
	mov si,0
	mov bx,0
	mov cx,6
	ChangeMessage:   ;GetMessage的逆过程
		push cx
		mov al,cmos[bx]
		out 70H,al    ;将al送入地址端口70h
		
		mov dx,word ptr change[si]
		sub dx,3030H
		mov cl,4
		and dh,00001111B
		shl dl,cl
		or dl,dh
		
		mov al,cmos[bx]
		out 70H,al    ;将al送入地址端口70h
		mov al,dl
		out 71H,al ;	将数据写入CMOSRAM时钟
		
		inc bx
		add si,3
		pop cx
	loop ChangeMessage
	
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
ret
;==============字符入栈、出栈、显示=============
charstack:
	jmp short charstart
table_stack	dw charpush,charpop,charshow
top 		dw 0
charstart:	;获取(al)功能号并判断
	push bx
	push dx
	push di
	
	cmp ah,2	;大于2则结束
	ja sret
	mov bl,ah
	mov bh,0
	add bx,bx
	jmp word ptr table_stack[bx]	;定址
charpush:
	mov bx,top
	mov ds:[si][bx],al	;入栈，al传入字符
	inc top				;栈顶指针上移一个字节
	jmp sret			;入栈完毕
charpop:
	cmp top,0
	je sret			;栈为空时不用出栈直接结束
	dec top			;先移动指针
	mov bx,top		;再出栈
	mov al,ds:[si][bx]	;al返回出栈字符
	jmp sret			;出栈后结束
charshow:
	mov al,160
	mov dh,20
	mov dl,15
	mov ah,0
	mul dh
	mov di,ax
	add dl,dl
	mov dh,0
	add di,dx	;计算：行号*160+列=((dh)*160+(dl)*2)=(di)
	mov bx,0
charshows:
	cmp bx,top		;是否到栈顶
	jne noempty		;没到栈顶就继续输出
	mov byte ptr es:[di],' '	
	;该句的作用在于：每次输出时，第一个无效字符都会被清空
	;那么删除一个，在输出时，此字符已成为第一个无效字符，被空格覆盖掉。再次输出时如果不加管理
	;新的输出变短不会覆盖原来被删除的位置，所以原来的未被删除的字符还会显示在屏幕上，看不出效果
	jmp sret
noempty:
	mov al,ds:[si][bx]
	mov es:[di],al
	mov byte ptr es:[di+2],' '
	inc bx
	add di,2
	jmp charshows	;循环判断下一个是否到栈顶
sret:
	pop di
	pop dx
	pop bx
ret
;================================
ShowClock_Function:
	push ax
	call init_reg			;寄存器初始化
	call clear_screen		;清屏并重新画边框
		
	;设置显示提示信息的位置为14行15列开始
	mov di,14*160+15*2		
	mov si,offset clock1
	call show_diff_message	;显示
	
	ShowClockAgain:
		call GetTimeMessage		;获取时间信息放到time中去
		;设置显示时间的位置为10行30列开始
		mov di,10*160+30*2
		mov si,offset time
		call show_diff_message	;按规则显示
		
		mov ah,1	;非阻塞式读取，由于是非阻塞读取，当读取到之后，缓冲区不会清空
		int 16H
		cmp ah,3BH
		je ChangeColor
		cmp al,1BH		;ESC扫描码为1，与设定的功能号有冲突，所以用ASCII码
		je ExitToMainMenu
		cmp al,0		;能到达这一步说明不为F1也不为ESC，但是不为0说明一定是有键盘中断产生，就要清除无用的键盘中断
		jne ClearKeyBuffer
	jmp ShowClockAgain
;改变颜色
ChangeColor:
	call ChangeShowColor
ClearKeyBuffer:
	mov ah,0	;清空非阻塞读取没有清空的缓冲区
	int 16H
	jmp ShowClockAgain
ExitToMainMenu:
	mov ah,0	;清空非阻塞读取没有清空的缓冲区
	int 16H
	
	pop ax
ret
;================================
;该函数一次显示一行，给定参数为：
;di:显示位置(计算过的值)
;si:显示的内容在table中的位置
;================================
show_diff_message:
	push ax
	push si
	push di
	loop_show_diff:
		mov al,ds:[si]
		cmp al,0
		je show_over
		mov es:[di],al
		inc si
		add di,2
	jmp short loop_show_diff
show_over:
	pop di
	pop si
	pop ax
ret
;================================
GetTimeMessage:
	push ax
	push bx
	push cx
	push si
	
	mov si,0
	mov bx,0
	mov cx,6
	GetMessage:   
		push cx
		mov al,cmos[bx]
		
		out 70H,al    ;将al送入地址端口70h
		in al,71H ;从数据端口71h处读出单元内容
		mov ah,al
		mov cl,4
		shr al,cl ;右移4位
		and ah,0FH    ;al分成两个表示BCD码值的数据
		add ax,3030H  ;BCD码+30h=10进制数对应的ASCII码
		
		mov word ptr time[si],ax     ;ASCII码写入time段
		inc bx
		add si,3
		pop cx
	loop GetMessage
	
	pop si
	pop cx
	pop bx
	pop ax
ret
;================================
ChangeShowColor:
	push bx
	push cx
	
	mov cx,2000
	mov bx,1
	loopChangeShowColor:
		add byte ptr es:[bx],1
		or byte ptr es:[bx],00001000B		;高亮不闪烁设置
		and byte ptr es:[bx],10001111B		;背景一直为黑色
		add bx,2
	loop loopChangeShowColor

	pop cx
	pop bx
ret
;================================
code ends
end start