#include<QApplication>
#include<QWidget>   //窗口空间基类
#include<QPushButton>   //按钮
int main(int argc,char **argv)
{
    QApplication app(argc,argv);

    QWidget NewWin;
    NewWin.setWindowTitle("I Love You");    //设置窗户标题
    //NewWin.move(0,0);

    //如果不指定父对象，则两个对象(窗口)是相互独立的没有联系的
    //父窗口在底下，子窗口在上面显示
    //指定父对象有两种方式：
    //①调用setParent()成员函数
    //②通过构造函数传参(构造函数默认为0，即父窗口为Windows界面)

    //通过setParent()指定父对象
    QPushButton Yes;
    Yes.setText("Yes");         //给按钮设置内容
    Yes.setParent(&NewWin);   //指定父对象
    Yes.move(50,100);        //移动坐标(一像素为单位，父窗口左上角为起点)

    //通过构造函数指定父对象
    QPushButton No(&NewWin);
    No.setText("No");
    No.move(200,100);

    NewWin.show();
/*
 * 这种脱离指定父对象的写法，使得按钮的父对象是Windwos界面窗口
 *  QPushButton b;
 *  b.setText("是");
 *  b.show();
*/

    app.exec();
    return 0;
}
