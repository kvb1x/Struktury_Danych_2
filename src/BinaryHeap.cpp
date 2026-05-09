
#include "BinaryHeap_q.h"
#include <algorithm> // std::swap
#include <stdexcept>

// lewe dziecko 2k + 1
// prawe   2k + 2
// rodzic   (k - 2)/2

BinaryHeap::BinaryHeap(int capacity) : m_size{0}, m_capacity{capacity}, heap{new Node[capacity]} {};
BinaryHeap::~BinaryHeap() { delete[] heap; };

void BinaryHeap::heapifyUp(int index)
{
    if (index < 0 || index > m_size)
    {
        throw std::runtime_error("Nieprawidlowy index");
    }

    int parent = (index - 1) / 2;

    while (heap[index].priority > heap[parent].priority)
    {
        std::swap(heap[index], heap[parent]);
        if (heap[index].priority == heap[parent].priority)
        {
            return;
        }
        index = parent;
        parent = (index - 1) / 2;
    };
};
void BinaryHeap::heapifyDown(int index)
{
    if (index < 0 || index > m_size)
    {
        throw std::runtime_error("Nieprawidlowy index");
    }

    while (true)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if ((left < m_size) && heap[left].priority > heap[largest].priority) // jelsi lewe jest wyzsze to swap
        {

            largest = left;
        }

        if ((right < m_size) && heap[right].priority > heap[largest].priority) // jelsi lewe jest wyzsze to swap
        {

            largest = right;
        }
        if (largest != index)
        {
            std::swap(heap[index], heap[largest]);
            index = largest;
        }
        else
        {
            return;
        }
    }
};
void BinaryHeap::resize()
{
    m_capacity = m_capacity * 2; // zwiekszanie rozmiaru tablicy *2
    if (m_capacity == 0)
    {
        m_capacity = 1;
    }
    Node *newHeap = new Node[m_capacity];
    for (int i = 0; i < m_size; ++i)
    {
        newHeap[i] = heap[i];
    }
    delete[] heap;
    heap = newHeap;
};

int BinaryHeap::getSize() { return m_size; };

void BinaryHeap::insert(int element, int priority)
{
    if (m_capacity == m_size)
    {
        resize();
    }

    heap[m_size].element = element; // pakujemy wartosc do nowego wezla
    heap[m_size].priority = priority;

    heapifyUp(m_size);
    ++m_size;
};
int BinaryHeap::extract_max()
{
    if (m_size <= 0)
    {
        throw std::runtime_error(" Kolejka jest pusta!");
    }
    Node max = heap[0];

    int temp = max.element;

    heap[0] = heap[m_size - 1];
    --m_size;
    heapifyDown(0);

    return temp;
};
int BinaryHeap::find_max() { return heap[0].element; };
void BinaryHeap::modify_key(int element, int priority)
{

    for (int i = 0; i < m_size; ++i)
    {
        if (heap[i].element == element)
        {
            if (heap[i].priority <= priority)
            {
                heap[i].priority = priority;
                heapifyUp(i);
                return;
            }
            else
            {
                heap[i].priority = priority;
                heapifyDown(i);
                return;
            }
        }
    }
    throw std::runtime_error("Brak takiego leementu");
};
int BinaryHeap::return_size() { return m_size; };
