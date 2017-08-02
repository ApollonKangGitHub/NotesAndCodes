# include <iostream>
# define MAX 10
using namespace std;
int main (void)
{
	int i,j;
	int array_yang[MAX][MAX];

	for(i=0;i<MAX;++i)
	{
		for(j=0;j<=i;++j)
		{
			array_yang[i][j] = (j==0 || j==i) ? 1 : array_yang[i-1][j-1] + array_yang[i-1][j];
			cout << array_yang[i][j] << "\t";
		}
		cout << endl << endl;
	}
	return 0;
}