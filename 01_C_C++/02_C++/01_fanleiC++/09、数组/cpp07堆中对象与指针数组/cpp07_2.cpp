# include <iostream>
# define MAX 4000
using namespace std;

class area
{
public:
	area(){length = 0;width = 0;cout<<"���ù��캯�����ó��Ϳ�,"<<"��:"<<length<<"��:"<<width<<endl;}
	~area(){cout << "�������������ͷ��ڴ�." <<"��:"<<length<<"��:"<<width<<endl;}
	int get(){return length*width;}
	void set(int l,int w){length = l;width = w;cout<< "���ó��Ϳ�" << length << "\t" << width <<endl;}
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
		cout << "one["<<i<<"]���Ϊ:" << one[i].get() << endl;
	delete []one;//��ʾɾ����������

	return 0;
}