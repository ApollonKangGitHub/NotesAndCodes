;����0���ж��������жϴ������
assume cs:code

code segment
start:
	mov ax,1000H
	mov bl,1
	div bl
	
	mov ax,4C00H
	int 21H
code ends
end start