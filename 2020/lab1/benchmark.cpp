<<<<<<< HEAD
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "main.hpp"
using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

// Функция сравнения для std::sort
bool ComparePairs(const TKeyValuePair& a, const TKeyValuePair& b) {
    return memcmp(a.number, b.number, NUMBER_OF_DIGITS) < 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Чтение данных
    std::vector<TKeyValuePair> data;
    char line[MAX_STRING_LENGTH*2];
    
    while (std::cin.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;
        
        char* delimiter = strrchr(line, '\t');
        if (!delimiter) {
            char* last_space = nullptr;
            for (char* p = line; *p; p++) {
                if (*p == ' ' && p[1] != ' ' && p[1] != '\0') {
                    last_space = p;
                }
            }
            delimiter = last_space;
        }
        
        if (!delimiter || delimiter == line) continue;
        
        *delimiter = '\0';
        char* value = delimiter + 1;
        while (*value == ' ') value++;
        
        data.emplace_back(line, value);
    }

    // Создаем копию для std::sort
    std::vector<TKeyValuePair> stl_sorted = data;

    // Измеряем время работы сортировки
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();

    //start_ts = std::chrono::system_clock::now();
    // Radix-сортировка
    RadixSort(data.data(), data.size());
    auto end_ts = std::chrono::system_clock::now();
    uint64_t rad_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "Radix Sort Results:\n";
    for (const auto& item : data) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */
    
    start_ts = std::chrono::system_clock::now();
    // STL сортировка
    std::sort(stl_sorted.begin(), stl_sorted.end(), ComparePairs);
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "\nSTL Sort Results:\n";
    for (const auto& item : stl_sorted) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */


    std::cout << "Radix sort time: " << rad_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "Input array size: " << data.size() << std::endl;

    return 0;
}
=======
<<<<<<< HEAD
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "main.hpp"
using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

// Функция сравнения для std::sort
bool ComparePairs(const TKeyValuePair& a, const TKeyValuePair& b) {
    return memcmp(a.number, b.number, NUMBER_OF_DIGITS) < 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Чтение данных
    std::vector<TKeyValuePair> data;
    char line[MAX_STRING_LENGTH*2];
    
    while (std::cin.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;
        
        char* delimiter = strrchr(line, '\t');
        if (!delimiter) {
            char* last_space = nullptr;
            for (char* p = line; *p; p++) {
                if (*p == ' ' && p[1] != ' ' && p[1] != '\0') {
                    last_space = p;
                }
            }
            delimiter = last_space;
        }
        
        if (!delimiter || delimiter == line) continue;
        
        *delimiter = '\0';
        char* value = delimiter + 1;
        while (*value == ' ') value++;
        
        data.emplace_back(line, value);
    }

    // Создаем копию для std::sort
    std::vector<TKeyValuePair> stl_sorted = data;

    // Измеряем время работы сортировки
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();

    //start_ts = std::chrono::system_clock::now();
    // Radix-сортировка
    RadixSort(data.data(), data.size());
    auto end_ts = std::chrono::system_clock::now();
    uint64_t rad_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "Radix Sort Results:\n";
    for (const auto& item : data) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */
    
    start_ts = std::chrono::system_clock::now();
    // STL сортировка
    std::sort(stl_sorted.begin(), stl_sorted.end(), ComparePairs);
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "\nSTL Sort Results:\n";
    for (const auto& item : stl_sorted) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */


    std::cout << "Radix sort time: " << rad_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "Input array size: " << data.size() << std::endl;

    return 0;
}
=======
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "main.hpp"
using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";

// Функция сравнения для std::sort
bool ComparePairs(const TKeyValuePair& a, const TKeyValuePair& b) {
    return memcmp(a.number, b.number, NUMBER_OF_DIGITS) < 0;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    // Чтение данных
    std::vector<TKeyValuePair> data;
    char line[MAX_STRING_LENGTH*2];
    
    while (std::cin.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;
        
        char* delimiter = strrchr(line, '\t');
        if (!delimiter) {
            char* last_space = nullptr;
            for (char* p = line; *p; p++) {
                if (*p == ' ' && p[1] != ' ' && p[1] != '\0') {
                    last_space = p;
                }
            }
            delimiter = last_space;
        }
        
        if (!delimiter || delimiter == line) continue;
        
        *delimiter = '\0';
        char* value = delimiter + 1;
        while (*value == ' ') value++;
        
        data.emplace_back(line, value);
    }

    // Создаем копию для std::sort
    std::vector<TKeyValuePair> stl_sorted = data;

    // Измеряем время работы сортировки
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();

    //start_ts = std::chrono::system_clock::now();
    // Radix-сортировка
    RadixSort(data.data(), data.size());
    auto end_ts = std::chrono::system_clock::now();
    uint64_t rad_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "Radix Sort Results:\n";
    for (const auto& item : data) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */
    
    start_ts = std::chrono::system_clock::now();
    // STL сортировка
    std::sort(stl_sorted.begin(), stl_sorted.end(), ComparePairs);
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    
    /* std::cout << "\nSTL Sort Results:\n";
    for (const auto& item : stl_sorted) {
        std::cout << item.number[0] << ' '
                 << item.number[1] << item.number[2] << item.number[3] << ' '
                 << item.number[4] << item.number[5] << '\t'
                 << item.value << '\n';
    } */


    std::cout << "Radix sort time: " << rad_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "Input array size: " << data.size() << std::endl;

    return 0;
}
>>>>>>> 2ffdb2565556500fb9daa6f9a9c57f5e5bcef63e
>>>>>>> 017b9db (8 9 fiished)
