# include <stdio.h>
# define PRINT "�����Ϊ%d�����Ӵ�%c�����Ƶ�%c����\n", n, A, C

void Hanoi(int n, char A, char B, char C);

int main (void)
{
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';
	int n;
	int time = 1;
	int i;

	printf("������Ҫ�ƶ������ӵĸ�����");	
	scanf("%d",&n);

	Hanoi(n, 'A', 'B', 'C');

	for(i=1; i<=n; i++)
		time *= 2;

	printf("ִ�д���Ϊ%d\n",time-1);

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

/*
	�����һ������
		ֱ�ӽ�A�����ϵ����Ӵ�A�Ƶ�C
	����
		��1���Ƚ�A�����ϵ�n-1�����ӽ���C�Ƶ�B
		��2��ֱ�ӽ�A�����ϵ����Ӵ�A�Ƶ�C
		��3�����B�����ϵ�n-1�����ӽ���A�Ƶ�C
*/