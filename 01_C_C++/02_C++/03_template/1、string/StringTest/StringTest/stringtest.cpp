/*
 * 2017年3月31日20:45:00
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<functional>

using namespace std;
#pragma warning(disable:4101)//忽略4101警告即为引用的局部变量警告
#pragma warning(disable:4996)//忽略4996警告即string::copy()的不安全警告，设置预处理器增加_SCL_SECURE_NO_WARNINGS效果相同

/*定义初始化：string的构造器与拷贝构造器、empty()*/
void StrDefineInit(void)
{
	string str1;//无参数构造函数--string();
	cout << str1 << endl;
	cout << "str1:" << str1.empty() << endl;//empty()为空返回true(1)，不为空返回false(0)

	string str2(5, 'a');//string(size_type length, char ch);
	cout << str2 << endl;
	cout << "str2:" << str2.empty() << endl;

	string str3("string is very good!");//string( const char *str );
	cout << str3 << endl;

	string str4("string is very good!", 10);//string( const char *str, size_type length );
	cout << str4 << endl;

	string str5(str3, 10, 10);//string( string &str, size_type index, size_type length );
	cout << str5 << endl;
	/*
	* str4与str5：将length从10换成100测试，可以输出其size()以观察
	* 第一个方式(str4)：如果length大于str.size(),以length为准，所以可能会有输出越界问题
	* 第二个方式(str5)：从str的第index个开始算，共计length个,如果length大于str.size()-index，
	* 以str.size()-index为上限，所以不会越界，因此为了安全起见：
	* 用string str(string &str, 0, length)代替string str( const char *str, length );
	* 注意:可以发现，以上两个的第一个参数：一个为指针，一个为引用(引用比指针安全)
	*/

	string str6(str5);//copy constructor
	cout << str6 << endl;
}
/*属性测试设置
 *容量：capacity()测试容量、reserve()修改容量；
 *大小：size()、length()测试大小，resize()修改字符个数，不减小容量，但有可能增大容量*/
