#include <iostream>

using namespace std;

void Swap(char **a, char **b)/*传指针*/
{
    char * c = *a;
    *a = *b;
    *b = c;
}
void Swap(char * &a, char * &b)/*传引用*/
{
    char *c = a;
    a = b;
    b = c;
}
int main()
{
    int a = 10;
    int * p = &a;
    int * &rp = p;//right,指针的引用

    char * pstr = "China";
    char * qstr = "America";

    cout<<"pstr = "<<pstr<<endl<<"qstr = "<<qstr<<endl;

    Swap(&pstr, &qstr);
    cout<<"pstr = "<<pstr<<endl<<"qstr = "<<qstr<<endl;

    Swap(pstr, qstr);
    cout<<"pstr = "<<pstr<<endl<<"qstr = "<<qstr<<endl;

    return 0;
}
