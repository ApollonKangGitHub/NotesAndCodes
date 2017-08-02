/*
 * 2017��3��31��20:45:00
*/
#include<iostream>
#include<string>
#include<algorithm>
#include<functional>

using namespace std;
#pragma warning(disable:4101)//����4101���漴Ϊ���õľֲ���������
#pragma warning(disable:4996)//����4996���漴string::copy()�Ĳ���ȫ���棬����Ԥ����������_SCL_SECURE_NO_WARNINGSЧ����ͬ

/*�����ʼ����string�Ĺ������뿽����������empty()*/
void StrDefineInit(void)
{
	string str1;//�޲������캯��--string();
	cout << str1 << endl;
	cout << "str1:" << str1.empty() << endl;//empty()Ϊ�շ���true(1)����Ϊ�շ���false(0)

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
	* str4��str5����length��10����100���ԣ����������size()�Թ۲�
	* ��һ����ʽ(str4)�����length����str.size(),��lengthΪ׼�����Կ��ܻ������Խ������
	* �ڶ�����ʽ(str5)����str�ĵ�index����ʼ�㣬����length��,���length����str.size()-index��
	* ��str.size()-indexΪ���ޣ����Բ���Խ�磬���Ϊ�˰�ȫ�����
	* ��string str(string &str, 0, length)����string str( const char *str, length );
	* ע��:���Է��֣����������ĵ�һ��������һ��Ϊָ�룬һ��Ϊ����(���ñ�ָ�밲ȫ)
	*/

	string str6(str5);//copy constructor
	cout << str6 << endl;
}
/*���Բ�������
 *������capacity()����������reserve()�޸�������
 *��С��size()��length()���Դ�С��resize()�޸��ַ�����������С���������п�����������*/
void StrAttribute(void)
{
	/*
	 * ����(capacity)���С(size/length)
	 * length()�ǵ�ǰ�ַ����ĳ���(����ʹ�õĴ�С)
	 * size()������ַ��ĸ�������length()һ��,�����ԡ�\0��Ϊ׼����������\0��
	 * �����ǵ�ǰ�Ѿ�������ڴ�(���ܵĴ�С)
	 * ����VS���뻷��������Ŀռ��СΪ��((str.size()/16) * 16 + 15)��������С15����ÿ���һ������16��
	 * ����VC++6.0������Ŀռ��СΪ��((str.size()/32) * 32+ 31)��������С31����ÿ���һ������32��
	*/

	string test(12,'a');/*0�����λ���1��15��16��31��32��47��48��63��64��79��80��95...����*/
	test = "hello everyone!";
	//test = "hello \0 everyone!";
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	test.reserve(40);//�����޸�������С��ֻ�������ܼ�С
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	cout << test << endl;
	test.resize(5);//���ַ����ض�
	test.resize(50);//�����ַ���
	cout << "test size:" << test.size() << ",test length:" << test.length() << ",capacity:" << test.capacity() << endl;
	cout << test << endl;
}
/*���*/
void StrCout(void)
{
	/*����ַ���*/
	string str("hello world!");
	cout << str << endl;//���ʱ�õ������ص�<<���ǰ�������
	cout << str.c_str() << endl;//��������char*��ָ���Աͨ��c_str()���أ��ǰ��ַ�������
	
	/*��������ַ�*/
	for (unsigned int i = 0; i < str.size(); i++)
		cout << str[i];//[]�����ع�������Խ�磬��������
	cout << endl;
	try{
		for (unsigned int i = 0; i < str.size(); i++){
			cout << str.at(i);//ֱ�ӷ����ַ���Խ����׳�һ��out_of_range���ࣩ�쳣
		}
		cout << endl;
	}
	//out_of_range
#if 0
	class out_of_range : public logic_error{
		...//������Ա
	protected:virtual void _Doraise() const{ _RAISE(*this); }//��������
	};
#endif
	catch (out_of_range & a){//���д����쳣������Ҫϵͳ�ж��쳣
		cout << endl;
		cout << "out of range"<< endl;
	}
}
/*string���޸ģ�[]/at()�޸��ַ���insert()���롢append()ƴ�ӡ�>>/=/assign()��ֵ*/
void StrChange(void)
{
	/*�޸�*/
	string str("abcdefghijk");
	cout << str << endl;
	str[3] = 's';
	cout << str << endl;
	str.at(3) = 'q';
	cout << str << endl;

	/*����:insert()*/
	str.insert(3," HELLO WORLD ");
	cout << str << endl;
	str.insert(3, " KANG RUO JIN ", 5);
	cout << str << endl;
	/*�滻:replace()*/
	str.replace(0, 3, "YUAN JIA YU");//���µ��ַ����滻���±�Ϊ0��ʼ��3���ַ�
	cout << str << endl;
	str.replace(str.find_first_of('G')+1, 1, " RUO JIN");
	cout << str << endl;
	/*ɾ��:erase()*/
	str.erase(str.find_first_of('H'),20);
	cout << str << endl;
	/*��ֵ:assign()*/
	str.assign("YUAN JIA YU");
	cout << str << endl;
	str.assign("I am Kangruojin, I miss you", 0, 16);
	cout << str << endl;

	/*ĩβƴ�ӣ�append()*/
	str.append("I LOVE YOU");
	cout << str << endl;
	str.append("and I MISS YOU", 3, 11);
	cout << str << endl;
}
/*�Ƚϡ����ҡ������ִ���������*/
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
	//index2��length2����str��index��length�����Լ��������ߣ�
