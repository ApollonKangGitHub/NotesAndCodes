;����޸����һ�е�end startΪend���Ķδ���(TEST1.asm/TEST2.asm/TEST3.asm)���������У�
;TEST3���������У�TEST1��TEST2���ܡ�
;��Ϊstartֻ�Ǳ�ʶ��ַ����end start���Ǹ��߱�����start����ڣ�����޸����һ�е�end startΪend
;��ô�������Ͳ������start����Ĭ�ϵ���ڵ�ַд���ִ���ļ�������Ϣ��
;��Ĭ�ϵ���ڵ�ַ����codeseg+dataseg+stackseg���ε�ַ����ǰ��ĵ�ַ(�͵�ַ)
;��������(code)�����Ǳ���ʱ�������ڵ�һ�Σ���ô����end start�����������׶ε�ַ(cs)д���ִ���ļ�������Ϣ��
;�������stack/data���ǵ�һ�Σ���д���ִ���ļ�������Ϣ�ĵ�ַ����(ss)/(ds)�������ݽ�����ָ�����϶����޷��������е�
;����ֻ��TEST3������ȷ���С�

assume cs:code,ds:data,ss:stack
;code���ƶ�����һ��(�ڴ�Ҳ��Ӧ�����仯��)
code segment
	start:
	mov ax,data
	mov ds,ax
	mov ax,stack
	mov ss,ax
	mov sp,16
	
	push ds:[0]
	push ds:[2]
	pop ds:[2]
	pop ds:[0]
	
	mov ax,4C00H
	int 21H
	
code ends

data segment
	dw 0123H,0456H
data ends

stack segment
	dw 0,0
stack ends

end start