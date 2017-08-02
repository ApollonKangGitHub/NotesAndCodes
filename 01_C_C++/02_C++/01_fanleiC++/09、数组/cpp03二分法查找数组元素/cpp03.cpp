/*
	二分法优点：查找速度快
	二分法缺点：查找的数组必须有序且无重复值
*/
# include <iostream>
# define LEN 20
using namespace std;

int FindArrayKey(int *, int, int);
int FindArrayKey(int *a, int len, int key)
{
	int low = 0, high = len-1, between = (low+high)/2;
	for(; low<=high; between = (low+high)/2)
	{
		if(a[between] == key)
			return between;
		else if(a[between] < key)
			low = between+1;
		else
			high = between-1;	
	}
	return -1;
}
int main (void)
{
	int key = 0;
	int a[LEN] = {1,9,21,45,46,75,88,94,99,102,107,123,407,425,456,635,677,789,998,1001};
	cout << "请输入你要查找的元素：" << endl;
	cin >> key;
	int find = FindArrayKey(a,LEN,key);
	if(find == -1)
		cout << "没有这个元素!" << endl;
	else
		cout << "要查找的元素为第" << find+1 << "个元素,其值为" << a[find] << endl;
	return 0; 
}