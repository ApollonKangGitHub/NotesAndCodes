;��DOS��int 21H�ж�������ʾ�ַ����ڹ��������ʼλ��
;2017��5��7��18:09:42
assume cs:code

data segment
	db 'Yvyv I Love You!!$'
data ends
code segment
	start:
	mov ah,2
	mov bh,0
	mov dh,5
	mov dl,12
	int 10H
	
	;int 21H����ʾ�ַ����Ĺ���
	;ds:dxָ��Ҫ��ʾ���ַ���("��$��β��$����ʾ")
	;�ӳ����Ϊ9
	mov ax,data
	mov ds,ax
	mov dx,0
	mov ah,9
	int 21H
	
	mov ax,4C00H
	int 21H
code ends
end start