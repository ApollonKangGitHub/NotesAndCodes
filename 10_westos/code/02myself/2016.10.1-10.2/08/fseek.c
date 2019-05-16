#include<stdio.h>

int main(void)
{
	FILE *stream;
	long offset;
	fpos_t pos;

	stream = fopen("/etc/passwd", "r");
	fseek(stream, 5, SEEK_SET) ;
	printf("offset = %d\n", ftell(stream));
	rewind(stream);
	fgetpos(stream , &pos);  /* �� fgetpos()ȡ�ö�дλ�� */
	printf("offset = %d\n", pos);
	pos.__pos = 10;             /*pos.__pos���»������������»��������һ��*/
	fsetpos (stream, &pos);    /*�� fgetpos()���ö�дλ�� */
	printf("offset = %d\n", ftell(stream));
	fclose(stream);

	return 0;
}