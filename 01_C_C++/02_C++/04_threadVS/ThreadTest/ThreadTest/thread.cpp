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
	int val;//�����ڴ����ø����߳�ʱ��Ҫ�����������������ķ�������
	promise<int> p;//promise��futureֻ���ƶ����ܸ���
	future<int>  fu = p.get_future();
	future<int>  fu2 = async(launch::async,factorial,ref(fu));//����async()�����߳�
	p.set_value(4);

	val = fu2.get();
	cout << "val get from child is : " << val << endl;

	system("pause");
	return 0;
}