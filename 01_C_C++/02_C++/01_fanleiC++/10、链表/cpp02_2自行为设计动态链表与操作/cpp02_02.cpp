

# include <iostream>
# include <string>
using namespace std;

class Book
{
public:
	char book_name[20];//����
	char book_search_num[20];//�鼮��������
	float price;//�۸�
	int book_total_num;//��������
	int book_lend_num;//�Ѿ������Ŀ
	int book_surplus_num;//ʣ��ɽ���Ŀ
	Book * pNext;
};

Book * Creat_Book_Link(int NUM)
{
	Book * pHead=NULL,* pNewBook=NULL,* pTail=NULL;
	int i;
	for(i=0; i<NUM; ++i)
	{
		Book * pNewBook = new Book;
		cout<<"������������";
		cin>>pNewBook->book_name;
		cout<<"���������������ţ�";
		cin>>pNewBook->book_search_num;
		cout<<"�����������������Ŀ��";
		cin>>pNewBook->book_total_num;
		cout<<"������������ѽ����Ŀ��";
		cin>>pNewBook->book_lend_num;
		cout<<"�������������Ӧ�ο��۸�";
		cin>>pNewBook->price;
		pNewBook->book_surplus_num = pNewBook->book_total_num - pNewBook->book_lend_num;

		if(NULL == pHead)
		{
			pHead = pNewBook;
			pTail = pNewBook;
		}
		else
		{
			pTail->pNext = pNewBook;
			pTail = pNewBook;
		}
		pTail->pNext = NULL;
	}
	return pHead;
}

void Show_Boook_Message(Book * pHead)
{
	Book * p = pHead;
	for(p;p;p=p->pNext)
	{
		cout<<"������"<<p->book_name<<"\t���������ţ�"<<p->book_search_num<<"\t�ο��۸�"<<p->price;
		cout<<"\t����Ŀ��"<<p->book_total_num<<"\t�����Ŀ��"<<p->book_lend_num<<"\tʣ��ɽ���Ŀ��"<<p->book_surplus_num;
		cout<<endl;
	}
}
int main (void)
{
	Book * pHead = NULL;
	int book_type_num;
	cout<<"��������Ҫ�������鼮�������"<<endl;
	cin>>book_type_num;
	pHead = Creat_Book_Link(book_type_num);
	cout << "ͼ����Ϣ������ʾ��"<<endl;
	system("cls");
	Show_Boook_Message(pHead);
	return 0;
}