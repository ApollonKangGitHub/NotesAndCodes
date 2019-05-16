;2017��5��8��17:52:30
;����Ļ�м�������ʾ��a��~��z��
;�Դ���ʾ��Ҫ���ǵ���ʱ���⣬��Ϊ����ʱ�ܿ�ͻᱻˢ��
;����װ������¿��Խ�int 9��ԭ�ж����̵ĵ�ַ���ڱ��������
;�����ڰ�װ���������Ҫ���浽0000:0200��
assume cs:code

stack segment
	db 128 dup (0)
stack ends

data segment
	dw 0,0
data ends

code segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,128
	
	mov ax,data
	mov ds,ax
	
	;��BIOS�ġ�int 9������ڵ�ַ������ds:[0]��ds:[2]��
	mov ax,0
	mov es,ax
	push es:[9*4]
	pop ds:[0]		
	push es:[9*4+2]
	pop ds:[2]		
	
	;�µġ�int 9����ڵ�ַ���浽�������С�int 9����Ӧ��λ��
	cli
	;����Ӧ�����μ����жϣ��������ֻ�����˵�һ��ָ��֮��Ͳ�����һ�������ж�
	;תȥִ�м����ж�int 9����������û������ɣ����Դ�ʱ��int 9�Ȳ���BIOSҲ���������Լ��ģ�����һ������ĵ�ַ
	;�����������µ�ַ֮ǰ����Ҫ���ò���Ӧ�����εļ����жϣ��������Ƶģ����޸Ŀ������жϵ����̵�������ʱ��
	;��Ҫ���ò���Ӧ�޸�������Ӧ�Ŀ������жϣ������޸ĵĹ�����ȥ�����ж����̱ض����������
	mov word ptr es:[9*4],offset int9	
	mov es:[9*4+2],cs
	sti			;�ָ���Ӧ�����μ����ж�
	
	;�Լ����ж����̲���
	mov ax,0B800H
	mov es,ax
	mov al,'a'
	show:
		mov es:[160*12+40*2],al
		inc al
		call Delay
		cmp al,'z'
	jna show
	
	;�ָ���������BIOS�ġ�int 9�����ж�������ڵ�ַ
	mov ax,0
	mov es,ax
	push ds:[0]
	pop es:[9*4]
	push ds:[2]
	pop es:[9*4+2]
	
	mov ax,4C00H
	int 21H
;=====================��ʱ����:��ѭ��==============
Delay:
	push ax
	push dx
	
	mov dx,10H
	mov ax,0
	loopdelay:
			sub ax,1
			sbb dx,0	;(dx)=(dx)-0-CF
			cmp ax,0
		jne loopdelay	;�ڴ�ѭ��
		cmp dx,0
	jne loopdelay	;���ѭ��
	
	pop dx
	pop ax
ret
;====================�µ�"int 9H"�ж�����=======================
int9:
		push ax
		push bx
		push es
		
		in al,60H
		
		;����ģ�⡰int 9���ĵ��ù���
		pushf
		call dword ptr ds:[0]	;����ԭ���ġ�int 9���ж�����
		
		;�޸���ɫ����
		cmp al,1	;1��ESC��ͨ��
		jne int9ret
		
		mov ax,0B800H
		mov es,ax
		inc byte ptr es:[160*12+40*2+1]		;������ֵ��1���ı���ɫ
		
		int9ret:
		pop es
		pop bx
		pop ax
iret
;===============================================================
code ends
end start