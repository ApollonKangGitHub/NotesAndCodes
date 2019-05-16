;大数加法：两个128位数据进行相加
;2017年5月6日15:51:04
;Author:Kangruojin
;Version:v1.1
;Mail:mailbox_krj@163.com
;规则：将ds:si指向第一个数的存储单元，ds:di指向第二个数的存储单元
;由低地址到高地址单元依次存放128位数据由低到高的各个字(总共8个字)，
;结果存放在在第一个数的存储空间中

assume cs:code

data segment
	db 0FEH,0EDH,0A2H,0C3H,0D4H,0E5H,0F6H,0CCH,0CFH,0EDH,012H,064H,0FFH,01DH,0AAH,033H
	;db 16 dup (0FFH)	;ds:[0]开始存储第一个操作数2^128-1
	dw 0				;存最终的进位
	db 0FFH,01DH,0AAH,033H,0CFH,0EDH,012H,064H,0D4H,0E5H,0F6H,0CCH,0FEH,0EDH,0A2H,0C3H
	;db 16 dup (0FFH)	;ds:[130]开始存储第二个操作数2^128-1
data ends

code segment
start:
	mov ax,data
	mov ds,ax

	call add_128bit

mov ax,4C00H
int 21H
;========================================
add_128bit:
	mov si,0
	mov di,18
	
	sub ax,ax	;将CF设置为0
	mov cx,8
	add_loop:
		mov ax,ds:[si]
		adc ax,ds:[di]
		mov ds:[si],ax
		inc si
		inc si
		inc di
		inc di	;注意：不能将两个inc di和两个inc si合并为一个add si,2与add di,2.因为这种操作会对CF产生影响
	loop add_loop
	mov ax,0
	adc ax,0	;最后这一步是要将最终有可能存在的进位OF保存起来
	mov ds:[si],ax
ret
code ends
end start