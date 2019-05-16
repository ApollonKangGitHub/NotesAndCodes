assume cs:code,ss:stack

stack segment
	db 128 dup (0)
stack ends

data segment
	START_ROW		dw 160*0+25*2
							   ;0123456789ABCDEF0123456789ABCDEF
	ROW_MESSAGE		db 	1 dup ('11111111111111111111111111111111')	;��
					db 23 dup ('10000000000000000000000000000001')	;�м�
					db 	1 dup ('11111111111111111111111111111111')	;��
	ROW_NUMBER		dw 25							;����
	COLUMN_NUMBER	dw 32							;����
	NEXT_ROW		dw 160
	BORDER_COLOR	dw 0130H
	
	START_BLOCK_ROW	dw 160+14*2
	
	BLOCK_A			db '1100'
					db '1100'
					db '0000'
					db '0000'
					
	BLOCK_B			db '1000'
					db '1000'
					db '1000'
					db '1000'
					
	BLOCK_C			db '1100'
					db '0110'
					db '0000'
					db '0000'
					
	BLOCK_D			db '0110'
					db '1100'
					db '0000'
					db '0000'
					
	BLOCK_E			db '0100'
					db '1110'
					db '0000'
					db '0000'
					
	BLOCK_F			db '1000'
					db '1000'
					db '1100'
					db '0000'
					
	BLOCK_G			db '0100'
					db '0100'
					db '1100'
					db '0000'
	BLOCK 	dw offset BLOCK_A
			dw offset BLOCK_B
			dw offset BLOCK_C
			dw offset BLOCK_D
			dw offset BLOCK_E
			dw offset BLOCK_F
			dw offset BLOCK_G
	BLOCK_MAX_ROW		dw 2,4,2,2,2,3,3
	BLOCK_MAX_COLUMN	dw 2,1,3,3,3,2,2
	BLOCK_ROW			dw 4
	BLOCK_COLUMN		dw 4
	BLOCK_COLOR			dw 4031H
	
	;���ҡ��¡��ո񡢻س���ɨ����
	LEFT	db 4BH
	RIGHT	db 4DH
	DOWN 	db 50H
	SPACE 	db 39H
	STOP 	db 1CH
	
	BACK_GROUND_COLOR	dw 7030H
	NotArrivalBottom	dw 1		;����Ƿ񵽴�ײ�������Ϊ�٣�û���ײ�Ϊ��
	ARRIVAL_COLOR		dw 2031H
data ends
code segment
start:			
	mov bx,stack
	mov ss,bx
	mov sp,128
		
	call copy_tetris		;������θ�ֵ���ڴ�0:7E00H��ʼ�ĵ�ַ
	call save_old_int9h		;����BIOS��int 9�ĵ�ַ��0:200H~0:203H��ȥ
	call set_new_int9h		;����int 9���µ��ж�������
	
	mov bx,0
	push bx
	mov bx,7E00H
	push bx
	retf
	
	mov ax,4C00H
	int 21H
;===============================================
Tetris:
	mov ax,1000H
	call init_reg		;�Ĵ�����ʼ��
	call clear_screen	;����
	call init_screen	;��Ļ��ʼ��(���߿�)
	
	NewBlock:
	cli
	call init_block_type	;��ȡ��״
	call init_block_loction	;��ȡ��ַ
	call print_block		;��ʾ
	sti
	dieloop:
	jmp dieloop
	
	mov ax,4C00H
	int 21H
;===============================================
init_screen:
	mov bx,START_ROW
	mov si,offset ROW_MESSAGE		;��ȡҪ�������Ϣ��ַ
	mov cx,ROW_NUMBER		;��ȡ����
	loop_row:
		push cx
		push bx
		mov cx,COLUMN_NUMBER
		loop_column:
			mov dx,BORDER_COLOR
			mov dl,ds:[si]
			cmp dl,'1'
			jne next_column		;������1�򲻻��߿�
			or dh,00010001B
			next_column:
			mov es:[bx],dx
			inc si
			add bx,2
		loop loop_column
		pop bx
		pop cx
		add bx,NEXT_ROW
	loop loop_row
