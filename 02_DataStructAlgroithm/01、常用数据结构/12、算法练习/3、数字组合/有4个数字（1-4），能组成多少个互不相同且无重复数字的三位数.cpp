/*
	2016��4��29��21:45:17
	��1��2��3��4�����֣�����ɶ��ٸ�������ͬ�����ظ����ֵ���λ�������Ƕ��٣�
*/
# include <stdio.h>
int main(void) 
{ 

	int i,j,k,num=0; 

	printf("���еĽ����\n"); 

	/*����Ϊ����ѭ��*/ 
	for(i=1;i<6;i++)
	{
		for(j=1;j<6;j++)
		{
			for (k=1;k<6;k++) 
			{ 
				if (i!=k&&i!=j&&j!=k) 	/*ȷ��i��j��k��λ������ͬ*/ 
				{
					printf("%-5d",100*i+10*j+k); 
					num++;
				}
			} 
		}
		putchar('\n');
	}
	putchar('\n');
	printf("num=%d\n",num);
	return 0;
} 

