# include <iostream>
# define MAX 4000
using namespace std;

class area
{
public:
	area(int l,int w){length = l;width = w;cout<<"���ù��캯�����ó��Ϳ�,"<<"��:"<<length<<"��:"<<width<<endl;}
	~area(){cout << "�������������ͷ��ڴ�." <<"��:"<<length<<"��:"<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length = l;width = w;}
private:
	int length;
	int width;
};

int main (void)
{
	int i;
	int j;
	int k;
	area *one[MAX];
	for(i=0,k=0;i<MAX;++i)
	{
		one[i] = new area(i+5,i+10);
		++k;
	}
	for(i=0;i<MAX;++i)
	{
		cout << "*(one["<<i<<"]):" << one[i]->get() << endl;
	}
	for(i=0,j=0;i<MAX;++i)
	{
		delete one[i];
		++j;
	}
	return 0;
}