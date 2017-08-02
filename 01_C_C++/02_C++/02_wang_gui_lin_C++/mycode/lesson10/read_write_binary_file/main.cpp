/*
 * ios::beg(0)、ios::cur(1)、ios::end(2)
 * seekg()与seekp()一个拥有get(输入流)、一个用于put(输出流)
 * 但是其机制一样，且我们通常以fstream打开时，既能读又能写，则不牵扯
 *
*/
#include <iostream>
#include <fstream>

using namespace std;

struct Stu
{
    char name[30];
    char sex;
    int age;
};
int main()
{
    fstream fs("kang.txt", ios::in|ios::out|ios::trunc|ios::binary);
    if(!fs){
        cout<<"open kang.txt error!"<<endl;
    }

    Stu stu[5] =
    {
        {"wanger",'X',20},
        {"zhangsan",'Y',21},
        {"lisi",'X',21},
        {"zhaosi",'X',18},
        {"wangwu",'Y',20}
    };
    //fs.write((char *)stu,sizeof(stu));//可以直接写
    for(int i=0; i<5; i++){//也可以一个一个写
        fs.write((char*)&stu[i],sizeof(Stu));//两个参数
    }

    fs.seekg(0,ios::beg);
    Stu tmp;
    //加!fs.eof()为标准写法，不加也完全可以
    //因为fs.read()返回的是对象的引用，“！对象”则是进行了标志位判断
    //就是已经判断了!fs.eof()
    while(fs.read((char *)&tmp, sizeof(Stu)), !fs.eof()){
        cout<<"name:"<<tmp.name<<"\t";
        cout<<"namesex"<<tmp.sex<<"\t";
        cout<<"age:"<<tmp.age<<endl;
    }
    return 0;
}

