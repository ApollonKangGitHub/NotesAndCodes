#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>
#include<mutex>
#include<fstream>

#define MAX 50
using namespace  std;

mutex mu;
void share_print(string str, int i){//������������cout��Դ
	lock_guard<mutex> guard(mu);//���coutִ��ʱ�׳��쳣�����������������⣬��guard���󱻹���ʱ����������ʱ���Զ�����
	//mu.lock();
	cout << str << i << endl;
	//mu.unlock();

	/*ע�⣺coutΪһ��ȫ�ֱ����������߳���Ȼ�����ڲ������������ʹ�ã�����ҪѰ����õİ취*/
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
	ofstream fs;//fs����(��Ҫ)ͨ���������أ�����fs��¶�����⣬���ƻ�������
};
void function_thread(void){//������������Ƚ�����
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		cout << "From thread_function:" << i << endl;
}
void function1_thread(void){//ȫ������ȫ��cout��Դ���������ȶ�
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		share_print("From thread_function:", i);
}
void function2_thread(mutex_file & log){//����ר��������������fstream��Դ����������ȶ�
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		log.share_print("From thread_function:", i);
}

/*���ݾ����뻥�����*/
void DataCompetitionAndMutualExclusion(void)
{
#if 0	
	thread thread1(function_thread);
	for (int i = 0; i < MAX; i++)
		cout << "From thread_main:" << i << endl;//�����߳��ھ���cout���
	thread1.detach();
	Sleep(2000);
#endif
#if 0
	thread thread1(function1_thread);
	for (int i = 0; i < MAX; i++)
		share_print("From thread_main:", i);//��ȫ����΢���
	thread1.detach();
	Sleep(2000);
#endif
#if 1
	mutex_file log;
	thread thread1(function2_thread, ref(log));//����log������
	for (int i = 0; i < MAX; i++)
		log.share_print("From thread_main:", i);//�����д���ļ�����ȫ�Ը���
	thread1.join();//���ﲻ������Ϊ����̬���������߳������Ϻ�ر��ļ�����������
	Sleep(2000);
#endif
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}