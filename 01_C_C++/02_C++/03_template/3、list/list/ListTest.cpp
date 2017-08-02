#include<iostream>
#include<list>
#include<algorithm>

#pragma warning(disable:4305)//����float->double���Ͳ�ƥ��ľ���
using namespace std;

/*
 * list:�ײ�Ϊ˫��������֧��[]�����
 * forward_list:�ײ�Ϊ��������������������ͷ����C++11�±�׼��Ч�ʸ��ߣ���
*/

//�������ʼ�������캯��
struct Node{
	Node(int a = 0,float s = 0):age(a),socre(s){}
	bool operator==(const Node& another){//����const�������Ͳ�ƥ�䣬�������
		if (this->age == another.age && this->socre == another.socre)
			return true;
		else
			return false;
	}
	bool operator<(Node &another){//���ط�����if�еķ����Ƿ�ƥ��Ҳ�����Ǵ�С���󣬻��ǴӴ�С
		if (this->age < another.age)//�������䣬if(this->score < another.socre)���ݷ���
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
/*�������ʼ��*/
void ListDefineAndConstructor(void)
{
	list<Node> ls1(5);//C++����Ҫ��struct,����5���ڵ㣬Ĭ�ϳ�ʼ��Ϊ0�����Ӳ�����ͷָ��Ϊ��
	for_each(ls1.begin(),ls1.end(),trav);

	Node newnode = {20, 95.5};
	list<Node> ls2(5, newnode);//ָ������ʼ��ֵ
	for_each(ls2.begin(), ls2.end(), trav);

	list<Node> ls3(ls1);//�����������ʼ���ö���
	for_each(ls3.begin(), ls3.end(), trav);

	//�����������һ������ʼ��������Ϊ������
	//ע��:listģ������û�����ء�+���͡�-������Ϊ��+���͡�-������ƫ�Ʋ�����
	//�����ڷ������ռ�(list)��ƫ�������壨�����ص�û����������,���Լ��Լ�������ƫ�ƣ����Ա�����
	list<Node> ls4(++ls2.begin(), --ls2.end());
	for_each(ls4.begin(), ls4.end(), trav);
}
//�������С
void ListCapacityAndSize(void)
{
	//���������������顢�ַ��������ռ�����ʱ�ģ��ͷ�ԭ��С�Ŀռ�
	//����������������������,����List��������������,�ʲ�����capacity()������reserve()����

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
	cout << ls.max_size() << endl;//����list�����ɵ����Ԫ�ظ���
}
//��������
void ListCoutAndAddition(void)
{
	//���
	Node newnode = { 20, 80.5 };
	list<Node> ls(5, newnode);
	for (list<Node>::iterator ite = ls.begin(); ite != ls.end(); ite++)
		cout << "age:" << ite->age << "socre:" << ite->socre << endl;
	cout << endl;

	cout << "back.age:" << ls.back().age << "\tback.score:" << ls.back().socre << endl;//back()����β�ڵ������
	cout << "front.age:"<< ls.front().age << "\tfront.score:" << ls.front().socre << endl;//front()����ͷ�ڵ������

	list<Node> ls2;
	//ͷ��Ӻ�β���
	ls2.push_front(newnode);//����д����Ҫ�ȴ���newnode���ٳ�ʼ����������
	ls2.push_front(Node(19, 90.5));//����д��ֻ��һ��������Ҫ�ڽṹ�������ع��캯����ͷ���
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.push_back(Node(21, 88.5));//β���
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;

	/*�м����*/
	list<Node>::iterator ite = ls2.begin();
	ls2.insert(++ite, Node(18,89.9));//���һ����������ָ��λ��֮ǰ
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.insert(ite, 2, Node(17, 78.4));///���ָ����������ͬ�ڵ㵽ָ��������λ��
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	ls2.insert(++ls2.begin(), ++ls.begin(), --ls.end());//��ָ��������λ��֮ǰ���ĳ������м�һ��
	//ls2.insert(++ls2.begin(), ++ls2.begin(), --ls2.end());//�����Ƿ����������
	for_each(ls2.begin(), ls2.end(), trav);
	cout << endl;
	/*
	 *ע�⣺
	 *��Ҫ��ӵ��м������ȫ����������������룬������һ��һ������
	 *������������м�ξͿ��Բ��ԣ������һ��һ�����룬��������ѭ����
	 *���ڲ���û��������ѭ�������������忽���ٲ���
	*/
}
//ɾ�����޸�
void ListDeleteAndChange(void)
{
	list<Node> ls;
	ls.push_back(Node(18, 88.5));	ls.push_back(Node(18, 88.5));	ls.push_back(Node(19, 83.5));
	ls.push_back(Node(17, 85.5));	ls.push_back(Node(19, 83.5));	ls.push_back(Node(17, 85.5));
	for_each(ls.begin(), ls.end(), trav);

	/*ɾ����ɾ�������ı��ʶ��ǵ�����erase()����*/
#if 0
	cout << "\nɾ��β�ڵ�:" << endl;
	ls.pop_back();//βɾ��
	cout << "\nɾ��ͷ�ڵ�:" << endl;
	ls.pop_front();//ͷɾ��
	cout << "\nɾ���м�һ��:" << endl;
	ls.erase(++ls.begin());//ɾ��ָ��������λ��Ԫ��
	cout << "\nɾ���м�һ��:" << endl;
	ls.erase(++ls.begin(), --ls.end());//ɾ��ָ����һ��
	cout << "\nɾ�����нڵ�:" << endl;
	ls.clear();
	cout << "\nɾ��ָ��ֵ�Ľڵ�:" << endl;
	ls.remove(Node(17, 85.5));
	//remove()������forѭ�����ж��Ƿ���ȣ����ҵ���erase()����ɾ������ô����Ҫ��struct��class������==�����
#endif
	cout << "\n�޳��ظ�ֵ�ڵ�:" << endl;//ע�⣺uniqueֻ���޳��������ظ�ֵ�����ظ�ֵ���������ܼ��������޳�	
	ls.unique();
	for_each(ls.begin(), ls.end(), trav);	

	list<Node> ls2(5,Node(15,90));
	/*�޸�assign()*/
	cout << "������������һ����Ϊls��ֵ(�����滻)��" <<endl;
	ls.assign(ls2.begin(), ls2.end());
	for_each(ls.begin(), ls.end(), trav);
	cout << "��num����ͬ�ڵ���Ϊls��ֵ(�����滻)��" << endl;
	ls.assign(5, Node(20, 99));
	for_each(ls.begin(), ls.end(), trav);
}

//������������
void ListOtherFunction(void)
{
#if 0
	/*����*/
	list<Node> ls1(5, Node(20,99));
	list<Node> ls2(5, Node(21,89));
	cout << "����ǰ��" << endl;
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "ls1:" << endl;
	for_each(ls2.begin(), ls2.end(), trav);

	ls1.swap(ls2);
	cout << "������" << endl;
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "ls1:" << endl;
	for_each(ls2.begin(), ls2.end(), trav);
#endif 
#if 0
	/*����*/
	list<Node> ls1;
	ls1.push_back(Node(5, 5));	ls1.push_back(Node(21, 21));
	ls1.push_back(Node(13, 13));	ls1.push_back(Node(40, 40));
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "���ú�" << endl;
	ls1.reverse();//���ú���
	for_each(ls1.begin(), ls1.end(), trav);
	cout << "�����" << endl;
	/*����sort()��Ա������ע�����㷨���е�sort()����*/
	ls1.sort();//��Ҫ���رȽ�������ţ�������������������Ҫѡ��
	/*�����������ǽ��򣬿����������������ʵ��*/
	for_each(ls1.begin(), ls1.end(), trav);
#endif 
#if 1
	/*�ϲ�*/
	list<Node> ls1;
	ls1.push_back(Node(50, 50));	ls1.push_back(Node(60, 60));
	ls1.push_back(Node(70, 70));	ls1.push_back(Node(80, 80));
//	ls1.reverse();

	list<Node> ls2;
	ls2.push_back(Node(55, 55));	ls2.push_back(Node(65, 65));
	ls2.push_back(Node(75, 75));	ls2.push_back(Node(85, 85));
//	ls2.reverse();

	ls1.merge(ls2);//Ҳ��Ҫ���رȽ������
	/*
	 *merge()�����ļ���ע�����
	 *�������������(���������߱���ͳһ)
	 *����Ҫ���������(��>����<���������������Ӧ) 
	 *�����ص�ʵ�ֺ����У�������ʵ�ֱ����Ӧ����������"<"��if��Ҳ������"<"
	 *void merge( list &lst );//ֻ�߱��������������ϲ�
	 *void merge( list &lst, Comp compfunction );
	*/
	cout << "ls1:" << endl;
	for_each(ls1.begin(), ls1.end(), trav);
#endif
	/*ƴ�ӣ�splice()��������vector������ͬ*/
	/*�Ƚϵ������������������ṹ�廹��Ҫ�Լ�����һ�飬�����ֱ�ӿ���ʹ��Ĭ�ϵ����ص�*/
}

//���ҵ��㷨����
void ListFindNode(void)
{
	list<Node> ls;
	ls.push_back(Node(18, 88.5));	ls.push_back(Node(18, 88.5));	ls.push_back(Node(19, 83.5));
	ls.push_back(Node(17, 85.5));	ls.push_back(Node(19, 83.5));	ls.push_back(Node(17, 85.5));
	for_each(ls.begin(), ls.end(), trav);

	/*����Ҳ��Ҫ����==�����*/
	list<Node>::iterator ite = find(ls.begin(), ls.end(), Node(17, 85.5));//�����ҵ��ĵ�һ�ڵ�ĵ�����
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