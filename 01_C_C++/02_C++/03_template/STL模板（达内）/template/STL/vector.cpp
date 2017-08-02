#include<iostream>
#include<vector>
#include<string>
#include<cstring>
using namespace std;

template <typename T>
void print(T beg, T end){
	while(beg !=end)
		cout<<*beg++;
	cout<<endl;
}
int main(void)
{
#if 1
	const char * pcs = "Hello World!";
	vector<char> vc(pcs, pcs+strlen(pcs));//区间初始化
	print(vc.begin(), vc.end());
	print(vc.rbegin(),vc.rend());
#endif
	vector<string> pss;
	pss.push_back("Kang Ruo Jin");
	pss.push_back(" ");
	pss.push_back("Love");
	pss.push_back(" ");
	pss.push_back("YuanJiaYu");
	print(pss.begin(), pss.end());
	print(pss.rbegin(), pss.rend());
	
	vector<char> vcn(5,'#');
	print(vcn.begin(), vcn.end());
	vcn.resize(10,'$');//默认填充0
	print(vcn.begin(), vcn.end());
	vcn.assign(5,'~');
	print(vcn.begin(), vcn.end());
	vcn.assign(vc.begin(),vc.end());
	print(vcn.begin(), vcn.end());
	return 0;
}
