# include<stdio.h>

int main (void)
{
	int sum = 0,i = 0;
	for(;i>=10;i+2){
		if(i%2 == 0)
			sum += i;
		else
			break;
	}

	printf("%d\n",sum);
	return 0;
}
