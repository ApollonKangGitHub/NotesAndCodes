#include<iostream>
#include<thread>
#include<mutex>
#include<deque>
#include<condition_variable>

using namespace std;

deque<int> qi;
mutex mu;//������
condition_variable cond;//��������

void function_1()//������
{
	int count = 10;
	while (count > 0){
		unique_lock<mutex> locker(mu);
		qi.push_front(count);
		locker.unlock();
		cond.notify_one();//����notify_one����˯�ߵȴ����߳�2��ֻ�ܼ���һ����
		//cond.notify_all();//���Լ����������ߵ��߳�
		this_thread::sleep_for(chrono::seconds(1));
		count--;
	}
}
void function_2()//������
{
	int data = 0;
	while (data != 1){
		unique_lock<mutex> locker(mu);
		/*
		*����wait()��������if...else...��sleep()��ǡ������Ķ�ε����õĲ���
		*ע��һ�����������̲߳�������
		*wait�������Ƚ�locker����Ȼ������
		*�����߽����Ժ�������Ϊlocker����
		*�����ظ���������ֻ��ʹ��unique_lock<>������ʹ��lock_guard<>
		*/
		cond.wait(locker, [](){return !qi.empty(); });//�ڶ�������Ϊ�˷�ֹ�߳��Լ������Լ�
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
		this_thread::sleep_for(chrono::milliseconds(10));//�������Ϊ�յȴ�10ms�����½���ѭ��
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