ret
;===============================================
print_block:
	push si
	push bx

	mov cx,BLOCK_ROW
	mov dx,BLOCK_COLOR
	
	PrintBlockOne:
		push cx
		push bx
		push si
		mov cx,BLOCK_COLUMN
		PrintBlockTwo:
			cmp byte ptr ds:[si],'1'	;�������򲻻�����������1�򻭳���
			jne PrintBlockOneOver
			mov es:[bx],dx
			PrintBlockOneOver:
			add bx,2
			inc si
		loop PrintBlockTwo
	
		pop si
		pop bx
		pop cx
		add bx,NEXT_ROW
		add si,4
	loop PrintBlockOne
	
	pop bx
	pop si
ret
;===============================================
init_block_loction:
	mov bx,START_ROW
	add bx,START_BLOCK_ROW
ret
;===============================================
init_block_type:
	mov NotArrivalBottom,1
	mov bx,0
	mov si,ds:BLOCK[bx]
	
	push ds:BLOCK_MAX_ROW[bx]
	pop BLOCK_ROW
	push ds:BLOCK_MAX_COLUMN[bx]
	pop BLOCK_COLUMN	
ret
;===============================================
init_reg:			
	mov bx,0B800H
	mov es,bx
	mov bx,data
	mov ds,bx
ret
;===============================================
clear_screen:
	mov bx,0
	mov cx,2000
	mov dx,0700H	;����
	ClearScreen:
		mov es:[bx],dx	
		add bx,2
	loop ClearScreen
ret
;===============================================
save_old_int9h:	
	mov bx,0
	mov es,bx
	push es:[9*4]
	pop es:[200H]
	push es:[9*4+2]
	pop es:[202H]
ret
;===============================================
set_new_int9h:
	mov bx,0
	mov es,bx
	cli
	mov word ptr es:[9*4],offset new_int9h - offset Tetris + 7E00H
	mov word ptr es:[9*4+2],0
	sti
ret
;===============================================
new_int9h:
	push ax
	
	call clear_keyboard_buffer
	in al,60H
	pushf
	call dword ptr cs:[200H]
	
	cmp al,LEFT
	je isLeftKey
	cmp al,RIGHT
	je isRightKey
	cmp al,DOWN
	je isDownKey
	cmp al,SPACE		;���ո�ı���״
	je isSpaceKey
new_int9h_ret:
	pop ax
iret
;===============================================
isLeftKey:
	mov di,160*3+10*2
	mov byte ptr es:[di],'L'
	call MoveLeft
jmp new_int9h_ret

isRightKey:
	mov di,160*3+10*2
	mov byte ptr es:[di],'R'
	call MoveRight
jmp new_int9h_ret

isDownKey:
	mov di,160*3+10*2
	mov byte ptr es:[di],'D'
	call MoveDown
	cmp NotArrivalBottom,0
	je produce_next_block
jmp new_int9h_ret
produce_next_block:
	pop ax
	add sp,4	;ģ��iret���������ǲ��������
	popf
jmp NewBlock
isSpaceKey:
	mov di,160*3+10*2
	mov byte ptr es:[di],'S'
	;call ChangeType
jmp new_int9h_ret
;===============================================
MoveLeft:
	push bx
	
	mov cx,BLOCK_ROW
	MoveLeft_LoopOne:
		push cx
		push bx
		mov cx,BLOCK_COLUMN
		;ֻҪһ�з��ֵ�һ��1�ͽ�����һ�е��жϣ�����ֱ��һ���ж������ж���һ��
		MoveLeft_LoopTwo:		
			cmp byte ptr es:[bx],'1'
			jne MoveLeft_NextColumn		;û�з��ֵ�һ��1��������һ��
			cmp byte ptr es:[bx-2],'0'
			jne MoveLeft_NoMove			;���Ϊ�߿򣬲��ƶ�ֱ�ӽ���
			jmp MoveLeft_NextRow		;���ֵ�һ��1��������߲�Ϊ�߿򣬽�����һ��
		MoveLeft_NextColumn:
			add bx,2
		loop MoveLeft_LoopTwo
	MoveLeft_NextRow:		
		pop bx
		pop cx
		add bx,NEXT_ROW
	loop MoveLeft_LoopOne

	pop bx					;��ȡ��һ����bx
	call clear_old_block	;�����һ���ķ���
	sub bx,2				;��һ��������
	call print_block		;����
	ret	
MoveLeft_NoMove:
	add sp,4
	pop bx
