#include<iostream>
using namespace std;
#include<cstring>

template <class K, class V>
struct Pair
{
public:
	K first;
	V second;
public:
	Pair():first(),second(){}//构造函数重载

	template<class F, class Q>//构造函数重载
	Pair(const F& x,const Q& y):first(x),second(y){}

	template<class F, class Q>//拷贝构造函数重载
	Pair(const Pair<F,Q> &p){
		first = p.first;
		second = p.second;
	}

	template<class F, class Q>//赋值运算符重载
	Pair & operator=(const Pair<F,Q> &p){
		first = p.first;
		second = p.second;
		return * this;
	}
	
	friend ostream& operator<<(ostream &os, const Pair &p){//输出运算符重载
		return os<<'('<<p.first<<','<<p.second<<')'<<endl;
	}

};
int main(void)
{
	Pair<int, double> pid(1, 2.3);
	Pair<char, double> pac('a', 4.5);

	cout.setf(ios::showpoint);
	
	cout<<pid<<'\t'<<pac<<endl;
	pid = pac;
	cout<<pid<<'\t'<<pac<<endl;

	/*区分以下C风格的字符串和C++风格的字符串,C风格的字符串在实例化模板时只复制了地址，没有拷贝内容*/
	char a[10] = "Hello" ,b[10] = "World";
	Pair<const char *, const char *> pcc(a,b);
	Pair<string, string> pss = pcc;//	pss = pcc;

	cout<<pcc<<pss<<endl;
	strcpy(a, "Yuan");
	strcpy(b, "Kang");
	cout<<pcc<<pss<<endl;

	return 0;
}
