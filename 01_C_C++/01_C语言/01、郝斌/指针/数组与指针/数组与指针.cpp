# include <stdio.h>
int main (void)
{
	int a[5]={1,2,3,4,5};
	int i;

	for(i=0;i<=4;i++)
	{
		printf("%#x  ",(a+i));//a+i ��ʾa����i���ԣ�a��ָ��ı�����ռ���ֽ���������a+i���磺a+2����ʾ�ľ��ǵ�i+1���磺2+1=3����Ԫ�ص��׵�ַ
		printf("%#x  ",(i+a));

		printf("%p  ",a+i);//%#x��ʾ��0x��ʽʮ�����������%p(��ʮ��λʮ������)��ʾ�����a+1���ĵ�ַ����ַ����ʮ��������ʽ��
		printf("%p  ",&a[i]);
		printf("%p  ",*(a+i));

		printf("%d  ",*(a+i));
		printf("%d  ",*(i+a));
		printf("%d",a[i]);

		printf("\n");
	}
	printf("\n");

	return 0;
}