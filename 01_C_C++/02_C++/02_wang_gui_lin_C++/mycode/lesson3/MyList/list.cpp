#include "list.h"
#include <iostream>
using namespace std;

List::List(){
    CreateList();
}

void List::CreateList()
{
    head = new Node;
    head->data = 2147483648;
    head->next = NULL;
}

void List::AddNode(int num)
{
    /*头插法建链*/
    Node * cur = new Node;
    cur->data = num;
    cur->next = head->next;
    head->next = cur;
}

void List::TraverList()
{
    Node *p = head->next;
    while(p)
    {
        cout<<p->data<<endl;
        p=p->next;
    }
}

List::~List(){
    Node * tmp;

    while(head){
        tmp = head;
        head = head->next;
        cout<<"xigou value is"<<tmp->data<<endl;
        delete tmp;
    }
}
