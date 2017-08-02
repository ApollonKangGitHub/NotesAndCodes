/*
 *2017年4月21日18:46:21
 *Divide and Rule:分治(分而治之)
 *基本步骤：
 *①分解：将要求解的问题他划分成若干规模较小的同类问题
 *②求解：将子问题划分的足够小时，用简单的方法解决
 *③合并：按求解问题的要求，将子问题的解逐层合并，即可构成最终解
*/
#include<stdio.h>

/*实例：
 *2^n个乒乓球选手，每个人都需要与其他所有人均进行一场比赛（一个人一天只能比赛一场）
 *求需要天数与赛程表
*/
#define MAX 64	//最多人数
int a[MAX+1][MAX+1]={0};

void gamecal(int k, int n)
{
	int i,j;
	if(n == 2){//两个人的直接相互一安排即可
		/*求解*/
		a[k][1] = k;
		a[k][2] = k+1;
		a[k+1][1] = k+1;
		a[k+1][2] = k;
	}
	else{
		/*分解*/
		gamecal(k, n/2);
		gamecal(k+n/2, n/2);
		/*合并*/
		for(i=k; i<k+n/2; i++){
			for(j=n/2+1; j<=n; j++){
				a[i][j] = a[i+n/2][j-n/2];
			}
		}
		for(i=k+n/2; i<k+n; i++){
			for(j=n/2+1; j<=n; j++){
				a[i][j] = a[i-n/2][j-n/2];
			}
		}
	}
}
int main (void)
{
	int m,i,j;
	printf("请输入参数选手人数(人数必须为2的幂次个)：");
	scanf("%d",&m);
	for(j=1,i=2; i<8; i++){
		j *= 2;
		if(j == m) break;
	}
	if(i>=8){
		printf("参赛参数选手人数必须为2的幂次个，且不超过64个！\n");
		return 0;
	}
	gamecal(1,m);
	printf("\n编号 ");
	for(i=2; i<=m; i++)
		printf("%2d天 ", i-1);
	printf("\n");
	for(i=1; i<=m; i++){
		for(j=1; j<=m; j++)
			printf("%4d ",a[i][j]);
		printf("\n");	
	}
	return 0;	
}