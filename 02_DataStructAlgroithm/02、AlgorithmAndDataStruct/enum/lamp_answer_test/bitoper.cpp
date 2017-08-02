#include "bitoper.h"

#include <cstring>
#include <string>
#include <memory>

bitOper::bitOper()
{
    memset(init, 0, 5);
    memset(lights, 0, 5);
    memset(result, 0, 5);
}
//获取bit位
int bitOper::GetBit(char c, int i)
{
    return ((c >> i) & 0X01);
}

//设置bit位
void bitOper::SetBit(char &c, int i, int value)
{
    (1 == value) ? (c |= (1 << i)) : (c &= (~(1 << i)));
}

//bit位取反
void bitOper::BackBit(char &c, int i)
{
    //即bit与1异或运算结果为~bit，bit与0异或运算结果仍为bit
    c ^= (1 << i);
}
void bitOper::ProcessAlgroithm()
{
    int n, i, j;
    char line;
    for(n = 0; n < 64; n++){//遍历第一行的所有状态（6盏灯/6个开关，2^6=64）
        memcpy(lights, init, sizeof(init));
        line = n;//第i行开关状态,第i行状态一旦确定，i+1行为了满足i+1及之前行的全灭状态，开关按下的方法就固定
        for(i = 0; i < 5; i++){
            result[i] = line;//将第i行的开关方案置为line的状态
            for(j = 0; j < 6; j++){
                if(1 == GetBit(line, j)){//开关状态为按下则需要改变周围灯的状态
                    if(j > 0)//左边存在灯
                        BackBit(lights[i], j-1);
                    BackBit(lights[i], j);
                    if(j < 5)//右边灯存在
                        BackBit(lights[i], j+1);
                }
            }
            if(i < 4)//下一行存在，则根据line状态改变下一行灯状态
                lights[i+1] ^= line;
            line = lights[i];
        }
        if(lights[4] == 0){//如果该方案可以使第5行全灭（前4行自然全灭）则方案可行
            break;//直接结束
        }
    }
}
