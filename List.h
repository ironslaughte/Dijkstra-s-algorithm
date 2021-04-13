#pragma once
#include "Queue.h"
#define INF 2147483647



class List {
public:
    List();

    void Pop_Front();
    void Clear();
    void Push_back(Top Top);
    void Push_front(Top Top);
    void Pop_back();
    size_t GetSize();
    bool IsEmpty();
    bool Contains(Top top);
    Top& operator[] (size_t index);
    void Remove(size_t index);
 
private:
    size_t Size;
    Elem* head;
};

bool List::Contains(Top top) {
    if (head != nullptr) {
        Elem* cur = head;
        while (cur != nullptr) {
            if (top.city == cur->top.city) return true;
            cur = cur->pnext;
        }
        return false;
    }
    return false;
}


List::List() {
    Size = 0;
    head = nullptr;
}



void List::Pop_back() {
    Elem* cur = head;
    while (cur->pnext != nullptr) {
        cur = cur->pnext;
    }
    delete cur;
    cur = nullptr;
    Size--;
}


void List::Pop_Front()
{
    Elem* cur = head;
    head = head->pnext;
    delete cur;
    Size--;
}


void List::Push_front(Top top) {
    head = new Elem(top, head);
    Size++;
}


void List::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}




void List::Push_back(Top top)
{
    if (head == nullptr) {
        head = new Elem(top);
    }
    else {
        Elem* cur = head;
        while (cur->pnext != nullptr) {
            cur = cur->pnext;
        }
        cur->pnext = new Elem(top);
    }
    Size++;
}


size_t List::GetSize()
{
    return Size;
}




Top& List::operator[](size_t index)
{
    int count = 0;  
    Elem* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->top;
        } cur = cur->pnext;
        count++;
    }
}




bool List::IsEmpty() {

    return Size == 0;
}




void List::Remove(size_t index) {
    if (index > Size - 1) {
        throw std::out_of_range("Wrong index\n");
    }
    if (index == 0) {
        Pop_Front();
    }
    else if (index == Size - 1) {
        Pop_back();
    }
    else {
        Elem* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                Elem* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}


