/*

	16进制数转换成浮点数
	2016年5月23日18:04:50

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

    printf("请输入一个数（十六进制（32位））：");
    scanf("%X%X%X%X",&th[0],&th[1],&th[2],&th[3]);

	t.h[0] = th[0];
	t.h[1] = th[1];
	t.h[2] = th[2];
	t.h[3] = th[3];

	printf("%X %X %X %X在内存中的存放为：%f\n",t.h[0],t.h[1],t.h[2],t.h[3],t.f);

	return 0;

}
