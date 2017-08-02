#include <iostream>

using namespace std;
class A{
public:
    bool operator!(){
        return false;
    }
#if 0
    operator void *()
    {
        return 0;
    }
#endif
#if 1
    operator bool(){
        return true;
    }
#endif
};
int main()
{
    A a;

    if(!a){
        cout<<"!a is false"<<endl;
    }
    if(a){
        cout<<"a is true"<<endl;
    }
    return 0;
}

