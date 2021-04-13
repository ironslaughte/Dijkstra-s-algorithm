#pragma once
#include "Elem.h"
#include <exception>

class Queue {
public:
    Queue();    
    Top Dequeue();
    void pop_Front();
    void clear();
    bool contains(Top top);
    void push_back(Top top);
    size_t getSize();
    //char& operator[] (size_t index);

private:
    std::size_t Size;
    Elem* head;
};



Queue::Queue() {
    Size = 0;
    head = nullptr;
}

bool Queue::contains(Top top) {
    if (head == nullptr) {
        return false;
    }
    else {
        Elem* cur = head;
        while (cur != nullptr)
        {
            if (top.city == cur->top.city) return true;
            cur = cur->pnext;
        }
        return false;
    }
}



Top Queue::Dequeue() {
    Top data = head->top;
    pop_Front();
    return data;
}
void Queue::pop_Front()
{
    Elem* tmp = head;
    head = head->pnext;
    delete tmp;
    Size--;
}

void Queue::push_back(Top top) {
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

void Queue::clear()
{
    while (Size > 0) {
        pop_Front();
    }
}



size_t Queue::getSize()
{
    return Size;
}


/*string& Queue::operator[](size_t index)
{
    int count = 0;
    Elem* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->top.city;
        } cur = cur->pnext;
        count++;
    }
}*/


