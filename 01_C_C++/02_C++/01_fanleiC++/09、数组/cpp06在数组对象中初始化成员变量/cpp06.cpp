# include <iostream>
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
	int l, w;
	area one[4] = {area(10,10),area(21,22),area(8,34),area(21,12)};
	for(i=0; i<4; ++i)
		cout << "����area["<<i<<"]:" << one[i].get() << endl;

	for(i = 0; i<4; ++i)
	{
		cout << "�������i������ĳ��Ϳ��ÿո������";
		cin >> l >> w;
		one[i].set(l,w);
	}

	for(i=0; i<4; ++i)
		cout << "����area["<<i<<"]:" << one[i].get() << endl;

	return 0;
}