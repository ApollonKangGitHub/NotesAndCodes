;2017��5��13��16:18:14
;Mail:mailbox_krj@163.com
;Author:KangRuoJin
;Version:v1.2
assume cs:code,ds:data,ss:stack

data segment
	db 256 dup (0)
data ends
stack segment
	db 128 dup (0)
stack ends

code segment
start:
	mov bx,stack
	mov ss,bx
	mov sp,128

	call copy_boot
	
	mov bx,0
	push bx
	mov bx,7E00H
	push bx
	retf	;��ת��0:7E00H��ʼִ��
	
mov ax,4C00H
int 21H
;================================================================
boot:
	jmp boot_start
;*******************************************************************************************
	MENU_1	db 'Weclome to System of Mr.Kang',0
	MENU_2	db '(1) Reset PC',0
	MENU_3	db '(2) Start System',0
	MENU_4	db '(3) ShowClock',0
	MENU_5	db '(4) Set Clock',0
	MENU_6 	db 'Please Enter Your Choose(1~4):',0
	
	MENU_ADDRESS	dw offset MENU_1 - offset boot + 7E00H
					dw offset MENU_2 - offset boot + 7E00H
					dw offset MENU_3 - offset boot + 7E00H
					dw offset MENU_4 - offset boot + 7E00H
					dw offset MENU_5 - offset boot + 7E00H
					dw offset MENU_6 - offset boot + 7E00H
	time 	db 'YY/MM/DD hh:mm:ss',0
	cmos 	db 9,8,7,4,2,0
	clockone	db 'press F1 to change the color, press ESC to return',0
	clock2	db 'Please input Date and Time,(YY MM DD hh mm ss):',0
	change 	db 12 dup (0),0
;*******************************************************************************************
boot_start:
	call init_reg
	call clear_screen
	call show_menu
	jmp choose_option
mov ax,4C00H
int 21H
;================================================================
choose_option:
	call clear_keyboard_buffer	;������̻�����
	mov ah,0
	int 16H
	
	cmp al,'1'
	je choose_option_one
	cmp al,'2'
	je choose_option_two
	cmp al,'3'
	je choose_option_three
	cmp al,'4'
	je choose_option_four
	jmp choose_option
;================================
choose_option_one:               
jmp choose_option                

choose_option_two:               
jmp choose_option                

choose_option_three:             
	call ShowClock               
jmp boot_start			;���ص�boot_start��������������ʾ                

choose_option_four:    
	call SetClock
jmp boot_start	   
;=================================================================
SetClock:
	call init_reg			;�Ĵ�����ʼ��
	call clear_screen		;���������»��߿�
	call clear_change_stack	;��մ���޸����ݵ�ջ������
	
	;������ʾ��ʾ��Ϣ��λ��Ϊ10��15�п�ʼ
	mov di,160*10+15*2
	mov si,offset clock2 - offset boot + 7E00H
	call show_line
	;��ʾ�޸Ļ������е�����
	mov di,160*12+30*2		
	mov si,offset change - offset boot + 7E00H
	call show_line
	
	call get_string
	call set_CMOSRAM
ret
;=================================================================
set_CMOSRAM:
	mov bx,offset cmos - offset boot + 7E00H
	mov si,offset change - offset boot + 7E00H
	mov cx,6
	
	ChangeMessage:   ;GetMessage�������
		push cx
		
		mov dx,ds:[si]
		sub dx,3030H
		mov cl,4
		shl dl,cl
		and dh,00001111B
		or dl,dh
		
		mov al,ds:[bx]
		out 70H,al    ;��al�����ַ�˿�70h
		mov al,dl
		out 71H,al ;	������д��CMOSRAMʱ��
		
		inc bx
		add si,2
		pop cx
	loop ChangeMessage
ret
;================================================================= 
get_string:
	mov si,offset change - offset boot + 07E00H
	mov bx,0
getSting:
	mov ah,0
	int 16H
	cmp al,'0'	;�ж��Ƿ���С�ڡ�0��
	jb noNumber
	cmp al,'9'	;�ж��Ƿ����'9'
	ja noNumber
	call char_push
	cmp bx,12
	ja EnterKey			;�������뷶Χ�Ͳ��������䣬ֱ�ӽ���
	mov di,160*12+30*2	;��SetClock�У���ʾ�޸Ļ������е�����λ�����Ӧ
	call show_line
	jmp getSting
noNumber:
	cmp ah,0EH	;�˸�ͨ��
	je BackspaceKey
	cmp ah,1CH	;�س�ͨ��
	je EnterKey
	jmp getSting
BackspaceKey:
	call char_pop
	mov di,160*12+30*2	;��SetClock�У���ʾ�޸Ļ������е�����λ�����Ӧ	
	call show_line
	jmp getSting
EnterKey:
ret
;=================================================================
char_push:
	cmp bx,12
	ja char_push_over
	mov ds:[si+bx],al
	inc bx
	char_push_over:
ret
char_pop:
	cmp bx,0
	je char_pop_over
	dec bx
	mov byte ptr ds:[si+bx],'*'
	char_pop_over:
