;用DOS的int 21H中断例程显示字符串在光标所在起始位置
;2017年5月7日18:09:42
assume cs:code

data segment
	db 'Yvyv I Love You!!$'
data ends
code segment
	start:
	mov ah,2
	mov bh,0
	mov dh,5
	mov dl,12
	int 10H
	
	;int 21H的显示字符串的功能
	;ds:dx指向要显示的字符串("以$结尾，$不显示")
	;子程序号为9
	mov ax,data
	mov ds,ax
	mov dx,0
	mov ah,9
	int 21H
	
	mov ax,4C00H
	int 21H
code ends
end start