;2017年5月14日10:55:17
;将当前屏幕上的内容保存到磁盘上

assume cs:code

code segment
	db 'write error',0
	start:	mov ax,0B800H
			mov es,ax
			mov bx,0	;es:bx指向屏幕，向磁盘写入
			
			mov ah,3	;写
			mov al,8	;扇区数
			mov ch,0	;磁道
			mov cl,1	;扇区
			mov dh,0	;盘面
			mov dl,0	;驱动器A
			int 13H
			
			cmp ah,0
			jne show_error	;ah不为0则出错
			;je show_error
			
			code_over:
			mov ax,4C00H
			int 21H

			show_error:
			mov ax,cs
			mov ds,ax
			mov si,0	

			mov ax,0B800H
			mov es,ax
			mov di,160*15+35*2

			loop_error:
				cmp byte ptr ds:[si],0
				je code_over
				mov al,ds:[si]
				mov es:[di],al
				inc si
				add di,2
			jmp loop_error
							
code ends
end start