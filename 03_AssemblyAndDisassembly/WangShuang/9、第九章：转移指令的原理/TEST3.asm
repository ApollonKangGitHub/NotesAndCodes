assume cs:codeseg

codeseg segment
	start:
	mov ax,2000H
	mov es,ax
	mov ds,ax
	;mov bx,1000H
	;jmp dword ptr [bx]	
	jmp dword ptr ds:[1000H] ;[]��Ϊ����ʱ��������ε�ַ�Ĵ���
	
	mov ax,4C00H
	int 21H
codeseg ends

end start