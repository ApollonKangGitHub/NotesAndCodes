;�����ݶθ�������ʵ�ֵ��ʹ��jmpָ��ִ�к�CS:IPָ���һ��ָ��
assume cs:codeseg

data segment
	db 16 dup (0)
data ends
codeseg segment 
	start:
	mov ax,data
	mov ds,ax
	mov bx,0
	jmp word ptr [bx+1]	;��ȡds:[1]��ds:[2]�ŵ�IP�У���ôIP�ͱ�Ϊ0���ӵ�һ��ָ�����¿�ʼ
codeseg ends

end start