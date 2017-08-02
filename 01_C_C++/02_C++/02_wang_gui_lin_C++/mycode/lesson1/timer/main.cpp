#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

#define HOUR 24
#define MIN 60
#define SEC 60

int main(void)
{
    int hour = 0, min = 0, sec = 0;

    for(hour = 0; hour < HOUR; hour++){
        for(min = 0; min < MIN; min++){
            for(sec = 0; sec < SEC; sec++){
                cout<<setfill('0');
                cout<<setw(2)<<hour<<":"<<setw(2)<<min<<":"<<setw(2)<<sec<<endl;
                Sleep(1000);
                system("cls");
            }
        }
    }
    return 0;
}

