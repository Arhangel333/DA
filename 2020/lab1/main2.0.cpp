<<<<<<< HEAD
#include <iostream>
#include <cstring>
#include <cstdlib>

const unsigned int NUMBER_OF_DIGITS = 6;
const unsigned int MAX_DIGIT_VALUE = 91;
const unsigned int MAX_STRING_LENGTH = 1024;

struct TCarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];
};

struct TKeyValuePair {
    TCarNumber Key;
    char* Value;
    void Print(){
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
        {
            std::cout<<Key.vals[i];
        }
        
    }
    TKeyValuePair() : Value(nullptr) {}
    
    TKeyValuePair(const TKeyValuePair& other) {
        Key = other.Key;
        Value = new char[strlen(other.Value) + 1];
        strcpy(Value, other.Value);
    }
    
    TKeyValuePair& operator=(const TKeyValuePair& other) {
        if (this != &other) {
            delete[] Value;
            Key = other.Key;
            Value = new char[strlen(other.Value) + 1];
            strcpy(Value, other.Value);
        }
        return *this;
    }
    
    ~TKeyValuePair() {
        delete[] Value;
    }
};

void RadixSort(TKeyValuePair* pairs, size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];
    TKeyValuePair* nextArray = new TKeyValuePair[size];

    for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--) {
        memset(countArray, 0, sizeof(countArray));

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            countArray[d]++;
        }

        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;
            count += tmp;
        }

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];
            countArray[d]++;
        }

        for (int j = 0; j < size; ++j) {
            pairs[j] = nextArray[j];
        }
    }
    delete[] nextArray;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t size = 0;
    size_t capacity = 1;
    TKeyValuePair* pairs = new TKeyValuePair[capacity];
    
    std::string line;
    while (getline(std::cin, line)) {  
        if (line.empty()) continue;
        
        if (size == capacity) {
            capacity *= 2;
            TKeyValuePair* new_pairs = new TKeyValuePair[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_pairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
        }

        unsigned char vals[NUMBER_OF_DIGITS];
        char valueStr[MAX_STRING_LENGTH];
        
        if (sscanf(line.c_str(), "%c %c%c%c %c%c %1023[^\n]", 
               &vals[0], 
               &vals[1], &vals[2], &vals[3],
               &vals[4], &vals[5],
               valueStr) < 7) {
            continue; 
        }

        TCarNumber cn = {{vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]}};
        pairs[size].Key = cn;
        pairs[size].Value = new char[strlen(valueStr) + 1];
        strcpy(pairs[size].Value, valueStr);
        size++;
    }

    RadixSort(pairs, size);

    for (size_t i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%s\n",
               pairs[i].Key.vals[0],
               pairs[i].Key.vals[1],
               pairs[i].Key.vals[2],
               pairs[i].Key.vals[3],
               pairs[i].Key.vals[4],
               pairs[i].Key.vals[5],
               pairs[i].Value);
    }

    delete[] pairs;
    return 0;
=======
<<<<<<< HEAD
<<<<<<< HEAD
#include <iostream>
#include <cstring>
#include <cstdlib>

const unsigned int NUMBER_OF_DIGITS = 6;
const unsigned int MAX_DIGIT_VALUE = 91;
const unsigned int MAX_STRING_LENGTH = 1024;

struct TCarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];
};

struct TKeyValuePair {
    TCarNumber Key;
    char* Value;
    void Print(){
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
        {
            std::cout<<Key.vals[i];
        }
        
    }
    TKeyValuePair() : Value(nullptr) {}
    
    TKeyValuePair(const TKeyValuePair& other) {
        Key = other.Key;
        Value = new char[strlen(other.Value) + 1];
        strcpy(Value, other.Value);
    }
    
    TKeyValuePair& operator=(const TKeyValuePair& other) {
        if (this != &other) {
            delete[] Value;
            Key = other.Key;
            Value = new char[strlen(other.Value) + 1];
            strcpy(Value, other.Value);
        }
        return *this;
    }
    
    ~TKeyValuePair() {
        delete[] Value;
    }
};

