/*
 * 运算符()重载--将类对象当做函数名一样使用：仿函数
 * 主要用于STL(集算法与数据结构大成者)和模板
 *
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#if 0
/*类对象当做函数使用举例*/
class Pow{
public:
    int operator()(int i){
        return i*i;
    }
};

int main()
{
    Pow pow;
    int i = 4;
    cout<<pow(i)<<endl;

    return 0;
}
#endif
bool mycmp(int i, int j)
{
    return i>j;
}
class Cmp{
public:
    bool operator()(int i, int j)
    {
        return i<j;
    }
};
int main(void)
{
    int i;
    int array[8] = {1,2,3,4,5,6,7,8};
    vector<int> vi(array, array+8);

    cout<<"---------------------"<<endl;
    sort(vi.begin(), vi.end(), mycmp);//普通函数方式mycmp()
    for(i=0; i<vi.size(); i++)
        cout<<vi[i]<<endl;

    cout<<"---------------------"<<endl;
    sort(vi.begin(), vi.end(), Cmp());//仿函数方式Cmp()
    for(i=0; i<vi.size(); i++)
        cout<<vi[i]<<endl;
    cout<<"---------------------"<<endl;
    sort(vi.begin(), vi.end(), [=](int i, int j){return i>j;});
    //C++11标准lambda表达式：本质是仿函数
    //真没没节操,看都看不懂:生命不休，装X不止

    for(i=0; i<vi.size(); i++)
        cout<<vi[i]<<endl;
    cout<<"---------------------"<<endl;
    return 0;
}
