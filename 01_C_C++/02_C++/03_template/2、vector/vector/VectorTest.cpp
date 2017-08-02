/*
* vector����(��̬����)��������string���ڴ����ԭ����һ���ģ��������Ŀռ䣬
* �ռ䲻����ʱ��������һ������������ռ䣬ͬʱ������ʧЧ
* arrary�����������ǹ̶�����������C++11��׼�����
*/
#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>
#include<ctime>

using namespace std;
//����
void VectorDefine(void)
{
	typedef struct Student{
		int age;
		string name;
	}STU;
	//string��ר������ַ������ַ�char��ģ�壬����Ҫ���ֶ��巽ʽ��������Ҫ֪��string�ı�����vector��һ���ģ����£�
	//typedef basic_string<char, char_traits<char>, allocator<char> > string;//vector<char> str; <==> string str;
	
 	vector<int> vet;//��������
	vector<STU> vet2;//�ṹ������
	vector<int *> vect3;//ָ������
	vector<string> vect4;//�ַ�������
}
//���졢������
void VectorConstructor(void)
{
	//vector<int> vet_int;//����һ���յ�int��������
	//cout << vet[0];//���Խ�����,����ע��Խ������
	//string�ĺ����ܶ࣬����vector�ĺ���������ô�࣬��Ϊvector�ĺ��������������ǵ����������±�����������ˣ����������
	//�Ժ��ڳ���string�Ĳ����о;���ʹ�õ�������

	/*�����ʼ���������͵����飬��ʽҲ��һ����*/
	vector<int> vet1(5);//Ĭ�ϳ�ʼ��Ϊ0
	for (unsigned int i = 0; i < vet1.size(); i++)
		cout << vet1[i] << "\t";
	cout << endl;

	vector<int> vet2(5,12);//��vet2.size()��12��ʼ��
	for (unsigned int  i = 0; i < vet2.size(); i++)
		cout << vet2[i] << "\t";//Ĭ�ϳ�ʼ��Ϊ0
	cout << endl;

	vector<int> vet3(vet1);//��ͬ���Ͷ����ʼ�������������죩
	for (unsigned int i = 0; i < vet3.size(); i++)
		cout << vet3[i] << "\t";
	cout << endl;

	vector<int>::iterator ite = vet2.begin();
	vector<int>::iterator ite1 = vet2.end();
	vector<int> vet4(ite+1, ite1-1);//��ͬ���Ͷ���Ĳ��ֳ�ʼ�������������죩
	for (unsigned int i = 0; i < vet4.size(); i++)
		cout << vet4[i] << "\t";
	cout << endl;
}
//������С
void VectorCapacity(void)
{
	/*��ʼ�������ʼ����Ԫ�ظ�����ͬ*/
	vector<int> vet1;
	cout << vet1.capacity() << endl;

	/*VS:���ӵ����� = ����������2ȡ����VC++6.0�����ӵ����� = ��������*/
	vector<int> vet2(4);
	cout << "capacity:" << "\t";
	cout << vet2.capacity() << "\t";
	for (int i = 0; i < 12; i++){
		//����һ��push_back()����β������һ��Ԫ�أ�push_back()�Ĳ�����ֵ
		vet2.push_back(vet2.capacity());
		cout << vet2.capacity() << "\t";
	}
	cout << endl;
	cout << "val:" << "\t";
	for (unsigned int i = 0; i < vet2.size(); i++)
		cout << vet2[i] << "\t";//
	cout << endl;

	/*reserve()����ֻ�������������ܼ�С��������string��ͬ�����е�����ʧЧ����*/
	vector<int> vet3;
	vet3.reserve(10);	cout << vet3.capacity() << endl;
	vet3.reserve(5);	cout << vet3.capacity() << endl;
	vet3.reserve(20);	cout << vet3.capacity() << endl;
	//��Ȼ����Ϊ20���Ҿ���ʼ��ֵΪ0��������ЧԪ�ظ���Ϊ0����ʱ�����޸ķ���,�����Խ�����
	//vector<int>::iterator ite = vet3.begin();
	//*(ite+10) = 5;
	//cout << *(ite + 10) << endl;

	//ֻ����resize()������Ч����֮����ܷ�����Ч�Ŀռ�
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
//�������
void VectorShow(void)
{
	vector<int> vet;
	/*��at()��Ա��������*/
	for (int i = 0; i < 10; i++)
		vet.push_back(i);
	for (int i = 0; i < 10; i++)
		cout << vet.at(i) << "\t";//at()Խ����׳��쳣������ȫ
	cout << endl;
	/*�����ص��±����������*/
	for (int i = 0; i < 10; i++)
		cout << vet[i] << "\t";//�±�����Խ������
	cout << endl;
	/*���õ������Լ�д����*/
	vector<int>::iterator ite = vet.begin();
	for (ite; ite != vet.end(); ite++)
		cout << *ite << "\t";
	cout << endl;

	/*���õ������㷨����*/
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	cout << vet.back() << endl;//����βԪ�ص�����
}
//��ɾ�Ĳ�Ȳ���
void VectorOPeration(void)
{
	/*���ӣ��ڲ������㹻ʱ��β��ӵ�Ч�ʱ��м���ӵ�Ч��Ҫ�ߺܶ�*/
	vector<int> vet(10, 1);
	vet.insert(vet.begin()+5, 5, 100);//��ָ��λ��֮ǰ����5��100����������ʱĬ���ǲ���1��
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vector<int> vet2;
	for (int i = 0; i < 10; i++)
		vet2.push_back(i*i);
	//��vet2��[5��10)��Ԫ�ز��뵽vet��end()������֮ǰ
	vet.insert(vet.end(), vet2.begin()+5, vet2.begin()+10);
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	/*ɾ��*/
	vet.pop_back();//ɾ��һ��βԪ�أ���push_back()���
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;
	vet.erase(vet.end()-1);//ɾ��ָ��λ�ã�����Ϊ������
	vet.erase(vet.end() - 1);
	vet.erase(vet.end() - 1);
	vet.erase(vet.end() - 1);

	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vet.erase(vet.begin()+5, vet.begin()+10);//ɾ��[start, end)�����Ԫ��
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;

	vector<int> vet3(10,1);
	vet3.clear();//ɾ������Ԫ��
	for_each(vet3.begin(), vet3.end(), traversal);
	cout << endl;

	/*�޸ģ�����ͨ��at()��[]��back()���޸�*/
	/*����*/
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;
	vet.swap(vet2);
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;

	/*���¸�ֵ*/
	vet2.assign(vet.begin()+2, vet.end()-3);
	vet.assign(10, 20);//10��20
	cout << "vet:";		for_each(vet.begin(), vet.end(), traversal);
	cout << "vet2:";	for_each(vet2.begin(), vet2.end(), traversal);
	cout << endl;
}
/*�Ƚ����������*/
void VectorCompare(void)
{
	/*�ȽϷ�ʽ��string��ͬ������ֵΪ0/1*/
	vector<int> vec1(5,1);
	vector<int> vec2(5,0);
	vector<int> vec3(5,2);
	vector<int> vec4(5,1);
	cout << (vec1 > vec2) << (vec1 < vec2) << (vec1 == vec2) << (vec1 != vec2) << endl;
	cout << (vec1 > vec3) << (vec1 < vec3) << (vec1 == vec3) << (vec1 != vec3) << endl;
	cout << (vec1 > vec4) << (vec1 < vec4) << (vec1 == vec4) << (vec1 != vec4) << endl;
}
/*����*/
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

	sort(vet.begin(), vet.end());//��С����
	for_each(vet.begin(), vet.end(), traversal); 
	cout << endl;

	sort(vet.begin(), vet.end(), greater<int>());//�Ӵ���
	for_each(vet.begin(), vet.end(), traversal);
	cout << endl;
}

/*��������㷨*/
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
	random_shuffle(vet.begin(), vet.end());//�������������Ϊ��������,#include<algorithm>

	for_each(vet.begin(), vet.end(), traversal);//�������srand(time(NULL)),ÿ����������Ľ����һ����
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