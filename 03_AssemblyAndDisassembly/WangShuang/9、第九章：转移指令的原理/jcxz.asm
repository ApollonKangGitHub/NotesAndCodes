;����jcxzָ��ʵ�����ڴ�2000H���в��ҵ�һ��ֵΪ0���ֽ��ҵ�������ƫ�Ƶ�ַ�����dx�С�
assume cs:codeseg

codeseg segment
	start:
	mov ax,2000H
	mov ds,ax
	mov bx,0
	;Ѱ�ҵ��ֽ�ֵΪ0�ĵ�ַ
	again:
	mov cx,0
	mov cl,ds:[bx]
	jcxz ok	;���ҵ���ֵ�浽cx�У��ҵ�0������CX��ҲΪ0����ô���Զ�����ok��
	inc bx
	jmp short again
	
	;�ҵ��������ô�����ַ�ŵ�DX��
	ok:
	mov dx,bx
	
	mov ax,4C00H
	int 21H
codeseg ends
end start