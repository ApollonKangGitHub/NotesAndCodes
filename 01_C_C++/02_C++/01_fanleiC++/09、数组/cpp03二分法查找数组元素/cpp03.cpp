/*
	���ַ��ŵ㣺�����ٶȿ�
	���ַ�ȱ�㣺���ҵ�����������������ظ�ֵ
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
	cout << "��������Ҫ���ҵ�Ԫ�أ�" << endl;
	cin >> key;
	int find = FindArrayKey(a,LEN,key);
	if(find == -1)
		cout << "û�����Ԫ��!" << endl;
	else
		cout << "Ҫ���ҵ�Ԫ��Ϊ��" << find+1 << "��Ԫ��,��ֵΪ" << a[find] << endl;
	return 0; 
}