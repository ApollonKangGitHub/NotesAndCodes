;int 10H用ah传递子程序编号，指定要调用的功能
;2017年5月7日17:39:27
;本例程功能：在屏幕的第五行第十二列开始显示3个'a'，其属性为红底绿字高亮闪烁
;我们可以看到光标的变化
assume cs:code

code segment
	start:
	mov ah,2			;ah指定int10H的子程序编号:2表示置光标位置为指定的位置
	mov bh,0			;bh指定页面:第0页
	mov dh,5			;dh指定行数:第5行
	mov dl,0			;dl指定列数:第0列
	int 10H				;根据参数调用BIOS的int 10H中断例程的子程序	
	
	mov ah,9			;ah指定int10H的子程序编号:9表示显示字符子程序
	mov al,'a'			;al指定字符:'a'
	mov bl,11001010B	;bl指定属性:红底绿字高亮闪烁
	mov bh,0			;bh指定页面:第0页
	mov cx,80			;cx指定个数:80个
	int 10H
	
	TestA:
		mov ax,0
	jmp TestA
	mov ax,4C00H
	int 21H
code ends
end start