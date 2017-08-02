

# include <iostream>
# include <string>
using namespace std;

class Book
{
public:
	char book_name[20];//书名
	char book_search_num[20];//书籍检索号码
	float price;//价格
	int book_total_num;//该书总数
	int book_lend_num;//已经借出数目
	int book_surplus_num;//剩余可借数目
	Book * pNext;
};

Book * Creat_Book_Link(int NUM)
{
	Book * pHead=NULL,* pNewBook=NULL,* pTail=NULL;
	int i;
	for(i=0; i<NUM; ++i)
	{
		Book * pNewBook = new Book;
		cout<<"请输入书名：";
		cin>>pNewBook->book_name;
		cout<<"请输入书名检索号：";
		cin>>pNewBook->book_search_num;
		cout<<"请输入该书名的总数目：";
		cin>>pNewBook->book_total_num;
		cout<<"请输入该书名已借出数目：";
		cin>>pNewBook->book_lend_num;
		cout<<"请输入该书名对应参考价格：";
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
		cout<<"书名："<<p->book_name<<"\t书名检索号："<<p->book_search_num<<"\t参考价格："<<p->price;
		cout<<"\t总数目："<<p->book_total_num<<"\t借出数目："<<p->book_lend_num<<"\t剩余可借数目："<<p->book_surplus_num;
		cout<<endl;
	}
}
int main (void)
{
	Book * pHead = NULL;
	int book_type_num;
	cout<<"请输入您要创建的书籍类别数："<<endl;
	cin>>book_type_num;
	pHead = Creat_Book_Link(book_type_num);
	cout << "图书信息如下所示："<<endl;
	system("cls");
	Show_Boook_Message(pHead);
	return 0;
}