;����10.5(1),AX���յ�ֵ��Debug�������ٽ��������CPUִ�н��
;debug�������Բ��У�����Debugһ���������(CPU��ִ�н��)�ǿ��Ե�
assume cs:codeseg

stack segment
	dw 8 dup (0)
stack ends
codeseg segment
	start:
	mov ax,stack
	mov ss,ax
	mov sp,16
	mov ds,ax
	mov ax,0
	call word ptr ds:[0EH]
	inc ax
	inc ax
	inc ax
	
	mov ax,4C00H
	int 21H
codeseg ends
end start