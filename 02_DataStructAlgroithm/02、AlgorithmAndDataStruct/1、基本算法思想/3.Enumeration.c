/*
 *枚举法本质：从所有的候选答案中去搜索正确的解
 *必须满足条件：
 *①可以预先确定候选答案的数量
 *②候选答案的范围在求解之前必须有一个确定的集合
 *我们根据下面的两个例子可以发现：凡是枚举法都具有深层次的嵌套
*/

/*
 *实例1：
 *			ABCDE
 *			*	A
 *		-----------
 *		   EEEEEE
 *	ABCDE可取范围均为0~9，求出所有可能满足以上乘法的结果
*/
#if 0
void find_num(void)
{
	int a, b, c, d, e, num=0, res=0;
		for(a=1; a<10; a++){
			for(b=0; b<10; b++){
				for(c=0; c<10; c++){
					for(d=0; d<10; d++){
						for(e=0; e<10; e++){
							num = a*10000 + b*1000 + c*100 + d*10 +e;
							res = 111111 * e;
							if(num * a == res){
								printf("%d%d%d%d%d\n",a,b,c,d,e);
								printf("x   %d\n",a);
								printf("------------\n");
								printf("=%d%d%d%d%d%d\n",e,e,e,e,e,e);
							}
						}
					}
				}
			}
		}
}
#endif
/*优化*/
void find_num(void)
{
	int num, res, a, e;
	for(e=1; e<10; e++){
		num = e*111111;
		for(a=1; a<10; a++){
			res = num / a;
			if(res%10 == e && res/10000 == a){
				printf("%d\n",res);
				printf("x   %d\n",a);
				printf("------------\n");
				printf("=%d\n",num);
			}
		}
	}
}
/*
 *实例2：
 *A○B○C○D○E = F
 *当ABCDEF均为整数时
 *如何填入运算符使得等式成立(运算符可以为“+”“-”“*”“/”四种)
 *注意：在填入除号时，除号运算符右侧的数不能为0
 *这里采用的是从左到右的人为控制运算，所以要确保在加减以前，右侧的乘法除法已经运算完毕
*/

void find_operator(void)
{
	int j, i[4];//用四个整数来代表第几个(1\2\3\4)运算符
	int sign;//保存符号
	int result;//保存运算式的结果
	int count=0;//计数器，保存符合要求结果的个数
	int num[5];//保存5个操作数
	float left,right;//保存中间计算结果
	char oper[4] = {'+','-','*','/'};
	
	printf("请输入5参与运算的数: ");
	for(j=0; j<5; j++){
		scanf("%d",&num[j]);
	}
	printf("请输入运算结果: ");
	scanf("%d",&result);

	for(i[0]=0; i[0]<4; i[0]++){
		//操作符为/""与右操作数为0不同时满足(oper[3]为"/")，
		//如果同时满足则此种情况不符合，不再判断下一个操作符，而是直接回到上层循环测试下一种情况
		if(i[0]!=3 || num[1]!=0){
			for(i[1]=0; i[1]<4; i[1]++){
				if(i[1]!=3 || num[2]!=0){
					for(i[2]=0; i[2]<4; i[2]++){
						if(i[2]!=3 || num[3]!=0){
							for(i[3]=0; i[3]<4; i[3]++){
								if(i[3]!=3 || num[4]!=0){//四层循环与四个条件判断确定4个操作符
									left = 0;//左值初始为0
									right = num[0];//右值初始为第一个数
									sign = 1;//用来标记加法的右值是正数还是负数(加法减法合并)
									for(j=0; j<4; j++){
										//oper[i[j]]从循环从开始一次判断四个操作符的类型，最终根据结果判断是否合乎要求
										//oper[i[j]]中j是确定位置的，而i[j]是确定具体位置的符号，该符号在上面的四层for与if的嵌套中已经确定了
										switch(oper[i[j]]){
											case '+':
												left += sign * right;//先计算新的左值
												sign = 1;//是加法，则右值仍然是正数，sign标记其为+
												right = num[j+1];//赋给新的右值
												break;
											case '-':
												left += sign * right;//先计算新的左值
												sign = -1;//是减法，则右值为负，sign标记其为-
												right = num[j+1];//赋给新的右值
												break;
											case '*':
												right = right * num[j+1];//优先级最高，直接乘
												break;
											case '/':
												right = right / num[j+1];//直接除
												break;
										}
									}
									if(left+sign*right == result){//格式化输出
										count++;
										printf("%3d:",count);
										for(j=0; j<4; j++)
											printf("%d%c",num[j],oper[i[j]]);
										printf("%d=%d\n",num[4],result);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if(count==0)
		printf("没有符合要求的填写方式!\n");
}
int main(void)
{
	find_num();
	find_operator();
	return 0;
}