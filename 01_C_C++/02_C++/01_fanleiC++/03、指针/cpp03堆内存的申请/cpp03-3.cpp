/*
	2016��8��6��13:39:17
*/
# include <iostream>
using namespace std;

int main (void)
{
	int * p;
	p = new int ;
	delete p;//ע�⵱�㲻������pָ�����һ����ڴ棨������Ϊ�ǿ��ڴ��С����������pָ����һ���ڴ�ʱ��
			//�ͱ������ͷ�p��ǰָ����ڴ�ռ��������µ��ڴ档�������ɵ�һ���ڴ�й¶��
	p = (int *)new double;

	return 0;
}