;2017��4��25��13:14:17
;Mail��mailbox_krj@163.com
;����FFFF:0~FFFF:F���ֽ������ݵĺͣ�������浽DX��
assume cs:codeseg

codeseg segment

		mov bx,0
		mov ax,0FFFFH
		mov ds,ax
		
		mov dx,0
		mov cx,16
		mov ax,0		;��λ�������㣬֮����AL�����ݣ�����ֻ������һ��
		
	addNumber:
		mov al,ds:[bx]	;�ֽ�������
		add dx,ax		;�ۼ�
		inc bx			;ƫ�Ƶ�ַ�ƶ�һ���ֽ�<==>add bx,1
		loop addNumber	;����(CX)��1
		
		mov ax,4C00H
		int 21H
	
codeseg ends

end