<<<<<<< HEAD
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
        memset(number, ' ', NUMBER_OF_DIGITS);
    }
    
    TKeyValuePair(const char* num, const char* val) {
        int j = 0;
        for (int i = 0; i < strlen(num) && j < NUMBER_OF_DIGITS; i++) {
            if (num[i] != ' ') {
                number[j++] = num[i];
            }
        }
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
=======
<<<<<<< HEAD
<<<<<<< HEAD
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
        memset(number, ' ', NUMBER_OF_DIGITS);
    }
    
    TKeyValuePair(const char* num, const char* val) {
        int j = 0;
        for (int i = 0; i < strlen(num) && j < NUMBER_OF_DIGITS; i++) {
            if (num[i] != ' ') {
                number[j++] = num[i];
            }
        }
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
=======
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
        memset(number, ' ', NUMBER_OF_DIGITS);
    }
    
    TKeyValuePair(const char* num, const char* val) {
        int j = 0;
        for (int i = 0; i < strlen(num) && j < NUMBER_OF_DIGITS; i++) {
            if (num[i] != ' ') {
                number[j++] = num[i];
            }
        }
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
>>>>>>> 2ffdb2565556500fb9daa6f9a9c57f5e5bcef63e
=======
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
        memset(number, ' ', NUMBER_OF_DIGITS);
    }
    
    TKeyValuePair(const char* num, const char* val) {
        int j = 0;
        for (int i = 0; i < strlen(num) && j < NUMBER_OF_DIGITS; i++) {
            if (num[i] != ' ') {
                number[j++] = num[i];
            }
        }
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
>>>>>>> 2ffdb2565556500fb9daa6f9a9c57f5e5bcef63e
>>>>>>> 017b9db (8 9 fiished)
}