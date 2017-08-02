# include <iostream>
# define MAX_class 3
# define MAX_main 3
using namespace std;

class array
{
public:
	int a[MAX_class];
};
int main (void)
{
	array ARR[MAX_main];
	int i, j;

	for(i = 0; i<MAX_main; ++i)
	{
		for(j = 0; j<MAX_class; ++j)
		{
			cout << "请输出对象" << "ARR["<<i<<"]" << "的元素" << "a["<<j<<"]" << ":";
			cin >> ARR[i].a[j];
		}
	}

	for(i = 0; i<MAX_main; ++i)
		for(j = 0; j<MAX_class; ++j)
			cout << ARR[i].a[j] << "\t";

	return 0;
}