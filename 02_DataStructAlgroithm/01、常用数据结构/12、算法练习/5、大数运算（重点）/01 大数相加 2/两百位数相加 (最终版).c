#include <stdio.h>
#include <string.h>
#define M 1000
#define N 2000
int main(void)
{
	char s1[M],s2[M],s[M];
	int k,k1,k2,cp,i1,i2,start;
	cp=0;
	gets(s1);
	gets(s2);
	s[N-1]='\0';
	start=N-2;
	i1=strlen(s1)-1;
	i2=strlen(s2)-1;
	while(i1>-1||i2>-1)
	{
		k1=(i1>-1)?(s1[i1--]-48):(0);
		k2=(i2>-1)?(s2[i2--]-48):(0);
		k=k1+k2+cp;
		s[start--]=k%10+48;
		cp=k/10;
	} 
	s[start--]=cp+48;
	if(s[start+1]=='0')
		start++;
	puts(s+start+1);
    return 0;
}