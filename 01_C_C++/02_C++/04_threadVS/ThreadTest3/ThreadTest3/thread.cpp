#include<iostream>
#include<thread>
#include<string>
#include<Windows.h>
#include<mutex>
#include<fstream>

#define MAX 50
using namespace  std;
/*
 *�������������������������ļ���˳��ͬ����ͬ�̷ֱ߳������������ʱ���ܻ��������
 *���ԣ�������������Զ�����ļ���˳��ͬ���Ϳ��ܵ���������һ�����ǻᰴͬ����˳����������������
 *���ǵ����Ƚ϶�ʱ������˳��д�Ĳ�һ�������Ǿ���lock����ǰ���������ã�
 *��lock()������ǰָ��˳���Ժ󣬲����ڴ�������ʱ��lock_guard<mutex>�ĳ�ʼ�����������
 *���adopt_lock��������ʹ���󴴽�˳��д�Ĳ�ͬ(������˳��ͬ)Ҳ���ᵼ������,
 *������Ҫ����ʹ�ô����������˳����ͬ
*/
class mutex_file{
public:
	mutex_file(){
		fs.open("log.txt");
	}
	void share_print(string str, int i){
#if 1
		/*��������*/
		lock(m_mutex, m_mutex2);
		lock_guard<mutex> locker(m_mutex, adopt_lock);
		lock_guard<mutex> locker2(m_mutex2, adopt_lock);
#endif
#if 0
		/*���ܻ�����*/
		lock_guard<mutex> locker(m_mutex);
		lock_guard<mutex> locker2(m_mutex2);
#endif
		//fs << str << i << endl;
		cout << str << i << endl;
	}
	void share_print2(string str, int i){
#if 1
		/*��������*/
		lock(m_mutex, m_mutex2);
		lock_guard<mutex> locker2(m_mutex2, adopt_lock);
		lock_guard<mutex> locker(m_mutex, adopt_lock);
#endif
#if 0
		/*���ܻ�����*/
		lock_guard<mutex> locker2(m_mutex2);
		lock_guard<mutex> locker(m_mutex);
#endif
		//fs << str << i << endl;
		cout << str << i << endl;
	}
private:
	mutex m_mutex;
	mutex m_mutex2;
	ofstream fs;//fs����(��Ҫ)ͨ���������أ�����fs��¶�����⣬���ƻ�������
};
void function2_thread(mutex_file & log){//����ר��������������fstream��Դ����������ȶ�
	cout << "thread_id:" << this_thread::get_id() << endl;
	for (int i = 0; i > -MAX; i--)
		log.share_print("From thread_function:", i);
}

void DataCompetitionAndMutualExclusion(void)
{
	mutex_file log;
	thread thread1(function2_thread, ref(log));//����log������
	for (int i = 0; i < MAX; i++)
		log.share_print2("From thread_main:", i);//�����д���ļ�����ȫ�Ը���
	thread1.join();//���ﲻ������Ϊ����̬���������߳������Ϻ�ر��ļ�����������
	Sleep(2000);
}
int main(void)
{
	DataCompetitionAndMutualExclusion();

	system("pause");
	return 0;
}