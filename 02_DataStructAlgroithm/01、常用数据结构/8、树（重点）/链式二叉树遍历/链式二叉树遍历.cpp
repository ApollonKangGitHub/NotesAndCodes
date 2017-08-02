# include <stdio.h>
# include <malloc.h>
/*Binary Tree 二叉树*/
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
	PBTNODE pT = CreateBTree();//CreateBTree()静态构造了一个链式二叉树，并返回根节点的地址
	
	printf("先序遍历为：\n");	
	PreTraverseBTree(pT);//先序遍历

	printf("中序遍历为：\n");
	InTraverseBTree(pT);//中序遍历

	printf("后序遍历为：\n");
	PosTraverseBTree(pT);//后序遍历

	return 0;
}
void PosTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//不空的时候才可以遍历
	{
		
		if (NULL != pT->pLchild)
		{
			PosTraverseBTree(pT->pLchild);	//pT->pLchild代表整个左子树
		}

		if (NULL != pT->pRchild)
		{
			PosTraverseBTree(pT->pRchild);
		}

		printf("%c\n",pT->data);//pT->data == pA->data
		
	}

	/*
		
		先后序遍历左子树；
		再后序遍历右子树；
		再访问根节点；
	*/
}
void InTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//不空的时候才可以遍历
	{
		
		if (NULL != pT->pLchild)
		{
			InTraverseBTree(pT->pLchild);	//pT->pLchild代表整个左子树
		}

		printf("%c\n",pT->data);//pT->data == pA->data

		if (NULL != pT->pRchild)
		{
			InTraverseBTree(pT->pRchild);
		}
		
	}

	/*
		先先序遍历左子树；
		再访问根节点；
		再先序遍历右子树。
	*/
}
void PreTraverseBTree(PBTNODE pT)
{
	if (NULL != pT)//不空的时候才可以遍历
	{
		printf("%c\n",pT->data);//pT->data == pA->data
		
		if (NULL != pT->pLchild)
		{
			PreTraverseBTree(pT->pLchild);	//pT->pLchild代表整个左子树
		}

		if (NULL != pT->pRchild)
		{
			PreTraverseBTree(pT->pRchild);
		}
		
	}

	/*
		先访问根节点；
		再先序遍历左子树；
		再先序遍历右子树。
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