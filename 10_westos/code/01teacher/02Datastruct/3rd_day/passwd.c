#include <stdio.h>




int main()
{
	printf("%s\n", __FUNCTION__);		
}


__attribute ((destructor))int after_main()
{
	printf("%s\n", __FUNCTION__);
}



__attribute ((constructor))int befor_main()
{
	printf("%s\n", __FUNCTION__);
}




