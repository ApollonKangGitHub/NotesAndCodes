;˵���� 
;�ڽ������ʵ��ʱ����װ����ϰ�߲�������ͼ1��װ�ṹ
;assume cs:code 
;code segment 
;	start: 
;		��װ���� 
;-------------------------- 
;		����װ���� 
;-------------------------- 
;code ends 
;end start 
;==   ͼ1   == 
;������⣬����������: 
;1��table dw Set_ClearScreen������Set_ClearScreen��ŵ�Ӧ�����ӳ����ƫ�Ƶ�ַ�����ƫ�Ƶ�ַ��������жϳ�����ڵģ�
;����ʱSub1�д�ŵ�������ڰ�װ������ڵĵ�ַ������Ӧ�ý�����װ����ŵ�code�α��Startǰ�ߡ� 
;2���жϳ��򱻵���ʱ��table[bx]Ĭ�ϵĶδ���Ϊcs�������ڰ�װ�����������ж�������ʱ��Ӧ�裺cs=200h(20H)��ip=0��������cs=0��ip=200h
assume cs:code

code segment
SetScreen:
	jmp short SetBegin
	table dw Set_ClearScreen,Set_ForegroundColor,Set_BackgroundColor,Set_ScollUpOneLine
SetBegin:
	push bx
	;ah���ݹ��ܺ���
	cmp ah,3
	ja SetScreenRet	;����3�Ĵ��ݹ��ܺŷǷ�
	mov bl,ah
	mov bh,0
	add bx,bx
	
	call word ptr table[bx]
	
	SetScreenRet:
	pop bx
iret
;====================================
Set_ClearScreen:
	push bx
	push cx
	push es
	
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov cx,2000
	Loop_Set_ClearScreen:
		mov byte ptr es:[bx],' '
		add bx,2
	loop Loop_Set_ClearScreen
	
	pop es
	pop cx
	pop bx
ret
;====================================
Set_ForegroundColor:
	push bx
	push cx
	push es
	
	mov bx,0B800H
	mov es,bx
	mov bx,1
	mov cx,2000
	Loop_ForegroundColor:
		and byte ptr es:[bx],11111000B	;ǰ��ɫֵΪ0(��)
		or es:[bx],al		;al������ɫ
		add bx,2
	loop Loop_ForegroundColor
	
	pop es
	pop cx
	pop bx
ret
;====================================
Set_BackgroundColor:
	push ax
	push bx
	push cx
	push es
	
	mov cl,4
	shl al,cl	;al������ɫ����ǰ����������������Ҫ����
	mov bx,0B800H
	mov es,bx
	mov bx,1
	mov cx,2000
	Loop_BackgroundColor:
		and byte ptr es:[bx],10001111B	;ǰ��ɫֵΪ0(��)
		or es:[bx],al		;al������ɫ
		add bx,2
	loop Loop_BackgroundColor
	
	pop es
	pop cx
	pop bx
	pop ax
ret
;====================================
Set_ScollUpOneLine:
	push cx
	push es
	push ds
	push si
	push di
	
	mov si,0B800H
	mov es,si
	mov ds,si
	mov si,160
	mov di,0
	
	cld
	mov cx,24
	;��һ�и��Ƶ���һ��
	Loop_ScollUpOneLine:
		push cx
		mov cx,160
		rep movsb
		pop cx
	loop Loop_ScollUpOneLine
	;���һ�����
	mov cx,80
	mov si,0
	Loop_Clrer_lastLine:
		mov byte ptr [160*24+si],' '
		add si,2
	loop Loop_Clrer_lastLine
	
	pop di
	pop si
	pop ds
	pop es
	pop cx
ret
;====================================
start:	
	mov ax,cs
	mov ds,ax
	mov si,offset SetScreen
	
	mov ax,0
	mov es,ax
	mov di,200H
	
	;����
	mov cx,offset start - offset SetScreen
	cld
	rep movsb

	;��װ
	cli
	mov word ptr es:[7CH*4],0
	mov word ptr es:[7CH*4+2],20H	;CS:IP=20:0=0000:200H
	sti
	
mov ax,4C00H
int 21H
;====================================
code ends
end start