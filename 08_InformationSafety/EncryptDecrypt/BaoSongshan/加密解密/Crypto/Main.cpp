#include"Sha.h"
#include"Md5.h"
#include"Des.h"
#include"Rc4.h"
#include"Rsa.h"

void main()
{
	int select = 1;
	while(select)
	{
		printf("**************************\n");
		printf("* [1] SHA       [2] MD5  *\n");
		printf("* [3] DES       [4] RC4  *\n");
		printf("* [5] RSA       [0] Quit *\n");
		printf("**************************\n");
		printf("ÇëÑ¡Ôñ:>");
		scanf("%d",&select);
		switch(select)
		{
		case 1:
			Sha();
			break;
		case 2:
			Md5();
			break;
		case 3:
			Cbc_Des();
			break;
		case 4:
			Rc4();
			break;
		case 5:
			Rsa();
			break;
		default:
			break;
		}
	}
}
