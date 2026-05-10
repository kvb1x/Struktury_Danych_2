#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>
#include "utility.h"
#include "BinaryHeap_q.h"
#include "LinkedList_q.h"

// zapis wynikow do pliku CSV
void saveResult(const std::string &filename, int size, double timeBH, double timeLL)
{
    std::string fullPath = "/home/kuba/DSA/SD/SD_2/results/" + filename;
    std::ofstream file(fullPath, std::ios::app);
    if (file.is_open())
    {
        file << size << ";" << timeBH << ";" << timeLL << "\n";
    }
    else
    {
        std::cerr << "Nie mozna otworzyc pliku do zapisu: " << fullPath << "\n";
    }
}

// Funkcja czyszczaca pliki przed rozpoczeciem nowych badan
void initResultFile(const std::string &filename)
{
    std::string fullPath = "/home/kuba/DSA/SD/SD_2/results/" + filename;
    std::ofstream file(fullPath, std::ios::trunc);
    if (file.is_open())
    {
        file << "Rozmiar;BinaryHeap;LinkedList\n";
    }
}

int minInt(int a, int b)
{
    return (a < b) ? a : b;
}

void clearBinaryHeap(BinaryHeap &bh)
{
    while (bh.getSize() > 0)
    {
        bh.extract_max();
    }
}

void normalizeElements(DataPair *data, int size, int probe)
{
    int base = probe * 200000 + 1;
    for (int i = 0; i < size; ++i)
    {
        data[i].element = base + i;
    }
}

int *buildRandomIndices(int size, int requestedCount, int &actualCount, std::mt19937 &gen)
{
    actualCount = minInt(size, requestedCount);

    int *allIndices = new int[size];
    for (int i = 0; i < size; ++i)
    {
        allIndices[i] = i;
    }

    for (int i = size - 1; i > 0; --i)
    {
        std::uniform_int_distribution<int> dist(0, i);
        int j = dist(gen);

        int temp = allIndices[i];
        allIndices[i] = allIndices[j];
        allIndices[j] = temp;
    }

    int *queries = new int[actualCount];
    for (int i = 0; i < actualCount; ++i)
    {
        queries[i] = allIndices[i];
    }

    delete[] allIndices;
    return queries;
}

void buildInsertBatch(int count, int baseElement, int *elements, int *priorities, std::mt19937 &gen)
{
    std::uniform_int_distribution<int> distPriority(-100000000, 100000000);

    for (int i = 0; i < count; ++i)
    {
        elements[i] = baseElement + i;
        priorities[i] = distPriority(gen);
    }
}

