# include <iostream>
using namespace std;

int main(void)
{
	unsigned int i = 0XFFFFFFFF;
	int j = 0XFFFFFFFF;
	cout << i << endl;
	cout << j << endl;

	unsigned int unsignedmin = 0X00000000;
	unsigned int unsignedmax = 0XFFFFFFFF;
	int signedmin = 0X80000000;
	int signedmax = 0X7FFFFFFF;

	cout << "�޷���������СֵΪ��" << unsignedmin << "\t\t\t�޷������ֵΪ��" << unsignedmax << endl;
	cout << "�з���������СֵΪ��" << signedmin << "\t\t�з������ֵΪ��" << signedmax << endl;

	return 0;
}