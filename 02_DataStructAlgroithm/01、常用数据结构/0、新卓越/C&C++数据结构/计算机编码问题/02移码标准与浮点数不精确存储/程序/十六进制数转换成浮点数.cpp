/*

	16������ת���ɸ�����
	2016��5��23��18:04:50

*/
# include <stdio.h>
union FloatData
{
    float f;
    unsigned char h[4];
}; 
int main(void)
{
    FloatData t;
    unsigned char th[4];

    printf("������һ������ʮ�����ƣ�32λ������");
    scanf("%X%X%X%X",&th[0],&th[1],&th[2],&th[3]);

	t.h[0] = th[0];
	t.h[1] = th[1];
	t.h[2] = th[2];
	t.h[3] = th[3];

	printf("%X %X %X %X���ڴ��еĴ��Ϊ��%f\n",t.h[0],t.h[1],t.h[2],t.h[3],t.f);

	return 0;

}
