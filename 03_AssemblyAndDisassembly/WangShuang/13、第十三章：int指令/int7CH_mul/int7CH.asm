;2017年5月7日15:11:39
;编写、安装中断7ch的中断例程实现计算平方
;参数：ax传参，dx存放高16位，ax存放低十六位
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
;==================================
doint7CH:
	mul ax
	iret
doint7CH_end:nop
;==================================
code ends
end start
