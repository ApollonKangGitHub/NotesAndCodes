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
					;je last	Ҳ����
		cmp cl,'a'	;97Ҳ����
		jb over		;С��97(a)����Ҫת����ֱ����һ��
		cmp cl,'z'	;122Ҳ����
		ja over		;����122(z)����Ҫת����ֱ����һ��
		and byte ptr ds:[si],11011111B	;������[97,122]�ķ�Χ�����20H��ת���ɴ�д
	over:
		inc si
		jmp short again
	last:
ret
codeseg ends
end start