# include <stdio.h>
# include <math.h>

int main (void)
{

	/*�����Ʋ�����ʽʶ��*/
	int ti = 858993459;

	printf(" ti = %d\n",ti);
	printf(" ti = %#X\n",ti);
	printf("-ti = %#X\n",-ti);

	int p=0;
	/*ti=0X3333 3333(H)=858993459(D); -ti=0XCCCC CCCD*/
	p = (int)(((int)p)+pow(2,29)+pow(2,28)+pow(2,25)+pow(2,24)+pow(2,21)+pow(2,20)+pow(2,17)+pow(2,16) );
	p = (int)(((int)p)+pow(2,13)+pow(2,12)+pow(2,9)+pow(2,8)+pow(2,5)+pow(2,4)+pow(2,1)+pow(2,0));
	/*pow(x,y)Ϊ��x��y�η���math.h�⺯����x��y����double�ͣ���������ʹ��ʱӦ��ǿ������ת��*/

	printf(" ti = %d\n",p);

	return 0;
}
