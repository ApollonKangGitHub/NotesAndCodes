;2017��5��7��21:16:24
;int 7CH�ж����̣�ʵ��loopָ��ж����̰�װ��0:200��
;(cx)=ѭ��������(bx)=λ��
assume cs:code

code segment
start:
	mov ax,cs
	mov ds,ax
	mov si,offset doint7CH
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	mov cx,offset doint7CHend - offset doint7CH
	cld
	rep movsb
	
	mov ax,0
	mov es,ax
	mov word ptr es:[7CH*4],200H
	mov word ptr es:[7CH*4+2],0
	
mov ax,4C00H
int 21H
;===========================
doint7CH:
	push bp
	mov bp,sp
	dec cx
	jcxz over
	add ss:[bp+2],bx
	over:
		pop bp
		iret
doint7CHend:nop
;===========================
code ends
end start