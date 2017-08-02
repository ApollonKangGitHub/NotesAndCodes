# include <iostream>
using namespace std;

int main (void)
{
	enum Day{Sunday=7,Monday=1,Tuesday,Wednesday,Tursday,Friday,Saturday};
	Day today = Monday;//只能初始化，不能赋值。所以感觉并没有什么卵用
	if(today == Sunday || today == Saturday)
		cout << "休息日!\n";
	else
		cout << "工作日!\n";

	return 0;
}