#endif
	cout << "Compare function:" <<endl;
	cout << str1.compare(str2) << str1.compare(str3) << str1.compare(str4) << endl;
	cout << str1.compare(0,2,str2) << str1.compare(0,3,str3) << str1.compare(0,4,str4) << endl;
	cout << str1.compare(0, 2, str2, 0, 3) << str1.compare(1, 4, str3, 1, 4) << str1.compare(0, 4, str4, 0, 4) << endl;

	//char *buf = new char[4];
	char buf[4] = {0};
	/*copy�ǽ�string�����е�ĳһ�Σ����Ƴ����������ǽ�buffer���ǵ�string������ַ�������ȥ*/
	str1.copy(buf, 3, 0);//size_type copy( char *str, size_type num, size_type index );
	cout << buf << endl;

	cout << str1.find(buf) << (int)str1.find(buf, 1) << endl;//�ҵ�����ƥ�䵽���ִ���һ���ַ����±꣬û�ҵ�����-1��Ĭ�ϲ���ҵ���ʼλ��Ϊ0
	cout << str1.find('b') << (int)str1.find('b',3) << endl;

	string str("KANG RUO JIN LOVE YUAN JIA YU!");
	cout << str.substr(0, str.find_last_of('L')) << endl;//����ָ��λ�ô�С���ִ�
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
 *string�����ĵ��������������ʧЧ�����⣬begin()������end()����
 *����ͬһ�������������ڲ�ͬ����Ԫ�صĶ����ϣ�
 *��������������һ�����ڸ�����ͨ�õ�ָ�룬���������������Ԫ������������
 *���������������㷨��������ϵ����������ֲ��ԣ���������Ҫ�����ã���ȻҲ����һ������(ͨ��ָ��)
 */
void StrIterator(void)
{
	string str("KANG RUO JIN");
	string str2("YUAN JIA YU!");
	string::iterator ite;
	//������һ��string�����ĵ�����,string��ite��������һ��char*��ָ��,�÷�Ҳ����
	//����˵�Ƕ�����һ��ָ��string����Ԫ�ص�ָ��
	//��ͬ���͵�����������������Ƕ�Ӧ������ָ��
	ite = str.begin();//iterator begin()����str��һ���ַ��ĵ�����

	/*ͨ�������������ֱ�����ʽ*/
	for (size_t i = 0; i < str.size(); i++){
		cout << ite[i];//��ʽ��
		//cout << *(ite + i);//��ʽ��
		ite[i] = str2.c_str()[i];//�����������ܱ�����Ҳ���޸�
	}
	cout << endl;

	for (ite; ite != str.end(); ite++)//��ʽ�ۣ�end()�������һ���ַ�����һ��
		cout << *ite;//��������޸�֮���
	cout << endl;

	//��str�Ŀռ�ı�ʱ����������ʧЧ
	str += "KANG RUO JIN!";
	//str����ռ�����ԭ����15���ռ����ӵ�31����ԭ�����ڴ汻�ͷ�(��������Ե���:�����ռ�)��
	//�µ�31�ֽڵ��׵�ַ���ظ�str
	//��ô��iteָ���ԭ�еĵ�ַ�Ĳ����ͻᷢ���������Ե�����ռ䷢���ı�����޸�ָ�����ĵ�����
	#if 1
	ite = str.begin();
	#endif
	cout << ite[0] << endl;
}
/*string�����������ص���������*/
void StrIteratorOtherFunc(void)
{
	/*append()���*/
	string str1("KANG RUO JIN ");
	string str2("LOVE YUAN JIA YU!");
	str1.append(str2.begin(), str2.end());//����ԭ�ͣ�basic_string &append( input_iterator start, input_iterator end );
	cout << str1<< endl;

	/*erase()ɾ��*/
	// iterator erase( iterator pos );
	//iterator erase(iterator start, iterator end);
	str1.erase(str1.begin(),str1.begin()+str1.find("LOVE"));
	str1.erase(str1.begin()+str1.find_first_of(' '), str1.end());
	cout << str1 << endl;

	/*insert()���룬����ǰ��*/
	//iterator insert( iterator i, const char &ch );//����һ���ַ�
	//void insert( iterator i, size_type num, const char &ch );//����num���ַ�ch
	//void insert(iterator i, iterator start, iterator end);//����һ���ַ���
	str1.insert(str1.end(), ' ');
	str1.insert(str1.end(), 2, 'Y');
	str1.insert(str1.begin(), str2.begin(), str2.end());
	cout << str1 << endl;
}

/*�㷨*/
void func(char c){ cout << c; }
void StrAlgorithm(void)
{
	/*����ַ�*/
	string str("KANGRUOJIN");
	for_each(str.begin(), str.end(), func);//func()Ϊ���������еľ������
	//for_each()Ϊalgorithm�㷨ͷ�ļ��е�ģ��:
	//UnaryFunction for_each(iterator start, iterator end, UnaryFunction f);
	cout << endl;

	//void sort(iterator start, iterator end);
	//void sort(iterator start, iterator end, StrictWeakOrdering cmp);//������Ϊ�º���
	sort(str.begin(),str.end());//Ĭ�ϴ�С��������
	for_each(str.begin(), str.end(), func);//�������ٴα������
	cout << endl;

	sort(str.begin(), str.end(), greater<char>());//�Ӵ�С����,���÷º���
	for_each(str.begin(), str.end(), func);//�������ٴα������
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