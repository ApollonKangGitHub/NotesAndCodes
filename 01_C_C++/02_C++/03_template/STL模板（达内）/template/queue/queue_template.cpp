#include<iostream>
using namespace std;

#include<string>

template <typename T>
class Queue{
private:
/*环形队列*/
	int _size;//队列大小
	int _front;//队头指针,出队时先出队后移动指针
	int _tail;//队尾指针,入队时先入队后移动指针
	T * _arr;
public:
	Queue(int size = 32):_size(size+1),_front(1),_tail(1){//最初浪费的是第一个(下标为0)空间
		//用户申请size个，但是环形队列会浪费一个,那就多申请一个
		//队列默认大小为32,初始化头和尾指针均为1
		//环形队列浪费一个空间
		_arr = static_cast<T*>(new T[_size]);
	}
	int size(){
		return _size-1;//给用户返回的依旧是用户申请的数目
	}
	bool empty(){
		return (_front == _tail);
	}
	bool full(){
		return (((_tail+1)%_size) == _front);
	}
	Queue & push(const T & data){//注意返回的引用是类的引用，而不是参数类型T的引用
		if(!full()){
			_arr[_tail++] = data;
			_tail %= _size;
		}
		return *this;//为了实现q.push(1).push(2).push(3);的调用模式
	}
	T& pop(){
		if(!empty()){
			int ret = _front++;
			_front %= _size;
			return (_arr[ret]);
		}
	}
	T& showfront(){
		if(!empty())
			return (_arr[_front]);
	}
	~Queue(){
		delete []_arr;
	}
};
int main(void)
{
#if 1
	Queue<int> q1(16);
	cout<<"size:"<<q1.size()<<endl;
	for(int i = 0; i<q1.size(); i++)
		q1.push(i+1);
	for(int i = 0; i<q1.size(); i++)
		cout<<q1.pop()<<'\t';
	cout<<endl;
	
	q1.push(1).push(3).push(5).push(7).push(9);
	while(!q1.empty()){
		cout<< "front:" << q1.showfront() << '\t';
		cout<< "pop front:" << q1.pop() << endl;
	}
#endif
#if 1
	Queue<double> q2;
	cout<<"size:"<<q2.size()<<endl;
	for(int i = 0; i<q2.size(); i++)
		q2.push(i+1.115);
	for(int i = 0; i<q2.size(); i++)
		cout<<q2.pop()<<'\t';
	cout<<endl;
	
	q2.push(1+1.125).push(3+1.125).push(5+1.125).push(7+1.125).push(9+1.125);
	while(!q2.empty()){
		cout<< "front:" << q2.showfront() << '\t';
		cout<< "pop front:" << q2.pop() << endl;
	}
#endif
	return 0;
}

