;int 10H��ah�����ӳ����ţ�ָ��Ҫ���õĹ���
;2017��5��7��17:39:27
;�����̹��ܣ�����Ļ�ĵ����е�ʮ���п�ʼ��ʾ3��'a'��������Ϊ������ָ�����˸
;���ǿ��Կ������ı仯
assume cs:code

code segment
	start:
	mov ah,2			;ahָ��int10H���ӳ�����:2��ʾ�ù��λ��Ϊָ����λ��
	mov bh,0			;bhָ��ҳ��:��0ҳ
	mov dh,5			;dhָ������:��5��
	mov dl,0			;dlָ������:��0��
	int 10H				;���ݲ�������BIOS��int 10H�ж����̵��ӳ���	
	
	mov ah,9			;ahָ��int10H���ӳ�����:9��ʾ��ʾ�ַ��ӳ���
	mov al,'a'			;alָ���ַ�:'a'
	mov bl,11001010B	;blָ������:������ָ�����˸
	mov bh,0			;bhָ��ҳ��:��0ҳ
	mov cx,80			;cxָ������:80��
	int 10H
	
	TestA:
		mov ax,0
	jmp TestA
	mov ax,4C00H
	int 21H
code ends
end start