# include <stdio.h>

int main (void)

{
	int a, b, c, t;

	printf("please input three numbers (a,b,c):");
	scanf("%d,%d,%d",&a, &b, &c);

	if (a < b)
	{
		t = a;
		a = b;
		b = t;
	}   
	//���С�ھͻ����������С�ھ�����ı�

	if (a < c)
	{
		t = a;
		a = c;
		c = t;
	}

	if (b < c)               //���a<c,��ô��ʱ��c���Ѿ�����������ʱ��a��
	{
		t = b;
		b = c;
		c = t;
	}

	printf("%d,%d,%d\n",a, b, c);


	return 0;
}