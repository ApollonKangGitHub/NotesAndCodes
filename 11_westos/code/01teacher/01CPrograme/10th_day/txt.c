

	int char float double 
	int* char*     

	指针： 期望存放地址。(一级指针)   int* pa = a; 
	数组：   一维数组      int a[5]    char ch[5]	
		二维数组      int a[2][3];	
		数组指针      int (*pa)[3];    pa = a;

		int* pa = &a;		int** ppa = &pa;
		指针数组：  int*   a[5];
			int**  pa = a;

		函数指针： 存放函数的入口地址。  （函数名字代表函数的入口地址）
		int test(int, char*);
		int (*ptest)(int, char*) = NULL;
		ptest = test;
		ptest(100, "hello");
	回调函数：参数列表里包含了一个函数指针。
	struct person lily;	
	lily.age

	struct person* plily;
	plily->age = 200;
	plily->pt(20, "jim");

文件操作：
	fopen()    fread()   fwrite();   fclose();
读文件：  fgets  fgetc   getchar     
写文件：  fputs  fputc   putchar    
控制文件：   rewind    ftell    fseek    

-----------------------------------------------------
open   read   write colse     
 

struct person{
	int age;
	char* name;
//	int test(){ }
	int (*pt)(int , char*);
};

struct person jim = {
	.age = 20,
	.name = "jim",
	.pt = test, 

};	
int test(int a, char* name)
{

}	
int main()
{
	jim.pt(20, "jim");
	int a = 20;
	//test(&a);
	a = test();
}

int test()
{
	*pa = 200; 

	return 200;
}







