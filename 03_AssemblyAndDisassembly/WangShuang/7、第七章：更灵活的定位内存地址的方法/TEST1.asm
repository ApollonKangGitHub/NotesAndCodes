;��data���е�ÿ�����ʵĵ�һ����ĸ��Ϊ��д��ĸ
assume cs:codeseg,ds:dataseg

dataseg segment
	db '1. file         '
	db '2. edit         '
	db '3. serach       '
	db '4. view         '
	db '5. options      '
	db '6. help         '
dataseg ends

codeseg segment
	start:
	mov ax,dataseg
	mov ds,ax
	
	mov cx,6
	mov bx,0
	
	ChangeFirst_LTB:	;Big to little
		mov al,0DFH
		and [bx][3],al	;ע�⣺bxҪ��[]������
		add bx,16
	loop ChangeFirst_LTB
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start