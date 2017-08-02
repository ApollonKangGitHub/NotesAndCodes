/*
	2016年9月3日12:54:04
	利用C++类可以重载数组下标运算符，解决数组越界问题
*/

# include <iostream>
using namespace	std;

class ARRAY
{
public:
	ARRAY(int l){length = l;size=new char[length];cout<<"构造函数执行中，数组内存分配！"<<endl;}
	~ARRAY(){delete []size;cout<<"析构函数执行中，数组内存释放！"<<endl;}
	int Getlength(){return length;}
	char&operator[](int i)
	{
		if(i>=0 && i<length)	return size[i];
		else
		{
			cout << endl << "第" << i << "个超出范围!";
			return size[length-1];//将越界的全部返回为'\0'
		}
	}
private:
	int length;
	char * size;
};
int main (void)
{
	int len,i;
	cout << "请输入您要创建的数组长度:" << endl;
	cin >> len;
	ARRAY array(len);
	char * ch = "hello everyone!";
	cout << ch << endl;
	for(i=0; i<=strlen(ch); ++i)
		array[i] = ch[i];//接收返回的未越界的字符

	cout << endl << endl;
	for(i=0; i<=strlen(ch); ++i)
		cout << array[i];
	cout << endl;
	
	return 0;
}
/*
运行结果：
		请输入您要创建的数组长度:
		12
		构造函数执行中，数组内存分配！
		hello everyone!

		第12个超出范围!
		第13个超出范围!
		第14个超出范围!
		第15个超出范围!

		hello every
		第12个超出范围!
		第13个超出范围!
		第14个超出范围!
		第15个超出范围!
		第12个超出范围!
		析构函数执行中，数组内存释放！
		Press any key to continue

		请输入您要创建的数组长度:
		18
		构造函数执行中，数组内存分配！
		hello everyone!


		hello everyone!
		析构函数执行中，数组内存释放！
		Press any key to continue
*/
