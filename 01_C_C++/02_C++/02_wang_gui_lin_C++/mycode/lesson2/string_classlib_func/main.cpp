#include <iostream>

using namespace std;

int main()
{
    string str = "***********Hello World!************";
    str.erase(0,str.find_first_not_of('*'));
    cout<<str<<endl;
    str.erase(str.find_last_not_of('*')+1);
    cout<<str<<endl;

    return 0;
}

