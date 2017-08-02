#ifndef BITOPER_H
#define BITOPER_H


class bitOper
{
public:
    bitOper();
    int GetBit(char, int);//获取某一位
    void SetBit(char &, int, int);//设置某一位
    void BackBit(char &, int);//反转某一位
    void ProcessAlgroithm();//进行求解
public:
    char init[5];//存储初始值
    char lights[5];//存储中间变化值
    char result[5];//存储按键提示结果
};

#endif // BITOPER_H
