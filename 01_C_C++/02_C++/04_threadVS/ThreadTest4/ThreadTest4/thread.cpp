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
		//fs.open("log.txt");//ÿ�ι��춼��򿪣����������಻��ȫ�����Էŵ�share_print()���ж��ٴ�
	}
	void share_print(string str, int i){
		#if 0
		{
			unique_lock<mutex> locker(m_mutex, defer_lock);
			//����������z�����ڴ������ڣ������ĵط����ܷ���if��openǰ����Ϊ��ԭ�Ӳ����̲߳���ȫ
			if (!fs.is_open())
				fs.open("log.txt");
		}
		#endif
		#if 1
		call_once(m_flag, [&](){fs.open("log.txt"); });//д��������Ĺ�����ͬ�������Ա�ֻ֤��һ��
		#endif
		//lock_guard<mutex> locker(m_mutex, adopt_lock);
		unique_lock<mutex> locker(m_mutex, defer_lock);

		//...�����������Ķ�

		//unique_lock�����Ծֲ������������Ը��ã�lock_guard�򲻿���,
		//��Ϊlock_guard������lock()��unlock()������Ա
		locker.lock();
		cout << str << i << endl;//������Ļ�����ڹ۲�
		fs << str << i << endl;//��ȫ
		locker.unlock();

		//...�����������Ķ�

		locker.lock();
		Sleep(10);
		locker.unlock();
		//unique_lock�������ƶ���lock_guard�򲻿����ƶ�
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
	thread thread1(function2_thread, ref(log));//����log������
	for (int i = 0; i < MAX; i++)
		log.share_print("From thread_main:", i);//�����д���ļ�����ȫ�Ը���
	thread1.join();//���ﲻ������Ϊ����̬���������߳������Ϻ�ر��ļ�����������
	Sleep(2000);
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}