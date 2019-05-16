;2017年5月4日17:51:56
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1
;将实验七的公司数据全部显示在屏幕上
assume cs:code

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
	db 128 dup (0)
stack ends
;存放数字的ASCII转换成对应字符ASCII后的值
string segment
	db 10 dup ('0'),0
string ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	call input_table
	call clear_screen
	call output_table
	
	testA:
		mov ax,1000H
	jmp testA
	
	mov ax,4C00H
	int 21H
;========================================
init_reg:
	push bx
	
	mov bx,string
	mov ds,bx
	
	mov bx,0B800H
	mov es,bx
	
	pop bx
ret
;=================将ASCII转换成字符放到string中随后输出========================
isShort_div:
	mov cx,dx
	jcxz short_div	;dx中没有数字就跳转到短除法的操作函数中
	mov cx,10
	push ax			;没有跳转到short_div，说明dx有数字要进行防止溢出操作
	mov bp,sp
	call long_div
	add sp,2
	add cx,30H
	mov es:[bx],cl	;一一保存余数到string中，由于余数不大于9所以用cl即可(非得用cl不可)
	dec bx		
	jmp isShort_div	;一旦能用短除法就不再使用长除法
shortDivRet:
ret
;====================短除法=====================
short_div:
	mov cx,10
	div cx
	add dx,30H
	mov es:[bx],dl
	mov cx,ax
	jcxz shortDivRet
	mov dx,0
	dec bx
	jmp short_div
;====================长除法消耗性能=====================
long_div:
	mov ax,dx
	mov dx,0
	div cx
	push ax
	mov ax,ss:[bp]
	div cx
	mov cx,dx
	pop dx
ret
;================显示年份=================
show_year:
	push bx
	push es
	push di
	push cx
	push ds
	push si
	push dx
	
	mov bx,0B800H
	mov es,bx
	add di,3*2	;前面空3个字符
	
	mov cx,4
	showYear:
		mov dl,ds:[si]
		mov es:[di],dl
		inc si
		add di,2
	loop showYear
	
	pop dx
	pop si
	pop ds
	pop cx
	pop di
	pop es
	pop bx
ret

;=================显示收入================
show_sum:
	push bx
	push cx
	push dx
	push ds
	push es
	push si
	push di
	
	mov ax,ds:[si+5]
	mov dx,ds:[si+7]
	
	call isShort_div	;判断是不是短除法，并且将数字的ASCII转化成对应字符的ASCII，源ds(table表)、目标es(string暂存字符串空间)
	call init_reg		;修改源ds(table)、目标es(string)为：源ds(string)、目标es(0B800H的显卡)
	add di,15*2		;前面空15个字符(包含年份的四个)
	call show_string	;显示string到显卡上
	
	pop di
	pop si
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
ret
;===================显示员工人数=====================
show_number:
	push bx
	push cx	
	push ds
	push es
	push si
	push di
	
	mov ax,ds:[si+10]
	mov dx,0
	call isShort_div
	add di,30*2		;前面空30个字符
	call init_reg
	call show_string
	
	pop di
	pop si
	pop es
	pop ds
	pop cx
	pop bx
ret
;==================显示平均工资======================
show_sarlay:
	;push ax
	push bx
	push cx	
	push ds
	push es
	push si
	push di
	
	mov ax,ds:[si+13]
	mov dx,0
	call isShort_div
	add di,45*2			;前面空45个字符
	call init_reg
	call show_string
	
	pop di
	pop si
	pop es
	pop ds
	pop cx
	pop bx
	;pop ax
ret
;===================将string中由ASCII转换后的数字输出=====================
show_string:
	showString:
		mov cl,ds:[bx]
		jcxz showStringRet
		mov es:[di],cl
		add di,2
		inc bx	;bx由9减到(9-len)，再由(9-len)加到9，即完成了取余逆向存储->正向输出的过程
	jmp showString
	showStringRet:
ret
;==============屏幕输出初始化==============
init_reg_output_table:
	mov bx,table
	mov ds,bx
	mov bx,string
	mov es,bx
ret
;=================显示====================
output_table:
	call init_reg_output_table
	mov si,0
	mov cx,21
	mov di,160*3	;从第三行开始
	mov bx,9

	outputTable:
	;四个子程序无关联，因此每个子程序中开始对寄存器大规模入栈，结束对寄存器出栈，互不影响
	;但四个子程序各自的子程序之间是有关联的，不需要大规模入栈，除非寄存器不够用产生冲突
		call show_year
		call show_sum
		call show_number
		call show_sarlay
		
		add si,16	
		add di,160	;行数加一
	loop outputTable
ret
;=================清屏====================
clear_screen:
	mov bx,0B800H
	mov es,bx
	
	mov bx,0
	mov dx,3700H	;高位为37(00000111B)背景靛色字为白色，低位为0(00000000B)即空字符
	mov cx,2000		;总共80*25=2000个字符
	
	clearScreen:
		mov es:[bx],dx
		add bx,2
	loop clearScreen
ret
;==============表输入初始化===================
init_reg_input_table:
	mov bx,data
	mov ds,bx
	mov bx,table
	mov es,bx
ret
;===============向表中写入==================
input_table:
	call init_reg_input_table
	mov si,0
	mov di,21*4*2	;员工偏移地址
	mov bx,0
	
	mov cx,21
	inputTable:
		push ds:[si]
		pop es:[bx+0]
		push ds:[si+2]
		pop es:[bx+2]
		
		mov ax,ds:[si+84]
		mov dx,ds:[si+86]
		mov es:[bx+5],ax
		mov es:[bx+7],dx
		
		push ds:[di]
		pop es:[bx+10]
		
		div word ptr es:[bx+10]
		mov es:[bx+13],ax
		
		add si,4
		add di,2
		add bx,16
	loop inputTable
ret
code ends
end start