void RadixSort(TKeyValuePair* pairs, size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];
    TKeyValuePair* nextArray = new TKeyValuePair[size];

    for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--) {
        memset(countArray, 0, sizeof(countArray));

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            countArray[d]++;
        }

        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;
            count += tmp;
        }

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];
            countArray[d]++;
        }

        for (int j = 0; j < size; ++j) {
            pairs[j] = nextArray[j];
        }
    }
    delete[] nextArray;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t size = 0;
    size_t capacity = 1;
    TKeyValuePair* pairs = new TKeyValuePair[capacity];
    
    std::string line;
    while (getline(std::cin, line)) {  
        if (line.empty()) continue;
        
        if (size == capacity) {
            capacity *= 2;
            TKeyValuePair* new_pairs = new TKeyValuePair[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_pairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
        }

        unsigned char vals[NUMBER_OF_DIGITS];
        char valueStr[MAX_STRING_LENGTH];
        
        if (sscanf(line.c_str(), "%c %c%c%c %c%c %1023[^\n]", 
               &vals[0], 
               &vals[1], &vals[2], &vals[3],
               &vals[4], &vals[5],
               valueStr) < 7) {
            continue; 
        }

        TCarNumber cn = {{vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]}};
        pairs[size].Key = cn;
        pairs[size].Value = new char[strlen(valueStr) + 1];
        strcpy(pairs[size].Value, valueStr);
        size++;
    }

    RadixSort(pairs, size);

    for (size_t i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%s\n",
               pairs[i].Key.vals[0],
               pairs[i].Key.vals[1],
               pairs[i].Key.vals[2],
               pairs[i].Key.vals[3],
               pairs[i].Key.vals[4],
               pairs[i].Key.vals[5],
               pairs[i].Value);
    }

    delete[] pairs;
    return 0;
=======
#include <iostream>
#include <cstring>
#include <cstdlib>

const unsigned int NUMBER_OF_DIGITS = 6;
const unsigned int MAX_DIGIT_VALUE = 91;
const unsigned int MAX_STRING_LENGTH = 1024;

struct TCarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];
};

struct TKeyValuePair {
    TCarNumber Key;
    char* Value;
    void Print(){
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
        {
            std::cout<<Key.vals[i];
        }
        
    }
    TKeyValuePair() : Value(nullptr) {}
    
    TKeyValuePair(const TKeyValuePair& other) {
        Key = other.Key;
        Value = new char[strlen(other.Value) + 1];
        strcpy(Value, other.Value);
    }
    
    TKeyValuePair& operator=(const TKeyValuePair& other) {
        if (this != &other) {
            delete[] Value;
            Key = other.Key;
            Value = new char[strlen(other.Value) + 1];
            strcpy(Value, other.Value);
        }
        return *this;
    }
    
    ~TKeyValuePair() {
        delete[] Value;
    }
};

void RadixSort(TKeyValuePair* pairs, size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];
    TKeyValuePair* nextArray = new TKeyValuePair[size];

    for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--) {
        memset(countArray, 0, sizeof(countArray));

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            countArray[d]++;
        }

        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;
            count += tmp;
        }

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];
            countArray[d]++;
        }

        for (int j = 0; j < size; ++j) {
            pairs[j] = nextArray[j];
        }
    }
    delete[] nextArray;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t size = 0;
    size_t capacity = 1;
    TKeyValuePair* pairs = new TKeyValuePair[capacity];
    
    std::string line;
    while (getline(std::cin, line)) {  
        if (line.empty()) continue;
        
        if (size == capacity) {
            capacity *= 2;
            TKeyValuePair* new_pairs = new TKeyValuePair[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_pairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
        }

        unsigned char vals[NUMBER_OF_DIGITS];
        char valueStr[MAX_STRING_LENGTH];
        
        if (sscanf(line.c_str(), "%c %c%c%c %c%c %1023[^\n]", 
               &vals[0], 
               &vals[1], &vals[2], &vals[3],
               &vals[4], &vals[5],
               valueStr) < 7) {
            continue; 
        }

        TCarNumber cn = {{vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]}};
        pairs[size].Key = cn;
        pairs[size].Value = new char[strlen(valueStr) + 1];
        strcpy(pairs[size].Value, valueStr);
        size++;
    }

    RadixSort(pairs, size);

    for (size_t i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%s\n",
               pairs[i].Key.vals[0],
               pairs[i].Key.vals[1],
               pairs[i].Key.vals[2],
               pairs[i].Key.vals[3],
               pairs[i].Key.vals[4],
               pairs[i].Key.vals[5],
               pairs[i].Value);
    }

    delete[] pairs;
    return 0;
