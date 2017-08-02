# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

struct Arr
{
	int * pBase;//�洢��������ĵ�һ��Ԫ�صĵ�ַ,�׵�ַΪ��һ��Ԫ���׵�ַ��ĩ��ַΪ���һ��Ԫ��ĩ��ַ��������Ϊsizeof("��������") * length
	int len;//�����������ɵ����Ԫ�صĸ���
	int cnt;//��ǰ������ЧԪ�صĸ���

	//int increment//�Զ���������
};//�мǷֺŲ�Ҫ���ǣ�

/*����ǰ������*/
void init_arr(struct Arr * pArr, int length);//��ʼ������
bool append_arr(struct Arr * pArr, int val);//׷�Ӻ���
bool insert_arr(struct Arr * pArr, int pos, int val);//���뺯����pos��ֵ��1��ʼ����ʾ�����λ��
bool delete_arr(struct Arr * pArr, int pos, int * pVal);//ɾ��
bool get();//��ȡ
bool is_empty(struct Arr * pArr);//�ж������Ƿ��
bool is_full(struct Arr * pArr);//�ж������Ƿ���
void sort_arr(struct Arr * pArr);//����
void show_arr(struct Arr * pArr);//��ʾ
void inwersion_arr(struct Arr * pArr);//����

int main (void)
{
	struct Arr arr;
	int val;

	init_arr(&arr,6);
	show_arr(&arr);
	append_arr(&arr,14);
	append_arr(&arr,9);
	append_arr(&arr,-7);
	append_arr(&arr,33);
	append_arr(&arr,-56);
	append_arr(&arr,7);

	if ( delete_arr(&arr,3,&val))
	{
		printf("ɾ���ɹ�\n");
		printf("ɾ����Ԫ����:%d\n",val);
	}	
	else
	{
		printf("ɾ��ʧ�ܣ�\n");
	}
	

/*	append_arr(&arr,6);
	append_arr(&arr,7);
	append_arr(&arr,8);
	if(append_arr(&arr,8))
	{
		printf("׷�ӳɹ���\n");
	}
	else
	{
		printf("׷��ʧ�ܣ�\n");
	}
*/
	show_arr(&arr);
	inwersion_arr(&arr);
	printf("����֮������������ǣ�\n");
	show_arr(&arr);
	sort_arr(&arr);
	printf("����֮��������ǣ�\n");
	show_arr(&arr);
	//printf("%d\n",arr.len );//�ж�init_arr(&arr,6)Ӧ�÷���arr��ַ����arr

	return 0;
}
/*�����ʼ��*/
void init_arr(struct Arr * pArr,int length)
{
	//(*pArr).len = 99;//arr�ĵ�ַ����pArr,(*pArr)���ʾarr

	pArr->pBase = (int *)malloc(sizeof(int) * length);
	if(NULL == pArr->pBase )
	{
		printf("�����ڴ�ʧ�ܣ�\n");
		exit(-1);//��ֹ��������ͷ�ļ�Ϊ<stdlib.h>
	}
	else
	{
		pArr->len = length;
		pArr->cnt =0;
	}
	return;
}


/*�ж������Ƿ�Ϊ��*/
bool is_empty(struct Arr * pArr)
{
	if(NULL == pArr->cnt)
		return true;
	else
		return false;
}
/*�ж������Ƿ���*/
bool is_full(struct Arr * pArr)
{
	if(pArr->cnt == pArr->len)
		return true;
	else 
		return false;
}
/*�������*/
void show_arr(struct Arr * pArr)
{
	if(is_empty(pArr))
	printf("����Ϊ�գ�\n");
	else
	{
		for(int i=0; i<pArr->cnt ; i++)
			printf("%d  ",(pArr->pBase)[i]);//����ĵ�ַ��pArr->pBase�洢
		printf("\n");
	}
}

bool append_arr(struct Arr * pArr,int val)
{
	if(is_full(pArr))
		return false;
	//����ʱ׷��
	else 
		pArr->pBase [pArr->cnt] = val;
	pArr->cnt++;
	return true;
}

/*���*/
bool insert_arr(struct Arr *pArr,int pos,int val)
{
	int i;

	if(is_full(pArr))
		return false;

	if(pos<1 || pos>pArr->cnt+1)
		return false;

	for( i=(pArr->cnt)-1; i>=pos-1; i--)
	{
		pArr->pBase[i+1] = pArr->pBase[i];
	}
	pArr->pBase[pos-1] = val;
	pArr->cnt++;
	return true;
}
/*ɾ��*/
bool delete_arr(struct Arr *pArr,int pos,int * pVal)
{
	int i;

	if (is_empty(pArr))
		return false;
	if (pos<1 || pos>pArr->cnt)
		return true;
	*pVal = pArr->pBase[pos-1];
	for( i=pos; i<pArr->cnt; i++)
	{
		pArr->pBase[i-1] = pArr->pBase[i];
	}
	pArr->cnt--;
	return true;
		
}
/*����*/
void inwersion_arr(struct Arr *pArr)
{
	int i = 0;
	int j =pArr->cnt-1;
	int t;

	while(i <j)
	{
		t = pArr->pBase[i];
		pArr->pBase[i] =  pArr->pBase[j];
		 pArr->pBase[j] = t;
		 i++;
		 j--;

	}
	return;

}

/*����*/
void sort_arr(struct Arr * pArr)
{
	int i, j, t;
	for(i=0; i<pArr->cnt; i++)
	{
		for(j=i+1; j<pArr->cnt; j++)
		{
			if(pArr->pBase[i] > pArr->pBase[j])
			{
				 t = pArr->pBase[i];
			   	 pArr->pBase[i] =  pArr->pBase[j];
				 pArr->pBase[j] = t;
			}
		}
	}
}

