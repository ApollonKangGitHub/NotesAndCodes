//#include <string.h>

char* mystrcpy(char* dest, char* src)
{
//	memset(dest, 0, 20);
	char* tmp = dest;
	while(*src != '\0'){
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return tmp;	
}




