assume cs:code,ds:table

stack segment
	db 128 dup (0)
stack ends

table segment
	change	db '00/00/00 00:00:00',0
	menu	db 'Weclome to System of Mr.Kang   ',0
			db '      (1) Reset PC             ',0
			db '      (2) Start System         ',0
			db '      (3) Clock                ',0
			db '      (4) Set Clock            ',0
			db 'Please Enter Your Choose(1~4): ',0
			
	time 	db 'YY/MM/DD hh:mm:ss',0
	cmos 	db 9,8,7,4,2,0
	clock1	db 'press F1 to change the color, press ESC to return',0
	clock2	db 'Please input Date and Time,(YY/MM/DD hh:mm:ss):',0
table ends

data segment
	db 256 dup (0)
data ends

code segment
start:
	mov ax,stack
	mov ss,ax
	mov sp,128

	call get_keyboard
mov ax,4C00H
int 21H
;================================
init_reg:
	mov ax,table
	mov ds,ax
	mov ax,0B800H
	mov es,ax
ret
;===============���������ñ߿�================
clear_screen:
	mov bx,0
	mov cx,2000
	clear:
		mov es:[bx],1F00H	;��������
		add bx,2
	loop clear
	
	mov bx,6*160+10*2
	mov cx,60
	clear_showframe_UpandDown:
		mov byte ptr es:[bx],'#'
		mov byte ptr es:[bx+160*9],'#'
		add bx,2
	loop clear_showframe_UpandDown
	
	mov bx,7*160+10*2
	mov cx,8
	clear_showframe_LeftandRight:
		mov byte ptr es:[bx],'#'
		mov byte ptr es:[bx+59*2],'#'
		mov byte ptr es:[bx+2],'#'
		mov byte ptr es:[bx+59*2-2],'#'
		add bx,160
	loop clear_showframe_LeftandRight
	
ret
;================================
show_message:
	mov cx,6
	mov di,160*8+25*2	;�ӵ�8�п�ʼ��ʾ
	mov si,offset menu
	loop_show:
		call show_diff_message	
		add di,160
		add si,32
	loop loop_show
ret
;================================
get_keyboard:
	push ax
get_keyboard_begin:
	call init_reg
	call clear_screen
	call show_message
	
	mov ah,0
	int 16H

	cmp al,'1'
	je ResetPC
	cmp al,'2'
	je StartSystem
	cmp al,'3'
	je ShowClock
	cmp al,'4'
	je SetClock
	jmp short get_keyboard_begin

ResetPC:
	;call ResetPC_Function
jmp get_keyboard_begin

StartSystem:
	;call StartSystem_Function
jmp get_keyboard_begin

ShowClock:
	call ShowClock_Function
jmp get_keyboard_begin
;����ʱ��
SetClock:
	call SetClock_Function
jmp get_keyboard_begin

get_keyboard_over:
	pop ax
ret
;================================
SetClock_Function:
;������ʾ��ʾ��Ϣ��λ��Ϊ18��15�п�ʼ
	mov di,160*18+15*2
	mov si,offset clock2
	call show_diff_message
	
	call clear_stack
	mov di,20*160+15*2		
	mov si,offset change
	call show_diff_message	;��ʾ
	
	call getstr
	call WriteCMOSRAM
ret
;=============���ղ���������ж�==============
getstr:
	push ax
getstrs:
	mov ah,0
	int 16H
	cmp al,20H	;ASCII��С��20H˵�������ַ�
	jb nochar
	mov ah,0	;�ַ���ջ
	call charstack
	mov ah,2	;��ʾջ���ַ�
	call charstack	
	jmp getstrs
nochar:
	cmp ah,0EH	;�˸�ͨ��
	je BackspaceKey
	cmp ah,1CH	;�س�ͨ��
	je EnterKey
	jmp getstrs
BackspaceKey:
	mov ah,1
	call charstack
	mov ah,2
	call charstack
	jmp getstrs
EnterKey:
	mov al,0
	mov ah,0
	call charstack	;�������룬0��ջ
	mov ah,2		;��ʾջ���ַ�
	call charstack
	pop ax
ret
;===============================================
clear_stack:
	push es
	push bx
	push cx
	
	mov bx,0
	mov cx,6
	loop_clear_stack:
		mov byte ptr ds:[bx],'0'
		mov byte ptr ds:[bx+1],'0'
		add bx,3
	loop loop_clear_stack
	
	mov bx,cs
	mov es,bx
	mov bx,offset top
	mov word ptr es:[bx],0
	
	pop cx
	pop bx
	pop es
ret
;===============================================
WriteCMOSRAM:
	push ax
	push bx
	push cx
	push dx
	push si
	push di	
	
	mov si,0
	mov bx,0
	mov cx,6
	ChangeMessage:   ;GetMessage�������
		push cx
		mov al,cmos[bx]
		out 70H,al    ;��al�����ַ�˿�70h
		
		mov dx,word ptr change[si]
		sub dx,3030H
		mov cl,4
		and dh,00001111B
		shl dl,cl
		or dl,dh
		
		mov al,cmos[bx]
		out 70H,al    ;��al�����ַ�˿�70h
		mov al,dl
		out 71H,al ;	������д��CMOSRAMʱ��
		
		inc bx
		add si,3
		pop cx
	loop ChangeMessage
	
	pop di
	pop si
	pop dx
	pop cx
	pop bx
	pop ax
