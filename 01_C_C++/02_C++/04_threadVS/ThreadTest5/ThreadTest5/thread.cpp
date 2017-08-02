#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<condition_variable>

using namespace std;

deque<int> qi;
mutex mu;//互斥锁
condition_variable cond;//条件变量

void function_1()//生产者
{
	int count = 10;
	while (count > 0){
		unique_lock<mutex> locker(mu);
		qi.push_front(count);
		locker.unlock();
		cond.notify_one();//调用notify_one激活睡眠等待的线程2（只能激活一个）
		//cond.notify_all();//可以激活所有休眠的线程
		this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}
void function_2()//消费者
{
	int data = 0;
	while (data != 1){
		unique_lock<mutex> locker(mu);
		/*
		*采用wait()函数避免if...else...的sleep()不恰当引起的多次的无用的操作
		*注意一个被加锁的线程不能休眠
		*wait函数会先将locker解锁然后休眠
		*在休眠结束以后再重新为locker加锁
		*所以重复加锁解锁只能使用unique_lock<>而不能使用lock_guard<>
		*/
		cond.wait(locker, [](){return !qi.empty(); });//第二个参数为了防止线程自己唤醒自己
		data = qi.back();
		qi.pop_back();
		locker.unlock();
		cout << "thread2 got a data from thread1:" << data << endl;
#if 0
	int data = 0;
	while (data != 1){
	unique_lock<mutex> locker(mu);
	if (!qi.empty()){
		data = qi.back();
		qi.pop_back();
		locker.unlock();
		cout << "thread2 got a data from thread1:" << data << endl;
	}
	else{
		locker.unlock();
		this_thread::sleep_for(chrono::milliseconds(10));//如果队列为空等待10ms再重新进入循环
	}
}
#endif}
int main(void)
{
	thread t1(function_1);
	thread t2(function_2);
	t1.join();
	t2.join();
	system("pause");
	return 0;
}