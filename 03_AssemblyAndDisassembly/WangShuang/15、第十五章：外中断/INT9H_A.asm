;2017年5月8日19:57:10
;安装新的int 9，在DOS下按A键后，除非不在松开，一旦松开就显示全屏的A
;大小有所谓
;0040:17的单元存储键盘状态字：
;7			6			5			4			3		2		1			0
;Insert		CapsLock	NumLock		ScrollLock	Alt		Ctrl	LeftShift	RightShift

assume cs:code 

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
	mov si,offset new_int9H
	
	mov ax,0
	mov es,ax
	mov di,204H
	
	mov cx,offset new_int9H_end - offset new_int9H
	cld
	rep movsb
	
	push es:[9*4]
	pop es:[200H]
	push es:[9*4+2]
	pop es:[202H]
	
	cli
	mov word ptr es:[9*4],204H
	mov word ptr es:[9*4+2],0
	sti
	
mov ax,4C00H
int 21H
;===============================
new_int9H:
	push ax
	push bx
	push cx
	push es
	push ds
	
	in al,60H
	
	pushf
	call dword ptr cs:[200H]
	
	;这一步是判断大小写，到这里说明是a的键，但不说明是大A，必须判断CapsLock、左右Shift的标志位是否为1
	;但是这里判断依旧不够严谨:当CapsLock与Shift同时有效时，显示的是小写字母(不再去细细划分了)
	mov bx,0040H
	mov ds,bx
	mov bl,ds:[17H]
	and bl,01000011B	;留下CapsLock、左右Shift
	cmp bl,0
	je new_int9H_ret	;等于0说明不是大写A
	
	cmp al,1EH+80H
	jne new_int9H_ret	;不是A的断码就直接结束
	
	;显示满屏A
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov cx,2000
	ShowA:
		mov byte ptr es:[bx],'A'
		add bx,2
	loop ShowA
	
new_int9H_ret:
	pop ds
	pop es
	pop cx
	pop bx
	pop ax
iret
new_int9H_end:nop	
code ends
end start