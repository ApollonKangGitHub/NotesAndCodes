;2017年5月8日17:52:30
;在屏幕中间依次显示‘a’~‘z’
;以此显示就要考虑到延时问题，因为不延时很快就会被刷新
;不安装的情况下可以将int 9的原中断例程的地址放在本代码段中
;但是在安装的情况在需要保存到0000:0200处
assume cs:code

stack segment
	db 128 dup (0)
stack ends

data segment
	dw 0,0
data ends

code segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	mov ax,data
	mov ds,ax
	
	;将BIOS的“int 9”的入口地址保存在ds:[0]、ds:[2]中
	mov ax,0
	mov es,ax
	push es:[9*4]
	pop ds:[0]		
	push es:[9*4+2]
	pop ds:[2]		
	
	;新的“int 9”入口地址保存到向量表中“int 9”对应的位置
	cli
	;不响应可屏蔽键盘中断，否则如果只设置了第一条指令之后就产生了一个键盘中断
	;转去执行键盘中断int 9，但是由于没设置完成，所以此时的int 9既不是BIOS也不是我们自己的，而是一个错误的地址
	;所以在设置新地址之前就需要设置不响应可屏蔽的键盘中断，而相类似的：在修改可屏蔽中断的例程的向量表时，
	;需要设置不响应修改向量对应的可屏蔽中断，否则修改的过程中去调用中断例程必定会产生错误
	mov word ptr es:[9*4],offset int9	
	mov es:[9*4+2],cs
	sti			;恢复响应可屏蔽键盘中断
	
	;自己的中断例程测试
	mov ax,0B800H
	mov es,ax
	mov al,'a'
	show:
		mov es:[160*12+40*2],al
		inc al
		call Delay
		cmp al,'z'
	jna show
	
	;恢复向量表中BIOS的“int 9”的中断例程入口地址
	mov ax,0
	mov es,ax
	push ds:[0]
	pop es:[9*4]
	push ds:[2]
	pop es:[9*4+2]
	
	mov ax,4C00H
	int 21H
;=====================延时函数:空循环==============
Delay:
	push ax
	push dx
	
	mov dx,10H
	mov ax,0
	loopdelay:
			sub ax,1
			sbb dx,0	;(dx)=(dx)-0-CF
			cmp ax,0
		jne loopdelay	;内存循环
		cmp dx,0
	jne loopdelay	;外层循环
	
	pop dx
	pop ax
ret
;====================新的"int 9H"中断例程=======================
int9:
		push ax
		push bx
		push es
		
		in al,60H
		
		;设置模拟“int 9”的调用过程
		pushf
		call dword ptr ds:[0]	;调用原来的“int 9”中断例程
		
		;修改颜色属性
		cmp al,1	;1是ESC的通码
		jne int9ret
		
		mov ax,0B800H
		mov es,ax
		inc byte ptr es:[160*12+40*2+1]		;将属性值加1，改变颜色
		
		int9ret:
		pop es
		pop bx
		pop ax
iret
;===============================================================
code ends
end start