ret
;=================================================================      
clear_change_stack:
	push bx
	push cx
	
	mov bx,offset change - offset boot + 7E00H
	mov cx,6			
	ClearChangeStack:
		mov word ptr ds:[bx],'**'
		add bx,2
	loop ClearChangeStack
	
	pop cx
	pop bx
ret
;=================================================================
ShowClock:
	call init_reg			;�Ĵ�����ʼ��
	call clear_screen		;���������»��߿�
	mov di,14*160+15*2		;������ʾ��ʾ��Ϣ��λ��Ϊ14��15�п�ʼ
	mov si,offset clockone - offset boot + 7E00H
	call show_line	;��ʾ
	
	ShowClockStart:
		call GetTimeMessage		;��ȡʱ����Ϣ�ŵ�time��ȥ
		mov di,10*160+30*2		;������ʾʱ�������ڵ�λ��Ϊ10��30�п�ʼ
		mov si,offset time - offset boot + 7E00H
		call show_line			;��������ʾ
		
		;����Ķ�ȡ���̻��������Լ���ɣ������������
		mov ah,1		;������ʽ��ȡ�������Ƿ�������ȡ������ȡ��֮�󣬻������������
		int 16H
		jz ShowClockStart
		cmp ah,3BH
		je ChangeColor
		cmp al,1BH		;ESCɨ����Ϊ1�����趨�Ĺ��ܺ��г�ͻ��������ASCII��
		je ReturnToMainMenu
		cmp al,0		;�ܵ�����һ��˵����ΪF1Ҳ��ΪESC
		jne ClearKeyBuffer	;���ǲ�Ϊ0˵��һ�����м����жϲ�������Ҫ������õļ����ж�
	jmp ShowClockStart
;================================
ChangeColor:					;�ı���ɫ
	call ChangeShowColor
ClearKeyBuffer:
	call clear_keyboard_buffer	;�����������ȡʱδ��յĻ�����
	jmp ShowClockStart
ReturnToMainMenu:				;�˻ص�choose_optionʱ��������������������ﲻ��Ҫ���������
ret
;================================================================
GetTimeMessage:
	mov cx,6
	mov bx,offset cmos - offset boot + 7E00H
	mov si,offset time - offset boot + 7E00H
	GetMessage:   
		push cx
		mov al,ds:[bx]
		
		out 70H,al    ;��al�����ַ�˿�70h
		in al,71H ;�����ݶ˿�71h��������Ԫ����
		mov ah,al
		mov cl,4
		shr al,cl ;����4λ
		and ah,0FH    ;al�ֳ�������ʾBCD��ֵ������
		add ax,3030H  ;BCD��+30h=10��������Ӧ��ASCII��
		
		mov word ptr ds:[si],ax     ;ASCII��д��time��
		inc bx
		add si,3
		pop cx
	loop GetMessage
ret
;================================================================
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
;================================================================
clear_keyboard_buffer:
	mov ah,1
	int 16H			;�޸���ax������ZF���ܻ�ı�

	jz ClearKeyboardBufferOver	;�����������ȡ������Ϊ0�����
	mov ah,0		;����������������ķ�ʽ���һ�λ������ֽ�
	int 16H
	jmp clear_keyboard_buffer
	ClearKeyboardBufferOver:
ret
;================================================================
init_reg:
	mov bx,0B800H
	mov es,bx
	mov bx,0
	mov ds,bx
ret
;================================================================
clear_screen:
	mov bx,0
	mov cx,2000
	mov dx,1F00H	;��������
	ClearScreen:
		mov es:[bx],dx	
		add bx,2
	loop ClearScreen
	
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
;================================================================
show_menu:
	mov bx,offset MENU_ADDRESS - offset boot + 7E00H
	mov di,160*8 + 25*2
	mov cx,6
	ShowMenu:	
		mov si,ds:[bx]	;��ȡ�������Ϣ��ƫ�Ƶ�ַ
		call show_line	;������ʾ��λ����ʾһ��
		add bx,2		;��ȡ��һ�����ݵĵ�ַ
		add di,160		;�������һ��
	loop ShowMenu
ret
;================================================================
show_line:
	push ax
	push si
	push di
ShowLineStart:
	mov al,ds:[si]	;��ȡһ���ַ�
	cmp al,0		;����0���������
	je ShowLineOver
	mov es:[di],al	;�����Ĳ���0���������ʾ����
	add di,2
	inc si
	jmp ShowLineStart
ShowLineOver:
	pop di
	pop si
	pop ax
ret
;================================================================
boot_end:nop
;================================================================
copy_boot:	;������θ��Ƶ�0:7E00H������ʽ��д������Ҫ������ŵ��ڴ���ȥ��
	mov bx,cs
	mov ds,bx
	mov si,offset boot
	
	mov bx,0
	mov es,bx
	mov di,7E00H
	mov cx,offset boot_end - offset boot
	cld
	rep movsb
ret
;================================================================
code ends
end start