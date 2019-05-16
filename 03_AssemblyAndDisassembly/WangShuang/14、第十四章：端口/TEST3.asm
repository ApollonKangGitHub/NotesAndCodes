;2017��5��8��16:46:51
;Author:Kangruojin
;Mail:mailbox_krj@163.com
;Version:v1.1
;����Ļ�м���ʾ������ʱ��
;��ʽ��"��/��/��  ʱ:��:��"
;CMOS RAM�洢���ݣ�
;				0	2	4	7	8	9	
;				��	��	ʱ	��	��	��
assume cs:code

code segment
start:
	mov dh,12	;��
	mov dl,30*2	;��
	
	call Init_Show
	call Clear_Screen
	Dieloop:
		mov si,0
		mov al,9	;9(Year)8(Month)7(Day)
		show_Date:
			call Get_CMOSRAM_Message	;��ȡ����/ʱ����Ϣ�����ַ�������cx���ݻ���(chΪʮλ��clΪ��λ)
			call Show_Message			;��ʾ
			add si,6					
			cmp al,7					
			je next
			dec al
		jmp short show_Date
		
		next:
			mov byte ptr es:[bx+si-2],' '	;����day֮����Ҫ���'/'���Թ�����si=si+6��������day����Ҫ�˻�2�ֽ�
			mov byte ptr es:[bx+si],' '		;18~21��ʾ"  "�ָ�������ʱ��
			add si,2	;��Ӧ������˻�2�ֽڣ�����ֻ���2����
			
		mov al,4	;4(Hour)2(Mintue)0(Second)
		show_Time:
			call Get_CMOSRAM_Message
			call Show_Message
			add si,6
			cmp al,0
			je again
			sub al,2
		jmp short show_Time
	again:
	jmp short Dieloop
over:
mov ax,4C00H
int 21H
;=============================����=================================
Clear_Screen:
	push bx
	push cx
	
	mov bx,0
	mov cx,80*25
	clear:
		mov es:[bx],0700H
		add bx,2
	loop clear
	
	pop cx
	pop bx
ret
;=======================es�Ĵ�������Կ��׵�ַ======================
Init_Show:
	mov ax,0B800H
	mov es,ax
	mov al,160
	mul dh
	mov dh,0
	mov bx,dx
	add bx,ax
ret
;=====================��ȡʱ��/������Ϣ========================
Get_CMOSRAM_Message:
	push ax
	
	mov cl,4
	out 70H,al
	in al,71H
	mov ah,al	;����һ�����ݵ�ah��
	shr ah,cl	;��ah�еĸ�λBCD�������
	and al,0FH	;��al�е�ʮλBCD�������
	add ah,30H	;������ת����ַ�
	add al,30H
	
	;cx����
	mov ch,ah	;�������������õ���al��������ch��cl�����ݻ�ȡ���ķ���ֵ
	mov cl,al

	pop ax
ret
;=====================����ȡ������ŵ�cx�е���Ϣ��ʾ����Ļ��========================
Show_Message:
	mov byte ptr es:[bx+si],ch
	mov byte ptr es:[bx+si+2],cl
	cmp si,13	
	;CMP si,n	�Ƚϵ�ֵ��ѡ�ĺֻܶ࣬Ҫn����12���ɣ������������jb...jnb����ת����ʽ��˵��
	;16~19��ʾ"  "�ָ�������ʱ��
	jb	Show_Date_Message	
	jnb	Show_Time_Message	
	Show_Date_Message:
		cmp al,7	
		je ShowOver	;�պ���Ҫ��'/'
		mov byte ptr es:[bx+si+4],'/'
		jmp short ShowOver
	Show_Time_Message:
		cmp al,0
		je ShowOver	;�����Ҫ��':'
		mov byte ptr es:[bx+si+4],':'
ShowOver:
ret
;=============================================
code ends
end start