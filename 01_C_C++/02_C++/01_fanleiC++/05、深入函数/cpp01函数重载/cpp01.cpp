# include <iostream>
using namespace std;

class number
{
public:
	number (int x, int y){cout << "���캯��������..." << endl; i = x; j = y;}
	~number (){cout << "��������������..." << endl;}
	int Add(){return i+j;}
	int Add(int x, int y, int z){return x+y+z;}
private:
	int i;
	int j;
};

int Add (int x ,int y, int z)
{
	return x+y+z;
}
int Add (int x, int y)
{
	return x+y;
}

int main (void)
{
	number NUM(10,12);

	cout << NUM.Add() << endl;
	cout << NUM.Add(10,12,14) << endl;

	cout << Add(4,5) << endl;
	cout << Add(4,5,6) << endl;

	return 0;
}