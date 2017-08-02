/*2016年8月22日10:41:39*/
# include <iostream>
using namespace std;

class FATHER
{
private:
	int height;//身高
	int weight;//体重
public:
	void set_height(int father_height){height = father_height;}//设置身高
	void set_weight(int father_weight){weight = father_weight;}//设置体重
	void get_heightandweight(){cout<<"身高(cm)="<<height<<"\t体重(kg)="<<weight<<endl;}//输出身高体重
};

class SON : public FATHER//SON子类继承FATHER父类并派生新属性
{
private:
	int shoulder_weidth;//肩宽
	int length_arm;//臂长
public:
	void set_shoulder_weidth(int son_shoulder_weidth){shoulder_weidth = son_shoulder_weidth;}//设置肩宽
	void set_length_arm(int son_length_arm){length_arm = son_length_arm;}//设置臂长
	void get_shouldrandarm(){cout<<"肩宽(cm)="<<shoulder_weidth<<"\t臂长(cm)="<<length_arm<<endl;}//输出肩宽与臂长
};

int main (void)
{
	SON Mike;
	FATHER Koaro;

	cout << "儿子Mike：" << endl;
	Mike.set_height(175);//SON类的对象可以调用其父类的成员函数
	Mike.set_weight(65);
	Mike.set_length_arm(70);//SON类的对象调用自己的成员函数
	Mike.set_shoulder_weidth(40);
	Mike.get_heightandweight();
	Mike.get_shouldrandarm();

	cout << endl << "父亲Koaro：" << endl;
	Koaro.set_height(170);
	Koaro.set_weight(65);
	Koaro.get_heightandweight();
	return 0;
}