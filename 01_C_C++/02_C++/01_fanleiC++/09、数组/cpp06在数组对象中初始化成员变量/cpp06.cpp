# include <iostream>
using namespace std;

class area
{
public:
	area(int l,int w){length = l;width = w;cout<<"调用构造函数设置长和宽,"<<"长:"<<length<<"宽:"<<width<<endl;}
	~area(){cout << "调用析构函数释放内存." <<"长:"<<length<<"宽:"<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length = l;width = w;}
private:
	int length;
	int width;
};

int main (void)
{
	int i;
	int l, w;
	area one[4] = {area(10,10),area(21,22),area(8,34),area(21,12)};
	for(i=0; i<4; ++i)
		cout << "对象area["<<i<<"]:" << one[i].get() << endl;

	for(i = 0; i<4; ++i)
	{
		cout << "请输入第i个对象的长和宽，用空格隔开：";
		cin >> l >> w;
		one[i].set(l,w);
	}

	for(i=0; i<4; ++i)
		cout << "对象area["<<i<<"]:" << one[i].get() << endl;

	return 0;
}