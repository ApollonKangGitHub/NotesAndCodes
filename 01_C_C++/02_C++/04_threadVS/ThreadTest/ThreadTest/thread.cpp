#include<iostream>
#include<thread>
#include<mutex>
#include<future>

using namespace std;

int factorial(future<int> &f)
{
	int N = f.get();
	int res = 1;
	for (int i = N; i > 1; i--){
		res *= i;
	}
	cout << "result at child  is : " << res << endl;
	return res;
}

int main(void)
{
	int val;//不存在传引用给子线程时需要加锁设置条件变量的繁琐问题
	promise<int> p;//promise和future只能移动不能复制
	future<int>  fu = p.get_future();
	future<int>  fu2 = async(launch::async,factorial,ref(fu));//采用async()创建线程
	p.set_value(4);

	val = fu2.get();
	cout << "val get from child is : " << val << endl;

	system("pause");
	return 0;
}