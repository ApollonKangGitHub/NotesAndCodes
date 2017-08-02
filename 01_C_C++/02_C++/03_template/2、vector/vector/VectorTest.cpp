/*
* vector向量(动态数组)容器，与string的内存分配原理是一样的：是连续的空间，
* 空间不够用时，会申请一个更大的连续空间，同时迭代器失效
* arrary数组容器：是固定数组容器，C++11标准新添加
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<ctime>

using namespace std;
//定义
void VectorDefine(void)
{
	typedef struct Student{
		int age;
		string name;
	}STU;
	//string是专门针对字符串的字符char的模板，不需要这种定义方式，但是需要知道string的本质与vector是一样的，如下：
	//typedef basic_string<char, char_traits<char>, allocator<char> > string;//vector<char> str; <==> string str;
	
 	vector<int> vet;//整型数组
	vector<STU> vet2;//结构体数组
	vector<int *> vect3;//指针数组
	vector<string> vect4;//字符串数组
}
//构造、迭代器
void VectorConstructor(void)
{
	//vector<int> vet_int;//创建一个空的int数组容器
	//cout << vet[0];//输出越界崩溃,所以注意越界问题
	//string的函数很多，但是vector的函数不是那么多，因为vector的函数参数基本都是迭代器，而下标基本不存在了，就少了许多
	//以后在除了string的操作中就尽量使用迭代器了

	/*构造初始化其它类型的数组，方式也是一样的*/
	vector<int> vet1(5);//默认初始化为0
	for (unsigned int i = 0; i < vet1.size(); i++)
		cout << vet1[i] << "\t";
	cout << endl;

	vector<int> vet2(5,12);//用vet2.size()个12初始化
	for (unsigned int  i = 0; i < vet2.size(); i++)
		cout << vet2[i] << "\t";//默认初始化为0
	cout << endl;

	vector<int> vet3(vet1);//用同类型对象初始化，（拷贝构造）
	for (unsigned int i = 0; i < vet3.size(); i++)
		cout << vet3[i] << "\t";
	cout << endl;

	vector<int>::iterator ite = vet2.begin();
	vector<int>::iterator ite1 = vet2.end();
	vector<int> vet4(ite+1, ite1-1);//用同类型对象的部分初始化，（拷贝构造）
	for (unsigned int i = 0; i < vet4.size(); i++)
		cout << vet4[i] << "\t";
	cout << endl;
}
//容量大小
void VectorCapacity(void)
{
	/*初始容量与初始化的元素个数相同*/
	vector<int> vet1;
	cout << vet1.capacity() << endl;

	/*VS:增加的容量 = 已有容量对2取整，VC++6.0：增加的容量 = 已有容量*/
	vector<int> vet2(4);
	cout << "capacity:" << "\t";
	cout << vet2.capacity() << "\t";
	for (int i = 0; i < 12; i++){
		//调用一次push_back()，在尾部增加一个元素，push_back()的参数是值
		vet2.push_back(vet2.capacity());
		cout << vet2.capacity() << "\t";
	}
	cout << endl;
	cout << "val:" << "\t";
	for (unsigned int i = 0; i < vet2.size(); i++)
		cout << vet2[i] << "\t";//
	cout << endl;

	/*reserve()函数只能增大容量不能减小容量，与string相同，会有迭代器失效问题*/
	vector<int> vet3;
	vet3.reserve(10);	cout << vet3.capacity() << endl;
	vet3.reserve(5);	cout << vet3.capacity() << endl;
	vet3.reserve(20);	cout << vet3.capacity() << endl;
	//虽然容量为20，且均初始赋值为0，但是有效元素个数为0，此时不能修改访问,否则会越界出错
	//vector<int>::iterator ite = vet3.begin();
	//*(ite+10) = 5;
	//cout << *(ite + 10) << endl;

	//只有在resize()设置有效个数之后才能访问有效的空间
	cout << "capacity:" << vet3.capacity() << "size:" << vet3.size() << endl;
	vet3.resize(15);
	cout << "capacity:" << vet3.capacity() << "size:" << vet3.size() << endl;
	vector<int>::iterator ite = vet3.begin();
	*(ite+10) = 5;
	cout << *(ite + 10) << endl;
}
void traversal(int a){
	cout << a << "\t";
}
//遍历输出
void VectorShow(void)
{
	vector<int> vet;
	/*用at()成员函数遍历*/
	for (int i = 0; i < 10; i++)
		vet.push_back(i);
	for (int i = 0; i < 10; i++)
		cout << vet.at(i) << "\t";//at()越界会抛出异常，更安全
	cout << endl;
	/*用重载的下标运算符遍历*/
	for (int i = 0; i < 10; i++)
		cout << vet[i] << "\t";//下标运算越界会崩溃
	cout << endl;
	/*利用迭代器自己写遍历*/
	vector<int>::iterator ite = vet.begin();
	for (ite; ite != vet.end(); ite++)
		cout << *ite << "\t";
	cout << endl;

	/*利用迭代器算法遍历*/
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	cout << vet.back() << endl;//返回尾元素的引用
}
//增删改查等操作
void VectorOPeration(void)
{
	/*增加，在不容量足够时，尾添加的效率比中间添加的效率要高很多*/
	vector<int> vet(10, 1);
	vet.insert(vet.begin()+5, 5, 100);//在指定位置之前加入5个100，两个参数时默认是插入1个
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vector<int> vet2;
	for (int i = 0; i < 10; i++)
		vet2.push_back(i*i);
	//将vet2的[5，10)的元素插入到vet的end()迭代器之前
	vet.insert(vet.end(), vet2.begin()+5, vet2.begin()+10);
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	/*删除*/
	vet.pop_back();//删除一个尾元素，与push_back()相对
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;
	vet.erase(vet.end()-1);//删除指定位置，参数为迭代器
	vet.erase(vet.end() - 1);
	vet.erase(vet.end() - 1);
	vet.erase(vet.end() - 1);

	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vet.erase(vet.begin()+5, vet.begin()+10);//删除[start, end)区间的元素
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vector<int> vet3(10,1);
	vet3.clear();//删除所有元素
	for_each(vet3.begin(), vet3.end(), traversal);
	cout << endl;

	/*修改：可以通过at()、[]、back()来修改*/
	/*交换*/
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;
	vet.swap(vet2);
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;

	/*重新赋值*/
	vet2.assign(vet.begin()+2, vet.end()-3);
	vet.assign(10, 20);//10个20
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;
}
/*比较运算符重载*/
void VectorCompare(void)
{
	/*比较方式与string相同，返回值为0/1*/
	vector<int> vec1(5,1);
	vector<int> vec2(5,0);
	vector<int> vec3(5,2);
	vector<int> vec4(5,1);
	cout << (vec1 > vec2) << (vec1 < vec2) << (vec1 == vec2) << (vec1 != vec2) << endl;
	cout << (vec1 > vec3) << (vec1 < vec3) << (vec1 == vec3) << (vec1 != vec3) << endl;
	cout << (vec1 > vec4) << (vec1 < vec4) << (vec1 == vec4) << (vec1 != vec4) << endl;
}
/*排序*/
void VectorSort(void)
{
	vector<int> vet;

	vet.push_back(10);
	vet.push_back(45); 
	vet.push_back(-5);
	vet.push_back(7);
	vet.push_back(3);
	vet.push_back(9);
	vet.push_back(100);
	vet.push_back(-13);
	vet.push_back(0);

	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	sort(vet.begin(), vet.end());//从小到大
	for_each(vet.begin(), vet.end(), traversal); 
	cout << endl;

	sort(vet.begin(), vet.end(), greater<int>());//从大到下
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;
}

/*随机乱序算法*/
void VectorRandOutOfOrder(void)
{
	vector<int> vet;

	vet.push_back(1);
	vet.push_back(3);
	vet.push_back(5);
	vet.push_back(7);
	vet.push_back(9);
	vet.push_back(11);
	vet.push_back(13);
	vet.push_back(15);
	vet.push_back(17);
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	srand(time(NULL));
	random_shuffle(vet.begin(), vet.end());//将有序的容器变为乱序容器,#include<algorithm>

	for_each(vet.begin(), vet.end(), traversal);//如果不加srand(time(NULL)),每次乱序输出的结果是一样的
	cout << endl;
}
int main(void)
{
	//VectorDefine();
	//VectorConstructor();
	//VectorCapacity();
	//VectorShow();
	//VectorOPeration();
	//VectorCompare();
	//VectorSort();
	VectorRandOutOfOrder();

	system("pause");
	return 0;
}