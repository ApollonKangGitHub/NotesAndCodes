#ifndef _LIST_H
#define _LIST_H

class List{
public:
    List();
    void CreateList();
    void AddNode(int num);
    void TraverList();
    ~List();
private:
    struct Node{
        int data;
        Node * next;
    } * head;//声明结构体并定义头指针，指针是操作List的关键
};

#endif
