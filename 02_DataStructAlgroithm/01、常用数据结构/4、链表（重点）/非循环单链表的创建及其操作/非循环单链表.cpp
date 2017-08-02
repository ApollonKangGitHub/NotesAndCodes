# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef struct Node 
{
	int data;//������
	struct Node * pNext;//ָ����
}NODE,* PNODE;//NODE�ȼ���struct Node ,PNODE�ȼ���struct Node * 

PNODE create_list(void);//����
void traverse_list(PNODE pHead);//���
bool is_empty(PNODE pHead);//�ж��Ƿ�Ϊ��
int length_list(PNODE);//����
bool insert_list(PNODE, int pos, int val);//����
bool delete_list(PNODE pHead, int pos, int * pVal);//ɾ��
void sort_list(PNODE pHead);//����

int main (void)
{

	PNODE pHead = NULL;//�ȼ��� struct Node * pHead = NULL
	int pos;
	int val;

	pHead = create_list();// create_list()���ܣ�����һ����ѭ�������������������ͷ���ĵ�ַ����pHead
	printf("��������Ϊ��\n");
	traverse_list(pHead);


	if(is_empty(pHead))
		printf("����Ϊ��!\n");
	else
		printf("����Ϊ��!\n");

	
	int len = length_list(pHead);
	printf("�������ǣ�%d\n",len);

	sort_list(pHead);
	printf("�������������Ϊ��\n");
	traverse_list(pHead);



	insert_list(pHead, pos, val);
	printf("������������Ϊ��\n");
	sort_list(pHead);
	traverse_list(pHead);

	if(delete_list(pHead, pos, &val))
	{
		printf("ɾ���ɹ�����ɾ����Ԫ����:%d\n",val);
	}
	else
	{
		printf("ɾ��ʧ��!\n");
	}
	printf("����Ԫ��ɾ��������Ϊ��\n");
	traverse_list(pHead);

	return 0;
}

PNODE create_list(void)
{
	int len;//���������Ч�ڵ�ĸ���
	int i;
	int val;//������ʱ����û�����Ľڵ��ֵ

	PNODE pHead = (PNODE)malloc(sizeof(NODE));//�����һ���������Ч���ݵ�ͷ���
	if(NULL == pHead)
	{
		printf("����ʧ�ܣ�������ֹ��\n");
		exit(-1);
	}
	PNODE pTail = pHead;
	pTail->pNext = NULL;

	printf("��������Ҫ���ɵ�����ڵ������len=");
	scanf("%d",&len);

	for(i=0;i<len;i++)
	{

		printf("�������%d���ڵ��ֵ:",i+1);
		scanf("%d",&val);

		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("����ʧ�ܣ�������ֹ��\n");
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

//	printf("��������Ϊ��\n");
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
/*��PNODE��ָ������ĵ�pos���ڵ��ǰ�����һ���µĽڵ㣬�ýڵ��ֵΪval������posֵ��1��ʼ*/
bool insert_list(PNODE pHead, int pos, int val)
{
	int i = 0;
	PNODE p = pHead;

	printf("���������Ԫ�ص�λ��pos������val:");
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
		printf("����ʧ�ܣ�������ֹ��\n");
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

	printf("��������Ҫɾ����Ԫ��λ��pos:");
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
//ɾ��p�ڵ������Ǹ��ڵ�
	p->pNext = p->pNext->pNext;
	free(q);
	q = NULL;

	return true;
}