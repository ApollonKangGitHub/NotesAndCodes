;��ˬ��������ԡ������桷ʵ����-P172
;��data�зֿ��ģ���ݡ���˾���롢Ա�����������Ⱥ�˳��д��table���
;���(4B)+(�ո�1B)+����(4B)+(�ո�1B)+Ա������(2B)+(�ո�1B)+ƽ������(2B)+(�ո�1B)
;�ܹ�16B����Debug��һ�����Ϣ��¼��ռһ�У�21�깲ռ21��
;Ա��ƽ������=����/Ա������(ȡ��)
assume cs:codeseg

data segment
	;���:0~84
	db '1975','1976','1977','1978','1979','1980','1981'
	db '1982','1983','1984','1985','1986','1987','1988'
	db '1989','1990','1991','1992','1993','1994','1995'
	;��˾����:84~168
	dd 16,22,382,1356,2390,8000,16000,24486,50065,97479,140417,197514,345980
	dd 590827,803530,1183000,1843000,2759000,3753000,4649000,5937000
	;Ա������:168~210
	dw 3,7,9,13,28,38,130,220,476,778,1001,1442,2258,2793
	dw 4037,5635,8226,11542,14430,15257,17800
data ends

table segment
	db 21 dup ('year summ ne ?? ')
table ends

codeseg segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,table
	mov es,ax

	mov bx,0
	mov bp,0
	mov cx,21
	mov di,0
	
	loop_one:
		mov ax,cx
		
		mov cx,2
		mov si,0
		loop_two:
			mov dx,ds:[bp].0[si]	;��ݸ���,ע�⣺Ҫͨ���Ĵ�������
			mov es:[bx].0[si],dx
			mov dx,ds:[bp].84[si]	;��˾�����븴��
			mov es:[bx].5[si],dx
			add si,2
		loop loop_two
		mov cx,ax	;��ǰת��������Ϊ����Ҫ�õ�ax
		
		mov dx,ds:168[di]
		mov es:[bx].10,dx;Ա������

		mov dx,es:[bx].7		;������ĸ�16λ
		mov ax,es:[bx].5		;������ĵ�16λ
		div word ptr es:[bx].10		;���г���������㹤��,word ptrָ����������AX��DX�Ĵ�����
		mov es:[bx].13,ax			;�����ƶ�������ƽ�����ʵ��ڴ���
		
		add di,2
		add bp,4
		add bx,16	;bx�Լӽ�����һ�������
	loop loop_one
	
	mov ax,4C00H
	int 21H
	
codeseg ends
end start