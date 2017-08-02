# include <iostream>
# define MAX 4000
using namespace std;

class area
{
public:
	area(){length = 0;width = 0;cout<<"调用构造函数设置长和宽,"<<"长:"<<length<<"宽:"<<width<<endl;}
	~area(){cout << "调用析构函数释放内存." <<"长:"<<length<<"宽:"<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length = l;width = w;cout<< "设置长和宽：" << length << "\t" << width <<endl;}
private:
	int length;
	int width;
};

int main (void)
{
	int i;

	area * one = new area[MAX];
	for(i=0;i<MAX;++i)
		one[i].set(i,i);
	for(i=0;i<MAX;++i)
		cout << "one["<<i<<"]面积为:" << one[i].get() << endl;
	delete []one;//表示删除整个数组

	return 0;
}