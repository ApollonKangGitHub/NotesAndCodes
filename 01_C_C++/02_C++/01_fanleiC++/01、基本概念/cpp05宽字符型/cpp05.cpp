# include <iostream>
# include <locale>

using namespace std;

int main(void)
{
	setlocale(LC_ALL,"chs");//��������������Ϊ���ļ���
	wchar_t wh[] =L"��";//L��ʾ���߱�����Ϊ���С����������ֽ�
	wcout<<wh<<endl;//wcout�����ڿ��ַ����

	return 0;
}