double measureFindMaxBH(BinaryHeap &bh, int queryCount)
{
    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int q = 0; q < queryCount; ++q)
    {
        dummy ^= bh.find_max();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureFindMaxLL(LinkedList &ll, int queryCount)
{
    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int q = 0; q < queryCount; ++q)
    {
        dummy ^= ll.find_max();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureReturnSizeBH(BinaryHeap &bh, int queryCount)
{
    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int q = 0; q < queryCount; ++q)
    {
        dummy ^= bh.return_size();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureReturnSizeLL(LinkedList &ll, int queryCount)
{
    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int q = 0; q < queryCount; ++q)
    {
        dummy ^= ll.return_size();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureInsertBH(DataPair *commonData, int size, int *elements, int *priorities, int batchCount)
{
    BinaryHeap bh(size + batchCount + 10);
    for (int i = 0; i < size; ++i)
    {
        bh.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < batchCount; ++i)
    {
        bh.insert(elements[i], priorities[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)batchCount;
}

double measureInsertLL(DataPair *commonData, int size, int *elements, int *priorities, int batchCount)
{
    LinkedList ll;
    for (int i = 0; i < size; ++i)
    {
        ll.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < batchCount; ++i)
    {
        ll.insert(elements[i], priorities[i]);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)batchCount;
}

double measureExtractBH(DataPair *commonData, int size, int batchCount)
{
    BinaryHeap bh(size + 10);
    for (int i = 0; i < size; ++i)
    {
        bh.insert(commonData[i].element, commonData[i].priority);
    }

    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < batchCount; ++i)
    {
        dummy ^= bh.extract_max();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)batchCount;
}

double measureExtractLL(DataPair *commonData, int size, int batchCount)
{
    LinkedList ll;
    for (int i = 0; i < size; ++i)
    {
        ll.insert(commonData[i].element, commonData[i].priority);
    }

    volatile int dummy = 0;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < batchCount; ++i)
    {
        dummy ^= ll.extract_max();
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)batchCount;
}

double measureIncreaseBH(DataPair *commonData, int size, int *queryIndices, int queryCount)
{
    BinaryHeap bh(size + 10);
    for (int i = 0; i < size; ++i)
    {
        bh.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; ++i)
    {
        int idx = queryIndices[i];
        bh.increase_key(commonData[idx].element, commonData[idx].priority + 5000000 + i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureIncreaseLL(DataPair *commonData, int size, int *queryIndices, int queryCount)
{
    LinkedList ll;
    for (int i = 0; i < size; ++i)
    {
        ll.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; ++i)
    {
        int idx = queryIndices[i];
        ll.increase_key(commonData[idx].element, commonData[idx].priority + 5000000 + i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureDecreaseBH(DataPair *commonData, int size, int *queryIndices, int queryCount)
{
    BinaryHeap bh(size + 10);
    for (int i = 0; i < size; ++i)
    {
        bh.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; ++i)
    {
        int idx = queryIndices[i];
        bh.decrease_key(commonData[idx].element, commonData[idx].priority - 5000000 - i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

double measureDecreaseLL(DataPair *commonData, int size, int *queryIndices, int queryCount)
{
    LinkedList ll;
    for (int i = 0; i < size; ++i)
    {
        ll.insert(commonData[i].element, commonData[i].priority);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < queryCount; ++i)
    {
        int idx = queryIndices[i];
        ll.decrease_key(commonData[idx].element, commonData[idx].priority - 5000000 - i);
    }
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)queryCount;
}

int main()
{
    char mainChoice{};

    while (true)
    {
        std::cout << "\n=== MENU GLOWNE ===\n";
        std::cout << "1 | KOPIEC BINARNY  -> wpisz 1\n";
        std::cout << "2 | LISTA JEDNOKIERUNKOWA  -> wpisz 2\n";
        std::cout << "3 | PRZEPROWADZ BADANIA  -> wpisz 3\n";
        std::cout << "q | Wyjscie z programu -> wpisz q\n";
        std::cout << "TWOJ WYBOR: ";
        std::cin >> mainChoice;

        if (mainChoice == 'q')
        {
            std::cout << "Zamykanie programu...\n";
            break;
        }

        switch (mainChoice)
        {
        case '1':
        {
            BinaryHeap bh(16);
            char subChoice{};
            while (true)
            {
                std::cout << "\n>| KOPIEC BINARNY |<\n";
                std::cout << "1 | Dodaj element (insert)\n";
                std::cout << "2 | Wyciagnij maksymalny (extract_max)\n";
                std::cout << "3 | Znajdz maksymalny (find_max)\n";
                std::cout << "4 | Zwieksz priorytet (increase_key)\n";
                std::cout << "5 | Zmniejsz priorytet (decrease_key)\n";
                std::cout << "6 | Rozmiar kolejki\n";
                std::cout << "7 | Zbuduj losowo\n";
                std::cout << "8 | Zbuduj z pliku\n";
                std::cout << "q | Powrot\n";
                std::cout << "Wybierz: ";
                std::cin >> subChoice;

                if (subChoice == 'q')
                    break;

                try
                {
                    if (subChoice == '1')
                    {
                        int elem, prio;
                        std::cout << "Podaj wartosc (element): ";
                        std::cin >> elem;
                        std::cout << "Podaj priorytet: ";
                        std::cin >> prio;
                        bh.insert(elem, prio);
                        std::cout << "Dodano\n";
                    }
                    else if (subChoice == '2')
                    {
                        std::cout << "Wyciagnieto element: " << bh.extract_max() << "\n";
                    }
                    else if (subChoice == '3')
                    {
                        std::cout << "Najwiekszy element to: " << bh.find_max() << "\n";
                    }
                    else if (subChoice == '4')
                    {
                        int elem, newPrio;
                        std::cout << "Podaj wartosc elementu : ";
                        std::cin >> elem;
                        std::cout << "Podaj nowy WIEKSZY priorytet: ";
                        std::cin >> newPrio;
                        bh.increase_key(elem, newPrio);
                        std::cout << "Priorytet zwiekszony.\n";
                    }
                    else if (subChoice == '5')
                    {
                        int elem, newPrio;
                        std::cout << "Podaj wartosc elementu : ";
                        std::cin >> elem;
                        std::cout << "Podaj nowy MNIEJSZY priorytet: ";
                        std::cin >> newPrio;
                        bh.decrease_key(elem, newPrio);
                        std::cout << "Priorytet zmniejszony.\n";
                    }
                    else if (subChoice == '6')
                    {
                        std::cout << "Rozmiar: " << bh.getSize() << "\n";
                    }
                    else if (subChoice == '7')
                    {
                        size_t size;
                        std::cout << "Podaj ilosc elementow do wylosowania: ";
                        std::cin >> size;
                        clearBinaryHeap(bh);
                        DataPair *data = generate_random_data_array(size);
                        for (size_t i = 0; i < size; i++)
                        {
                            data[i].element = static_cast<int>(i) + 1;
                            bh.insert(data[i].element, data[i].priority);
                        }
                        delete[] data;
                        std::cout << "Zbudowano losowo.\n";
                    }
                    else if (subChoice == '8')
                    {
                        std::string path;
                        std::cout << "Podaj nazwe pliku: ";
                        std::cin >> path;
                        size_t loaded_size = 0;
                        DataPair *data = load_data_from_file(path, loaded_size);
                        if (data)
                        {
                            clearBinaryHeap(bh);
                            for (size_t i = 0; i < loaded_size; i++)
                            {
                                bh.insert(data[i].element, data[i].priority);
                            }
                            delete[] data;
                            std::cout << "Wczytano " << loaded_size << " elementow.\n";
                        }
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "BLAD: " << e.what() << "\n";
                }
            }
            break;
        }

        case '2':
        {
            LinkedList ll;
            char subChoice{};
            while (true)
            {
                std::cout << "\n>| LISTA JEDNOKIERUNKOWA |<\n";
                std::cout << "1 | Dodaj element (insert)\n";
                std::cout << "2 | Wyciagnij maksymalny (extract_max)\n";
                std::cout << "3 | Znajdz maksymalny (find_max)\n";
                std::cout << "4 | Zwieksz priorytet (increase_key)\n";
                std::cout << "5 | Zmniejsz priorytet (decrease_key)\n";
                std::cout << "6 | Rozmiar kolejki\n";
                std::cout << "7 | Zbuduj losowo\n";
                std::cout << "8 | Zbuduj z pliku\n";
                std::cout << "q | Powrot\n";
                std::cout << "Wybierz: ";
                std::cin >> subChoice;

                if (subChoice == 'q')
                    break;

                try
                {
                    if (subChoice == '1')
                    {
                        int elem, prio;
                        std::cout << "Podaj wartosc (element): ";
                        std::cin >> elem;
                        std::cout << "Podaj priorytet: ";
                        std::cin >> prio;
                        ll.insert(elem, prio);
                        std::cout << "Dodano.\n";
                    }
                    else if (subChoice == '2')
                    {
                        std::cout << "Wyciagnieto element: " << ll.extract_max() << "\n";
                    }
                    else if (subChoice == '3')
                    {
                        std::cout << "Najwiekszy element to: " << ll.find_max() << "\n";
                    }
                    else if (subChoice == '4')
                    {
                        int elem, newPrio;
                        std::cout << "Podaj wartosc elementu : ";
                        std::cin >> elem;
                        std::cout << "Podaj nowy WIEKSZY priorytet: ";
                        std::cin >> newPrio;
                        ll.increase_key(elem, newPrio);
                        std::cout << "Priorytet zwiekszony.\n";
                    }
                    else if (subChoice == '5')
                    {
                        int elem, newPrio;
                        std::cout << "Podaj wartosc elementu : ";
                        std::cin >> elem;
                        std::cout << "Podaj nowy MNIEJSZY priorytet: ";
                        std::cin >> newPrio;
                        ll.decrease_key(elem, newPrio);
                        std::cout << "Priorytet zmniejszony.\n";
                    }
                    else if (subChoice == '6')
                    {
                        std::cout << "Rozmiar: " << ll.getSize() << "\n";
                    }
                    else if (subChoice == '7')
                    {
                        size_t size;
                        std::cout << "Podaj ilosc elementow do wylosowania: ";
                        std::cin >> size;
                        ll.clear();
                        DataPair *data = generate_random_data_array(size);
                        for (size_t i = 0; i < size; i++)
                        {
                            data[i].element = static_cast<int>(i) + 1;
                            ll.insert(data[i].element, data[i].priority);
                        }
                        delete[] data;
                        std::cout << "Zbudowano losowo.\n";
                    }
                    else if (subChoice == '8')
                    {
                        std::string path;
                        std::cout << "Podaj nazwe pliku: ";
                        std::cin >> path;
                        size_t loaded_size = 0;
                        DataPair *data = load_data_from_file(path, loaded_size);
                        if (data)
                        {
                            ll.clear();
                            for (size_t i = 0; i < loaded_size; i++)
                            {
                                ll.insert(data[i].element, data[i].priority);
                            }
                            delete[] data;
                            std::cout << "Wczytano " << loaded_size << " elementow.\n";
                        }
                    }
                }
                catch (const std::exception &e)
                {
                    std::cerr << "BLAD: " << e.what() << "\n";
                }
            }
            break;
        }

        case '3':
        {
            std::cout << "\n=== START BADAN ===\n";

            int sizes[] = {
                5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000,
                45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000};

            int probes = 50;

            std::cout << "Przygotowywanie plikow wynikowych...\n";
            initResultFile("insert.csv");
            initResultFile("extract_max.csv");
            initResultFile("find_max.csv");
            initResultFile("increase_key.csv");
            initResultFile("decrease_key.csv");
            initResultFile("return_size.csv");

            std::random_device rd;
            std::mt19937 gen(rd());

            for (int size : sizes)
            {
                std::cout << "Testowanie dla rozmiaru N = " << size << "...\n";

                double sum_BH_insert = 0, sum_LL_insert = 0;
                double sum_BH_extract = 0, sum_LL_extract = 0;
                double sum_BH_find = 0, sum_LL_find = 0;
                double sum_BH_inc_key = 0, sum_LL_inc_key = 0;
                double sum_BH_dec_key = 0, sum_LL_dec_key = 0;
                double sum_BH_size = 0, sum_LL_size = 0;

                for (int p = 0; p < probes; ++p)
                {
                    DataPair *commonData = generate_random_data_array(size);
                    normalizeElements(commonData, size, p);

                    int query_count = 1000;
                    int batch_count = minInt(size, 1000);

                    int incQueryCount = 0;
                    int decQueryCount = 0;
                    int *incQueries = buildRandomIndices(size, batch_count, incQueryCount, gen);
                    int *decQueries = buildRandomIndices(size, batch_count, decQueryCount, gen);

                    int *insertElements = new int[batch_count];
                    int *insertPriorities = new int[batch_count];
                    buildInsertBatch(batch_count, 100000000 + p * 200000, insertElements, insertPriorities, gen);

                    BinaryHeap bh(size + 10);
                    for (int i = 0; i < size; ++i)
                    {
                        bh.insert(commonData[i].element, commonData[i].priority);
                    }

                    sum_BH_find += measureFindMaxBH(bh, query_count);
                    sum_BH_size += measureReturnSizeBH(bh, query_count);

                    sum_BH_insert += measureInsertBH(commonData, size, insertElements, insertPriorities, batch_count);
                    sum_BH_extract += measureExtractBH(commonData, size, batch_count);
                    sum_BH_inc_key += measureIncreaseBH(commonData, size, incQueries, incQueryCount);
                    sum_BH_dec_key += measureDecreaseBH(commonData, size, decQueries, decQueryCount);

                    LinkedList ll;
                    for (int i = 0; i < size; ++i)
                    {
                        ll.insert(commonData[i].element, commonData[i].priority);
                    }

                    sum_LL_find += measureFindMaxLL(ll, query_count);
                    sum_LL_size += measureReturnSizeLL(ll, query_count);

                    sum_LL_insert += measureInsertLL(commonData, size, insertElements, insertPriorities, batch_count);
                    sum_LL_extract += measureExtractLL(commonData, size, batch_count);
                    sum_LL_inc_key += measureIncreaseLL(commonData, size, incQueries, incQueryCount);
                    sum_LL_dec_key += measureDecreaseLL(commonData, size, decQueries, decQueryCount);

                    delete[] insertElements;
                    delete[] insertPriorities;
                    delete[] incQueries;
                    delete[] decQueries;
                    delete[] commonData;
                }

                saveResult("insert.csv", size, sum_BH_insert / probes, sum_LL_insert / probes);
                saveResult("extract_max.csv", size, sum_BH_extract / probes, sum_LL_extract / probes);
                saveResult("find_max.csv", size, sum_BH_find / probes, sum_LL_find / probes);
                saveResult("increase_key.csv", size, sum_BH_inc_key / probes, sum_LL_inc_key / probes);
                saveResult("decrease_key.csv", size, sum_BH_dec_key / probes, sum_LL_dec_key / probes);
                saveResult("return_size.csv", size, sum_BH_size / probes, sum_LL_size / probes);
            }

            std::cout << "\nBadania ukonczone\n";
            break;
        }

        default:
            std::cerr << "Nieznana opcja\n";
            break;
        }
    }

    return 0;
}
