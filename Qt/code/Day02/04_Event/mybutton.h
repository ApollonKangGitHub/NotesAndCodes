#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class MyButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyButton(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *ev);
signals:

public slots:
};

#endif // MYBUTTON_H
