/*
 *Author:Kangruojin
 *Time:2017年7月20日15:11:28
 *Mail:mailbox_krj@163.com
 *versionL:v1.1
*/
#include "rc4.h"

int main(int argc, char * argv[])
{	
	unsigned char message[] = "I love you!";
	
	printf("明文：%s\n",message);
	int len = strlen((const char*)message); 
	for(int i = 0; i < len; i++){
		printf("%02x",message[i]);
	}
	printf("\n");
	
	rc4_algorithm(message, (unsigned char *)argv[1]);
	printf("秘文：%s\n",message);
	for(int i = 0; i < len; i++){
		printf("%02x",message[i]);
	}
	printf("\n");
	
	rc4_algorithm(message, (unsigned char *)argv[1]);
	printf("明文：%s\n",message);
	for(int i = 0; i < len; i++){
		printf("%02x",message[i]);
	}
	printf("\n");
	return 0;
}