ret
;==============�ַ���ջ����ջ����ʾ=============
charstack:
	jmp short charstart
table_stack	dw charpush,charpop,charshow
top 		dw 0
charstart:	;��ȡ(al)���ܺŲ��ж�
	push bx
	push dx
	push di
	
	cmp ah,2	;����2�����
	ja sret
	mov bl,ah
	mov bh,0
	add bx,bx
	jmp word ptr table_stack[bx]	;��ַ
charpush:
	mov bx,top
	mov ds:[si][bx],al	;��ջ��al�����ַ�
	inc top				;ջ��ָ������һ���ֽ�
	jmp sret			;��ջ���
charpop:
	cmp top,0
	je sret			;ջΪ��ʱ���ó�ջֱ�ӽ���
	dec top			;���ƶ�ָ��
	mov bx,top		;�ٳ�ջ
	mov al,ds:[si][bx]	;al���س�ջ�ַ�
	jmp sret			;��ջ�����
charshow:
	mov al,160
	mov dh,20
	mov dl,15
	mov ah,0
	mul dh
	mov di,ax
	add dl,dl
	mov dh,0
	add di,dx	;���㣺�к�*160+��=((dh)*160+(dl)*2)=(di)
	mov bx,0
charshows:
	cmp bx,top		;�Ƿ�ջ��
	jne noempty		;û��ջ���ͼ������
	mov byte ptr es:[di],' '	
	;�þ���������ڣ�ÿ�����ʱ����һ����Ч�ַ����ᱻ���
	;��ôɾ��һ���������ʱ�����ַ��ѳ�Ϊ��һ����Ч�ַ������ո񸲸ǵ����ٴ����ʱ������ӹ���
	;�µ������̲��Ḳ��ԭ����ɾ����λ�ã�����ԭ����δ��ɾ�����ַ�������ʾ����Ļ�ϣ�������Ч��
	jmp sret
noempty:
	mov al,ds:[si][bx]
	mov es:[di],al
	mov byte ptr es:[di+2],' '
	inc bx
	add di,2
	jmp charshows	;ѭ���ж���һ���Ƿ�ջ��
sret:
	pop di
	pop dx
	pop bx
ret
;================================
ShowClock_Function:
	push ax
	call init_reg			;�Ĵ�����ʼ��
	call clear_screen		;���������»��߿�
		
	;������ʾ��ʾ��Ϣ��λ��Ϊ14��15�п�ʼ
	mov di,14*160+15*2		
	mov si,offset clock1
	call show_diff_message	;��ʾ
	
	ShowClockAgain:
		call GetTimeMessage		;��ȡʱ����Ϣ�ŵ�time��ȥ
		;������ʾʱ���λ��Ϊ10��30�п�ʼ
		mov di,10*160+30*2
		mov si,offset time
		call show_diff_message	;��������ʾ
		
		mov ah,1	;������ʽ��ȡ�������Ƿ�������ȡ������ȡ��֮�󣬻������������
		int 16H
		cmp ah,3BH
		je ChangeColor
		cmp al,1BH		;ESCɨ����Ϊ1�����趨�Ĺ��ܺ��г�ͻ��������ASCII��
		je ExitToMainMenu
		cmp al,0		;�ܵ�����һ��˵����ΪF1Ҳ��ΪESC�����ǲ�Ϊ0˵��һ�����м����жϲ�������Ҫ������õļ����ж�
		jne ClearKeyBuffer
	jmp ShowClockAgain
;�ı���ɫ
ChangeColor:
	call ChangeShowColor
ClearKeyBuffer:
	mov ah,0	;��շ�������ȡû����յĻ�����
	int 16H
	jmp ShowClockAgain
ExitToMainMenu:
	mov ah,0	;��շ�������ȡû����յĻ�����
	int 16H
	
	pop ax
ret
;================================
;�ú���һ����ʾһ�У���������Ϊ��
;di:��ʾλ��(�������ֵ)
;si:��ʾ��������table�е�λ��
;================================
show_diff_message:
	push ax
	push si
	push di
	loop_show_diff:
		mov al,ds:[si]
		cmp al,0
		je show_over
		mov es:[di],al
		inc si
		add di,2
	jmp short loop_show_diff
show_over:
	pop di
	pop si
	pop ax
ret
;================================
GetTimeMessage:
	push ax
	push bx
	push cx
	push si
	
	mov si,0
	mov bx,0
	mov cx,6
	GetMessage:   
		push cx
		mov al,cmos[bx]
		
		out 70H,al    ;��al�����ַ�˿�70h
		in al,71H ;�����ݶ˿�71h��������Ԫ����
		mov ah,al
		mov cl,4
		shr al,cl ;����4λ
		and ah,0FH    ;al�ֳ�������ʾBCD��ֵ������
		add ax,3030H  ;BCD��+30h=10��������Ӧ��ASCII��
		
		mov word ptr time[si],ax     ;ASCII��д��time��
		inc bx
		add si,3
		pop cx
	loop GetMessage
	
	pop si
	pop cx
	pop bx
	pop ax
ret
;================================
ChangeShowColor:
	push bx
	push cx
	
	mov cx,2000
	mov bx,1
	loopChangeShowColor:
		add byte ptr es:[bx],1
		or byte ptr es:[bx],00001000B		;��������˸����
		and byte ptr es:[bx],10001111B		;����һֱΪ��ɫ
		add bx,2
	loop loopChangeShowColor

	pop cx
	pop bx
ret
;================================
code ends
end start