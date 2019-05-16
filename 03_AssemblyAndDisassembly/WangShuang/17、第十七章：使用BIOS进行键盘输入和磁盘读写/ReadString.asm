;(ah)存放功能号，0表示入栈，1表示出栈，2表示显示
;ds:si指向字符栈空间
;0号功能:(al)=入栈字符
;1号功能:(al)=返回字符
;2号功能:(dh)=行、(dl)=列
;top在增删上属于栈的访问方式(先进后出的删除方式)，但是在遍历显示时属于队列的访问方式(先进先访问显示)。
assume cs:code

data segment
	db 256 dup (0)
data ends

code segment
	start:
	call getstr
mov ax,4C00H
int 21H	
;=============接收并处理键盘中断==============
getstr:
	push ax
	push ds
	
	mov ax,data
	mov ds,ax
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
	pop ds
ret
;==============字符入栈、出栈、显示=============
charstack:
	jmp short charstart
table	dw charpush,charpop,charshow
top 	dw 0
charstart:	;获取(al)功能号并判断
	push bx
	push dx
	push di
	push es
	
	cmp ah,2	;大于2则结束
	ja sret
	mov bl,ah
	mov bh,0
	add bx,bx
	jmp word ptr table[bx]	;定址
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
	mov bx,0B800H	;设置es指向显卡第0个字节
	mov es,bx
	mov al,160
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
	pop es
	pop di
	pop dx
	pop bx
ret
;================================
code ends
end start