>>>>>>> 2ffdb2565556500fb9daa6f9a9c57f5e5bcef63e
=======
#include <iostream>
#include <cstring>
#include <cstdlib>

const unsigned int NUMBER_OF_DIGITS = 6;
const unsigned int MAX_DIGIT_VALUE = 91;
const unsigned int MAX_STRING_LENGTH = 1024;

struct TCarNumber {
    unsigned char vals[NUMBER_OF_DIGITS];
};

struct TKeyValuePair {
    TCarNumber Key;
    char* Value;
    void Print(){
        for (int i = 0; i < NUMBER_OF_DIGITS; i++)
        {
            std::cout<<Key.vals[i];
        }
        
    }
    TKeyValuePair() : Value(nullptr) {}
    
    TKeyValuePair(const TKeyValuePair& other) {
        Key = other.Key;
        Value = new char[strlen(other.Value) + 1];
        strcpy(Value, other.Value);
    }
    
    TKeyValuePair& operator=(const TKeyValuePair& other) {
        if (this != &other) {
            delete[] Value;
            Key = other.Key;
            Value = new char[strlen(other.Value) + 1];
            strcpy(Value, other.Value);
        }
        return *this;
    }
    
    ~TKeyValuePair() {
        delete[] Value;
    }
};

void RadixSort(TKeyValuePair* pairs, size_t size) {
    unsigned long long countArray[MAX_DIGIT_VALUE];
    TKeyValuePair* nextArray = new TKeyValuePair[size];

    for (int i = NUMBER_OF_DIGITS - 1; i >= 0; i--) {
        memset(countArray, 0, sizeof(countArray));

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            countArray[d]++;
        }

        unsigned long long count = 0;
        for (int j = 0; j < MAX_DIGIT_VALUE; ++j) {
            unsigned long long tmp = countArray[j];
            countArray[j] = count;
            count += tmp;
        }

        for (int j = 0; j < size; ++j) {
            unsigned int d = (int)pairs[j].Key.vals[i];
            nextArray[countArray[d]] = pairs[j];
            countArray[d]++;
        }

        for (int j = 0; j < size; ++j) {
            pairs[j] = nextArray[j];
        }
    }
    delete[] nextArray;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t size = 0;
    size_t capacity = 1;
    TKeyValuePair* pairs = new TKeyValuePair[capacity];
    
    std::string line;
    while (getline(std::cin, line)) {  
        if (line.empty()) continue;
        
        if (size == capacity) {
            capacity *= 2;
            TKeyValuePair* new_pairs = new TKeyValuePair[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_pairs[i] = pairs[i];
            }
            delete[] pairs;
            pairs = new_pairs;
        }

        unsigned char vals[NUMBER_OF_DIGITS];
        char valueStr[MAX_STRING_LENGTH];
        
        if (sscanf(line.c_str(), "%c %c%c%c %c%c %1023[^\n]", 
               &vals[0], 
               &vals[1], &vals[2], &vals[3],
               &vals[4], &vals[5],
               valueStr) < 7) {
            continue; 
        }

        TCarNumber cn = {{vals[0], vals[1], vals[2], vals[3], vals[4], vals[5]}};
        pairs[size].Key = cn;
        pairs[size].Value = new char[strlen(valueStr) + 1];
        strcpy(pairs[size].Value, valueStr);
        size++;
    }

    RadixSort(pairs, size);

    for (size_t i = 0; i < size; i++) {
        printf("%c %c%c%c %c%c\t%s\n",
               pairs[i].Key.vals[0],
               pairs[i].Key.vals[1],
               pairs[i].Key.vals[2],
               pairs[i].Key.vals[3],
               pairs[i].Key.vals[4],
               pairs[i].Key.vals[5],
               pairs[i].Value);
    }

    delete[] pairs;
    return 0;
>>>>>>> 2ffdb2565556500fb9daa6f9a9c57f5e5bcef63e
>>>>>>> 017b9db (8 9 fiished)
}