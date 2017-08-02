#include<iostream>
#include<list>
#include<algorithm>

#pragma warning(disable:4305)//忽略float->double类型不匹配的警告
using namespace std;

/*
 * list:底层为双向链表，不支持[]运算符
 * forward_list:底层为单向链表（操作都在链表头），C++11新标准，效率更高！？
*/

//定义与初始化，构造函数
struct Node{
	Node(int a = 0,float s = 0):age(a),socre(s){}
	bool operator==(const Node& another){//不加const参数类型不匹配，编译出错
		if (this->age == another.age && this->socre == another.socre)
			return true;
		else
			return false;
	}
	bool operator<(Node &another){//重载符号与if中的符号是否匹配也决定是从小到大，还是从大到小
		if (this->age < another.age)//根据年龄，if(this->score < another.socre)根据分数
			return true;
		else
			return false;
	}
	int age;
	float socre;
};
void trav(Node data)
{
	cout << "age:" << data.age << "\tsocre:" << data.socre << "\n";
}
/*定义与初始化*/
void ListDefineAndConstructor(void)
{
	list<Node> ls1(5);//C++不需要加struct,创建5个节点，默认初始化为0，不加参数则头指针为空
	for_each(ls1.begin(),ls1.end(),trav);

	Node newnode = {20, 95.5};
	list<Node> ls2(5, newnode);//指定出初始化值
	for_each(ls2.begin(), ls2.end(), trav);

	list<Node> ls3(ls1);//用其他对象初始化该对象
	for_each(ls3.begin(), ls3.end(), trav);

	//用其它对象的一段来初始化，参数为迭代器
	//注意:list模板类中没有重载“+”和“-”，因为“+”和“-”属于偏移操作，
	//但对于非连续空间(list)的偏移无意义（能重载但没有这样做）,但自加自减不属于偏移，所以被重载
	list<Node> ls4(++ls2.begin(), --ls2.end());
	for_each(ls4.begin(), ls4.end(), trav);
}
//容量与大小
void ListCapacityAndSize(void)
{
	//由于链表不存在数组、字符串那样空间增加时的，释放原有小的空间
	//重新申请所有容量的问题,所以List不存在容量问题,故不存在capacity()函数与reserve()函数

	Node newnode = { 20, 95.5 };
	list<Node> ls(5, newnode);
	for_each(ls.begin(), ls.end(), trav);
	cout << "size:" << ls.size() << endl;

	ls.resize(3);
	for_each(ls.begin(), ls.end(), trav);
	cout << "size:" << ls.size() << endl;

	ls.resize(8);
	for_each(ls.begin(), ls.end(), trav);
	cout << "size:" << ls.size() << endl;

	cout << ls.empty();	ls.resize(0);	cout << ls.empty()<<endl;
	cout << ls.max_size() << endl;//返回list能容纳的最大元素个数
}
//输出与添加
void ListCoutAndAddition(void)
{
	//输出
	Node newnode = { 20, 80.5 };
	list<Node> ls(5, newnode);
	for (list<Node>::iterator ite = ls.begin(); ite != ls.end(); ite++)
		cout << "age:" << ite->age << "socre:" << ite->socre << endl;
	cout << endl;

	cout << "back.age:" << ls.back().age << "\tback.score:" << ls.back().socre << endl;//back()返回尾节点的引用
	cout << "front.age:"<< ls.front().age << "\tfront.score:" << ls.front().socre << endl;//front()返回头节点的引用

	list<Node> ls2;
	//头添加和尾添加
	ls2.push_front(newnode);//这种写法需要先创建newnode、再初始化共两步骤
	ls2.push_front(Node(19, 90.5));//这种写法只需一步，但需要在结构体中重载构造函数。头添加
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.push_back(Node(21, 88.5));//尾添加
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;

	/*中间添加*/
	list<Node>::iterator ite = ls2.begin();
	ls2.insert(++ite, Node(18,89.9));//添加一个到迭代器指定位置之前
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.insert(ite, 2, Node(17, 78.4));///添加指定个数的相同节点到指定迭代器位置
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.insert(++ls2.begin(), ++ls.begin(), --ls.end());//在指定迭代器位置之前添加某链表的中间一段
	//ls2.insert(++ls2.begin(), ++ls2.begin(), --ls2.end());//测试是否是整体插入
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	/*
	 *注意：
	 *需要添加的中间段是先全部拷贝，再整体插入，而不是一个一个插入
	 *我们用自身的中间段就可以测试，如果是一个一个插入，会陷入死循环，
	 *由于测试没有陷入死循环，所以是整体拷贝再插入
	*/
}
//删除和修改
void ListDeleteAndChange(void)
{
	list<Node> ls;
	ls.push_back(Node(18, 88.5));	ls.push_back(Node(18, 88.5));	ls.push_back(Node(19, 83.5));
	ls.push_back(Node(17, 85.5));	ls.push_back(Node(19, 83.5));	ls.push_back(Node(17, 85.5));
	for_each(ls.begin(), ls.end(), trav);

	/*删除，删除函数的本质都是调用了erase()函数*/
#if 0
	cout << "\n删除尾节点:" << endl;
	ls.pop_back();//尾删除
	cout << "\n删除头节点:" << endl;
	ls.pop_front();//头删除
	cout << "\n删除中间一个:" << endl;
	ls.erase(++ls.begin());//删除指定迭代器位置元素
	cout << "\n删除中间一段:" << endl;
	ls.erase(++ls.begin(), --ls.end());//删除指定的一段
	cout << "\n删除所有节点:" << endl;
	ls.clear();
	cout << "\n删除指定值的节点:" << endl;
	ls.remove(Node(17, 85.5));
	//remove()本质是for循环里判断是否相等，并且调用erase()函数删除，那么就需要在struct或class中重载==运算符
#endif
	cout << "\n剔除重复值节点:" << endl;//注意：unique只能剔除连续的重复值，若重复值不连续则不能检测出来并剔除	
	ls.unique();
	for_each(ls.begin(), ls.end(), trav);	

	list<Node> ls2(5,Node(15,90));
	/*修改assign()*/
	cout << "用另外的链表的一段来为ls赋值(覆盖替换)：" <<endl;
	ls.assign(ls2.begin(), ls2.end());
	for_each(ls.begin(), ls.end(), trav);
	cout << "用num个相同节点来为ls赋值(覆盖替换)：" << endl;
	ls.assign(5, Node(20, 99));
	for_each(ls.begin(), ls.end(), trav);
}

