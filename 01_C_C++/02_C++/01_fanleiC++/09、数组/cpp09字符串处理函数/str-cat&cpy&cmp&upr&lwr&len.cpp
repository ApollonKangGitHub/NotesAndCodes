# include <iostream>
using namespace std;
int main (void)
{
/*�ַ������Ӻ���strcat()*/
	char a[20] = "My name is ";
	char b[] = "Jack";
	cout << strcat(a,b) << endl;
	//�ϲ������ַ����������ڶ����ַ������ڵ�һ���ַ����ĺ�ߴ����һ���ַ������������ڴ���
	//�ϲ�һ������ַ�����βҲ��һ��'\0'���ǵڶ����ַ����ģ���һ���ַ�����'\0'�ںϲ�ʱ���Զ�ȡ����
	cout << a << endl;

/*�ַ�����������strcpy()*/
	cout << strcpy(a,b) <<endl;//���ַ���b[]������a[]��
	cout << a << endl;
	cout << strcpy(a,"Mike is a big boy") <<endl;//a�����鳤�Ȳ��ܱȽ�Ҫ�������ַ�������С
	cout << a << endl;

/*�ַ����ȽϺ���strcmp()*/
	cout << strcmp("abcdef","abcdef") << endl;
	cout << strcmp("8123","7659") << endl;
	cout << strcmp("8123","9659") << endl;
	cout << strcmp("abcdeff","abcdefg") << endl;
	cout << strcmp("abcdefh","abcdefg") << endl;
	//�������ַ�����ȷ��ؼ٣�0��������ȷ����棨��0��
	//����:
	//����һ���ַ����ĵ�һ���ַ���ASCIIֵ�����ڵڶ����ַ����ĵ�һ���ַ���ASCIIֵ����1
	//����һ���ַ����ĵ�һ���ַ���ASCIIֵ��С�ڵڶ����ַ����ĵ�һ���ַ���ASCIIֵ����-1
	//�������ַ�����һ���ַ���ASCIIֵ��ȣ���Ƚ���һ��,�Դ�����;���Ƚ���֮����ȫ��Ӧ��Ⱦ��������ַ�����ȣ���Ȼ����0

/*���ַ���������Сд��ĸת��Ϊ��д��ĸstrupr()*/
	cout << a << endl;
	cout << strupr(a) << endl;
/*���ַ��������д�д��ĸת��ΪСд��ĸstrlwr()*/
	cout << a << endl;
	cout << strlwr(a) << endl;
/*�����ַ�������strlen()*/
	cout << strlen(a) << endl;//���Ե����ַ������ȣ��ַ��ĸ��������������ַ���������'\0'
	return 0;
}