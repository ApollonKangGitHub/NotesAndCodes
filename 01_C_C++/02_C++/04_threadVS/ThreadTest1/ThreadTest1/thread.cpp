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
/*�̵߳Ĵ�������ʼ�����ƶ��Ȳ���*/
void thread_create(void)
{
	/*�̳߳�ʼ���ȿ����ú����ֿ�������*/

	string msg = "I love YuYu!";
	thread thread1((Fctor()), msg);//����ֵ��Ĭ�ϣ�
	Sleep(1000);
	thread1.join(); //����Ϊ�Ƿ���״̬��thread1.detach();����Ϊ����״̬
	cout << "from thread_main:" << msg << endl;
	Sleep(1000);

	thread thread2((Fctor()), ref(msg));//std::ref()��������
	Sleep(1000);
	thread2.detach();
	cout << "from thread_main:" << msg << endl;
	Sleep(1000);

	thread thread3(function_thread);
	thread3.detach();
	Sleep(1000);

	//std::move()��msg����������߳��ƶ�����������չ�������߳��У����߳���msg������ʹ�ã����Ϊ��
	thread thread4((Fctor()), move(msg));
	cout << "thread4 id:" << thread4.get_id() << endl;
	//thread4.detach();//���ں���thread5ռ��/ȫ�̽�����thread4����Դ���������ﲻ������thread��״̬
	thread thread5 = move(thread4);//move���߳�thread4��Դȫ���ƶ������߳�thread5���߳�thread4����ȫʧЧ
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

	thread_create();//�̵߳Ĵ������̺߳�������

	system("pause");
	return 0;
}