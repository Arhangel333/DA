#include <iostream>
#include <cstring>
#include <cstdlib>

const int NUMBER_OF_DIGITS = 6;
const int MAX_DIGIT_VALUE = 256;
const int MAX_STRING_LENGTH = 2048;

struct TKeyValuePair {
    char number[NUMBER_OF_DIGITS];
    char* value;
    
    TKeyValuePair() : value(nullptr) {
        memset(number, ' ', NUMBER_OF_DIGITS); // Заполняем пробелами
    }
    
    TKeyValuePair(const char* num, const char* val) {
        // Копируем только первые 6 значимых символов (игнорируя пробелы)
        int j = 0;
        for (int i = 0; i < strlen(num) && j < NUMBER_OF_DIGITS; i++) {
            if (num[i] != ' ') {
                number[j++] = num[i];
            }
        }
        // Заполняем оставшиеся пробелами
        while (j < NUMBER_OF_DIGITS) {
            number[j++] = ' ';
        }
        
        value = new char[strlen(val) + 1];
        strcpy(value, val);
    }
    
    ~TKeyValuePair() {
        delete[] value;
    }
    
    TKeyValuePair(const TKeyValuePair& other) {
        memcpy(number, other.number, NUMBER_OF_DIGITS);
        value = new char[strlen(other.value) + 1];
        strcpy(value, other.value);
    }
    
    TKeyValuePair& operator=(const TKeyValuePair& other) {
        if (this != &other) {
            delete[] value;
            memcpy(number, other.number, NUMBER_OF_DIGITS);
            value = new char[strlen(other.value) + 1];
            strcpy(value, other.value);
        }
        return *this;
    }
};

void RadixSort(TKeyValuePair* pairs, size_t size) {
    int countArray[MAX_DIGIT_VALUE];
    TKeyValuePair* tempArray = new TKeyValuePair[size];

    for (int pos = NUMBER_OF_DIGITS - 1; pos >= 0; pos--) {
        memset(countArray, 0, sizeof(countArray));

        for (size_t i = 0; i < size; i++) {
            unsigned char c = pairs[i].number[pos];
            countArray[c]++;
        }

        for (int i = 1; i < MAX_DIGIT_VALUE; i++) {
            countArray[i] += countArray[i-1];
        }

        for (int i = size - 1; i >= 0; i--) {
            unsigned char c = pairs[i].number[pos];
            tempArray[--countArray[c]] = pairs[i];
        }

        for (size_t i = 0; i < size; i++) {
            pairs[i] = tempArray[i];
        }
    }
    delete[] tempArray;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t capacity = 16;
    size_t size = 0;
    TKeyValuePair* pairs = new TKeyValuePair[capacity];
    
    char line[MAX_STRING_LENGTH * 2];
    while (std::cin.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;
        
        if (size >= capacity) {
            capacity *= 2;
            TKeyValuePair* newPairs = new TKeyValuePair[capacity];
            for (size_t i = 0; i < size; i++) {
                newPairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = newPairs;
        }

        // Находим последний таб (разделитель между номером и значением)
        char* delimiter = strrchr(line, '\t');
        if (!delimiter) {
            // Если таба нет, ищем последний пробел перед значением
            char* last_space = nullptr;
            char* p = line;
            while (*p) {
                if (*p == ' ' && *(p+1) != ' ' && *(p+1) != '\0') {
                    last_space = p;
                }
                p++;
            }
            delimiter = last_space;
        }
        
        if (!delimiter) continue;
        
        *delimiter = '\0';
        char* number = line;
        char* value = delimiter + 1;
        
        // Пропускаем ведущие пробелы в значении
        while (*value == ' ') value++;
        
        pairs[size] = TKeyValuePair(number, value);
        size++;
    }
    //std::cout<<size<<"size "<<std::endl;
    RadixSort(pairs, size);

    // Выводим результаты
    for (size_t i = 0; i < size; i++) {
        // Восстанавливаем оригинальный формат номера
        std::cout << pairs[i].number[0] << ' ' 
                 << pairs[i].number[1] << pairs[i].number[2] << pairs[i].number[3] << ' '
                 << pairs[i].number[4] << pairs[i].number[5] << '\t'
                 << pairs[i].value << '\n';
    }

    delete[] pairs;
    return 0;
}