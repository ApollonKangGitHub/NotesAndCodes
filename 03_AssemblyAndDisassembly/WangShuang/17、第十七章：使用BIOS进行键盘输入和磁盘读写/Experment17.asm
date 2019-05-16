;2017年5月14日11:42:29
;Mail:mailbox_krj@163.com
;Author:KangRuoJin
;Version:v1.1

;安装一个新的int 7CH中断例程，实现通过逻辑扇区号对软盘进行读写
;(该例程需要时对逻辑扇区号到int 13H参数的转化)

;ah传递功能号：0表示读，1表示写
;dx传送要读写的逻辑扇区号
;es:bx指向与磁盘交互的内存区

;面号(dh)=(bx)/1440
;磁道号(ch)=((bx)%1440)/18)
;扇区号(cl)=((bx)%1440)%18)+1
assume cs:code

stack segment
	db 128 dup (0)
stack ends
code segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	call copy_newint7CH	;拷贝
	call install		;安装
	
	;测试
	mov dx,1439+80*18
	mov ah,1	;写
	mov al,5	;扇区数
	int 7CH
	
	mov ax,4C00H
	int 21H
;==================================
copy_newint7CH:
	mov ax,cs
	mov ds,ax
	mov si,offset INT_7CH
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	mov cx,offset INT_7CH_end - offset INT_7CH
	cld 
	rep movsb
ret
;==================================
install:
	cli 
	mov word ptr es:[7CH*4],200H
	mov word ptr es:[7CH*4+2],0
	cld
ret
;==================================
INT_7CH:
	push ax
	push bx
	push cx
	push dx
	
	call calc_physic_number
	add ah,2		;0+2=2(读),1+2=3(写)
	;转换完成以后就可以调用int 13H
	int 13H
	
	pop dx
	pop cx
	pop bx
	pop ax
iret
;==============================
calc_physic_number:	
	push ax
	push bx
	
	;DX作为参数，DXAX被除数,AX商，DX余数
	mov ax,dx
	mov dx,0
	mov bx,1440
	div bx
	
	;AX被除数，AL商，AH余数
	push dx	
	mov dh,al	;面号(磁头号)
	pop ax	
	mov bl,18
	div bl
	
	inc ah
	mov ch,al	;磁道号
	mov cl,ah	;扇区号
	mov dl,0 	;驱动器号
	
	pop bx
	pop ax
ret
INT_7CH_end:nop
;==============================
code ends
end start