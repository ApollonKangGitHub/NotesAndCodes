;如果修改最后一行的end start为end，哪段代码(TEST1.asm/TEST2.asm/TEST3.asm)能正常运行？
;TEST3能正常运行，TEST1和TEST2不能。
;因为start只是标识地址，而end start则是告诉编译器start是入口，如果修改最后一行的end start为end
;那么编译器就不会理睬start，将默认的入口地址写入可执行文件描述信息。
;而默认的入口地址就是codeseg+dataseg+stackseg三段地址中最前面的地址(低地址)
;如果代码段(code)在我们编码时本来就在第一段，那么不加end start，编译器将首段地址(cs)写入可执行文件描述信息。
;但是如果stack/data段是第一段，那写入可执行文件描述信息的地址就是(ss)/(ds)，将数据解析成指令程序肯定是无法正常运行的
;所以只有TEST3才能正确运行。

assume cs:code,ds:data,ss:stack
;code段移动到第一段(内存也相应发生变化？)
code segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	
	push ds:[0]
	push ds:[2]
	pop ds:[2]
	pop ds:[0]
	
	mov ax,4C00H
	int 21H
	
code ends

data segment
	dw 0123H,0456H
data ends

stack segment
	dw 0,0
stack ends

end start