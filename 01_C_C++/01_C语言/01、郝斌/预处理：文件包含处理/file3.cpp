int main(void)
{
	float x1,x2,x3,max;
	scanf("%f,%f,%f",&x1,&x2,&x3);
		
	max=maxthree(x1,x2,x3);
	printf("The max number of three is:%.1f\n",max);

	return 0;
}