#include <stdio.h>
#include <stdlib.h>

bool IsPrime(int m)
{
	int i;
	for(i=2;i<m;i++)
	{
		if(0 == m%i)
			break;
	}
	if (i == m)
		return true;
	else
		return false;

}

int main(void)
{
	int val;
	int i;
	char ch;

	do
	{
		system("cls");
		system("color 5A");

		loop:printf("������Ҫ�жϵ�����:\n");//����loop���������ͨ�������޲��죬���goto loopִ��������loop���������ʼִ�У����goto loop��ִ�У���loop����ſ��Ժ���
		scanf("%d", &val);
		system("cls");

		if(val<2)
		{
			printf("����������������루����1�����֣���\n");
			goto loop;//loopΪ����ţ���������Ϊ������š���goto�����Կ纯��ʹ�á�����ſ����ڹ涨������涨����������������Ϊ����ţ�
			//goto����ڸ߼������л����Ѿ�ȡ����C�����о��ܱ������Ǿ�����Ҫʹ��
		}

		else
		{
			printf("1-%d֮�����������Ϊ��\n",val);

			for(i=1; i<=val; ++i)
			{
				if( IsPrime(i) )
					printf("%d\t",i);
			}

			printf("\n");

			printf("�Ƿ�Ҫ������������Y����������N.\n");
		}
		scanf(" %c", &ch); //%cǰ�����ü�һ���ո�
	}while(ch=='y'||ch=='Y');

	return 0;
}
