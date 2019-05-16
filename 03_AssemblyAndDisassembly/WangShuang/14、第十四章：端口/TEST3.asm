;2017年5月8日16:46:51
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1
;在屏幕中间显示日期与时间
;格式："年/月/日  时:分:秒"
;CMOS RAM存储内容：
;				0	2	4	7	8	9	
;				秒	分	时	日	月	年
assume cs:code

code segment
start:
	mov dh,12	;行
	mov dl,30*2	;列
	
	call Init_Show
	call Clear_Screen
	Dieloop:
		mov si,0
		mov al,9	;9(Year)8(Month)7(Day)
		show_Date:
			call Get_CMOSRAM_Message	;获取日期/时间信息，并字符化，用cx传递回来(ch为十位，cl为个位)
			call Show_Message			;显示
			add si,6					
			cmp al,7					
			je next
			dec al
		jmp short show_Date
		
		next:
			mov byte ptr es:[bx+si-2],' '	;由于day之后不需要输出'/'所以规律中si=si+6不适用与day，需要退回2字节
			mov byte ptr es:[bx+si],' '		;18~21显示"  "分给日期与时间
			add si,2	;对应上面的退回2字节，所以只需加2即可
			
		mov al,4	;4(Hour)2(Mintue)0(Second)
		show_Time:
			call Get_CMOSRAM_Message
			call Show_Message
			add si,6
			cmp al,0
			je again
			sub al,2
		jmp short show_Time
	again:
	jmp short Dieloop
over:
mov ax,4C00H
int 21H
;=============================清屏=================================
Clear_Screen:
	push bx
	push cx
	
	mov bx,0
	mov cx,80*25
	clear:
		mov es:[bx],0700H
		add bx,2
	loop clear
	
	pop cx
	pop bx
ret
;=======================es寄存器存放显卡首地址======================
Init_Show:
	mov ax,0B800H
	mov es,ax
	mov al,160
	mul dh
	mov dh,0
	mov bx,dx
	add bx,ax
ret
;=====================获取时间/日期信息========================
Get_CMOSRAM_Message:
	push ax
	
	mov cl,4
	out 70H,al
	in al,71H
	mov ah,al	;复制一份数据到ah中
	shr ah,cl	;将ah中的个位BCD数据清空
	and al,0FH	;将al中的十位BCD数据清空
	add ah,30H	;将数组转变成字符
	add al,30H
	
	;cx传参
	mov ch,ah	;由于主程序中用到了al，所以用ch、cl来传递获取到的返回值
	mov cl,al

	pop ax
ret
;=====================将获取到并存放到cx中的信息显示到屏幕上========================
Show_Message:
	mov byte ptr es:[bx+si],ch
	mov byte ptr es:[bx+si+2],cl
	cmp si,13	
	;CMP si,n	比较的值可选的很多，只要n大于12即可，但是是针对于jb...jnb的跳转行形式来说的
	;16~19显示"  "分割日期与时间
	jb	Show_Date_Message	
	jnb	Show_Time_Message	
	Show_Date_Message:
		cmp al,7	
		je ShowOver	;日后不需要加'/'
		mov byte ptr es:[bx+si+4],'/'
		jmp short ShowOver
	Show_Time_Message:
		cmp al,0
		je ShowOver	;秒后不需要加':'
		mov byte ptr es:[bx+si+4],':'
ShowOver:
ret
;=============================================
code ends
end start