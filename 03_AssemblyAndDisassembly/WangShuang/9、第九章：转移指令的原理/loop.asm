;����loopָ��ʵ�����ڴ�2000H���в��ҵ�һ��ֵΪ0���ֽ��ҵ�������ƫ�Ƶ�ַ�����dx�С�
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
	inc cx	;��cxΪ0ʱ���Լ�һ��Ϊ1����loopʱ�Լ�һ��Ϊ0�ͽ���ѭ��
	inc bx
	loop again
	
	;�ҵ��������ô�����ַ�ŵ�DX��
	ok:
	dec bx;��incָ�������෴���Լ���(bx)=(bx)-1
	mov dx,bx
	
	mov ax,4C00H
	int 21H
codeseg ends
end start