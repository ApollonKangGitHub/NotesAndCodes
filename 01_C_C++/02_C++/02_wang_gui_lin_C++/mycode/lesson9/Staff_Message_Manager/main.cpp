/*
 * 2017年3月25日18:35:30
 * “废掉”构造器是比较流行的做法
*/
#include <iostream>
#include "employee.h"
#include "techincian.h"
#include "manager.h"
#include "saleman.h"
#include "salemanager.h"
#include <typeinfo>
using namespace std;

int main()
{
#if 0
    /*经理*/
    Manager man;
    man.CalcSarlary();
    man.Promote();
    man.DisplayInfo();

    /*技术人员*/
    Techincian tech2;
    tech2.CalcSarlary();
    tech2.DisplayInfo();

    /*销售人员*/
    SaleMan sm;
    sm.CalcSarlary();
    sm.Promote();
    sm.DisplayInfo();

    /*销售经理*/
    SaleManager smg;
    smg.CalcSarlary();
    smg.Promote();
    smg.DisplayInfo();
#endif

    Employee * emp[] =
    {
        new Techincian,
        new Manager,
        new SaleMan,
        new SaleManager
    };
    for(int i = 0; i<sizeof(emp)/sizeof(emp[0]); i++){
        emp[i]->init();
        if(typeid(*emp[i]) == typeid(Manager)){
            //dynamic_cast只能用在父子类型转换中
            Manager * tmp = dynamic_cast<Manager*>(emp[i]);
            tmp->addFixSalary(10000);
            //增加底薪，该接口只属于Manager，要想用emp[i]对象访问该接口
            //就必须将Employee *的emp[i]用dynamic_cast转成Manager*后来调用
        }

        emp[i]->CalcSarlary();
        emp[i]->Promote();
        emp[i]->DisplayInfo();
        cout<<"-------------------------------------"<<endl;
    }

    for(int i = 0; i < 4; i++)
        delete emp[i];
    return 0;
}

