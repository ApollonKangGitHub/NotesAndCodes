# include <iostream>
using namespace std;

class rectangle
{
public:
	rectangle(){cout << "���캯��������..." << endl; cout << "����һ��������" << endl;}
	rectangle(int l, int w)
	{
		cout << "���캯��������..." << endl;
		length = l; width = w;
		cout << "�����ε����Ϊ��" << length * width << endl;
	}
	rectangle(int l, int w, int h)
	{
		cout << "���캯��������..." << endl;
		length = l;
		width = w;
		height = h;
		cout << "����������Ϊ��" << length * width * height << endl;
	}
	~rectangle(){cout << "��������������..." << endl;}
	int area(){return length * width;}
private:
	int length;
	int width;
	int height;
};

int main (void)
{
	rectangle a;
	rectangle b(3,4);
	rectangle c(3,4,5);

	cout << b.area() << endl;
	cout << c.area() << endl;
	return 0;
}
