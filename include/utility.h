#pragma once
#include <random>
#include <string>
#include <fstream>
#include <chrono>
int getRandom(int min, int max)
{

    int seed{1000};
    // std::random_device rd;
    static std::mt19937 gen(seed);                     // uruchomienei mt
    std::uniform_int_distribution<int> dist(min, max); // ustalenie min i max

    return dist(gen); // przypisanie losowej liczby do indexu
}

void generateFile(int size, std::string fileData)
{
    // int size{5000}; // size bierzemy z jakiegos zrodla
    int min{1};
    int max{100000};
    // std::string fileData{"SD/SD_1/data/test_data.txt"};
    std::ofstream file(fileData);
    if (file.is_open())
    {
        for (int i = 0; i < size; ++i)
        {
            int value{getRandom(min, max)};

            file << value << " ";
        }
        file.close();
        std::cout << "Wygenerowano nowe dane!\n";
    }
    else
    {
        std::cerr << "Blad zapisu pliku o nazwie" << fileData << "!\n";
    }
}

// zapis wynikow do CSV
void saveResult(std::string fileName, int size, long long timeNs)
{
    // Sciezka musi istniec w systemie: SD/SD_1/results/ >>>> filename trza napisac jako argument
    std::string path = "/home/kuba/DSA/SD/SD_1/results/" + fileName;
    std::ofstream file(path, std::ios::app); // app sprawia ze dopisujemy do pliku zamiast go nadpisywac

    if (file.is_open())
    {
        file << size << "," << timeNs << "\n"; // format: rozmiar,czas(ns)
        file.close();
    }
    else
    {
        std::cerr << "Nie udalo sie zapisac wyniku do: " << path << "\n";
    }
}

//  pomiar czasu
class Timer
{
    // zmienna do zapamietania dokladnego momentu wlaczenia stopera
    std::chrono::high_resolution_clock::time_point start_time;

public:
    // funkcja ktora wlacza stoper
    void start()
    {
        // pobieramy aktualny czas z systemu i zapisujemy jako start
        start_time = std::chrono::high_resolution_clock::now();
    }

    // funkcja ktora zatrzymuje stoper i zwraca ile czasu minelo
    long long stop()
    {
        // pobieramy z systemu czas w momencie zatrzymania
        auto end_time = std::chrono::high_resolution_clock::now();

        // obliczamy roznice (czas koncowy minus czas startu) i przeliczamy ja na nanosekundy, zeby zwrocic konkretna liczbe
        return std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time).count();
    }
};
