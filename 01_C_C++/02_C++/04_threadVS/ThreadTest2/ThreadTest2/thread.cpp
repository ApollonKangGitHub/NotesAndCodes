#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>
#include<mutex>
#include<fstream>

#define MAX 50
using namespace  std;

mutex mu;
void share_print(string str, int i){//互斥量来管理cout资源
	lock_guard<mutex> guard(mu);//解决cout执行时抛出异常不能正常解锁的问题，当guard对象被构造时加锁，析构时会自动解锁
	//mu.lock();
	cout << str << i << endl;
	//mu.unlock();

	/*注意：cout为一个全局变量，其它线程仍然可以在不加锁的情况下使用，所以要寻求更好的办法*/
}

class mutex_file{
public:
	mutex_file(){
		fs.open("log.txt");
	}
	void share_print(string str, int i){
		lock_guard<mutex> locker(m_mutex);
		fs << str << i << endl;
	}
protected:
private:
	mutex m_mutex;
	ofstream fs;//fs不能(不要)通过函数返回，否则fs暴露在类外，会破坏保护性
};
void function_thread(void){//不加锁，输出比较杂乱
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		cout << "From thread_function:" << i << endl;
}
void function1_thread(void){//全局锁，全局cout资源，输出相对稳定
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		share_print("From thread_function:", i);
}
void function2_thread(mutex_file & log){//对象专属锁，对象所属fstream资源，输出更加稳定
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		log.share_print("From thread_function:", i);
}

/*数据竞争与互斥对象*/
void DataCompetitionAndMutualExclusion(void)
{
#if 0	
	thread thread1(function_thread);
	for (int i = 0; i < MAX; i++)
		cout << "From thread_main:" << i << endl;//两个线程在竞争cout输出
	thread1.detach();
	Sleep(2000);
#endif
#if 0
	thread thread1(function1_thread);
	for (int i = 0; i < MAX; i++)
		share_print("From thread_main:", i);//安全性稍微提高
	thread1.detach();
	Sleep(2000);
#endif
#if 1
	mutex_file log;
	thread thread1(function2_thread, ref(log));//传递log的引用
	for (int i = 0; i < MAX; i++)
		log.share_print("From thread_main:", i);//将输出写入文件，安全性更高
	thread1.join();//这里不能设置为分离态，否则主线程输出完毕后关闭文件就有问题了
	Sleep(2000);
#endif
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}