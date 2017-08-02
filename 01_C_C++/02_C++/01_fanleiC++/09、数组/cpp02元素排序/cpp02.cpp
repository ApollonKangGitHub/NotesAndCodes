# include <iostream>
using namespace std;

void print(int a[], int n);
void sort(int a[], int n);

void print(int a[], int n)
{
	int i = 0;
	for(i = 0; i<n; ++i)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
	return;
}

void sort(int a[], int n)
{
	int i = 0;
	int j = 0;
	int temp = 0;
	
	for(i = 0; i<n-1; ++i)
	{
		for(j = 0; j<n-i-1; ++j)
		{
			if(a[j] > a[j+1])
			{
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
			}
		}
	}
}
int main (void)
{
	int a[20] = {777,9,31,4,5,55,6,7,22,554,69,84,15,64,74,23,39,91,112,3};
	print(a,20);
	sort(a,20);
	print(a,20);

	return 0;
}