/*标准库中有一个pair和make_pair()*/
#include<iostream>
using namespace std;

#include<string>

template <typename K, typename V>
struct Pair{
	K first;
	V second;
	void show(){
		cout<<"<typename K, typename V>:("<<first<<','<<second<<')'<<endl;
	}
};
#if 1
template <typename K>//部分特殊化
struct Pair<K,const char *>{
	K first;	//这里的顺序必须和<K,const char*>里的顺序相同
	string second;
	void show(){
		cout<<"<typename K, const char *>:("<<first<<','<<second<<')'<<endl;
	}
};
template <typename K>//部分特殊化
struct Pair<const char *, K>{
	string first;//顺序与上面的<const char *, K>对应
	K second;
	void show(){
		cout<<"<const char *, typename K>:("<<first<<','<<second<<')'<<endl;
	}
};
#endif
template <>//全特化
struct Pair<const char *, const char *>{
	string first;//顺序与上面的<const char *, K>对应
	string second;
	void show(){
		cout<<"<const char *, const char*>:("<<first<<','<<second<<')'<<endl;
	}
};
/*一种取巧的方式进行非人为模板类的实例化*/
template <typename K, typename V>
Pair<K,V> MakePair(K x, V y){
	Pair<K,V> pkv = {x,y};
	return pkv;
}
int main(void)
{
	/*人为实例化*/
	Pair<int, double> pid = {3, 5.5};
	Pair<int, const char*> pic = {4, "Hello"};
	Pair<const char*,int > pci = {"World", 5};	
	Pair<const char*, const char*> pcc = {"Hello","World"};//部分特化有歧义,需要全特化版本

	pid.show();
	pic.show();
	pci.show();
	pcc.show();
	
	/*模板类需要人为实例化，如何不用人为实例化，就可以自动识别参数类型实例化*/
	cout<<"模板函数壳可以自动实例化:因此采用模板函数来自动实例化模板类:"<<endl;	
	MakePair(3, 5.5).show();
	MakePair(4, "Hello").show();
	MakePair("World", 5).show();
	MakePair("Hello","World").show();

	return 0;
}
