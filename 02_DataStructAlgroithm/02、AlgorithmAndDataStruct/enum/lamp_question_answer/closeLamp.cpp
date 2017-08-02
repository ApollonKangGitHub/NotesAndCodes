/*
 *���һ���㣨���أ�������Ӧ��λ�ú��������������ĸ�λ�õ�״̬���ᷢ���仯
 *ԭ��Ϊ��(1)�������Ϊ��(0)��ԭ��Ϊ��(0)��������Ϊ��(1)
 *eg: 
 *	1 1 1 1 1
 *	1 0 1 0 1
 *	0 1 1 1 0
 *������ĵ��״̬��Ϊ��
 *	1 1 0 1 1
 *	1 1 0 1 1
 *  0 1 0 1 0
 *������ʼ״̬���ҳ�һ�ַ�ʽ��ʹ�ö���5*6�Ŀ��ؾ��󣬵������Ժ����еƶ���
*/

#include <iostream>
#include <cstring>
#include <string>
#include <memory>

using namespace std;

//��ȡbitλ
int GetBit(char c, int i)
{
	return ((c >> i) & 0X01);
}

//����bitλ
void SetBit(char &c, int i, int value)
{
	if(1 == value){
		c |= (1 << i);	
	}
	else{
		c &= (~(1 << i));
	}
}

//bitλȡ��
void BackBit(char &c, int i)
{
	//��iλΪ1������(1<<i)�����Ϊ0��
	//��iλΪ0���������Ϊ1.��bit��1���������Ϊ~bit��bit��0�����������Ϊbit
	c ^= (1 << i);
}

//����������صİ���״̬
void OutPutResult(char result[])
{
	for(int i = 0; i < 5; i++){
		for(int j = 0; j < 6; j++){
			cout<< GetBit(result[i], j);//��1�еĵ�j�е�״̬
			if(j < 5){
				cout<<" ";
			}
		}
		cout<<endl;
	}
}

void SetInitStatus(char init[])
{
	cout<<"�������ʼ״̬(5*6����ֵΪ0/1:)"<<endl;
	int i, j, bit;
	//�Ӽ��̶����ʼ״̬��5*6
	for(i = 0; i < 5; i++){
		for(j = 0; j < 6; j++){
			cin >> bit;
			SetBit(init[i], j, bit);//���ó���״̬
		}
	}
}

int main(void)
{
	char init[5] = {0};//��ʼ������״̬
	char lights[5] = {0};//�洢�м�״̬
	char result[5] = {0};//�洢���ذ���״̬
	char line;//ĳһ��
	int n, i, j;

#if 0
	init[0] = 0X16;
	init[1] = 0X39;
	init[2] = 0X24;
	init[3] = 0X29;
	init[4] = 0X0E;
#endif

	SetInitStatus(init);

	for(n = 0; n < 64; n++){//������һ�е�����״̬��6յ��/6�����أ�2^6=64��
		memcpy(lights, init, sizeof(init));
		line = n;//��i�п���״̬,��i��״̬һ��ȷ����i+1��Ϊ������i+1��֮ǰ�е�ȫ��״̬�����ذ��µķ����͹̶�
		for(i = 0; i < 5; i++){
			result[i] = line;//����i�еĿ��ط�����Ϊline��״̬
			for(j = 0; j < 6; j++){
				if(1 == GetBit(line, j)){//����״̬Ϊ��������Ҫ�ı���Χ�Ƶ�״̬
					if(j > 0)//��ߴ��ڵ�
						BackBit(lights[i], j-1);
					BackBit(lights[i], j);
					if(j < 5)//�ұߵƴ���
						BackBit(lights[i], j+1);
				}
			}
			if(i < 4)//��һ�д��ڣ������line״̬�ı���һ�е�״̬
				lights[i+1] ^= line;
			line = lights[i];
		}
		if(lights[4] == 0){//����÷�������ʹ��5��ȫ��ǰ4����Ȼȫ���򷽰�����
			cout<<"\n�����ȫ��ķ���Ϊ:"<<endl;
			OutPutResult(result);
			break;//ֱ�ӽ���
		}
	}
	return 0;
}