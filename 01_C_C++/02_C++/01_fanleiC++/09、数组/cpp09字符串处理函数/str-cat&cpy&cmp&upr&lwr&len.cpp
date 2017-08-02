# include <iostream>
using namespace std;
int main (void)
{
/*字符串连接函数strcat()*/
	char a[20] = "My name is ";
	char b[] = "Jack";
	cout << strcat(a,b) << endl;
	//合并两个字符串，并将第二个字符串接在第一个字符串的后边存入第一个字符串所在连续内存中
	//合并一个后的字符串结尾也有一个'\0'，是第二个字符串的，第一个字符串的'\0'在合并时就自动取消了
	cout << a << endl;

/*字符串拷贝函数strcpy()*/
	cout << strcpy(a,b) <<endl;//将字符串b[]拷贝到a[]中
	cout << a << endl;
	cout << strcpy(a,"Mike is a big boy") <<endl;//a的数组长度不能比将要拷贝的字符串长度小
	cout << a << endl;

/*字符串比较函数strcmp()*/
	cout << strcmp("abcdef","abcdef") << endl;
	cout << strcmp("8123","7659") << endl;
	cout << strcmp("8123","9659") << endl;
	cout << strcmp("abcdeff","abcdefg") << endl;
	cout << strcmp("abcdefh","abcdefg") << endl;
	//若两个字符串相等返回假（0），不相等返回真（非0）
	//规律:
	//若第一个字符串的第一个字符的ASCII值，大于第二个字符串的第一个字符的ASCII值返回1
	//若第一个字符串的第一个字符的ASCII值，小于第二个字符串的第一个字符的ASCII值返回-1
	//若两个字符串第一个字符的ASCII值相等，则比较下一个,以此类推;当比较完之后完全对应相等就是两个字符串相等，自然返回0

/*将字符串中所有小写字母转化为大写字母strupr()*/
	cout << a << endl;
	cout << strupr(a) << endl;
/*将字符串中所有大写字母转化为小写字母strlwr()*/
	cout << a << endl;
	cout << strlwr(a) << endl;
/*测试字符串长度strlen()*/
	cout << strlen(a) << endl;//测试的是字符串长度（字符的个数），不包括字符串结束符'\0'
	return 0;
}