;Author:Kangruojin
;Time:2017��5��1��23:39:12
;Mail:mailbox_krj@163.com
;Version:V1.1

;��λ�ֽڣ�BL(��˸)��E��G��B(����)��I(����)��R��G��B(ǰ��)
;B8000~BFFFF�ܹ�32K����Ϊ8ҳ��һҳ4K��������һҳ��д������

;��1ҳ��B8000~B8F9F
;��ʮ�У�B8640~B86DF
;��ʮһ�У�B86E0~B877F
;��ʮ���У�B8780~B881F

assume cs:codeseg,ds:data,ss:stack

data segment
	   ;0123456789ABCDEF
	db 'welcome to masm!'	;16���ַ�
	db 00000010B	;�ڵ�����
	db 01110001B	;�׵�����
	db 00100100B	;�̵׺���
	;db 10001111B	;�ڵװ��ָ�����˸
	;db 11011111B	;�ϵװ��ָ�����˸
data ends

stack segment
	db 16 dup (0)
stack ends

codeseg segment
	start:
		mov ax,data
		mov ds,ax
		mov ax,stack
		mov ss,ax
		mov sp,16
		mov ax,0B864H	;��ʮ����ʼλ��
		mov es,ax
		
		mov bx,30*2	;�ӵ�30���ַ���ʼ
		mov cx,3	
		mov bp,16	
		
		loop_line:
			push cx
			mov si,0
			mov di,0
			mov cx,16
			loop_color:
				mov al,ds:[si]
				mov es:[bx][di],al	;дASCII��
				mov ah,ds:[bp]
				mov es:[bx][di+1],ah	;д����
				inc si		;���ݶ��±����һ��
				add di,2	;д��һ�����ƶ������ֽ�
			loop loop_color
			pop cx
			add bx,80*2	;����һ��
			inc bp	;��һ�л���һ������
		loop loop_line
		
		mov ax,4C00H
		int 21H
codeseg ends
end start