void StrAttribute(void)
{
	/*
	 * 容量(capacity)与大小(size/length)
	 * length()是当前字符串的长度(即已使用的大小)
	 * size()测的是字符的个数，与length()一样,都是以“\0”为准，不包括“\0”
	 * 容量是当前已经申请的内存(即总的大小)
	 * 对于VS编译环境其申请的空间大小为：((str.size()/16) * 16 + 15)个，即最小15个，每溢出一次增加16个
	 * 对于VC++6.0其申请的空间大小为：((str.size()/32) * 32+ 31)个，即最小31个，每溢出一次增加32个
	*/

	string test(12,'a');/*0将依次换成1、15、16、31、32、47、48、63、64、79、80、95...测试*/
	test = "hello everyone!";
	//test = "hello \0 everyone!";
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	test.reserve(40);//自行修改容量大小，只能增大不能减小
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	cout << test << endl;
	test.resize(5);//将字符串截断
	test.resize(50);//扩充字符串
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	cout << test << endl;
}
/*输出*/
void StrCout(void)
{
	/*输出字符串*/
	string str("hello world!");
	cout << str << endl;//输出时用的是重载的<<，是按对象处理
	cout << str.c_str() << endl;//将类对象的char*的指针成员通过c_str()返回，是按字符串处理
	
	/*输出单个字符*/
	for (unsigned int i = 0; i < str.size(); i++)
		cout << str[i];//[]被重载过，不能越界，否则会崩溃
	cout << endl;
	try{
		for (unsigned int i = 0; i < str.size(); i++){
			cout << str.at(i);//直接返回字符，越界会抛出一个out_of_range（类）异常
		}
		cout << endl;
	}
	//out_of_range
#if 0
	class out_of_range : public logic_error{
		...//其它成员
	protected:virtual void _Doraise() const{ _RAISE(*this); }//返回引用
	};
#endif
	catch (out_of_range & a){//自行处理异常，不需要系统中断异常
		cout << endl;
		cout << "out of range"<< endl;
	}
}
/*string的修改：[]/at()修改字符、insert()插入、append()拼接、>>/=/assign()赋值*/
void StrChange(void)
{
	/*修改*/
	string str("abcdefghijk");
	cout << str << endl;
	str[3] = 's';
	cout << str << endl;
	str.at(3) = 'q';
	cout << str << endl;

	/*插入:insert()*/
	str.insert(3," HELLO WORLD ");
	cout << str << endl;
	str.insert(3, " KANG RUO JIN ", 5);
	cout << str << endl;
	/*替换:replace()*/
	str.replace(0, 3, "YUAN JIA YU");//用新的字符串替换从下标为0开始的3个字符
	cout << str << endl;
	str.replace(str.find_first_of('G')+1, 1, " RUO JIN");
	cout << str << endl;
	/*删除:erase()*/
	str.erase(str.find_first_of('H'),20);
	cout << str << endl;
	/*赋值:assign()*/
	str.assign("YUAN JIA YU");
	cout << str << endl;
	str.assign("I am Kangruojin, I miss you", 0, 16);
	cout << str << endl;

	/*末尾拼接：append()*/
	str.append("I LOVE YOU");
	cout << str << endl;
	str.append("and I MISS YOU", 3, 11);
	cout << str << endl;
}
/*比较、查找、返回字串、交换等*/
void StrOtherFunc(void)
{
	string str1("abcd");
	string str2("abce");
	string str3("abcd");
	string str4("abcc");

	/*Overloaded operator test,Only 0 and 1 results of two*/
	cout << "Overloaded operator test:" << endl;
	cout << (str1 > str2) << (str1 < str2) << (str1 == str2) << (str1 != str2) << endl;
	cout << (str1 > str3) << (str1 < str3) << (str1 == str3) << (str1 != str3) << endl;
	cout << (str1 > str4) << (str1 < str4) << (str1 == str4) << (str1 != str4) << endl;

	/*Compare function,-1, 0, 1 results of the three*/
#if 0
	int compare(const basic_string &str);
	int compare(const char *str);
	int compare(size_type index, size_type length, const basic_string &str);
	int compare(size_type index, size_type length, const basic_string &str, size_type index2, size_type length2);
	int compare(size_type index, size_type length, const char *str, size_type length2);
	//index2和length2引用str，index和length引用自己（调用者）
#endif
	cout << "Compare function:" <<endl;
	cout << str1.compare(str2) << str1.compare(str3) << str1.compare(str4) << endl;
	cout << str1.compare(0,2,str2) << str1.compare(0,3,str3) << str1.compare(0,4,str4) << endl;
	cout << str1.compare(0, 2, str2, 0, 3) << str1.compare(1, 4, str3, 1, 4) << str1.compare(0, 4, str4, 0, 4) << endl;

	//char *buf = new char[4];
	char buf[4] = {0};
	/*copy是将string对象中的某一段，复制出来；而不是将buffer覆盖到string对象的字符数组中去*/
	str1.copy(buf, 3, 0);//size_type copy( char *str, size_type num, size_type index );
	cout << buf << endl;

	cout << str1.find(buf) << (int)str1.find(buf, 1) << endl;//找到返回匹配到的字串第一个字符的下标，没找到返回-1，默认差查找的起始位置为0
	cout << str1.find('b') << (int)str1.find('b',3) << endl;

	string str("KANG RUO JIN LOVE YUAN JIA YU!");
	cout << str.substr(0, str.find_last_of('L')) << endl;//返回指定位置大小的字串
	cout << str.substr(str.find_last_of('L'), str.size() - str.find_last_of('L')) << endl;

	string S1 = "KangRuoJin";
	string S2 = "YuanJiaYu";
	cout << S1 << ":" << S2 << endl;
	S1.swap(S2);
	cout << S1 << ":" << S2 << endl;

	cout << (S1 + S2) << endl;
	cout << (S2 + S1) << endl;
}
/*
 *string容器的迭代器定义与遍历失效等问题，begin()函数、end()函数
 *由于同一个容器可以用在不同类型元素的对象上，
 *而迭代器是类似一个对于该容器通用的指针，不必区分容器里的元素是那种类型
 *迭代器是用来将算法与容器结合的向下面这种测试，不是其主要的作用，当然也算其一个功能(通用指针)
 */
