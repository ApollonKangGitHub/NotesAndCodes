;①在cs:IP指向loop指令时，可以-p直接快速结束循环
;避免debug的-t操作
;②(CX)的自减是先减再判断，相当于do{}while();而不是while(){}
;那么CX初始化为0时，先减到FFFF再判断，而不是直接判断等于0退出循环。
;并且这是倒计时式的循环，不是计数式的循环

assume cs:codeseg

codeseg segment

	mov ax,0
	mov cx,123			;236,循环123次更优
addNumber:	
	add ax,236	;123
	loop addNumber		;(CX)自减，判断(CX)不等于零，从addNumber循环，类似于goto...loop
	mov ax,4C00H
	int 21H
	
codeseg ends

end