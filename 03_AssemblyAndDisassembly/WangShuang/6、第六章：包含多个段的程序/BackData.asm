;用栈将数据段的数据进行逆转
;初始条件下(编译连接装载后，但是没执行前)：
;DS:0在PSP区首字节
;CS:0=SS:0=DS+10H:0在codeseg首字节
;CS:IP=ds+18H:0在start首字节
;SS:SP=ds+18H:0在栈顶
assume cs:codeseg

codeseg segment
	;DS+10:0(√)
	;CS:0(√)
	;SS:0(√)
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H	;8word=16Byte
	dw 0,0,0,0,0,0,0,0,0,0	;栈设置的比实际要用的大10word=20Byte
	;SS:SP(√)
	;CS:IP(√)
start:
		mov ax,cs
		mov ss,ax
		mov sp,36	;给栈设置初始值
		
		mov bx,0
		mov cx,8	;给CX循环计数寄存器设置初值

		loop_push:
			push cs:[bx]
			add bx,2
			loop loop_push
		
		mov bx,0
		mov cx,8
		
		loop_pop:
			pop cs:[bx]
			add bx,2
			loop loop_pop
		
		mov ax,4C00H
		int 21H
		
codeseg ends

end start
