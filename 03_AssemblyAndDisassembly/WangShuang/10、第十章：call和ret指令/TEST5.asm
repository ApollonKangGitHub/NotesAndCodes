;��data���е���ĸת���ɴ�д
assume cs:codeseg

data segment
	db 'conversation'
data ends
codeseg segment
	start:
	mov ax,data
	mov ds,ax
	
	mov si,0
	mov cx,12
	
	call change
	
	mov ax,4C00H
	int 21H
;***************************Сд��ĸת���ɴ�д��ĸ****************************
	change:
			and byte ptr ds:[si],11011111B
			inc si
		loop change
	ret
;====================================================================end change
codeseg ends
end start