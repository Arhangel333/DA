#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>

const int MAX_STR_LEN = 1034;
const int MAX_LINE_LEN = MAX_STR_LEN * 2 + 2;

struct Pair {
    char* first;
    char* second;

    Pair() : first(nullptr), second(nullptr) {}

    Pair(const char* a, const char* b) {
        first = new char[strlen(a) + 1];
        strcpy(first, a);
        second = new char[strlen(b) + 1];
        strcpy(second, b);
    }

    Pair(const Pair& other) {
        first = new char[strlen(other.first) + 1];
        strcpy(first, other.first);
        second = new char[strlen(other.second) + 1];
        strcpy(second, other.second);
    }

    Pair& operator=(const Pair& other) {
        if (this != &other) {
            delete[] first;
            delete[] second;
            first = new char[strlen(other.first) + 1];
            strcpy(first, other.first);
            second = new char[strlen(other.second) + 1];
            strcpy(second, other.second);
        }
        return *this;
    }

    ~Pair() {
        delete[] first;
        delete[] second;
    }
};

class Vector {
private:
    Pair* data;
    int size;
    int capacity;

    void realloc(int new_capacity) {
        Pair* new_data = new Pair[new_capacity];
        for (int i = 0; i < size; ++i) {
            new_data[i] = data[i];
        }
        delete[] data;
        data = new_data;
        capacity = new_capacity;
    }

public:
    Vector() : data(nullptr), size(0), capacity(0) {}
    explicit Vector(int n) : data(new Pair[n]), size(n), capacity(n) {}

    ~Vector() {
        delete[] data;
    }

    void push_back(const Pair& x) {
        if (size >= capacity) {
            realloc(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = x;
    }

    Pair& operator[](int i) {
        return data[i];
    }

    int getSize() const {
        return size;
    }
};

inline char getChar(const char* key, int pos) {
    if (key == nullptr || pos < 0 || pos >= (int)strlen(key)) {
        return 0;
    }
    return key[pos];
}

void radixSort(Vector& data) {
    const int maxLen = MAX_STR_LEN;
    const int countSize = 256;
    int n = data.getSize();

    Vector output(n);
    int count[countSize];

    for (int pos = maxLen - 1; pos >= 0; --pos) {
        memset(count, 0, sizeof(count));

        for (int i = 0; i < n; ++i) {
            char ch = getChar(data[i].first, pos);
            ++count[static_cast<unsigned char>(ch)];
        }

        for (int i = 1; i < countSize; ++i) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; --i) {
            char ch = getChar(data[i].first, pos);
            output[--count[static_cast<unsigned char>(ch)]] = data[i];
        }

        for (int i = 0; i < n; ++i) {
            data[i] = output[i];
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    Vector data;
    char line[MAX_LINE_LEN];

    while (fgets(line, MAX_LINE_LEN, stdin)) {
        if (line[0] == '\n') continue;
        char* tabPos = strchr(line, '\t');
        if (!tabPos) continue;

        *tabPos = '\0';
        char* key = line;
        char* value = tabPos + 1;
        value[strcspn(value, "\n")] = '\0';

        if (strlen(key) == 0 || strlen(value) == 0) continue;

        data.push_back(Pair(key, value));
    }

    radixSort(data);

    for (int i = 0; i < data.getSize(); ++i) {
        std::cout << data[i].first << '\t' << data[i].second << '\n';
    }

    return 0;
}