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
	fgetpos(stream , &pos);  /* 用 fgetpos()取得读写位置 */
	printf("offset = %d\n", pos);
	pos.__pos = 10;             /*pos.__pos的下划线是两道短下划线组合在一起*/
	fsetpos (stream, &pos);    /*用 fgetpos()设置读写位置 */
	printf("offset = %d\n", ftell(stream));
	fclose(stream);

	return 0;
}