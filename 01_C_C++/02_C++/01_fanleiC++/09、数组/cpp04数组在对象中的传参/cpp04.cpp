# include <iostream>
# define LEN 20
using namespace std;

class findkey//Ԫ�ز�����
{
public:
	bool judge(int *, int len);
	int find_one(int *,int len,int key);
	int find_two(int *,int len,int key);
};

bool findkey::judge(int * a, int len)
{
	int i;
	for(i=1; i<len; ++i)
	{
		if(a[i-1]>a[i])
			return false;
	}
	return true;
}

int findkey::find_one(int * a, int len,int key)
{
	int i = 0;
	for(i; i<len; ++i)
	{
		if(a[i] == key)
			return i;
	}
	return len;
}

int findkey::find_two(int * a, int len, int key)
{
	int low = 0, high = len-1, i = (low+high)/2;
	for(; low<=high; i = (low+high)/2)
	{
		if(a[i] == key)
			return i;
		else if(a[i] < key)
			low = i+1;
		else
			high = i-1;	
	}
	return len;
}

int main (void)
{
	findkey array;
	int key,pos;
	int a[LEN] = {1,9,21,45,46,75,88,94,99,102,107,123,407,425,456,635,677,789,998,1001}; 

	cout << "��������Ҫ���ҵ�����Ԫ��key��" << endl;
	cin >> key;
	pos = (array.judge(a,LEN) == true) ? array.find_one(a,LEN,key) : array.find_two(a,LEN,key);

	if(pos == LEN)
		cout << "��Ҫ���ҵ�Ԫ�ز���������!" << endl;
	else
		cout << "��Ҫ���ҵ�Ԫ���������еĵ�" << pos+1 << "��Ԫ�أ���ֵΪ��" << a[pos] << endl;
	return 0;
}