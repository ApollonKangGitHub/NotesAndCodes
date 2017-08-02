#include <stdio.h>

int main (void)
{
	int delta;
	printf("please input delta:\n");
	scanf("%d",&delta);

	if (delta > 0)
		printf("有两个解\n");
	//printf("哈哈！\n");
	else if(delta == 0)
		printf("有一个解\n");
	else
		printf("无解!\n");
	return 0;
}
/*
	如果有
	printf("哈哈！\n");
	语句，程序编译会出错
	因为第一个else没有匹配的if
	只需将第一个else删除即可消除编译错误，但是程序运行结果是不对的

	所以，最好的改法是将
	printf("有两个解\n");
	printf("哈哈！\n");
	两句用{}括起来
*/