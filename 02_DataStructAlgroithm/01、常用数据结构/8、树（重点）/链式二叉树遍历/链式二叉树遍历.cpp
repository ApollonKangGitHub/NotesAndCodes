# include <stdio.h>
# include <malloc.h>
/*Binary Tree ������*/
typedef struct BTNode
{
	char data;
	struct BTNode * pLchild;
	struct BTNode * pRchild;
}BTNODE,* PBTNODE;

void PreTraverseBTree(PBTNODE pT);
PBTNODE CreateBTree(void);
void InTraverseBTree(PBTNODE pT);
void PosTraverseBTree(PBTNODE pT);

int main (void)
{
	PBTNODE pT = CreateBTree();//CreateBTree()��̬������һ����ʽ�������������ظ��ڵ�ĵ�ַ
	
	printf("�������Ϊ��\n");	
	PreTraverseBTree(pT);//�������

	printf("�������Ϊ��\n");
	InTraverseBTree(pT);//�������

	printf("�������Ϊ��\n");
	PosTraverseBTree(pT);//�������

	return 0;
}
void PosTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//���յ�ʱ��ſ��Ա���
	{
		
		if (NULL != pT->pLchild)
		{
			PosTraverseBTree(pT->pLchild);	//pT->pLchild��������������
		}

		if (NULL != pT->pRchild)
		{
			PosTraverseBTree(pT->pRchild);
		}

		printf("%c\n",pT->data);//pT->data == pA->data
		
	}

	/*
		
		�Ⱥ��������������
		�ٺ��������������
		�ٷ��ʸ��ڵ㣻
	*/
}
void InTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//���յ�ʱ��ſ��Ա���
	{
		
		if (NULL != pT->pLchild)
		{
			InTraverseBTree(pT->pLchild);	//pT->pLchild��������������
		}

		printf("%c\n",pT->data);//pT->data == pA->data

		if (NULL != pT->pRchild)
		{
			InTraverseBTree(pT->pRchild);
		}
		
	}

	/*
		�����������������
		�ٷ��ʸ��ڵ㣻
		�����������������
	*/
}
void PreTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//���յ�ʱ��ſ��Ա���
	{
		printf("%c\n",pT->data);//pT->data == pA->data
		
		if (NULL != pT->pLchild)
		{
			PreTraverseBTree(pT->pLchild);	//pT->pLchild��������������
		}

		if (NULL != pT->pRchild)
		{
			PreTraverseBTree(pT->pRchild);
		}
		
	}

	/*
		�ȷ��ʸ��ڵ㣻
		�����������������
		�����������������
	*/
}

PBTNODE CreateBTree(void)
{
	PBTNODE pA = (PBTNODE)malloc(sizeof(BTNODE));
	PBTNODE pB = (PBTNODE)malloc(sizeof(BTNODE));
	PBTNODE pC = (PBTNODE)malloc(sizeof(BTNODE));
	PBTNODE pD = (PBTNODE)malloc(sizeof(BTNODE));
	PBTNODE pE = (PBTNODE)malloc(sizeof(BTNODE));

	pA->data = 'A';
	pB->data = 'B';
	pC->data = 'C';
	pD->data = 'D';
	pE->data = 'E';

	pA->pLchild = pB;
	pA->pRchild = pC;
	pB->pLchild = pB->pRchild = NULL;
	pC->pLchild = pD;
	pC->pRchild = NULL;
	pD->pLchild = NULL;
	pD->pRchild = pE;
	pE->pLchild = pE->pRchild = NULL;

	return pA;
	
}