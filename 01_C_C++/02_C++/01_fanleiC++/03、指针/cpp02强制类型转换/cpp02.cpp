/*
	2016年8月5日18:03:04
*/
# include <iostream>
using namespace std;
int main (void)
{
	int i = -185;
	int * p = &i;
	char * q = (char *)p;
	char ch = *q;

	cout << ch << endl;
	cout << (short)ch << endl;
	cout << (int)ch << endl;
	cout << i << endl;
	cout << (short)i << endl;
	cout << (char)i << endl;

	return 0;
}

/*
	运行结果：
		G
		71
		71
		-185
		-185
		G
		Press any key to continue
	G的ASCII值为71
*/