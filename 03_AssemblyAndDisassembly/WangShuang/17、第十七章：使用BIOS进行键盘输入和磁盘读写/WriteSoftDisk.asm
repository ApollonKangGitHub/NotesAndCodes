;2017��5��14��10:55:17
;����ǰ��Ļ�ϵ����ݱ��浽������

assume cs:code

code segment
	db 'write error',0
	start:	mov ax,0B800H
			mov es,ax
			mov bx,0	;es:bxָ����Ļ�������д��
			
			mov ah,3	;д
			mov al,8	;������
			mov ch,0	;�ŵ�
			mov cl,1	;����
			mov dh,0	;����
			mov dl,0	;������A
			int 13H
			
			cmp ah,0
			jne show_error	;ah��Ϊ0�����
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