# include <stdio.h>
int main (void)
{
	char ch;
	scanf("%c",&ch);
	printf("%c,%d,%o,%x,%#x\n",ch,ch,ch,ch,ch);
	return 0;
}
/*
������Ϊ��
	5
	5,53,63,35,0x35
��
	f
	f,102,146,66,0x66
*/
