#ifndef ANIMAL_H
#define ANIMAL_H


class Animal//存在的意义是被继承
{
public:
    Animal();
    //虚析构只有一个用处：析构完全(在delete父类指针的时候，将子类对象析构完全)
    //所以说，当一个类中有虚函数的时候，需要将其析构函数一并设为virtual
    virtual ~Animal();
    virtual void voice() = 0;
};

#endif // ANIMAL_H
