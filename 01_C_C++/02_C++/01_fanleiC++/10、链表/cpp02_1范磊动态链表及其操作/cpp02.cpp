/*
	2016��9��10��13:13:27
	��̬����C++ʵ��
	//str���������string��c_str()��������C++���͵��ַ���ת��ΪC�������͵��ַ���
	//ctoiΪC���Եĺ������ú�����C���������ַ���ת��Ϊ����
	//atof�ὫC���������ַ���ת��Ϊ������
*/
# include <iostream>
# include <string>

using namespace std;

class Book
{
public:
	float num;
	float price;
	Book * pNext;
};

Book * pHead = NULL;
bool check(string str)//���������ж�
{
	for(int i=0; i<str.length(); i++)
		if((str[i]>'9' || str[i]<str.length()) && (str[i]!='.'))
			return false;
	return true;
}
Book * Creat()//��������
{
	Book *p, *q;
	p = new Book;
	q = pHead = p;

	cout << "������ͼ��ı�ţ���0������";
	string str;
	cin >> str;
	while(!check(str))	{
		cout << "����Ĳ������֣�����������,��0���أ�" << endl;
		cin >> str;
	}
	p->num = atoi(str.c_str());
	
	if(p->num !=0)	{
		cout<<"������ͼ��ļ۸�";
		cin >> str;
		while(!check(str))	{
			cout << "����Ĳ������֣����������룺";
			cin >> str;
		}
		p->price = atof(str.c_str());
	}
	else{
		delete p;
		q = q->pNext = pHead = NULL;
		return pHead;
	}

	while(p->num != 0){
		q = p;
		p = new Book;
		cout << "������ͼ��ı�ţ���0������";
		cin >> str;
		while(!check(str)){
			cout << "����Ĳ������֣����������룺";
			cin >> str;
		}
		p->num = atoi(str.c_str());

		if(p->num !=0){
			cout<<"������ͼ��ļ۸�";
			cin >> str;
			while(!check(str))	{
				cout << "����Ĳ������֣����������룺";
				cin >> str;
			}
			p->price = atof(str.c_str());//�Ὣ�ַ���ת��Ϊ������
		}
		q->pNext = p;
	}
	delete p;
	q->pNext = NULL;

	return pHead;
}

void Show_Book(Book * pHead)//����
{
	Book * p = pHead;
	cout<<"ͼ����Ϣ���£�"<<endl;
	while(p)
	{
		cout << "ͼ���ţ�" << p->num <<"\tͼ��۸�" <<p->price << endl;
		p =  p->pNext;
	}
}

void Delete(Book *pHead,int num)
{
	Book *l;
	if(pHead->num ==num)
	{
		l = pHead;
		::pHead=pHead->pNext;//��һ��pHeadΪȫ�ֵ�ͷָ�룬�ڶ���Ϊ�ֲ���ͷָ��
		delete l;
		cout << "�����ɹ���"<<endl;
		return;
	}
	while(pHead)
	{
		if(pHead->pNext == NULL)
		{
			cout << "�Ҳ���Ҫɾ���ı�ţ�"<<endl;
			return;
		}
		if(pHead->pNext->num == num)
		{
			l=pHead->pNext;
			pHead->pNext = l->pNext;
			delete l;
			cout << "�����ɹ���" <<endl;
			return;
		}
		pHead=pHead->pNext;
	}
	cout << "�Ҳ���Ҫɾ���ĵĽڵ㣡" << endl;
}
void insert(Book*pHead,int num,float price)//β��
{
	Book*list = new Book;
	Book*l;
	while(pHead)
	{
		l = pHead;
		pHead = pHead->pNext;
	}
	l->pNext = list;
	list->num = num;
	list->price = price;
	list->pNext = NULL;
}
int GetBookNum(Book*pHead)
{
	int num = 0;
	for(pHead;pHead;pHead=pHead->pNext)
	{
		++num;
	}
	return num;

}
int main (void)
{
	pHead = Creat();
	Show_Book(pHead);
	cout <<"��������Ҫɾ����ͼ���ţ�"<<endl;
	int BookNum;
	cin >> BookNum;

	Delete(pHead,BookNum);
	Show_Book(pHead);

	cout<<"��������Ҫ�����ͼ��۸�"<< endl;
	float BookPrice;
	cin >> BookPrice;
	insert(pHead,BookNum,BookPrice);
	Show_Book(pHead);

	int BookAllNum = GetBookNum(pHead);
	cout << "ͼ������Ϊ��" << BookAllNum <<endl;
	return 0;
}