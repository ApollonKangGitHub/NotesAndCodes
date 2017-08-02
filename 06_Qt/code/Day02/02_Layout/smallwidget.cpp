#include "smallwidget.h"
#include <QSpinBox>
#include <QSlider>
#include <QHBoxLayout>

//用代码实现Horizontal Slider、spin box等功能
smallWidget::smallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox * spin = new QSpinBox(this);
    QSlider * slider = new QSlider(Qt::Horizontal, this);//Qt::Horizontal水平

    //把控件添加到布局中
    QHBoxLayout * hLayout = new QHBoxLayout(this);
    hLayout->addWidget(spin);
    hLayout->addWidget(slider);

    //让Horizontal Slider与spin box产生联系,一个变另一个跟着变
    //static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged)强转为带int型参数的信号
    connect(spin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            slider,&QSlider::setValue);
    connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
}


//添加一个Widget容器，按右键-->提升-->将类名复制过去-->添加-->选中"全举包含"-->提升-->编译运行
