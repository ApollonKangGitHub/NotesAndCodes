;2017-5-7 15:33:08
;��XP�ϲ���ȷ�Ľ��
;��DOSBOX�ϲ���ʱ�������
assume cs:code 

code segment
	start:
	mov ax,0B800H
	mov es,ax
	mov byte ptr es:[12*160+40*2],'!'
	int 0
	
	mov ax,4C00H
	int 21H
code ends
end start
