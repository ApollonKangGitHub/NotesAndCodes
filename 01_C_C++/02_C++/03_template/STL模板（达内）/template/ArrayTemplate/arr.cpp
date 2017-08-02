#include<iostream>
using namespace std;

template <typename T = int>
class Array{
public:
	int _len;
	T * _arr;
public:
	Array(int len = 16):_len(len){
		_arr = static_cast<T*>(new T[_len]);	
	}
#if 1
	T &operator[](int index){
		if(index < _len)
			return _arr[index];
		else
			throw -1;
	}
#endif
#if 1
	const T &operator[](int index)const{
		if(index < _len)
			return _arr[index];
		else
			throw -1;
	}
#endif
	void fill(T start, const T&step){//根据步长和起始值来初始化
		for(int i = 0; i<_len; i++, start += step){
			_arr[i] = start;
		}
	}
	template <typename Q>//友元函数声明为模板
	friend ostream& operator<<(ostream & os,const Array<Q>& x);
	~Array(){
		delete []_arr;
	}
};

template<typename Q>
//由于operator<<()参数列表中Array数组被修饰为const,那么<<运算符在输出x[i]的时候
//重载的operator[]()也需要承诺不会修改数据,故要加const修饰[]的重载函数,否则编译不通过
//并且返回值修饰为const,不允许其他人修改(此处可以省略但是不太安全)
//当然也可以修改operator<<()的参数类型为非const的,其它的也就不用修改为const,但是这更不安全
//注意operator[]()的两个函数为重载关系，因为隐含的省略的this指针作为参数在两个函数中是不一样的:
//operator[]const()中为const Array* this,而operator[]()中为Array* this
ostream& operator<<(ostream &os, const Array<Q>& x)
{
	os<<"{ ";
	for(int i = 0; i < x._len; i++)
		os<<x[i]<<' ';
	os<<"}";
}
int main(void)
{
	Array<> iarr;//默认type为int,默认长度为16
	iarr.fill(11,2);
	cout<<iarr<<endl;

	Array<char> carr(8);
	carr.fill(65,2);
	cout<<carr<<endl;

//	cout<<arr[1]<<arr[8]<<endl;
	return 0;
}
