#include<iostream>
#include<deque>
#include<string>
using namespace std;

int main(void)
{
	deque<string> task;
	/*任务列表*/
	task.push_back("起床");
	task.push_back("洗漱");
	task.push_back("吃饭");
	task.push_back("上班");
	//显示任务列表
	int size = task.size();//一次计算多次使用，因为deque的size计算更麻烦
	for(int i = 0; i<size; i++){
		cout<<task[i]<<"==>";
	}		
	cout<<"OK"<<endl;

	/*处理任务，并从任务列表中删除*/
	while(!task.empty()){
		cout<<task.front();
		task.pop_front();
		cout<<"完成"<<endl;
	}

	return 0;
}