ret
;===============================================
MoveRight:
	push bx
	add bx,BLOCK_COLUMN
	add bx,BLOCK_COLUMN		;ͼ�ε����һ���ռ�(4*4��)
	sub bx,2				;���һ���ռ���׵�ַ
	
	mov cx,BLOCK_ROW
	MoveRight_LoopOne:
		push cx
		push bx
		mov cx,BLOCK_COLUMN
		;ֻҪһ�з��ֵ�һ��1�ͽ�����һ�е��жϣ�����ֱ��һ���ж������ж���һ��
		MoveRight_LoopTwo:		
			cmp byte ptr es:[bx],'1'
			jne MoveRight_LastColumn		;û�з��ֵ�һ��1��������һ��
			cmp byte ptr es:[bx+2],'0'
			jne MoveRight_NoMove			;���Ϊ�߿򣬲��ƶ�ֱ�ӽ���
			jmp MoveRight_NextRow		;���ֵ�һ��1��������߲�Ϊ�߿򣬽�����һ��
		MoveRight_LastColumn:
			sub bx,2					
		loop MoveRight_LoopTwo
	MoveRight_NextRow:		
		pop bx
		pop cx
		add bx,NEXT_ROW
	loop MoveRight_LoopOne

	pop bx
	call clear_old_block
	add bx,2					;��һ��������
	call print_block
	ret	
MoveRight_NoMove:
	add sp,4
	pop bx
ret
;===============================================
MoveDown:
	push bx
	
	mov cx,BLOCK_ROW
	MoveDown_LoopOne:
		push cx
		push bx
		mov cx,BLOCK_COLUMN
		
		MoveDown_LoopTwo:		
			cmp byte ptr es:[bx],'1'
			jne MoveDown_NextColumn		
			cmp byte ptr es:[bx+160],'1'
			je MoveDown_NextColumn
			cmp byte ptr es:[bx+160],'0'
			jne MoveDown_NoMove	
		MoveDown_NextColumn:
			add bx,2
		loop MoveDown_LoopTwo	
		pop bx
		pop cx
		add bx,NEXT_ROW
	loop MoveDown_LoopOne
	
	pop bx					;��ȡ��һ����bx
	call clear_old_block	;�����һ���ķ���
	add bx,NEXT_ROW			;��һ��������
	call print_block		;����
	ret	
MoveDown_NoMove:
	add sp,4
	pop bx
	mov NotArrivalBottom,0
	call ArrivalChangeColor
ret
;===============================================
ArrivalChangeColor:
	push bx
	
	mov cx,BLOCK_ROW
	mov dx,ARRIVAL_COLOR
	LoopArrivalChangeColor_One:
		push cx
		push bx
		mov cx,BLOCK_COLUMN
		LoopArrivalChangeColor_Two:
			cmp byte ptr es:[bx],'1'
			jne ToNextBlock
			mov es:[bx],dx
			ToNextBlock:
			add bx,2
		loop LoopArrivalChangeColor_Two
		pop bx
		pop cx
		add bx,NEXT_ROW
	pop bx
ret
;===============================================
clear_old_block:
	push bx

	mov cx,BLOCK_ROW
	mov dx,BACK_GROUND_COLOR
	ClearBolckRow:	
		push cx
		push bx
		mov cx,BLOCK_COLUMN
		ClearBlockColumn:		
			cmp byte ptr es:[bx],'1'		;����1��Ϊ0����������򲻱���Ϊ0�����
			jne ClearNextColumn
			mov es:[bx],dx
			ClearNextColumn:
			add bx,2
		loop ClearBlockColumn
		pop bx
		pop cx
		add bx,NEXT_ROW
	loop ClearBolckRow
	pop bx
ret
;===============================================
clear_keyboard_buffer:			;������̻�����
	mov ah,1
	int 16H			
	jz ClearKeyboardBufferOver	;�����������ȡ������Ϊ0�����
	mov ah,0					;����������������ķ�ʽ���һ�λ������ֽ�
	int 16H
	jmp clear_keyboard_buffer
	ClearKeyboardBufferOver:
ret
;===============================================
Tetris_end:nop
;===============================================
copy_tetris:	
	mov bx,cs
	mov ds,bx
	mov si,offset Tetris

	mov bx,0
	mov es,bx
	mov di,07E00H

	mov cx,offset Tetris_end - offset Tetris
	cld 
	rep movsb
ret
code ends
end start