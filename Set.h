#pragma once
#include <string>

struct  Node {
    std::string str; // City
    Node* pnext;
    Node(std::string str, Node* pnext = nullptr) {
        this->str = str;
        this->pnext = pnext;
    }
};


class Set {
public:
    Set();
    void Pop_Front();
    void Clear();
    void Insert(std::string str);
    size_t GetSize();
    bool IsEmpty();    
    bool Find(std::string str);
    std::string operator[] (size_t index);
    void Erase(size_t index);
    void Sort();
private:   
    size_t Size;
    Node* head;
};


Set::Set() {
    Size = 0;
    head = nullptr;
}


bool Set::Find(std::string str) {
    if (head == nullptr) return false;
    else {        
        Node* cur = head;
        while (cur != nullptr) {
            if (str == cur->str) return true;
            cur = cur->pnext;
        }
        return false;
    }
}

void Set::Pop_Front()
{
    Node* cur = head;
    head = head->pnext;
    delete cur;
    Size--;
}




void Set::Clear()
{
    while (Size > 0) {
        Pop_Front();
    }
}




void Set::Insert(std::string str)
{
    if (!Find(str)) {
        if (head == nullptr) {
            head = new Node(str);
        }
        else {
            Node* cur = head;
            while (cur->pnext != nullptr) {
                cur = cur->pnext;
            }
            cur->pnext = new Node(str);
        }
        Size++;
        //Sort();
    }

}


size_t Set::GetSize()
{
    return Size;
}


std::string Set::operator[](size_t index)
{
    int count = 0;
    Node* cur = head;
    while (cur != nullptr) {
        if (count == index) {
            return cur->str;
        } cur = cur->pnext;
        count++;
    }
}


bool Set::IsEmpty() {

    return Size == 0;
}



void Set::Erase(size_t index) {
    if (index > Size - 1) {
        throw std::out_of_range("Wrong index\n");
    }
    if (index == 0) {
        Pop_Front();
    }
    else {
        Node* cur = head;
        size_t i = 0;
        while (cur != nullptr) {
            if (index == i - 1) {
                Node* tmp = cur->pnext;
                cur->pnext = tmp->pnext;
                delete tmp;
                break;
            }
            i++;
            cur = cur->pnext;
        }
    }
}


// Quick sort block
int partition(Set& set, int low, int high)
{
    Node* pivot = new Node(set[high]);
    int i = (low - 1); // index of smaller element 
    for (int j = low; j < high; j++)
    {
        // If current element is smaller than the pivot 
        if (set[j] < pivot->str)
        {
            i++;
            // swap Set[i] and Set[j] 

            std::string tmp = set[j];
            set[j] = set[i];
            set[i] = tmp;
        }
    }

    // swap Set[i+1] and Set[high] (or pivot) 
    std::string tmp=  set[high];
    //Node* tmp = Set[high];
    set[high] = set[i + 1];
    set[i + 1] = tmp;
    return i + 1;
}


/* The main function that implements QuickSort()
  Set[] --> Set to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void Qsort(Set& set, int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, Set[pi] is
          now at right place */
        int pi = partition(set, low, high);

        // Recursively sort elements before 
        // partition and after partition 
        Qsort(set, low, pi - 1);
        Qsort(set, pi + 1, high);
    }
}

void Set::Sort() {
    Set set = *this;
    Qsort(set, 0, this->Size - 1);
    *this = set;
}
