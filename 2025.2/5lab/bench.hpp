#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include "fin.hpp" 

struct Benchmark {
    std::string generateRandomString(int length) {
        static const char alphanum[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
        static std::mt19937 rng(std::random_device{}());
        static std::uniform_int_distribution<> dist(0, sizeof(alphanum) - 2);
        
        std::string result;
        result.reserve(length);
        for (int i = 0; i < length; ++i) {
            result += alphanum[dist(rng)];
        }
        return result;
    }

    void benchmarkConstruction(int textSize) {
        std::string text = generateRandomString(textSize);
        
        auto start = std::chrono::high_resolution_clock::now();
        auto suffix_array = BuildArr(text + "$");
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);//время за которое построили массив
        std::cout << "Construction for text size " << textSize 
                  << ": " << duration.count() << " μs" << std::endl;
    }

    void benchmarkSearch(int textSize, int patternSize, int numSearches) {//размер текста паттерна количество паттернов
        std::string text = generateRandomString(textSize);
        auto suffix_array = BuildArr(text + "$");
        
        std::vector<std::string> patterns;
        for (int i = 0; i < numSearches; ++i) {
            patterns.push_back(generateRandomString(patternSize));
        }
        
        auto start = std::chrono::high_resolution_clock::now();
        for (const auto& pattern : patterns) {
            auto result = Search(text, pattern, suffix_array);
        }
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        std::cout << "Search " << numSearches << " patterns (size " << patternSize //время поиска
                  << ") in text size " << textSize << ": " 
                  << duration.count() << " μs" << std::endl;
    }

    void benchmarkMemoryUsage(int textSize) {
        std::string text = generateRandomString(textSize);
        
        auto suffix_array = BuildArr(text + "$");
        
        size_t memory_used = text.size() + suffix_array.size() * sizeof(int);
        std::cout << "Estimated memory for text size " << textSize 
                  << ": " << memory_used / 1024 << " KB" << std::endl;
    }
};
