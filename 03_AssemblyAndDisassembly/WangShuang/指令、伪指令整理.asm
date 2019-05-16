;指令:

;数据传送指令:
mov X1,X2	;移动X2到X1(条件:①X1X2至少有一个是寄存器②类型要相同②类型大小要一致③X1不能为立即数)
push X		;将X入栈(注：s先加2再入栈)
pop X		;出栈到X中(注：先出sp再减2)
pushf		;将标志位寄存器入栈(注：同push)
popf		;将栈顶值出栈到标志位寄存器(注：同pop)
xchg X1,X2	;交换X1与X2的值(条件:①X1X2至少有一个是寄存器②类型大小要一致③X1X2均不为立即数④寄存器不能为段寄存器)

;算数运算指令:这些指令实现寄存器和内存中数据的算术运算。他们执行结果会影响标志寄存器的sf、zf、of、cf、pf、af
add X1,X2	;加法
sub X1,X2	;减法
adc X1,X2	;带进位加法((X1)=(X1)+(X2)+CF)
sbb	X1,X2	;带借位减法((X1)=(X1)-(X2)-CF)
inc	X		;自加
dec	X		;自键
cmp	X1,X2	;相减，不保存最终结果，但是中间结果会影响标志位寄存器的相关标志位
mul X1,X2	;无符号数乘法(被乘数->结果:al->ax,ax->dxax)
div X1,X2	;无符号数除法(被除数->商...余数:ax->al...ah,dxax->ax...dx)
imul X1,X2	;有符号数乘法
idiv X1,X2	;有符号数除法
aaa	 		;将AL调整为一个非压缩BCD格式的数字。AL是两个非压缩BCD数字相加后的结果。
			;如果AL(3-0)大于9或辅助进位AF=1，则AH=AH+01H，AL=AL+06H，且置AF和CF为1；否则置AF和CF为零。AL(7-4)=0。
;逻辑指令（从数字电路的角度来看，计算机只会作位运算；从集成电路的角度来看计算机可以做加减乘除法）:
and X1,X2	;按位与
or	X1,X2	;按位或
not	X		;按位非
xor X1,X2	;异或运算
test X1,X2	;测试某一位是否为0，与and相同，但是不保存与的结果只影响标志位寄存器，如果测试的位均为0则CF为1(测试哪一位在X2中将该位值为1即可)
shl	X1,X2	;逻辑左移(补0)
shr	X1,X2	;逻辑右移(补0)
sal	X1,X2	;算数左移(补0)
sar	X1,X2	;算数右移(补符号位)
;即对于正数，逻辑移位与算数移位是一样的；对于负数逻辑移位补0，算数移位补1
;汇编中用sar和shr区别是算数右移还是逻辑右移，C语言中右移都是>>，unsigned类型右移是逻辑右移，signed类型右移是算术右移
rol	X1,X2	;循环左移(左边高位移出的循环补到右边低位)
ror	X1,X2	;循环右移(右边低位移出的循环补到左边高位)
rcl	X1,X2	;带Carry Flag的循环左移(CF被认为是寄存器最高位)
rcr	X1,X2	;带Carry Flag的循环右移(同上)
			
;转移指令:
jmp ;无条件转移指令(jmp reg、jmp 标号、jmp short 标号、jmp near ptr 标号、jmp far ptr 标号、jmp word ptr 标号、jmp dword ptr 标号)
jcxz\je\jb\ja\jne\jnb\jna 标号,等	;条件转移指令(条件为:CX等于0、等于0、小于0、大于0、不等于0、不小于0、不大于0等)
loop 标号	;循环指令(CX不等于0)
call、ret、retf				;过程(call 标号、call 16位reg、call far ptr 标号、call word ptr 标号、call dword ptr 标??
int、iret					;中断

;处理机控制指令：
cld		;df置为0(si、di自加)
std		;df置为1(si、di自减)
cli		;if置为0(不响应)
sti		;if置为1(响应)
nop		;只占一个字节
clc		;CF=0
stc		;CF=1
cmc		;CF=!CF,进位标志位求反指令
hlt		;CPU暂停指令，当复位(RESET)线上有复位信号或CPU相应中断时，CPU脱离暂停状态，执行HLT的下一条指令。
wait	;当芯片引线TEST为高电平时使CPU进入等待状态
esc		;打印机控制指令
lock	;LOCK前缀的作用是保持当前CPU对系统总线的控制，直到整条指令执行完毕(保证原子操作)

;串处理指令:
movsb		;从ds:[si]复制一个字节到es:[di]
movsw		;从ds:[si]复制一个字到es:[di]
movsd		;从ds:[si]复制两个字到es:[di]
movs		;串传送指令
cmps		;串比较指令
scas		;串搜索
lods		;从串中取
stos		;存入串中
;与上面的指令配合使用实现批量处理
rep			;作为前缀循环后缀指令
repe		
repne
repz


;伪指令:
db
dw
dd
ptr
offset
seg
end
ends
seg
segment
assume
short

