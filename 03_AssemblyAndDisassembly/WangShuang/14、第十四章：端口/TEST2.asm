;����λָ����ӷ�ָ�����:
;n*10 = n*2 + n*8
;shl:�߼����ƣ�����Ƴ���һλ�ŵ�CF�У��ұ߲�0	<==> ����2
;shr:�߼����ƣ�����Ƴ���һλ�ŵ�CF�У���߲�0	<==> ����2
;����λ������1ʱ����λλ����Ҫ�ŵ�cl��
;ע�����߼���λ������������λ
assume cs:code

code segment
	start:
	;eg:����188*10
		mov al,188
		mov ah,0
		shl ax,1
		mov bx,ax
		
		mov cl,2
		shl ax,cl
		
		add ax,bx
	mov ax,4C00H
	int 21H
code ends
end start