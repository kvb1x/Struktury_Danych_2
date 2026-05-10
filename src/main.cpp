#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include "utility.h"
#include "BinaryHeap_q.h"
#include "LinkedList_q.h"

//  zapis wynikow do pliku CSV
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
    std::ofstream file(fullPath, std::ios::trunc); // trunc czysci plik
    if (file.is_open())
    {
        file << "Rozmiar;BinaryHeap;LinkedList\n";
    }
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
                        DataPair *data = generate_random_data_array(size);
                        // czyszczenie obecnego kopca przez tworzenie od nowa
                        for (size_t i = 0; i < size; i++)
                            bh.insert(data[i].element, data[i].priority);
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
                            for (size_t i = 0; i < loaded_size; i++)
                                bh.insert(data[i].element, data[i].priority);
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
                            ll.insert(data[i].element, data[i].priority);
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
                                ll.insert(data[i].element, data[i].priority);
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
                45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000,
                85000, 90000, 95000, 100000};

            int probes = 50; // Ilosc seedów dla kazdego rozmiaru

            std::cout << "Przygotowywanie plikow wynikowych...\n";
            initResultFile("insert.csv");
            initResultFile("extract_max.csv");
            initResultFile("find_max.csv");
            initResultFile("increase_key.csv");
            initResultFile("decrease_key.csv");
            initResultFile("return_size.csv");

            // Generator do losowania randomowych indeksow wewnatrz testow
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
                    // 1. Generujemy wspolne dane dla obu struktur
                    DataPair *commonData = generate_random_data_array(size);

                    // przygotowanie zmiennych do testow
                    int testElem = 999999;
                    int testPrio = 999999;

                    std::uniform_int_distribution<int> distIndex(0, size - 1);

                    // Element do testu INCREASE_KEY (zwiekszamy priorytet)
                    int modIncIndex = distIndex(gen);
                    int elemToIncrease = commonData[modIncIndex].element;
                    int newIncPrio = commonData[modIncIndex].priority + 5000000;

                    // Element do testu DECREASE_KEY (zmniejszamy priorytet)
                    int modDecIndex = distIndex(gen);
                    // Upewniamy sie, ze nie wylosujemy tego samego elementu co do increase_key
                    while (modDecIndex == modIncIndex)
                    {
                        modDecIndex = distIndex(gen);
                    }
                    int elemToDecrease = commonData[modDecIndex].element;
                    int newDecPrio = commonData[modDecIndex].priority - 5000000; // Drastyczny spadek

                    // TESTY KOPIEC BINARNY

                    BinaryHeap bh(size + 10);
                    for (int i = 0; i < size; ++i)
                    {
                        bh.insert(commonData[i].element, commonData[i].priority);
                    }

                    // metodyka zapytan dla wyszukiwania i rozmiaru (czas o(1) - 1000 zapytan)
                    int query_count = 1000;

                    // Test: find_max
                    auto start = std::chrono::high_resolution_clock::now();
                    for (int q = 0; q < query_count; ++q)
                    {
                        volatile int dummy = bh.find_max();
                    }
                    auto end = std::chrono::high_resolution_clock::now();
                    sum_BH_find += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)query_count;

                    // Test: return_size
                    start = std::chrono::high_resolution_clock::now();
                    for (int q = 0; q < query_count; ++q)
                    {
                        volatile int dummy = bh.return_size();
                    }
                    end = std::chrono::high_resolution_clock::now();
                    sum_BH_size += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)query_count;

                    // Testy modyfikujące strukture
                    sum_BH_insert += measure_time(&bh, &BinaryHeap::insert, testElem, testPrio);
                    sum_BH_extract += measure_time(&bh, &BinaryHeap::extract_max);
                    sum_BH_inc_key += measure_time(&bh, &BinaryHeap::increase_key, elemToIncrease, newIncPrio);
                    sum_BH_dec_key += measure_time(&bh, &BinaryHeap::decrease_key, elemToDecrease, newDecPrio);

                    //  TESTY LISTA JEDNOKIERUNKOWA

                    LinkedList ll;
                    for (int i = 0; i < size; ++i)
                    {
                        ll.insert(commonData[i].element, commonData[i].priority);
                    }

                    // Test: find_max
                    start = std::chrono::high_resolution_clock::now();
                    for (int q = 0; q < query_count; ++q)
                    {
                        volatile int dummy = ll.find_max();
                    }
                    end = std::chrono::high_resolution_clock::now();
                    sum_LL_find += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)query_count;

                    // Test: return_size
                    start = std::chrono::high_resolution_clock::now();
                    for (int q = 0; q < query_count; ++q)
                    {
                        volatile int dummy = ll.return_size();
                    }
                    end = std::chrono::high_resolution_clock::now();
                    sum_LL_size += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / (double)query_count;

                    // Testy modyfikujace strukture
                    sum_LL_insert += measure_time(&ll, &LinkedList::insert, testElem, testPrio);
                    sum_LL_extract += measure_time(&ll, &LinkedList::extract_max);
                    sum_LL_inc_key += measure_time(&ll, &LinkedList::increase_key, elemToIncrease, newIncPrio);
                    sum_LL_dec_key += measure_time(&ll, &LinkedList::decrease_key, elemToDecrease, newDecPrio);

                    delete[] commonData; // Oczyszczanie pamieci po zakonczonej probie
                }

                // Zapisywanie wynikow do odpowiednich 6 plikow CSV
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
