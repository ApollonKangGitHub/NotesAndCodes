;2017年5月7日16:37:05
;实现“int 7CH”代替jmp near ptr s指令的功能，实现在指定位置输出字符串
;用bx传送位移
assume cs:code 

code segment
	start:
		mov ax,cs
		mov ds,ax
		mov si,offset doint7CH
		mov ax,0
		mov es,ax
		mov di,0200H
		
		mov cx,offset doint7CH_end - offset doint7CH
		cld
		rep movsb
		
		;修改向量表
		mov ax,0
		mov es,ax
		mov word ptr es:[7CH*4],200H
		mov word ptr es:[7CH*4+2],0
		
	mov ax,4C00H
	int 21H
;=============jmp near ptr s只修改IP即可，=====================
doint7CH:
	push bp	;保存旧值
	mov bp,sp
	add ss:[bp+2],bx	;jmp near ptr s为偏移16位的值
	over:
		pop bp
		iret
doint7CH_end:nop
;==================================
code ends
end start
