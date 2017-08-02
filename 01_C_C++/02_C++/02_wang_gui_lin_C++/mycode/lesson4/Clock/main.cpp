#include <iostream>
#include <time.h>
#include <iomanip>
#include <unistd.h>

using namespace std;

class Clock{//初始化的数据来自系统,之后的逻辑及显示自己实现
public:
    Clock(){
        time_t t = time(NULL);
        //struct tm *__cdecl localtime(const time_t *_Time)
        struct tm clo_tim = *localtime(&t);
        hour = clo_tim.tm_hour;
        min = clo_tim.tm_min;
        sec = clo_tim.tm_sec;
    }
    void run()
    {
        while(1){
            show();//显示
            tick();//数据更新
        }
    }
private:
    short hour;
    short min;
    short sec;

    void show()
    {
        system("cls");
        cout<<setfill('0');
        cout<<setw(2)<<hour<<":";
        cout<<setw(2)<<min<<":";
        cout<<setw(2)<<sec;
    }
    void tick()
    {
        sleep(0.1);
        if(++sec == 60){
            sec = 0;
            if(++min == 60){
                min = 0;
                if(++hour == 24)
                    hour=0;
            }
        }
    }
};
int main()
{
    Clock c;
    c.run();

    return 0;
}

