;2017年5月13日16:18:14
;Mail:mailbox_krj@163.com
;Author:KangRuoJin
;Version:v1.2
assume cs:code,ds:data,ss:stack

data segment
	db 256 dup (0)
data ends
stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov bx,stack
	mov ss,bx
	mov sp,128

	call copy_boot
	
	mov bx,0
	push bx
	mov bx,7E00H
	push bx
	retf	;跳转到0:7E00H开始执行
	
mov ax,4C00H
int 21H
;================================================================
boot:
	jmp boot_start
;*******************************************************************************************
	MENU_1	db 'Weclome to System of Mr.Kang',0
	MENU_2	db '(1) Reset PC',0
	MENU_3	db '(2) Start System',0
	MENU_4	db '(3) ShowClock',0
	MENU_5	db '(4) Set Clock',0
	MENU_6 	db 'Please Enter Your Choose(1~4):',0
	
	MENU_ADDRESS	dw offset MENU_1 - offset boot + 7E00H
					dw offset MENU_2 - offset boot + 7E00H
					dw offset MENU_3 - offset boot + 7E00H
					dw offset MENU_4 - offset boot + 7E00H
					dw offset MENU_5 - offset boot + 7E00H
					dw offset MENU_6 - offset boot + 7E00H
	time 	db 'YY/MM/DD hh:mm:ss',0
	cmos 	db 9,8,7,4,2,0
	clockone	db 'press F1 to change the color, press ESC to return',0
	clock2	db 'Please input Date and Time,(YY MM DD hh mm ss):',0
	change 	db 12 dup (0),0
;*******************************************************************************************
boot_start:
	call init_reg
	call clear_screen
	call show_menu
	jmp choose_option
mov ax,4C00H
int 21H
;================================================================
choose_option:
	call clear_keyboard_buffer	;清除键盘缓冲区
	mov ah,0
	int 16H
	
	cmp al,'1'
	je choose_option_one
	cmp al,'2'
	je choose_option_two
	cmp al,'3'
	je choose_option_three
	cmp al,'4'
	je choose_option_four
	jmp choose_option
;================================
choose_option_one:               
jmp choose_option                

choose_option_two:               
jmp choose_option                

choose_option_three:             
	call ShowClock               
jmp boot_start			;跳回到boot_start清屏，并重新显示                

choose_option_four:    
	call SetClock
jmp boot_start	   
;=================================================================
SetClock:
	call init_reg			;寄存器初始化
	call clear_screen		;清屏并重新画边框
	call clear_change_stack	;清空存放修改内容的栈缓冲区
	
	;设置显示提示信息的位置为10行15列开始
	mov di,160*10+15*2
	mov si,offset clock2 - offset boot + 7E00H
	call show_line
	;显示修改缓冲区中的内容
	mov di,160*12+30*2		
	mov si,offset change - offset boot + 7E00H
	call show_line
	
	call get_string
	call set_CMOSRAM
ret
;=================================================================
set_CMOSRAM:
	mov bx,offset cmos - offset boot + 7E00H
	mov si,offset change - offset boot + 7E00H
	mov cx,6
	
	ChangeMessage:   ;GetMessage的逆过程
		push cx
		
		mov dx,ds:[si]
		sub dx,3030H
		mov cl,4
		shl dl,cl
		and dh,00001111B
		or dl,dh
		
		mov al,ds:[bx]
		out 70H,al    ;将al送入地址端口70h
		mov al,dl
		out 71H,al ;	将数据写入CMOSRAM时钟
		
		inc bx
		add si,2
		pop cx
	loop ChangeMessage
ret
;================================================================= 
get_string:
	mov si,offset change - offset boot + 07E00H
	mov bx,0
getSting:
	mov ah,0
	int 16H
	cmp al,'0'	;判断是否是小于‘0’
	jb noNumber
	cmp al,'9'	;判断是否大于'9'
	ja noNumber
	call char_push
	cmp bx,12
	ja EnterKey			;超过输入范围就不允许再输，直接结束
	mov di,160*12+30*2	;与SetClock中，显示修改缓冲区中的内容位置相对应
	call show_line
	jmp getSting
noNumber:
	cmp ah,0EH	;退格通码
	je BackspaceKey
	cmp ah,1CH	;回车通码
	je EnterKey
	jmp getSting
BackspaceKey:
	call char_pop
	mov di,160*12+30*2	;与SetClock中，显示修改缓冲区中的内容位置相对应	
	call show_line
	jmp getSting
EnterKey:
ret
;=================================================================
char_push:
	cmp bx,12
	ja char_push_over
	mov ds:[si+bx],al
	inc bx
	char_push_over:
