/*
 *点击一个点（开关），则相应的位置和其上上下左右四个位置的状态都会发生变化
 *原来为亮(1)，点击后为灭(0)，原来为灭(0)，点击后变为亮(1)
 *eg: 
 *	1 1 1 1 1
 *	1 0 1 0 1
 *	0 1 1 1 0
 *点击中心点后，状态变为：
 *	1 1 0 1 1
 *	1 1 0 1 1
 *  0 1 0 1 0
 *给定初始状态，找出一种方式，使得对于5*6的开关矩阵，点击多次以后，所有灯都灭
*/

#include <iostream>
#include <cstring>
#include <string>
#include <memory>

using namespace std;

//获取bit位
int GetBit(char c, int i)
{
	return ((c >> i) & 0X01);
}

//设置bit位
void SetBit(char &c, int i, int value)
{
	if(1 == value){
		c |= (1 << i);	
	}
	else{
		c &= (~(1 << i));
	}
}

//bit位取反
void BackBit(char &c, int i)
{
	//第i位为1，则与(1<<i)异或结果为0；
	//第i位为0，则异或结果为1.即bit与1异或运算结果为~bit，bit与0异或运算结果仍为bit
	c ^= (1 << i);
}

//遍历输出开关的按下状态
void OutPutResult(char result[])
{
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 6; j++){
			cout<< GetBit(result[i], j);//第1行的第j列的状态
			if(j < 5){
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

void SetInitStatus(char init[])
{
	cout<<"请输入初始状态(5*6矩阵，值为0/1:)"<<endl;
	int i, j, bit;
	//从键盘读入初始状态：5*6
	for(i = 0; i < 5; i++){
		for(j = 0; j < 6; j++){
			cin >> bit;
			SetBit(init[i], j, bit);//设置出事状态
		}
	}
}

int main(void)
{
	char init[5] = {0};//初始化输入状态
	char lights[5] = {0};//存储中间状态
	char result[5] = {0};//存储开关按下状态
	char line;//某一行
	int n, i, j;

#if 0
	init[0] = 0X16;
	init[1] = 0X39;
	init[2] = 0X24;
	init[3] = 0X29;
	init[4] = 0X0E;
#endif

	SetInitStatus(init);

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
			cout<<"\n满足灯全灭的方案为:"<<endl;
			OutPutResult(result);
			break;//直接结束
		}
	}
	return 0;
}