void StrIterator(void)
{
	string str("KANG RUO JIN");
	string str2("YUAN JIA YU!");
	string::iterator ite;
	//定义了一个string容器的迭代器,string的ite类似于与一个char*的指针,用法也类似
	//或者说是定义了一个指向string对象元素的指针
	//不同类型的容器，其迭代器则是对应的类型指针
	ite = str.begin();//iterator begin()返回str第一个字符的迭代器

	/*通过迭代器的三种遍历方式*/
	for (size_t i = 0; i < str.size(); i++){
		cout << ite[i];//方式①
		//cout << *(ite + i);//方式②
		ite[i] = str2.c_str()[i];//迭代器不但能遍历，也能修改
	}
	cout << endl;

	for (ite; ite != str.end(); ite++)//方式③，end()返回最后一个字符的下一个
		cout << *ite;//输出的是修改之后的
	cout << endl;

	//当str的空间改变时，迭代器会失效
	str += "KANG RUO JIN!";
	//str对象空间增大，原来的15个空间增加到31个，原来的内存被释放(数组的特性导致:连续空间)，
	//新的31字节的首地址返回给str
	//那么对ite指向的原有的地址的操作就会发生错误，所以当对象空间发生改变必须修改指向对象的迭代器
	#if 1
	ite = str.begin();
	#endif
	cout << ite[0] << endl;
}
/*string类与迭代器相关的其他函数*/
void StrIteratorOtherFunc(void)
{
	/*append()添加*/
	string str1("KANG RUO JIN ");
	string str2("LOVE YUAN JIA YU!");
	str1.append(str2.begin(), str2.end());//函数原型：basic_string &append( input_iterator start, input_iterator end );
	cout << str1<< endl;

	/*erase()删除*/
	// iterator erase( iterator pos );
	//iterator erase(iterator start, iterator end);
	str1.erase(str1.begin(),str1.begin()+str1.find("LOVE"));
	str1.erase(str1.begin()+str1.find_first_of(' '), str1.end());
	cout << str1 << endl;

	/*insert()插入，均是前插*/
	//iterator insert( iterator i, const char &ch );//插入一个字符
	//void insert( iterator i, size_type num, const char &ch );//插入num个字符ch
	//void insert(iterator i, iterator start, iterator end);//插入一段字符串
	str1.insert(str1.end(), ' ');
	str1.insert(str1.end(), 2, 'Y');
	str1.insert(str1.begin(), str2.begin(), str2.end());
	cout << str1 << endl;
}

/*算法*/
void func(char c){ cout << c; }
void StrAlgorithm(void)
{
	/*输出字符*/
	string str("KANGRUOJIN");
	for_each(str.begin(), str.end(), func);//func()为遍历过程中的具体操作
	//for_each()为algorithm算法头文件中的模板:
	//UnaryFunction for_each(iterator start, iterator end, UnaryFunction f);
	cout << endl;

	//void sort(iterator start, iterator end);
	//void sort(iterator start, iterator end, StrictWeakOrdering cmp);//最后参数为仿函数
	sort(str.begin(),str.end());//默认从小到大排序
	for_each(str.begin(), str.end(), func);//排完序再次遍历输出
	cout << endl;

	sort(str.begin(), str.end(), greater<char>());//从大到小排序,采用仿函数
	for_each(str.begin(), str.end(), func);//排完序再次遍历输出
	cout << endl;
}

int main(void)
{
	//StrDefineInit();
	//StrAttribute();
	//StrCout();
	//StrChange();
	//StrOtherFunc();
	//StrIterator();
	//StrIteratorOtherFunc();
	StrAlgorithm();

	system("pause");
	return 0;
}