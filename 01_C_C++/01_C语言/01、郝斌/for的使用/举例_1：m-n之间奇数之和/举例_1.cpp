/*
	2016��2��2��12:45:39
	���m��ʼ��n������֮��(m,n�ɸ�ֵ)
*/
# include <stdio.h>
int main (void)
{
	int i,n,m;
	int sum = 0;
	printf("please input m&n(m<n)(m=_,n=_):\n");
	scanf("m=%d,n=%d",&m,&n);

	for(i=m; i<=n; i +=2)
		sum += i;

	printf("%d��%d֮����������֮��Ϊ��sum=%d\n",m,n,sum);

	return 0;
}