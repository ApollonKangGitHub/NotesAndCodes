assume cs:codeseg

dataseg segment
	db "Beginner's All-purpose Symbolic Instruction Code.",0
dataseg ends

codeseg segment
start:
	mov ax,dataseg
	mov ds,ax
	mov si,0
	call letterc
	
mov ax,4C00H
int 21H
;=============================
letterc:
	mov ch,0
	again:
		mov cl,ds:[si]
		jcxz last	;cmp cl,0
					;je last	也可以
		cmp cl,'a'	;97也可以
		jb over		;小于97(a)不需要转换，直接下一个
		cmp cl,'z'	;122也可以
		ja over		;大于122(z)不需要转换，直接下一个
		and byte ptr ds:[si],11011111B	;满足在[97,122]的范围内则减20H，转换成大写
	over:
		inc si
		jmp short again
	last:
ret
codeseg ends
end start