# include <stdio.h>
# define PRINT "将编号为%d的盘子从%c柱子移到%c柱子\n", n, A, C

void Hanoi(int n, char A, char B, char C);

int main (void)
{
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';
	int n;
	int time = 1;
	int i;



							printf("请输入要移动的盘子的个数：");	

								scanf("%d",&n);



									Hanoi(n, 'A', 'B', 'C');



										for(i=1; i<=n; i++)

												time *= 2;



													printf("执行次数为%d\n",time-1);



														return 0;

														}



														void Hanoi(int n, char A, char B, char C)

														{



															if(1 == n)

																{

																		printf(PRINT);



																			}

																				else

																					{

																							

																									Hanoi(n-1, A, C, B);

																											printf(PRINT);

																													Hanoi(n-1, B, A, C);

																														}



																														}
