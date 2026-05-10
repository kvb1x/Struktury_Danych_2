#pragma once
class LinkedList
{
private:
    struct Node
    {
        int element{};
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

    void removeFirst();

    void insert(int element, int priority);
    int extract_max();
    int find_max();
    // void modify_key(int element, int priority);
    void increase_key(int element, int priority);
    void decrease_key(int element, int priority);
    int return_size();

    void clear();
};
