#include<iostream>
#include<string>
#include<cstring>

using namespace std;

/*
 *比较两个模板函数：
 *第一个模板函数的参数V const&
 *第二个模板函数的参数const char* const&
 *由两个参数比较可知，后面的修饰都是const &
 *而当前面的const char*等价于V,即当模板参数是C风格的字符串的时候
 *优先采用第二种模板函数已经制定参数类型的方式
*/

template <typename V>
bool lessthan(V const & la, V const & ra){
	return la<ra;
}
#if 1
template<>//该写法是为了与上面的模板形式匹配，但是函数写法更为复杂(如下)
bool lessthan<const char*>(const char* const & la, const char* const & ra){//<const char *>可以省略，编译器可以推断出
	return (strcmp(la, ra) < 0);//cout<<"lessthan <const char *>"<<endl;
}
#endif
/*
 *关于上面的空模板与下面的函数其区别在于：
 *如果模板没有被用到，可执行文件中就不存在该部分的代码
 *而函数就不一样了，即使函数没有被用到，可执行文件中依旧会产生代码
 *
*/
#if 1
bool lessthan(const char *  la, const char * ra){
	//不是模板，可认为该函数与上面的模板属于重载关系,但是编译器在存在模板与特殊函数时优先调用特殊函数
	return (strcmp(la, ra) < 0);//cout<<"lessthan"<<endl;
}
#endif
template <typename T>//告诉编译器T为类型名
void sort(T *a, int n)
{
	for(int i = 0; i<n; i++)
		for(int j = 0; j<i; j++)
			if(lessthan(a[i], a[j]))
				swap(a[i], a[j]);
}
template<typename T>
void traversal(T *a, int n)
{
	for(int i = 0; i<n; i++)
		cout<<a[i]<<'\t';
	cout<<endl;
}
int main(void)
{
	int ai[6] = {8,1,9,2,7,-1};
	char ac[5] = {'d', 'x', 's', 'a', 'm'};
	double ad[5] = {5.5,1.3,2.4,-1.5,7.2};
	string as[4] = {"Good", "morning", "My", "friend"};
	const char * asc[4] = {"Good", "morning", "My", "friend"};//需要特殊处理

	sort(ai,6);traversal(ai,6);		
	sort(ac,5);traversal(ac,5);  
	sort(ad,5);traversal(ad,5);  
	sort(as,4);traversal(as,4);  
	sort(asc,4);traversal(asc,4);
	
	return 0;
}
