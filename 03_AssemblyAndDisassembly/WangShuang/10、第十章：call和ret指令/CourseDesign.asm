;2017��5��4��17:51:56
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1
;��ʵ���ߵĹ�˾����ȫ����ʾ����Ļ��
assume cs:code

data segment
	;���:0~84
	db '1975','1976','1977','1978','1979','1980','1981'
	db '1982','1983','1984','1985','1986','1987','1988'
	db '1989','1990','1991','1992','1993','1994','1995'
	;��˾����:84~168
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514,345980
	dd 590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
	;Ա������:168~210
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793
	dw 4037,5635,8226,11542,14430,15257,17800
data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

stack segment
	db 128 dup (0)
stack ends
;������ֵ�ASCIIת���ɶ�Ӧ�ַ�ASCII���ֵ
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
;=================��ASCIIת�����ַ��ŵ�string��������========================
isShort_div:
	mov cx,dx
	jcxz short_div	;dx��û�����־���ת���̳����Ĳ���������
	mov cx,10
	push ax			;û����ת��short_div��˵��dx������Ҫ���з�ֹ�������
	mov bp,sp
	call long_div
	add sp,2
	add cx,30H
	mov es:[bx],cl	;һһ����������string�У���������������9������cl����(�ǵ���cl����)
	dec bx		
	jmp isShort_div	;һ�����ö̳����Ͳ���ʹ�ó�����
shortDivRet:
ret
;====================�̳���=====================
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
;====================��������������=====================
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
;================��ʾ���=================
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
	add di,3*2	;ǰ���3���ַ�
	
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

;=================��ʾ����================
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
	
	call isShort_div	;�ж��ǲ��Ƕ̳��������ҽ����ֵ�ASCIIת���ɶ�Ӧ�ַ���ASCII��Դds(table��)��Ŀ��es(string�ݴ��ַ����ռ�)
	call init_reg		;�޸�Դds(table)��Ŀ��es(string)Ϊ��Դds(string)��Ŀ��es(0B800H���Կ�)
	add di,15*2		;ǰ���15���ַ�(������ݵ��ĸ�)
	call show_string	;��ʾstring���Կ���
	
	pop di
	pop si
	pop es
	pop ds
	pop dx
	pop cx
	pop bx
ret
;===================��ʾԱ������=====================
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
	add di,30*2		;ǰ���30���ַ�
	call init_reg
	call show_string
	
	pop di
	pop si
	pop es
	pop ds
	pop cx
	pop bx
ret
;==================��ʾƽ������======================
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
	add di,45*2			;ǰ���45���ַ�
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
;===================��string����ASCIIת������������=====================
show_string:
	showString:
		mov cl,ds:[bx]
		jcxz showStringRet
		mov es:[di],cl
		add di,2
		inc bx	;bx��9����(9-len)������(9-len)�ӵ�9���������ȡ������洢->��������Ĺ���
	jmp showString
	showStringRet:
ret
;==============��Ļ�����ʼ��==============
init_reg_output_table:
	mov bx,table
	mov ds,bx
	mov bx,string
	mov es,bx
ret
;=================��ʾ====================
output_table:
	call init_reg_output_table
	mov si,0
	mov cx,21
	mov di,160*3	;�ӵ����п�ʼ
	mov bx,9

	outputTable:
	;�ĸ��ӳ����޹��������ÿ���ӳ����п�ʼ�ԼĴ������ģ��ջ�������ԼĴ�����ջ������Ӱ��
	;���ĸ��ӳ�����Ե��ӳ���֮�����й����ģ�����Ҫ���ģ��ջ�����ǼĴ��������ò�����ͻ
		call show_year
		call show_sum
		call show_number
		call show_sarlay
		
		add si,16	
		add di,160	;������һ
	loop outputTable
ret
;=================����====================
clear_screen:
	mov bx,0B800H
	mov es,bx
	
	mov bx,0
	mov dx,3700H	;��λΪ37(00000111B)������ɫ��Ϊ��ɫ����λΪ0(00000000B)�����ַ�
	mov cx,2000		;�ܹ�80*25=2000���ַ�
	
	clearScreen:
		mov es:[bx],dx
		add bx,2
	loop clearScreen
ret
;==============�������ʼ��===================
init_reg_input_table:
	mov bx,data
	mov ds,bx
	mov bx,table
	mov es,bx
ret
;===============�����д��==================
input_table:
	call init_reg_input_table
	mov si,0
	mov di,21*4*2	;Ա��ƫ�Ƶ�ַ
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