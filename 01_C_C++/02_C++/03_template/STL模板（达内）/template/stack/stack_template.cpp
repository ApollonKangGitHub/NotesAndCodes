#include<iostream>
#include<stdio.h>
#include<unistd.h>

using namespace std;

template <typename T>
class Stack{
	int _top;
	int _size;
	T * _arr;
public:
	Stack(int size = 32):_size(size), _top(0){
		_arr = static_cast<T*>(new T[_size]);
		cout<<"constructor"<<endl;
	}
	void push(const T data){
		if(!full())
			_arr[_top++] = data;
	}
	T &pop(void){
		if(!empty())
			return _arr[--_top];
		else
			throw 0;
	}
	T &top(void){
		if(_top >= 1)		
			return _arr[_top-1];
		else
			throw 0;
	}
	int size(){
		return _size;
	}
	bool empty(void){
		return (_top == 0);
	}
	bool full(void){
		return (_top == _size);
	}
	~Stack(){
		delete []_arr;
		cout<<"destructor"<<endl;
	}
};

int main(void){
	Stack<int> ai(16);
	for(int i = 0; i<ai.size(); i++)
		ai.push(i+1);
	for(int i = 0; i<ai.size(); i++)
		cout<<ai.pop()<<'\t';
	cout<<endl;

	char buf[20] = {};
	Stack<string> as(3);
	for(int i = 0; i<as.size(); i++){
			sprintf(buf, "string%d", i+1);
			as.push(buf);
	}
	for(int i = 0; i<as.size(); i++){
		cout<<as.pop()<<'\t'<< flush;
		sleep(1);
		try{
			cout<<as.top()<<endl;//top()在遇到0时,>=1不成立,所以抛出异常,就不能输出故而捕获异常防止段错误
		}catch(...){
			break;
		}
	}
	cout<<endl;
	return 0;
}
