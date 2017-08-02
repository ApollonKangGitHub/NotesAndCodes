# include <iostream>
# include <locale>

using namespace std;

int main(void)
{
	setlocale(LC_ALL,"chs");//将本机语言设置为中文简体
	wchar_t wh[] =L"中";//L表示告诉编译器为“中”分配两个字节
	wcout<<wh<<endl;//wcout恋用于宽字符输出

	return 0;
}