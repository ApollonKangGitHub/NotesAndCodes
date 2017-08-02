#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>
#include<mutex>
#include<fstream>

#define MAX 50
using namespace  std;

class mutex_file{
public:
	mutex_file(){
		//fs.open("log.txt");//每次构造都会打开，链接数过多不安全，所以放到share_print()中判断再打开
	}
	void share_print(string str, int i){
		#if 0
		{
			unique_lock<mutex> locker(m_mutex, defer_lock);
			//该锁作用域z仅限于大括号内，加锁的地方不能放在if内open前，因为非原子操作线程不安全
			if (!fs.is_open())
				fs.open("log.txt");
		}
		#endif
		#if 1
		call_once(m_flag, [&](){fs.open("log.txt"); });//写法与上面的功能相同，都可以保证只打开一次
		#endif
		//lock_guard<mutex> locker(m_mutex, adopt_lock);
		unique_lock<mutex> locker(m_mutex, defer_lock);

		//...其它不加锁的段

		//unique_lock锁可以局部加锁解锁弹性更好，lock_guard则不可以,
		//因为lock_guard不包含lock()与unlock()两个成员
		locker.lock();
		cout << str << i << endl;//打在屏幕上用于观察
		fs << str << i << endl;//安全
		locker.unlock();

		//...其它不加锁的段

		locker.lock();
		Sleep(10);
		locker.unlock();
		//unique_lock锁可以移动，lock_guard则不可以移动
		unique_lock<mutex> locker2 = move(locker);
	}
private:
	mutex m_mutex;
	mutex m_mutex2;
	once_flag m_flag;
	ofstream fs;
};
void function2_thread(mutex_file & log){
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		log.share_print("From thread_function:", i);
}

void DataCompetitionAndMutualExclusion(void)
{
	mutex_file log;
	thread thread1(function2_thread, ref(log));//传递log的引用
	for (int i = 0; i < MAX; i++)
		log.share_print("From thread_main:", i);//将输出写入文件，安全性更高
	thread1.join();//这里不能设置为分离态，否则主线程输出完毕后关闭文件就有问题了
	Sleep(2000);
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}