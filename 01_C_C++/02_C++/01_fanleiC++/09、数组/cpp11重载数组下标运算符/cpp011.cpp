/*
	2016��9��3��12:54:04
	����C++��������������±���������������Խ������
*/

# include <iostream>
using namespace	std;

class ARRAY
{
public:
	ARRAY(int l){length = l;size=new char[length];cout<<"���캯��ִ���У������ڴ���䣡"<<endl;}
	~ARRAY(){delete []size;cout<<"��������ִ���У������ڴ��ͷţ�"<<endl;}
	int Getlength(){return length;}
	char&operator[](int i)
	{
		if(i>=0 && i<length)	return size[i];
		else
		{
			cout << endl << "��" << i << "��������Χ!";
			return size[length-1];//��Խ���ȫ������Ϊ'\0'
		}
	}
private:
	int length;
	char * size;
};
int main (void)
{
	int len,i;
	cout << "��������Ҫ���������鳤��:" << endl;
	cin >> len;
	ARRAY array(len);
	char * ch = "hello everyone!";
	cout << ch << endl;
	for(i=0; i<=strlen(ch); ++i)
		array[i] = ch[i];//���շ��ص�δԽ����ַ�

	cout << endl << endl;
	for(i=0; i<=strlen(ch); ++i)
		cout << array[i];
	cout << endl;
	
	return 0;
}
/*
���н����
		��������Ҫ���������鳤��:
		12
		���캯��ִ���У������ڴ���䣡
		hello everyone!

		��12��������Χ!
		��13��������Χ!
		��14��������Χ!
		��15��������Χ!

		hello every
		��12��������Χ!
		��13��������Χ!
		��14��������Χ!
		��15��������Χ!
		��12��������Χ!
		��������ִ���У������ڴ��ͷţ�
		Press any key to continue

		��������Ҫ���������鳤��:
		18
		���캯��ִ���У������ڴ���䣡
		hello everyone!


		hello everyone!
		��������ִ���У������ڴ��ͷţ�
		Press any key to continue
*/
