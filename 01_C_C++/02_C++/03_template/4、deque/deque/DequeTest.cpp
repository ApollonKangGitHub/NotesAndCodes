/*
 *deque��˫�˶��У����ڴ�ռ�ģ������ʽ���飬
 *������һ�������ж���ڵ㣬ÿ���ڵ���һ������������ʽ�Ŀռ䣨һ����˵һ��Ϊ512���ֽڣ�
 *���ڴ治��ʱ��������һ�������ռ������ڶ�����
 *deque��ƽ��Ч�ʽ���vector��list֮�䣬Ҳ֧��[]�����������ʣ���Ϊdeque��Ҫ������ת���������ṹ����
 *
 *vector��list��deque���߱Ƚ�(�ڴ�ģ�;����ص�)��
 *
 *vector��	�����ռ�	���λ�ò���Ч�ʵ�	֧��β��ӣ���֧��ͷ���	֧���������
 *list��	������		���λ�ò���Ч�ʸ�	֧��β��ӣ�֧��ͷ���		��֧���������
 *deque��	������		���λ�ò���Ч����	֧��β��ӣ�֧��ͷ���		֧���������
 *�������Ƶ�ʸ�������ѡ��vector��ɾ������Ƶ�ʸ�����ѡ��list��deque���к͵���vector��list��ȱ��,
 *����deque�ĵ������ǳ����ӣ������Լ��Լ��Ȳ������鷳(û��һ������Ҫ�ж��Ƿ���Ҫ��Ծ��)
 *�����vector��dequeû��capacity()��reserve()������pop_front()��push_front()���ڲ�ʵ�ֲ�ͬ�����ǲ�������(�ӿ�)��ͬ
 */
#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

void trav(int a)
{
	cout << a << " ";
}
int main(void)
{
	/*�򵥲���*/
	deque<int> de;
	cout << de.max_size() << endl;

	de.push_back(10);
	de.push_front(20);
	de.push_front(30);
	de.push_front(40);
	de.push_back(0);

	for_each(de.begin(), de.end(), trav);
	cout << endl;
	cout << de.size() << endl;

	de.pop_front();

	deque<int>::iterator ite = de.begin();
	for (ite; ite != de.end(); ite++)
		cout << *ite << " ";
	cout << endl;

	system("pause");
	return 0;
}