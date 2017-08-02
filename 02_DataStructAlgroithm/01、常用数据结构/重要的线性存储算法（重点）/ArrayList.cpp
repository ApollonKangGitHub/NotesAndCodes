# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>
# include <string.h>

struct Arr
{
	int * pBase;//存储的是数组的第一个元素的地址,首地址为第一个元素首地址，末地址为最后一个元素末地址，总容量为sizeof("变量类型") * length
	int len;//数组所能容纳的最大元素的个数
	int cnt;//当前数组有效元素的个数

	//int increment//自动增长因子
};//切记分号不要忘记！

/*函数前置声明*/
void init_arr(struct Arr * pArr, int length);//初始化函数
bool append_arr(struct Arr * pArr, int val);//追加函数
bool insert_arr(struct Arr * pArr, int pos, int val);//插入函数，pos的值从1开始，表示插入的位置
bool delete_arr(struct Arr * pArr, int pos, int * pVal);//删除
bool get();//获取
bool is_empty(struct Arr * pArr);//判断数组是否空
bool is_full(struct Arr * pArr);//判断数组是否满
void sort_arr(struct Arr * pArr);//排序
void show_arr(struct Arr * pArr);//显示
void inwersion_arr(struct Arr * pArr);//倒置

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
		printf("删除成功\n");
		printf("删除的元素是:%d\n",val);
	}	
	else
	{
		printf("删除失败！\n");
	}
	

/*	append_arr(&arr,6);
	append_arr(&arr,7);
	append_arr(&arr,8);
	if(append_arr(&arr,8))
	{
		printf("追加成功！\n");
	}
	else
	{
		printf("追加失败！\n");
	}
*/
	show_arr(&arr);
	inwersion_arr(&arr);
	printf("倒置之后的数组内容是：\n");
	show_arr(&arr);
	sort_arr(&arr);
	printf("排序之后的内容是：\n");
	show_arr(&arr);
	//printf("%d\n",arr.len );//判断init_arr(&arr,6)应该发送arr地址还是arr

	return 0;
}
/*数组初始化*/
void init_arr(struct Arr * pArr,int length)
{
	//(*pArr).len = 99;//arr的地址赋给pArr,(*pArr)则表示arr

	pArr->pBase = (int *)malloc(sizeof(int) * length);
	if(NULL == pArr->pBase )
	{
		printf("分配内存失败！\n");
		exit(-1);//终止整个程序，头文件为<stdlib.h>
	}
	else
	{
		pArr->len = length;
		pArr->cnt =0;
	}
	return;
}


/*判断数组是否为空*/
bool is_empty(struct Arr * pArr)
{
	if(NULL == pArr->cnt)
		return true;
	else
		return false;
}
/*判断数组是否满*/
bool is_full(struct Arr * pArr)
{
	if(pArr->cnt == pArr->len)
		return true;
	else 
		return false;
}
/*数组输出*/
void show_arr(struct Arr * pArr)
{
	if(is_empty(pArr))
	printf("数组为空！\n");
	else
	{
		for(int i=0; i<pArr->cnt ; i++)
			printf("%d  ",(pArr->pBase)[i]);//数组的地址在pArr->pBase存储
		printf("\n");
	}
}

bool append_arr(struct Arr * pArr,int val)
{
	if(is_full(pArr))
		return false;
	//不满时追加
	else 
		pArr->pBase [pArr->cnt] = val;
	pArr->cnt++;
	return true;
}

/*添加*/
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
/*删除*/
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
/*倒置*/
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

/*排序*/
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

