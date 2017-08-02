#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<int> vi;
    vi.reserve(256);//预定空间。事先申请1024空间，不用用时再申请(自己掌控大小)
    int i = 0;
    for(i=0; i<200; i++){//内存增长方式：2^n
        vi.push_back(i);
        cout<<"size:"<<vi.size()<<"\t"<<"capacity:"<<vi.capacity()<<endl;
    }
    if(i > 192)
        vi.reserve(512);//判断已经用了的空间，调整增大预定空间（只能增大不能减小）
    cout<<"size:"<<vi.size()<<"\t"<<"capacity:"<<vi.capacity()<<endl;
    return 0;
}

