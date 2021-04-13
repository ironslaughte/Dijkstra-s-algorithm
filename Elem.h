#pragma once
#include "Top.h"
class Elem {
public:
    Elem* pnext;
    Top top;
    Elem(Top new_top, Elem* pNext = nullptr) {
        top = new_top;
        pnext = pNext;
    }

    Elem() {
        pnext = nullptr;
        top = Top();
    }
};