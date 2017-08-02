/*
 *deque是双端队列，其内存空间模型是链式数组，
 *类似于一个链表有多个节点，每个节点是一段连续的数组式的空间（一般来说一段为512个字节）
 *当内存不够时，再申请一段连续空间连接在队列上
 *deque的平均效率介于vector和list之间，也支持[]运算符随机访问，因为deque需要做堆跳转，迭代器结构复杂
 *
 *vector、list、deque三者比较(内存模型决定特点)：
 *
 *vector：	连续空间	随机位置插入效率低	支持尾添加，不支持头添加	支持随机访问
 *list：	不连续		随机位置插入效率高	支持尾添加，支持头添加		不支持随机访问
 *deque：	段连续		随机位置插入效率中	支持尾添加，支持头添加		支持随机访问
 *随机访问频率高则优先选用vector，删除插入频率高优先选用list。deque则中和淡化vector和list的缺点,
 *但是deque的迭代器非常复杂，对于自加自减等操作很麻烦(没走一步都需要判断是否需要跳跃段)
 *相对于vector，deque没有capacity()和reserve()，多了pop_front()和push_front()。内部实现不同，但是操作方法(接口)相同
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
	/*简单测试*/
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