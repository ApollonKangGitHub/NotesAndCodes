#include<iostream>
#include<stack>
#include<queue>

using namespace std;

int main(void)
{
	int a[5] = {3,8,6,9,2};
	stack<int> si;
	queue<int> qi;
	priority_queue<int> pi;
	for(int i=0;i<5;i++){
		si.push(a[i]);
		qi.push(a[i]);
		pi.push(a[i]);
	}
	cout<<"stack\t"<<"queue\t"<<"priority_queue"<<endl;
	while(!si.empty() && !qi.empty() && !pi.empty()){
		cout<<si.top()<<'\t';si.pop();
		cout<<qi.front()<<'\t';qi.pop();
		cout<<pi.top()<<'\t';pi.pop();
		cout<<endl;
	}

	return 0;
}
