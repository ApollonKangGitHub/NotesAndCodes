;��ջ�����ݶε����ݽ�����ת
;��ʼ������(��������װ�غ󣬵���ûִ��ǰ)��
;DS:0��PSP�����ֽ�
;CS:0=SS:0=DS+10H:0��codeseg���ֽ�
;CS:IP=ds+18H:0��start���ֽ�
;SS:SP=ds+18H:0��ջ��
assume cs:codeseg

codeseg segment
	;DS+10:0(��)
	;CS:0(��)
	;SS:0(��)
	dw 0123H,0456H,0789H,0ABCH,0DEFH,0FEDH,0CBAH,0987H	;8word=16Byte
	dw 0,0,0,0,0,0,0,0,0,0	;ջ���õı�ʵ��Ҫ�õĴ�10word=20Byte
	;SS:SP(��)
	;CS:IP(��)
start:
		mov ax,cs
		mov ss,ax
		mov sp,36	;��ջ���ó�ʼֵ
		
		mov bx,0
		mov cx,8	;��CXѭ�������Ĵ������ó�ֵ

		loop_push:
			push cs:[bx]
			add bx,2
			loop loop_push
		
		mov bx,0
		mov cx,8
		
		loop_pop:
			pop cs:[bx]
			add bx,2
			loop loop_pop
		
		mov ax,4C00H
		int 21H
		
codeseg ends

end start
