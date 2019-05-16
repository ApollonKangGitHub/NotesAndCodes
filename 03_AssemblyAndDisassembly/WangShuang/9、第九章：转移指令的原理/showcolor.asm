;Author:Kangruojin
;Time:2017年5月1日23:39:12
;Mail:mailbox_krj@163.com
;Version:V1.1

;高位字节：BL(闪烁)、E、G、B(背景)、I(高亮)、R、G、B(前景)
;B8000~BFFFF总共32K，分为8页，一页4K，在任意一页上写都可以

;第1页：B8000~B8F9F
;第十行：B8640~B86DF
;第十一行：B86E0~B877F
;第十二行：B8780~B881F

assume cs:codeseg,ds:data,ss:stack

data segment
	   ;0123456789ABCDEF
	db 'welcome to masm!'	;16个字符
	db 00000010B	;黑底绿字
	db 01110001B	;白底蓝字
	db 00100100B	;绿底红字
	;db 10001111B	;黑底白字高亮闪烁
	;db 11011111B	;紫底白字高亮闪烁
data ends

stack segment
	db 16 dup (0)
stack ends

codeseg segment
	start:
		mov ax,data
		mov ds,ax
		mov ax,stack
		mov ss,ax
		mov sp,16
		mov ax,0B864H	;第十行起始位置
		mov es,ax
		
		mov bx,30*2	;从第30个字符开始
		mov cx,3	
		mov bp,16	
		
		loop_line:
			push cx
			mov si,0
			mov di,0
			mov cx,16
			loop_color:
				mov al,ds:[si]
				mov es:[bx][di],al	;写ASCII码
				mov ah,ds:[bp]
				mov es:[bx][di+1],ah	;写属性
				inc si		;数据段下标后移一个
				add di,2	;写完一个，移动两个字节
			loop loop_color
			pop cx
			add bx,80*2	;换下一行
			inc bp	;下一行换下一个属性
		loop loop_line
		
		mov ax,4C00H
		int 21H
codeseg ends
end start