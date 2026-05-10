#pragma once
class BinaryHeap
{
private:
    struct Node
    {

        int element;
        int priority;
        unsigned long long order;
    };
    Node *heap{nullptr};

    int m_size;
    int m_capacity;
    unsigned long long insertionCounter;

    bool isHigher(int a, int b);
    void heapifyUp(int index);
    void heapifyDown(int index);

    void resize(); // zwiekszanie rozmiaru tablicy *2

public:
    BinaryHeap(int m_capacity = 16);
    ~BinaryHeap();

    int getSize();

    void insert(int element, int priority);
    int extract_max();
    int find_max();
    // void modify_key(int element, int priority);
    void increase_key(int element, int priority);
    void decrease_key(int element, int priority);
    int return_size();
};
