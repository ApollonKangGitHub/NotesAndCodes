;2017年5月8日18:37:00
assume cs:code,ss:stack

stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128

	mov ax,cs
	mov ds,ax
	mov si,offset new_int9
	
	mov ax,0
	mov es,ax
	mov di,0204H
	
	;复制新的int 9的例程代码段到向量表的空闲空间中
	mov cx,offset new_int9_over - offset new_int9
	cld
	rep movsb
	
	;保存旧的int 9例程的地址
	push es:[9*4]
	pop es:[200H]
	push es:[9*4+2]
	pop es:[202H]
	
	;设置新的int 9例程的地址到向量表中
	cli 
	mov word ptr es:[9*4],204H
	mov word ptr es:[9*4+2],0
	sti
	
mov ax,4C00H
int 21H
;=========================================
new_int9:
	push ax
	push bx
	push cx
	push es
	
	in al,60H		;获取键盘中断
	pushf
	call dword ptr cs:[200H]	;此时cs为0
	
	mov bx,0B800H
	mov es,bx
	mov cx,2000
	mov bx,1
	
	;判断是否是F1键并处理
	new_int9_F1:	;写上此标号是为了统一
		cmp al,3BH
		jne new_int9_F2
		change_F1:
			mov byte ptr es:[bx],01110001B	;按F1修改为白屏蓝字
			add bx,2
		loop change_F1
	;判断是否是F2键并处理
	new_int9_F2:
		cmp al,3CH
		jne new_int9_F3
		change_F2:
			mov byte ptr es:[bx],00001010B	;按F2修改为黑屏绿字
			add bx,2
		loop change_F2
	;判断是否是F3键并处理	
	new_int9_F3:
		cmp al,3DH
		jne new_int9_ret
		change_F3:
			mov byte ptr es:[bx],01010111B	;按F3修改为紫屏白字
			add bx,2
		loop change_F3
		
new_int9_ret:
	pop es
	pop cx
	pop bx
	pop ax
iret
new_int9_over:nop
code ends
end start
