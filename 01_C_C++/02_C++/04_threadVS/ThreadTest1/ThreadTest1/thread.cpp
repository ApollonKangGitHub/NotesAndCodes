#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>

#define MAX 10
using namespace  std;

void function_thread(void){
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		cout << "From thread_function:" << i << endl;
}
class Fctor{
public:
	void operator()(string & msg){
		cout << "thread_id:" << this_thread::get_id() << "\tFrom thread_class:" << msg << endl;
		msg = "I love you!";
	}
};
/*线程的创建、初始化、移动等操作*/
void thread_create(void)
{
	/*线程初始化既可以用函数又可以用类*/

	string msg = "I love YuYu!";
	thread thread1((Fctor()), msg);//传递值（默认）
	Sleep(1000);
	thread1.join(); //设置为非分离状态，thread1.detach();设置为分离状态
	cout << "from thread_main:" << msg << endl;
	Sleep(1000);

	thread thread2((Fctor()), ref(msg));//std::ref()传递引用
	Sleep(1000);
	thread2.detach();
	cout << "from thread_main:" << msg << endl;
	Sleep(1000);

	thread thread3(function_thread);
	thread3.detach();
	Sleep(1000);

	//std::move()将msg作用域从主线程移动到（不是扩展到）子线程中，主线程中msg不能再使用，输出为空
	thread thread4((Fctor()), move(msg));
	cout << "thread4 id:" << thread4.get_id() << endl;
	//thread4.detach();//由于后面thread5占用/全盘接收了thread4的资源，所以这里不能设置thread的状态
	thread thread5 = move(thread4);//move将线程thread4资源全部移动给了线程thread5，线程thread4就完全失效
	cout << "thread4 id:" << thread4.get_id() << endl;
	cout << "thread5 id:" << thread5.get_id() << endl;
	Sleep(1000);
	thread5.detach();
	cout << "from thread_main:" << msg << endl;
	Sleep(1000);
}

int main(void)
{
	cout << thread::hardware_concurrency() << endl;
	cout << "main thread id:" << this_thread::get_id() << endl;
	Sleep(1000);

	thread_create();//线程的创建与线程函数调用

	system("pause");
	return 0;
}