ret
char_pop:
	cmp bx,0
	je char_pop_over
	dec bx
	mov byte ptr ds:[si+bx],'*'
	char_pop_over:
ret
;=================================================================      
clear_change_stack:
	push bx
	push cx
	
	mov bx,offset change - offset boot + 7E00H
	mov cx,6			
	ClearChangeStack:
		mov word ptr ds:[bx],'**'
		add bx,2
	loop ClearChangeStack
	
	pop cx
	pop bx
ret
;=================================================================
ShowClock:
	call init_reg			;寄存器初始化
	call clear_screen		;清屏并重新画边框
	mov di,14*160+15*2		;设置显示提示信息的位置为14行15列开始
	mov si,offset clockone - offset boot + 7E00H
	call show_line	;显示
	
	ShowClockStart:
		call GetTimeMessage		;获取时间信息放到time中去
		mov di,10*160+30*2		;设置显示时间与日期的位置为10行30列开始
		mov si,offset time - offset boot + 7E00H
		call show_line			;按规则显示
		
		;这里的读取键盘缓冲区是自己完成，我们亦可以在
		mov ah,1		;非阻塞式读取，由于是非阻塞读取，当读取到之后，缓冲区不会清空
		int 16H
		jz ShowClockStart
		cmp ah,3BH
		je ChangeColor
		cmp al,1BH		;ESC扫描码为1，与设定的功能号有冲突，所以用ASCII码
		je ReturnToMainMenu
		cmp al,0		;能到达这一步说明不为F1也不为ESC
		jne ClearKeyBuffer	;但是不为0说明一定是有键盘中断产生，就要清除无用的键盘中断
	jmp ShowClockStart
;================================
ChangeColor:					;改变颜色
	call ChangeShowColor
ClearKeyBuffer:
	call clear_keyboard_buffer	;清除非阻塞读取时未清空的缓冲区
	jmp ShowClockStart
ReturnToMainMenu:				;退回到choose_option时会清除缓冲区，所以这里不需要清除缓冲区
ret
;================================================================
GetTimeMessage:
	mov cx,6
	mov bx,offset cmos - offset boot + 7E00H
	mov si,offset time - offset boot + 7E00H
	GetMessage:   
		push cx
		mov al,ds:[bx]
		
		out 70H,al    ;将al送入地址端口70h
		in al,71H ;从数据端口71h处读出单元内容
		mov ah,al
		mov cl,4
		shr al,cl ;右移4位
		and ah,0FH    ;al分成两个表示BCD码值的数据
		add ax,3030H  ;BCD码+30h=10进制数对应的ASCII码
		
		mov word ptr ds:[si],ax     ;ASCII码写入time段
		inc bx
		add si,3
		pop cx
	loop GetMessage
ret
;================================================================
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
;================================================================
clear_keyboard_buffer:
	mov ah,1
	int 16H			;修改了ax，所以ZF可能会改变

	jz ClearKeyboardBufferOver	;如果非阻塞读取的数据为0则结束
	mov ah,0		;否则，则继续用阻塞的方式清除一次缓冲区字节
	int 16H
	jmp clear_keyboard_buffer
	ClearKeyboardBufferOver:
ret
;================================================================
init_reg:
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov ds,bx
ret
;================================================================
clear_screen:
	mov bx,0
	mov cx,2000
	mov dx,1F00H	;黑屏白字
	ClearScreen:
		mov es:[bx],dx	
		add bx,2
	loop ClearScreen
	
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
;================================================================
show_menu:
	mov bx,offset MENU_ADDRESS - offset boot + 7E00H
	mov di,160*8 + 25*2
	mov cx,6
	ShowMenu:	
		mov si,ds:[bx]	;获取输出行信息的偏移地址
		call show_line	;给定显示的位置显示一行
		add bx,2		;获取下一条内容的地址
		add di,160		;输出到下一行
	loop ShowMenu
ret
;================================================================
show_line:
	push ax
	push si
	push di
ShowLineStart:
	mov al,ds:[si]	;获取一个字符
	cmp al,0		;遇到0则输出结束
	je ShowLineOver
	mov es:[di],al	;遇到的不是0则输出到显示屏上
	add di,2
	inc si
	jmp ShowLineStart
ShowLineOver:
	pop di
	pop si
	pop ax
ret
;================================================================
boot_end:nop
;================================================================
copy_boot:	;将代码段复制到0:7E00H处（正式的写法都需要将代码放到内存中去）
	mov bx,cs
	mov ds,bx
	mov si,offset boot
	
	mov bx,0
	mov es,bx
	mov di,7E00H
	mov cx,offset boot_end - offset boot
	cld
	rep movsb
ret
;================================================================
code ends
end start