#include "LinkedList_q.h"
#include <iostream>
#include <stdexcept>

LinkedList::LinkedList(int size) : m_size{0} {};
LinkedList::~LinkedList() { clear(); };

int LinkedList::getSize() { return m_size; }

void LinkedList::insert(int element, int priority)
{
    Node *newNode = new Node;
    newNode->element = element;   // pakujemy wartosc do nowego wezla
    newNode->priority = priority; // pakujemy wartosc do nowego wezla
    newNode->next = nullptr;

    if (head == nullptr || priority > head->priority) // sprawdzienie czy lista jest pusta
    {

        newNode->next = head; // ustawiamy head na nowy node jesli lista nie jest pusta
        head = newNode;       // teraz head jest poczatkiem listy
        if (tail == nullptr)
        {
            tail = newNode;
        } // tail tez do tego przypisujemy bo to jedyno node w liscie
        ++m_size;
        return;
    }

    Node *current = head; // tworzymy wskaznik na aktualny node

    while (current->next != nullptr && current->next->priority >= priority) // przechodzimy przez wszystkie nody az do "pustego"
    {
        current = current->next;
    }

    newNode->next = current->next; // przyczepiamy node z prawej
    current->next = newNode;       // przyczepiamy stary node do lewej strony newNode

    if (newNode->next == nullptr)
    {
        tail = newNode; // update tail
    }
    ++m_size;
};

int LinkedList::extract_max()
{
    if (head == nullptr) // jesli head jest puste rzucamy wyjatek
    {
        throw std::runtime_error(" Kolejka jest pusta!");
    }

    int tempElement = head->element; // tymczasowo przrchowujemy  wartosc node
    Node *temp = head;               // tymczasowo przechowujemy aktualny head

    head = head->next;   // ustawiamy nowy head
    if (head == nullptr) // sprawdzamy czy lista jest pusta i resetujem tail
    {
        tail = nullptr;
    }

    delete temp; // usuwamy node
    --m_size;

    return tempElement;
};

int LinkedList::find_max()
{
    if (head == nullptr) // sprawdzenie czy head jest pusty  gdy wywolujemy find max
    {
        throw std::runtime_error("Kolejka jest pusta!");
    }

    return head->element; // zwracamy max priorytet i usuwamy go
};

void LinkedList::increase_key(int element, int priority)
{
    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        return;
    }

    if (head->element == element)
    {
        if (priority < head->priority)
            throw std::invalid_argument("W operacji increase_key nowy priorytet nie moze byc mniejszy!");
        Node *temp = head; // tymczasowo przechowujemy aktualny head
        head = head->next;
        if (head == nullptr)
            tail = nullptr; // zabezpieczenie ogona
        delete temp;
        --m_size;
        insert(element, priority);
        return;
    }

    Node *current = head->next; // tworzymy wskaznik na aktualny node
    Node *previous = head;

    while (current != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
    {
        if (current->element == element)
        {
            if (priority < current->priority)
                throw std::invalid_argument("W operacji increase_key nowy priorytet nie moze byc mniejszy!");
            Node *temp = current;           // przechowanie tymczasowe starego node
            previous->next = current->next; // przyczepiamy stary node do lewej strony newNode
            if (previous->next == nullptr)
                tail = previous; // zabezpieczenie ogona
            delete temp;
            --m_size;
            insert(element, priority);
            return;
        }
        previous = current;
        current = current->next;
    }

    throw std::out_of_range("Brak takiego elementu w kolejce!\n");
};

void LinkedList::decrease_key(int element, int priority)
{
    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        return;
    }

    if (head->element == element)
    {
        if (priority > head->priority)
            throw std::invalid_argument("W operacji decrease_key nowy priorytet nie moze byc wiekszy!");
        Node *temp = head; // tymczasowo przechowujemy aktualny head
        head = head->next;
        if (head == nullptr)
            tail = nullptr; // zabezpieczenie ogona
        delete temp;
        --m_size;
        insert(element, priority);
        return;
    }

    Node *current = head->next; // tworzymy wskaznik na aktualny node
    Node *previous = head;

    while (current != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
    {
        if (current->element == element)
        {
            if (priority > current->priority)
                throw std::invalid_argument("W operacji decrease_key nowy priorytet nie moze byc wiekszy!");
            Node *temp = current;           // przechowanie tymczasowe starego node
            previous->next = current->next; // przyczepiamy stary node do lewej strony newNode
            if (previous->next == nullptr)
                tail = previous; // zabezpieczenie ogona
            delete temp;
            --m_size;
            insert(element, priority);
            return;
        }
        previous = current;
        current = current->next;
    }

    throw std::out_of_range("Brak takiego elementu w kolejce!\n");
};

int LinkedList::return_size()
{
    return m_size;
};

void LinkedList::removeFirst()
{
    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        std::cout << "Lista jest pusta!\n";
        return;
    }
    else
    {
        Node *temp = head; // tymczasowo przechowujemy aktualny head
        head = head->next;

        delete temp;
        if (head == nullptr) // sprawdzamy czy lista jest pusta i resetujem tail jesli wczesniej lusta zawierala TYLKO JEDEN ELEMENT
        {
            tail = nullptr;
        }
    }
    --m_size;
};

void LinkedList::clear()
{
    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        return;
    }

    Node *current = head;
    Node *next = nullptr;

    while (current != nullptr)
    {
        next = current->next; // przechowujemy adres na head
        delete current;       // usuwamy pamiec current
        current = next;       // ustawiamy wskaznik na current na nastepny w liscie
    }

    head = nullptr;
    tail = nullptr; // resetujemy ogon
    m_size = 0;
};
