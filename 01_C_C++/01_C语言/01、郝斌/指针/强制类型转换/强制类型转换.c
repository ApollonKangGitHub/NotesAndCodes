# include <stdio.h>
int main (void)
{
	int i = -185;
	int * p = &i;
	char * q = (char *)p;
	char ch = *q;

	printf("%d\t%d\t%c\n", i,(short)i, (char)i);
	printf("%d\t%d\t%c\n", *p, *((short*)p), *(char *)p);

	printf("%d\t%d\t%c\n", *((int *)q),  *((short *)q) ,*q);
	printf("%d\t%d\t%c\n", (int)ch, (short)ch, ch);

	printf("%#x\t,%#x\t,%#x\n", i,(short)i, (char)i);
	printf("%#x\t,%#x\t,%#x\n", *p, *((short*)p), *(char *)p);
	printf("%#x\t,%#x\t,%#x\n", *((int *)q),  *((short *)q) ,*q);
	printf("%#x\t,%#x\t,%#x\n", (int)ch, (short)ch, ch);

	printf("%#x",i);

	return 0;
}
