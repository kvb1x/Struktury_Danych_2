#include <LinkedList.hpp>
#include <iostream>

LinkedList::LinkedList(int size) : m_size{0} {};
LinkedList::~LinkedList() { clear(); };

int LinkedList::getSize() { return m_size; }

void LinkedList::addLast(int element)
{

    Node *newNode = new Node;
    newNode->value = element;
    newNode->next = nullptr;

    if (head == nullptr) // sprawdzienie czy lista jest pusta
    {
        head = newNode; // jesli tak to zmieniamy nowy obiekt na startowy
        tail = newNode; // tail tez do tego przypisujemy bo to jedyno node w liscie
    }
    else
    {
        tail->next = newNode; // ustawiamy tail na nowy node jesli lista nie jest pusta
        tail = newNode;       // teraz tail jest koncem listy
    }
    ++m_size;
};
// void LinkedList::addFirst(int element)
// {
//     Node *newNode = new Node;
//     newNode->value = element; // pakujemy wartosc do nowego wezla
//     newNode->next = nullptr;

//     if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         head = newNode; // jesli tak to zmieniamy nowy obiekt na startowy
//         tail = newNode; // tail tez do tego przypisujemy bo to jedyno node w liscie
//     }
//     else
//     {

//         newNode->next = head; // ustawiamy head na nowy node jesli lista nie jest pusta
//         head = newNode;       // teraz head jest poczatkiem listy
//     }
//     ++m_size;
// };
// void LinkedList::add(int index, int element)
// {
//     if (index < 0 || index > m_size)
//     {
//         std::cout << "Nieprawidlowy index!\n";
//         return;
//     }
//     else if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         Node *newNode = new Node;
//         newNode->value = element; // pakujemy wartosc do nowego wezla
//         newNode->next = nullptr;

//         head = newNode; // jesli tak to zmieniamy nowy obiekt na startowy
//         tail = newNode; // tail tez do tego przypisujemy bo to jedyno node w liscie
//     }
//     else if (index == 0)
//     {
//         addFirst(element);
//         return;
//     }
//     else if (index == m_size)
//     {
//         addLast(element);
//         return;
//     }
//     else
//     {
//         Node *newNode = new Node;
//         Node *current = head; // tworzymy wskaznik na aktualny node

//         for (int i = 0; i < index - 1; ++i) // szukamy wezla o podanym indexie -1 (czyli poprzedniego od zadanego)
//         {
//             current = current->next;
//         }
//         newNode->value = element;
//         newNode->next = current->next; // przyczepiamy node z prawej
//         current->next = newNode;       // przyczepiamy stary node do lewej strony newNode
//     }

//     ++m_size;
// };

// void LinkedList::removeLast()
// {

//     if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         std::cout << "Lista jest pusta!\n";
//         return;
//     }
//     else if (tail == head) // tu sprawdzamy czy lista sklada sie tylko z jednego wezla
//     {

//         delete tail;
//         tail = nullptr;
//         head = nullptr;
//     }
//     else
//     {
//         Node *current = head;                  // tworzymy wskaznik na aktualny node
//         while (current->next->next != nullptr) // szukamy noda w ktorym jesli sie znajdziemy to bedziemy wiedzieli ze jestesmy w przedostatnim od konca
//         {
//             current = current->next;
//         }
//         delete tail;    // usuwamy stary node z ostatniego miejsca listy
//         tail = current; // po znalezienu przedostatniego ustawiamy go na tail

//         tail->next = nullptr; // ustawiamy ostatni node na null
//     }
//     --m_size;
// };

// void LinkedList::removeFirst()
// {

//     if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         std::cout << "Lista jest pusta!\n";
//         return;
//     }
//     else
//     {
//         Node *temp = head; // tymczasowo przechowujemy aktualny head
//         head = head->next;

//         delete temp;
//         if (head == nullptr) // sprawdzamy czy lista jest pusta i resetujem tail jesli wczesniej lusta zawierala TYLKO JEDEN ELEMENT
//         {
//             tail = nullptr;
//         }
//     }

//     --m_size;
// };
// void LinkedList::remove(int index)
// {
//     if (index < 0 || index > m_size - 1) // przy usuwaniu musi byc size -1
//     {
//         std::cout << "Nieprawidlowy index!\n";
//         return;
//     }
//     else if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {

//         std::cout << "Lista jest pusta!\n";
//         return;
//     }
//     else if (index == 0)
//     {
//         removeFirst();
//         return;
//     }
//     else if (index == m_size - 1) // tu tak saomo pryz usuwaniu size -1 (ostatni element bo liczymy od 0)
//     {
//         removeLast();
//         return;
//     }
//     else
//     {

//         Node *current = head; // tworzymy wskaznik na aktualny node

//         for (int i = 0; i < index - 1; ++i) // szukamy wezla o podanym indexie -1 (czyli poprzedniego od zadanego)
//         {
//             current = current->next;
//         }

//         Node *temp = current->next;          // przechowanie tymczasowe starego node
//         current->next = current->next->next; // przyczepiamy stary node do lewej strony newNode
//         delete temp;
//     }

//     --m_size;
// };
// int LinkedList::find(int value)
// {
//     if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         std::cout << "Lista jest pusta!\n";
//         return -1;
//     }
//     else
//     {
//         Node *current = head; // tworzymy wskaznik na aktualny node
//         int counter{0};
//         while (current != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
//         {

//             if (current->value == value)
//             {
//                 std::cout << "twoja wartosc znajduje sie pod indexem: " << counter << '\n';
//                 return counter;
//             }
//             current = current->next;
//             ++counter;
//         }
//     }
//     std::cerr << "Brak takiej warosci w liscie!\n";
//     return -1;
// };

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

// void LinkedList::print()
// {

//     if (head == nullptr) // sprawdzienie czy lista jest pusta
//     {
//         std::cout << "Lista jest pusta!\n";
//         return;
//     }
//     else
//     {
//         Node *current = head;      // tworzymy wskaznik na aktualny node
//         while (current != nullptr) // przechodzimy przez wszystkie nody az do "pustego"
//         {
//             std::cout << "Wartosc wezla to" << current->value << '\n';
//             current = current->next;
//         }
//     }
// };
