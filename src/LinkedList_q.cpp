#include <LinkedList_q.h>
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
    current->next = newNode;       // przyczepiamy stary node do lewej strony newNode oraz stary tail na nowy node jesli lista nie jest pusta

    if (newNode->next == nullptr)
    {

        tail = newNode; // teraz tail jest koncem listy
    }

    ++m_size;
};
int LinkedList::extract_max()
{
    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        throw std::out_of_range("Kolejka jest pusta!");
    }

    // std::cout << "Element o najwiekszym priorytecie w kolejce: [ " << head->priority << " ]\n";

    Node *temp = head; // tymczasowo przechowujemy aktualny head
    head = head->next;

    int return_temp_val = temp->element; // przechowanie wartosci przed usunieciem temp
    delete temp;
    if (head == nullptr) // sprawdzamy czy kolejka jest pusta i resetujem tail jesli wczesniej lusta zawierala TYLKO JEDEN ELEMENT
    {
        tail = nullptr;
    }

    --m_size;
    return return_temp_val;
};

int LinkedList::find_max()
{
    if (head == nullptr) // sprawdzienie czy kolejka jest pusta
    {
        throw std::out_of_range("Kolejka jest pusta!");
    }
    return head->element;
};
void LinkedList::modify_key(int element, int priority)
{
    if (head == nullptr) // sprawdzienie czy kolejka jest pusta
    {
        throw std::out_of_range("Kolejka jest pusta!");
    }
    Node *current = head;     // tworzymy wskaznik na aktualny node
    Node *previous = nullptr; // pomocniczy pointer

    // while (current->next != nullptr && current->next->priority >= priority) // przechodzimy przez wszystkie nody az do "pustego"
    // {

    //     current = current->next;
    // }

    if (head->element == element)
    {
        Node *temp_h = head; // tymczasowo przechowujemy aktualny head
        head = head->next;
        // current->priority = priority;
        // int priority_param = current->priority;
        delete temp_h;
        --m_size;
        insert(element, priority);
        return;
    }
    previous = current;
    current = head->next;

    while (current != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
    {

        if (current->element == element)
        {

            Node *temp = current;           // przechowanie tymczasowe starego node
            previous->next = current->next; // przyczepiamy stary node do lewej strony newNode
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
    // std::cout << "\nRozmiar tej kolejki to: [ " << m_size << " ]\n";
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

        std::cout << "Lista jest pusta!\n";
        return;
    }
    else
    {

        while (head != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
        {

            removeFirst();
        }
    }
};
