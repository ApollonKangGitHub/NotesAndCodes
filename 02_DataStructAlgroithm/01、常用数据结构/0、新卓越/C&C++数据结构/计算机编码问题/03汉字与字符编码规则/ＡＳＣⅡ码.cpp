# include <stdio.h>
int main (void)
{
	int asc = 0;
	int n = 0;
	for(asc; asc < 128; asc++)
	{
		if(asc < 7 || asc > 13)//由于7-14的ＡＳＣⅡ对应得字符不能明确显示，所以跳过即可
		{
			n++;
			if(0 == (n-1)%5) 
				printf("\n");
			printf("字符%c的ASCⅡ值为%d\t",asc,asc);
		}
	}

	printf("%\n");
	return 0;
}