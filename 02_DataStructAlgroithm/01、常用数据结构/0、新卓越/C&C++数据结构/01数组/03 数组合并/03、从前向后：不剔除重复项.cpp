/*
	2016��5��28��23:03:21
*/
# include <stdio.h>

int MergeProgram (int * a,int * b,int len_a,int len_b);

int main(void)
{
	int point;
	int data1[23] = {5,12,46,47,58,64,72,87,101,115,330};
	int data2[12] = {13,14,46,59,64,101,104,115,136,158,200,210}; 

	point = MergeProgram (data1,data2,11,12);//�����޳����ظ���ϲ����������Ԫ���±�Ϊ����ֵk

	printf("���޳��ظ���ϲ���data1[]Ϊ��\n");
	for(int i = 0; i<point; i++)
		printf("%-5d",data1[i]);
	putchar('\n');

	return 0;
}

int MergeProgram (int * a,int * b,int len_a,int len_b)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int point = len_a;

	/*
	while()ѭ���ʼi<len_a-1,��������֮�����һ��point�������ʹa[]�ĳ��ȷ����仯����û�иı��ж�������ʹ99��101��158�������ݶ�ʧ
	whileѭ��ֻ����Ƚ�a[]��b[]����a[]��b[]ֻʣһ��ʱ�Ͳ���Ҫ�ٱȽ�ֱ���˳�������һ��forѭ��
	*/
	while(i < point && j < len_b)
	{
		if(a[i] < b[j])
			a[k] = a[i];
		else
		{
			for(int m = point; m >= i; m--)
				a[m] = a[m-1];
			a[k] = b[j];
			point ++;
			j ++;
		}

		i ++;
		k ++;
	}

	for(j,k; j<len_b ; j++,k++)
	{
		a[k] = b[j];
		point ++;
	}
	//�ʼд��һ������˳�whileʱ��b[]�����a[]û������������������forѭ���������û�б�Ҫ����ɾ�ˡ�
	return point;
}
