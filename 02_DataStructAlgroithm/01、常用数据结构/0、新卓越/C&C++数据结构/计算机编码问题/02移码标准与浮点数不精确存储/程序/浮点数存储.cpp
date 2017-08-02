# include<stdio.h>
# include<math.h> 

int main(void)
{
	float i = 99.7;
	float j = 99.5;
	double k = 99.3;

	printf("%f\n",i);
	printf("%f\n",j);
	printf("%lf\n",k);

	int p= (int)pow(2,15);
	//p = (int)pow(2,0)+pow(2,1)+pow(2,4)+pow(2,5)+pow(2,8)+pow(2,9)+pow(2,12)+pow(2,13)+pow(2,14);

	printf("%d\n",p);

	double m = ((float)29491/(float)32768);
	printf("%lf\n",m);

	return 0;
}

