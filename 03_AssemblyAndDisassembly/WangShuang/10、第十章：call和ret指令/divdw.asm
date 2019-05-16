;2017年5月4日12:51:17
;Mail:mailbox_krj@163.com
;Author:Kangruojin
;Version:v1.1

;除法溢出的解决：用divdw函数实现：
;①参数(parameters):
;(ax)=dword型被除数的低16位
;(dx)=dword型被除数的高16位
;(cx)=除数
;②返回值(return value):
;(dx)=商的高16位
;(ax)=商的低16位
;(cx)=余数
;公式:X/N=int(H/N)*65535+[rem(H/N)*65535+L]/N
;X:被除数(dd型)、N除数(dw型)、H被除数的高16位、L被除数的低16位、int()表示取整、rem()表示取余
;X/N会溢出，分解后的几个除法都不会溢出

assume cs:codeseg,ss:stackseg

dataseg segment
	dd 0,0,0,0
dataseg ends

stackseg segment
	dd 0,0,0,0
stackseg ends

codeseg segment
start:
	mov ax,stackseg
	mov ss,ax
	mov sp,16
	
	mov dx,000FH	;H
	mov ax,4240H	;L
	mov cx,0AH		;N

	call divdw
mov ax,4C00H
int 21H
;=================大商的防溢出操作函数===============
divdw:
	mov bx,dataseg
	mov ds,bx
	push ax
	mov ax,dx
	mov dx,0
	div cx	
	mov ds:[0],ax
	pop ax	
	div cx		
	mov cx,dx	;保存rem([rem(H/N)*65535+L]/N),这才是最终的余数,放到cx中返回
	mov dx,ds:[0]	;返回值商的高16位,低16位在ax中
ret

;========================只用栈不用额外的dataseg========================
;======注意：当栈定指针向下移动后，不再保证上面的数据完整===============
divdw2:
	push ax
	mov ax,dx
	mov dx,0
	div cx
	mov bp,sp
	push ax
	mov ax,ss:[bp]
	div cx
	mov cx,dx
	pop dx
	pop bx	;早期的ax，已经用过的
ret
codeseg ends
	
end start