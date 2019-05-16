;2017-5-6 20:22:30
;Mail:mailbox_krj@163.com
;Author:Kangruojin
;Version:v1.1
;统计数据段中，值与8的关系：
;将值为8的个数存放到ax中
;将值大于8的个数存放到bx中
;将值小于8的个数存放到dx中
assume cs:code

data segment
	db 8,12,8,4,7,8,2,8,9,8,3,1,8,16,8,15
data ends

code segment
start:
	mov ax,data
	mov ds,ax
	
	call compare_eight
mov ax,4C00H
int 21H
;==============================
compare_eight:
	mov si,0
	mov ax,0
	mov bx,0
	mov dx,0
	
	mov cx,16
	again:
		cmp byte ptr ds:[si],8
		jne notequal	;不等于则跳过ax自加
		inc ax	;统计等于8的个数
		jmp short over	;该步统计了就直接跳到over，进行下一个
		notequal:
			jnb notless
			inc bx	;统计小于8的个数
			jmp short over	;该步统计了就直接跳到over，进行下一个
		notless:
			inc dx	;统计大于8的个数
		over:
			inc si
	loop again
ret
code ends
end start