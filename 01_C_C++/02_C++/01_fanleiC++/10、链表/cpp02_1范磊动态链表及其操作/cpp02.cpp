/*
	2016年9月10日13:13:27
	动态链表C++实现
	//str对象调用类string的c_str()函数，将C++类型的字符串转换为C语言类型的字符串
	//ctoi为C语言的函数，该函数将C语言类型字符串转化为数字
	//atof会将C语言类型字符串转化为浮点数
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
bool check(string str)//输入类型判断
{
	for(int i=0; i<str.length(); i++)
		if((str[i]>'9' || str[i]<str.length()) && (str[i]!='.'))
			return false;
	return true;
}
Book * Creat()//创建链表
{
	Book *p, *q;
	p = new Book;
	q = pHead = p;

	cout << "请输入图书的编号，以0结束：";
	string str;
	cin >> str;
	while(!check(str))	{
		cout << "输入的不是数字，请重新输入,按0返回：" << endl;
		cin >> str;
	}
	p->num = atoi(str.c_str());
	
	if(p->num !=0)	{
		cout<<"请输入图书的价格：";
		cin >> str;
		while(!check(str))	{
			cout << "输入的不是数字，请重新输入：";
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
		cout << "请输入图书的编号，以0结束：";
		cin >> str;
		while(!check(str)){
			cout << "输入的不是数字，请重新输入：";
			cin >> str;
		}
		p->num = atoi(str.c_str());

		if(p->num !=0){
			cout<<"请输入图书的价格：";
			cin >> str;
			while(!check(str))	{
				cout << "输入的不是数字，请重新输入：";
				cin >> str;
			}
			p->price = atof(str.c_str());//会将字符串转化为浮点数
		}
		q->pNext = p;
	}
	delete p;
	q->pNext = NULL;

	return pHead;
}

void Show_Book(Book * pHead)//遍历
{
	Book * p = pHead;
	cout<<"图书信息如下："<<endl;
	while(p)
	{
		cout << "图书编号：" << p->num <<"\t图书价格：" <<p->price << endl;
		p =  p->pNext;
	}
}

void Delete(Book *pHead,int num)
{
	Book *l;
	if(pHead->num ==num)
	{
		l = pHead;
		::pHead=pHead->pNext;//第一个pHead为全局的头指针，第二个为局部的头指针
		delete l;
		cout << "操作成功！"<<endl;
		return;
	}
	while(pHead)
	{
		if(pHead->pNext == NULL)
		{
			cout << "找不到要删除的编号！"<<endl;
			return;
		}
		if(pHead->pNext->num == num)
		{
			l=pHead->pNext;
			pHead->pNext = l->pNext;
			delete l;
			cout << "操作成功！" <<endl;
			return;
		}
		pHead=pHead->pNext;
	}
	cout << "找不到要删除的的节点！" << endl;
}
void insert(Book*pHead,int num,float price)//尾插
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
	cout <<"请输入您要删除的图书编号："<<endl;
	int BookNum;
	cin >> BookNum;

	Delete(pHead,BookNum);
	Show_Book(pHead);

	cout<<"请输入您要插入的图书价格："<< endl;
	float BookPrice;
	cin >> BookPrice;
	insert(pHead,BookNum,BookPrice);
	Show_Book(pHead);

	int BookAllNum = GetBookNum(pHead);
	cout << "图书总量为：" << BookAllNum <<endl;
	return 0;
}