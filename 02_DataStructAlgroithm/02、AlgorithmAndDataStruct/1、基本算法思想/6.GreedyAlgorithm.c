/*
 *̰���㷨�������������Ž⣬����ʱЧ�����Ž�
 *2017��4��26��17:15:58
*/
#include<stdio.h>
#define MAXN 12

//��λ�Ƿ�,����ĳ����ֵȥ��(�޸ĵ�Ҳ���Բ���)
//eg:��200(��2Ԫ)�޸�Ϊ20000(200Ԫ),���൱�������ֵû����
//ע�⣺����ֵӦ��С��100
int parvalue[MAXN] = {5000,2000,1000,500,200,100,50,20,10,5,2,1};	
int num[MAXN] = {0};

void exchange(int n)
{
	int i = 0;
	while(n>0 && i<MAXN){	//n���������������Ǯ
		if(n>=parvalue[i]){	//
			n -= parvalue[i];
			num[i]++;
		}
		else{
			i++;	//������㵱ǰ��ֵ��ϼ�����һ��С����ֵ
		}
	}
}
int main(void)
{
	//��78.45����float_%f��double_%lf�����������
	double money;
	int i;
	printf("������Ҫ����Ǯ�����:\n");
	scanf("%lf",&money);
	exchange((int)(money*100));	//��ԪΪ��λת�����Է�Ϊ��λ
	printf("���㷽����%.2lf:\n",money);
	for(i=0; i<MAXN; i++)
		if(num[i]>0)
			printf("%6.2lf:%d��\n", (float)(parvalue[i]/100.0),num[i]);
	printf("%X\n",money);
	return 0;
}
