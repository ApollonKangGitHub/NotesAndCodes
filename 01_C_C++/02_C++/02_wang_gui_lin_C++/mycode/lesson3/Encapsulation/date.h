#ifndef DATE_H_
#define DATE_H_

namespace Kang{
    class Date{
        /*对内而言，数据是开放的，无论是那种(public、private、protected)设置权限*/
    public://公有的成员函数
        void Print();
        void Init();
        bool IsLeapYear();
        int& GetYear();
    private://私有的
    protected://受保护的成员变量
        int year;
        int month;
        int day;
    };
}
#endif
