;����mov ax,4C00Hָ��֮ǰ������ָ�0:200��
assume cs:codeseg

codeseg segment

	mov ax,cs	;ֱ�ӻ�ȡ����μĴ���
	mov ds,ax
	mov ax,0020H
	
	mov es,ax
	mov bx,0
	mov cx,17H	;�ܹ����Ƶ��ֽ�����mov ax,4C00H֮ǰ23���ֽڣ����Բ鿴CopyCmd.LST�ļ�
	
	s:
	mov al,[bx]
	mov es:[bx],al
	inc bx
	loop s
	
	mov ax,4C00H
	int 21H

codeseg ends

end