//其它操作函数
void ListOtherFunction(void)
{
#if 0
	/*交换*/
	list<Node> ls1(5, Node(20,99));
	list<Node> ls2(5, Node(21,89));
	cout << "交换前：" << endl;
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "ls1:" << endl;
	for_each(ls2.begin(), ls2.end(), trav);

	ls1.swap(ls2);
	cout << "交换后：" << endl;
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "ls1:" << endl;
	for_each(ls2.begin(), ls2.end(), trav);
#endif 
#if 0
	/*倒置*/
	list<Node> ls1;
	ls1.push_back(Node(5, 5));	ls1.push_back(Node(21, 21));
	ls1.push_back(Node(13, 13));	ls1.push_back(Node(40, 40));
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "倒置后：" << endl;
	ls1.reverse();//倒置函数
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "排序后：" << endl;
	/*排序：sort()成员函数，注意与算法库中的sort()区分*/
	ls1.sort();//需要重载比较运算符号，并且重载条件根据需要选择
	/*排序是升序还是降序，可以在重载运算符中实现*/
	for_each(ls1.begin(), ls1.end(), trav);
#endif 
#if 1
	/*合并*/
	list<Node> ls1;
	ls1.push_back(Node(50, 50));	ls1.push_back(Node(60, 60));
	ls1.push_back(Node(70, 70));	ls1.push_back(Node(80, 80));
//	ls1.reverse();

	list<Node> ls2;
	ls2.push_back(Node(55, 55));	ls2.push_back(Node(65, 65));
	ls2.push_back(Node(75, 75));	ls2.push_back(Node(85, 85));
//	ls2.reverse();

	ls1.merge(ls2);//也需要重载比较运算符
	/*
	 *merge()函数的几点注意事项：
	 *①链表必须有序(升序或降序二者必须统一)
	 *②需要运算符重载(“>”或“<”与升序或降序必须对应) 
	 *③重载的实现函数中，声明与实现必须对应，即若重载"<"则if中也必须是"<"
	 *void merge( list &lst );//只具备升序的两个链表合并
	 *void merge( list &lst, Comp compfunction );
	*/
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
#endif
	/*拼接，splice()函数，与vector基本相同*/
	/*比较的运算符，如果遇到类或结构体还需要自己重载一遍，否则就直接可以使用默认的重载的*/
}

//查找的算法函数
void ListFindNode(void)
{
	list<Node> ls;
	ls.push_back(Node(18, 88.5));	ls.push_back(Node(18, 88.5));	ls.push_back(Node(19, 83.5));
	ls.push_back(Node(17, 85.5));	ls.push_back(Node(19, 83.5));	ls.push_back(Node(17, 85.5));
	for_each(ls.begin(), ls.end(), trav);

	/*这里也需要重载==运算符*/
	list<Node>::iterator ite = find(ls.begin(), ls.end(), Node(17, 85.5));//返回找到的第一节点的迭代器
	//cout << "ite->age:" << ite->age << "\tite->score:" << ite->socre << endl;
}
int main(void)
{
	//ListDefineAndConstructor();
	//ListCapacityAndSize();
	//ListCoutAndAddition();
	//ListDeleteAndChange();
	//ListOtherFunction();
	ListFindNode();

	system("pause");
	return 0;
}