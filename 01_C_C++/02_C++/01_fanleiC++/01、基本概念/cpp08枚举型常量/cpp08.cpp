# include <iostream>
using namespace std;

int main (void)
{
	enum Day{Sunday=7,Monday=1,Tuesday,Wednesday,Tursday,Friday,Saturday};
	Day today = Monday;//ֻ�ܳ�ʼ�������ܸ�ֵ�����Ըо���û��ʲô����
	if(today == Sunday || today == Saturday)
		cout << "��Ϣ��!\n";
	else
		cout << "������!\n";

	return 0;
}