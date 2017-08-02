# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node 
{
	int data;//数据域
	struct Node * pNext;//指针域
}NODE,* PNODE;//NODE等价于struct Node ,PNODE等价于struct Node * 

PNODE create_list(void);//创建
void traverse_list(PNODE pHead);//输出
bool is_empty(PNODE pHead);//判断是否为空
int length_list(PNODE);//长度
bool insert_list(PNODE, int pos, int val);//插入
bool delete_list(PNODE pHead, int pos, int * pVal);//删除
void sort_list(PNODE pHead);//排序

int main (void)
{

	PNODE pHead = NULL;//等价于 struct Node * pHead = NULL
	int pos;
	int val;

	pHead = create_list();// create_list()功能：创建一个非循环单链表，并将该链表的头结点的地址赋给pHead
	printf("链表内容为：\n");
	traverse_list(pHead);


	if(is_empty(pHead))
		printf("链表为空!\n");
	else
		printf("链表不为空!\n");

	
	int len = length_list(pHead);
	printf("链表长度是：%d\n",len);

	sort_list(pHead);
	printf("链表排序后内容为：\n");
	traverse_list(pHead);



	insert_list(pHead, pos, val);
	printf("链表插入后内容为：\n");
	sort_list(pHead);
	traverse_list(pHead);

	if(delete_list(pHead, pos, &val))
	{
		printf("删除成功，您删除的元素是:%d\n",val);
	}
	else
	{
		printf("删除失败!\n");
	}
	printf("链表元素删除后内容为：\n");
	traverse_list(pHead);

	return 0;
}

PNODE create_list(void)
{
	int len;//用来存放有效节点的个数
	int i;
	int val;//用来临时存放用户输入的节点的值

	PNODE pHead = (PNODE)malloc(sizeof(NODE));//存放了一个不存放有效数据的头结点
	if(NULL == pHead)
	{
		printf("分配失败，程序终止！\n");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL;

	printf("请输入您要生成的链表节点个数：len=");
	scanf("%d",&len);

	for(i=0;i<len;i++)
	{

		printf("请输入第%d个节点的值:",i+1);
		scanf("%d",&val);

		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("分配失败，程序终止！\n");
			exit(-1);
		}

		pNew->data = val;
		pNew->pNext = NULL;
		pTail = pTail->pNext = pNew;	
	}
	system("cls");
	return pHead;
}
void traverse_list(PNODE pHead)
{

//	printf("链表内容为：\n");
	PNODE p = pHead->pNext;
	while(NULL != p)
	{
		printf("%d ",p->data);
		p = p->pNext;
	}
	printf("\n");

	return;
}

bool is_empty(PNODE pHead)
{
	if(pHead->pNext == NULL)
		return true;
	else
		return false;	
}

int length_list(PNODE pHead)
{
	 PNODE p = pHead->pNext;
	 int len=0;

	 while(NULL != p)
	 {
		len++;
		p = p->pNext;
	 }
	 return len;
}

void sort_list(PNODE pHead)
{
	int i, j, t;
	int len = length_list(pHead);
	PNODE p, q;

	for(i=0,p=pHead->pNext;i<len-1;i++,p=p->pNext)
	{
		for(j=i+1,q=p->pNext;j<len;j++,q=q->pNext)
		{
			if(p->data > q->data)
			{
				t= p->data;
				p->data = q->data;
				q->data = t;
			}
		}
	}
	return;
}
/*在PNODE所指向链表的第pos个节点的前面插入一个新的节点，该节点的值为val，并且pos值从1开始*/
bool insert_list(PNODE pHead, int pos, int val)
{
	int i = 0;
	PNODE p = pHead;

	printf("请输入插入元素的位置pos和内容val:");
	scanf("%d%d",&pos,&val);

	while (NULL!=p && i<pos-1)
	{
		p = p->pNext;
		i++;
	}

	if(i>pos-1 || NULL==p)
		return false;

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if(NULL == pNew)
	{
		printf("分配失败，程序终止！\n");
		exit(-1);
	}
	pNew->data = val;
	PNODE q = p->pNext;
	p->pNext = pNew;
	pNew->pNext = q;

	return true;

}

bool delete_list(PNODE pHead, int pos, int * pVal)
{
	int i = 0;
	PNODE p = pHead;

	printf("请输入需要删除的元素位置pos:");
	scanf("%d",&pos);

	while (NULL!=p->pNext && i<pos-1)
	{
		p = p->pNext;
		i++;
	}

	if(i>pos-1 || NULL==p->pNext)
		return false;

	PNODE q = p->pNext;
	*pVal = q->data;
//删除p节点后面的那个节点
	p->pNext = p->pNext->pNext;
	free(q);
	q = NULL;

	return true;
}