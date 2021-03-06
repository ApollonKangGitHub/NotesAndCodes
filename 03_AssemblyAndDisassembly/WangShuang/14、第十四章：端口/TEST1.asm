;读取COMOS RAM的2号单元中的内容
;向CMOS RAM的2号单元中写入0
;in从端口读取数据
;out用于向端口写入数据
;注意：CMOS RAM的0~1D可以写入数据，但是其他单元不要写，因为其中保存着一些系统的配置信息，修改可能会引起系统错误
assume cs:code

code segment
	start:
	;CMOS RAM芯片有一个实时时钟和128自己的RAM存储器，有两个端口(70H与71H)
	;70H存放要操作的单元地址(地址端口)，71H为要操作的数据(数据端口)
	
	mov al,2
	out 70H,al	;设置要操作的地址为CMOS RAM的2号单元
	in al,71H	;从71H中读取CMOS RAM的2号单元一个字节放到al中
	
	mov al,0
	out 71H,al	;向2号单元中写一个数据
	
	in al,71H	;再把0读出来?不对，因为二号单元是存储时钟的分钟信息
				;写入的0会被及时更新的分钟数据覆盖
	;CMOS RAM的128单元，其中内部时钟占用0~dH单元来保存信息:
	;0	1		2	3		4	5		6		7	8	9	A			B			C			D
	;秒 秒报警	分	分报警	时	时报警	星期	日	月	年	状态寄存器A	状态寄存器B	状态寄存器C	状态寄存器D
	;以BCD码(只有0~9的码，与8421码前10个一样)的形式存储,高4位存十位，低四位存个位
	;eg:24 <==> (0010 0100)BCD,一个字节可以表示两个BCD码
	
	mov ax,4C00H
	int 21H
code ends
end start