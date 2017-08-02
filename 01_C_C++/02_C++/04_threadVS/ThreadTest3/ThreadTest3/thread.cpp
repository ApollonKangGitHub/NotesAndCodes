#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>
#include<mutex>
#include<fstream>

#define MAX 50
using namespace  std;
/*
 *两把锁，两个函数对两把锁的加锁顺序不同，不同线程分别调用两个函数时可能会出现死锁
 *所以，如果两个函数对多把锁的加锁顺序不同，就可能导致死锁。一般我们会按同样的顺序来加锁避免死锁
 *但是当锁比较多时，难免顺序写的不一样，这是就有lock来提前帮我们设置：
 *当lock()函数提前指定顺序以后，并且在创建对象时，lock_guard<mutex>的初始化构造参数中
 *添加adopt_lock参数，即使对象创建顺序写的不同(即加锁顺序不同)也不会导致死锁,
 *但还是要尽量使得创建对象加锁顺序相同
*/
class mutex_file{
public:
	mutex_file(){
		fs.open("log.txt");
	}
	void share_print(string str, int i){
#if 1
		/*不会死锁*/
		lock(m_mutex, m_mutex2);
		lock_guard<mutex> locker(m_mutex, adopt_lock);
		lock_guard<mutex> locker2(m_mutex2, adopt_lock);
#endif
#if 0
		/*可能会死锁*/
		lock_guard<mutex> locker(m_mutex);
		lock_guard<mutex> locker2(m_mutex2);
#endif
		//fs << str << i << endl;
		cout << str << i << endl;
	}
	void share_print2(string str, int i){
#if 1
		/*不会死锁*/
		lock(m_mutex, m_mutex2);
		lock_guard<mutex> locker2(m_mutex2, adopt_lock);
		lock_guard<mutex> locker(m_mutex, adopt_lock);
#endif
#if 0
		/*可能会死锁*/
		lock_guard<mutex> locker2(m_mutex2);
		lock_guard<mutex> locker(m_mutex);
#endif
		//fs << str << i << endl;
		cout << str << i << endl;
	}
private:
	mutex m_mutex;
	mutex m_mutex2;
	ofstream fs;//fs不能(不要)通过函数返回，否则fs暴露在类外，会破坏保护性
};
void function2_thread(mutex_file & log){//对象专属锁，对象所属fstream资源，输出更加稳定
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		log.share_print("From thread_function:", i);
}

void DataCompetitionAndMutualExclusion(void)
{
	mutex_file log;
	thread thread1(function2_thread, ref(log));//传递log的引用
	for (int i = 0; i < MAX; i++)
		log.share_print2("From thread_main:", i);//将输出写入文件，安全性更高
	thread1.join();//这里不能设置为分离态，否则主线程输出完毕后关闭文件就有问题了
	Sleep(2000);
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}