;TEST3�ĸ�����
assume cs:code,ds:data

data segment
	time db 'yy/mm/dd hh:mm:ss','$'
	cmos db 9,8,7,4,2,0
data ends

code segment
start: 
	mov ax,data
	mov ds,ax
	again:
	mov bx,0
	mov si,0
	mov cx,6
	GetMessage:   
		push cx
		mov al,cmos[bx]
		
		out 70h,al    ;��al�����ַ�˿�70h
		in al,71h ;�����ݶ˿�71h��������Ԫ����
		mov ah,al
		mov cl,4
		shr al,cl ;����4λ
		and ah,0fh    ;al�ֳ�������ʾBCD��ֵ������
		add ax,3030h  ;BCD��+30h=10��������Ӧ��ASCII��
		
		mov ds:[si],ax     ;ASCII��д��time��
		inc bx
		add si,3
		pop cx
	loop GetMessage
	;���ƣ�BIOS�ж�(int 10h)
	;���ܣ�(ah)=2�ù�굽��Ļָ��λ�á�(ah)=9�ڹ��λ����ʾ�ַ�
	;������(al)=�ַ���(bh)=ҳ����(dh)=�кš�(dl)=���š�(bl)=��ɫ���ԡ�(cx)=�ַ��ظ�����
	mov ah,2 ;�ù��
	mov bh,0 ;��0ҳ
	mov dh,13 ;dh�з��к�
	mov dl,32 ;dl�з�����
	int 10h
	;���ƣ�DOS�ж�(int 21h)
	;���ܣ�(ah)=9��ʾ��'$'�������ַ�����(ah)=4ch���򷵻�
	;������ds:dxָ���ַ�����(al)=����ֵ
	mov dx,0
	mov ah,9
	int 21h
	;һ����ʾ����
	loop again 	;ѭ����ʾ
mov ax,4c00h
int 21h
code ends
end start

 
