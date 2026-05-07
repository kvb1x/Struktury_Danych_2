#pragma once
class LinkedList
{
private:
    struct Node
    {
        int value{};
        int priority{};
        Node *next{};
    };

    int m_size{0}; // rozmiar listy

    Node *head{nullptr}; // lista jest pusta na poczatku

    Node *tail{nullptr};

public:
    // LinkedList() = default;
    LinkedList(int size = 0);
    ~LinkedList();

    int getSize();

    // void addLast(int element);
    // void addFirst(int element);
    // void add(int index, int element);

    // void removeLast();
    // void removeFirst();
    // void remove(int index);
    // int find(int value);

    void insert(int e, int p);
    int extract_max();
    int find_max();
    void modify_key(int e, int p);
    int return_size();

    void clear();
    // void print();
};
