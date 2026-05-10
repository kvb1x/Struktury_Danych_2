#pragma once
#include <string>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>
#include <functional> // do std::invoke
#include <cstdint>    // do int32_t (4-bajtowa liczba całkowita)

// Struktura pomocnicza do przechowywania pary (element, priorytet)

struct DataPair
{
    int32_t element;
    int32_t priority;
};

// Generuje plik .txt zawierający wiersze z losowymi parami: [element] [priorytet]

inline void generate_random_data_file(const std::string &dest_path, int32_t min, int32_t max, size_t n_rows)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int32_t> dist(min, max);

    std::ofstream file(dest_path);
    if (!file.is_open())
    {
        std::cerr << "Blad: Nie mozna otworzyc pliku do zapisu: " << dest_path << "\n";
        return;
    }

    for (size_t i = 0; i < n_rows; i++)
    {
        file << dist(gen) << " " << dist(gen) << "\n";
    }
    file.close();
}

// wczytuje dane z pliku do dynamicznie alokowanej tablicy.

inline DataPair *load_data_from_file(const std::string &src_path, size_t &out_size)
{
    std::ifstream file(src_path);
    if (!file.is_open())
    {
        std::cerr << "Blad: Nie mozna otworzyc pliku do odczytu: " << src_path << "\n";
        out_size = 0;
        return nullptr;
    }

    // liczymy linie zeby sprawdzic rozmiar
    size_t lines = 0;
    int32_t temp_e, temp_p;
    while (file >> temp_e >> temp_p)
    {
        lines++;
    }

    file.clear();  // czysxzcenie flag bledow
    file.seekg(0); // powrot na poczastk

    out_size = lines;
    DataPair *array = new DataPair[lines];

    // zapis do tablicy
    for (size_t i = 0; i < lines; i++)
    {
        file >> array[i].element >> array[i].priority;
    }
    file.close();
    return array;
}

// Generuje losowe dane bezpośrednio do dynamicznej tablicy dla szybszych testow
inline DataPair *generate_random_data_array(size_t n_rows)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // Zakres dla wartości elementów  od 1 do 1 000 000
    std::uniform_int_distribution<int32_t> distElement(1, 1000000);

    // ZAKRES PRIORYTETÓW: od 1 do (rozmiar * 5)
    std::uniform_int_distribution<int32_t> distPriority(1, n_rows * 5);

    DataPair *array = new DataPair[n_rows];
    for (size_t i = 0; i < n_rows; i++)
    {
        array[i].element = distElement(gen);
        array[i].priority = distPriority(gen); // Priorytet kilkukrotnie większy od n_rows
    }
    return array;
}

// POMIARY I TESTOWANIE

// Mierzy czas pojedynczego wywołania metody w ns
template <typename ObjectType, typename MethodType, typename... Parameters>
unsigned long long measure_time(ObjectType *object, MethodType method, Parameters... params)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::invoke(method, object, std::forward<Parameters>(params)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    return duration.count();
}

// Weryfikacja dzialania metody zwracajacej wartosxc
template <typename ObjectType, typename MethodType, typename ExpectedType, typename... Parameters>
bool assert_method(ObjectType *object, MethodType method, ExpectedType expected, Parameters... params)
{
    auto result = std::invoke(method, object, std::forward<Parameters>(params)...);

    if (result == expected)
    {
        std::cout << "[PASSED] Oczekiwano: " << expected << ", Otrzymano: " << result << "\n";
        return true;
    }
    else
    {
        std::cerr << "[FAILED] Oczekiwano: " << expected << ", Otrzymano: " << result << "\n";
        return false;
    }
}

// max fnc
template <typename T>
T get_max(T a, T b)
{
    return (a > b) ? a : b;
}
