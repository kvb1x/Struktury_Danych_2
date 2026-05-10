#include "BinaryHeap_q.h"
#include <algorithm> // std::swap
#include <stdexcept>

// lewe dziecko 2k + 1
// prawe   2k + 2
// rodzic   (k - 1)/2

BinaryHeap::BinaryHeap(int capacity) : m_size{0}, m_capacity{capacity}, heap{new Node[capacity]}, insertionCounter{0} {};
BinaryHeap::~BinaryHeap() { delete[] heap; };

bool BinaryHeap::isHigher(int a, int b)
{
    if (heap[a].priority > heap[b].priority)
        return true;
    if (heap[a].priority < heap[b].priority)
        return false;

    return heap[a].order < heap[b].order;
}

void BinaryHeap::heapifyUp(int index)
{
    if (index < 0 || index >= m_size)
    {
        throw std::runtime_error("Nieprawidlowy index");
    }

    while (index > 0)
    {
        int parent = (index - 1) / 2;

        if (isHigher(index, parent))
        {
            std::swap(heap[index], heap[parent]);
            index = parent;
        }
        else
        {
            return;
        }
    }
};

void BinaryHeap::heapifyDown(int index)
{
    if (index < 0 || index >= m_size)
    {
        throw std::runtime_error("Nieprawidlowy index");
    }

    while (true)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < m_size && isHigher(left, largest)) // jesli lewe jest wyzsze to swap
        {
            largest = left;
        }

        if (right < m_size && isHigher(right, largest)) // jesli prawe jest wyzsze to swap
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
    heap[m_size].order = insertionCounter++;

    ++m_size;

    heapifyUp(m_size - 1);
};

int BinaryHeap::extract_max()
{
    if (m_size <= 0)
    {
        throw std::runtime_error("Kolejka jest pusta!");
    }

    Node max = heap[0];
    int temp = max.element;

    heap[0] = heap[m_size - 1];
    --m_size;

    if (m_size > 0)
    {
        heapifyDown(0);
    }

    return temp;
};

int BinaryHeap::find_max()
{
    if (m_size <= 0)
    {
        throw std::runtime_error("Kolejka jest pusta!");
    }
    return heap[0].element;
};

void BinaryHeap::increase_key(int element, int priority)
{
    for (int i = 0; i < m_size; ++i)
    {
        if (heap[i].element == element)
        {
            if (priority < heap[i].priority)
            {
                throw std::invalid_argument("W operacji increase_key nowy priorytet nie moze byc mniejszy!");
            }
            heap[i].priority = priority;
            heapifyUp(i);
            return;
        }
    }
    throw std::runtime_error("Brak takiego elementu w kolejce!\n");
};

void BinaryHeap::decrease_key(int element, int priority)
{
    for (int i = 0; i < m_size; ++i)
    {
        if (heap[i].element == element)
        {
            if (priority > heap[i].priority)
            {
                throw std::invalid_argument("W operacji decrease_key nowy priorytet nie moze byc wiekszy!");
            }
            heap[i].priority = priority;
            heapifyDown(i);
            return;
        }
    }
    throw std::runtime_error("Brak takiego elementu w kolejce!\n");
};

int BinaryHeap::return_size() { return m_size; };
