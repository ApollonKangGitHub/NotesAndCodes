#include<iostream>
using namespace std;

#include<cstring>

struct Date{
	int year;
	int month;
	int day;
	bool operator==(const Date& d){
		return (year == d.year && month == d.month && day == d.day);
	}
	friend ostream &operator<<(ostream & os, const Date & date){
		return os<<date.year<<'-'<<date.month<<'-'<<date.day;
	}
};
template <typename T, int N>
T * FindElement(T (&a)[N], T key)
{
	for(int i = 0; i<N; i++)
		if(a[i]== key)
			return a+i;
	return NULL;
}
#if 1
template <int N>
const char **FindElement(const char *(&a)[N], const char * key)
{
	for(int i = 0; i<N; i++)
		if(!strcmp(a[i], key))
			return a+i;
	return NULL;
}
#endif
int main(void)
{
	char arr_c[10] = {'a','b','d','f','e','a','g','k','s','n'};
	int arr_i[10] = {0,1,2,3,4,5,6,7,8,9};
	double arr_d[10] = {1.9,2.1,4.2,3.3,1.4,5.5,3.6,1.7,2.8,3.9};
	string arr_ss[6] = {"Hello","World","I'am","Kang","Ruo","Jin"};
	Date arr_sd[3] = {{2005,3,4},{2007,4,6},{2017,2,14}};	
	const char * arr_cs[6] = {"Hello","World","I'am","Yuan","Jia","Yu"};
//也可以直接输出不用接收
	char * pc = FindElement(arr_c,arr_c[4]);
	int * pi = FindElement(arr_i,arr_i[5]);
	double * pd = FindElement(arr_d,arr_d[7]);
	string * pss = FindElement(arr_ss,arr_ss[3]);
	const char **pcs = FindElement(arr_cs,"Jia");

	if(pc)cout<<*pc<<endl;
	if(pi)cout<<*pi<<endl;
	if(pd)cout<<*pd<<endl;
	if(pss)cout<<*pss<<endl;
	if(pcs)cout<<*pcs<<endl;
	Date key = {2017,2,14};
	cout<<*FindElement(arr_sd, key)<<endl;
	return 0;
}
