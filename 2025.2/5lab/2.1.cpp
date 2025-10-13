#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cctype>

using namespace std;

// Функция для считывания строки с помощью fgets
string readLine() {
    char buffer[10000]; // Буфер достаточного размера
    if (fgets(buffer, sizeof(buffer), stdin) == nullptr) {
        return ""; // Конец файла или ошибка
    }
    
    string result = buffer;
    // Удаляем символы новой строки в конце
    while (!result.empty() && (result.back() == '\n' || result.back() == '\r')) {
        result.pop_back();
    }
    return result;
}

// Приведение к нижнему регистру (только английские буквы)
string toLowerEnglish(const string& s) {
    string result = s;
    /* for (char& c : result) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    } */
    return result;
}

class SuffixArray {
private:
    string text;
    vector<int> suffixArray;

    void buildSuffixArray() {
        int n = text.size();
        if (n == 0) return;
        
        suffixArray.resize(n);
        vector<int> rank(n), tempRank(n);
        
        for (int i = 0; i < n; i++) {
            suffixArray[i] = i;
            rank[i] = static_cast<unsigned char>(text[i]);
        }
        
        for (int k = 1; k < n; k *= 2) {
            auto cmp = [&](int i, int j) {
                if (rank[i] != rank[j]) return rank[i] < rank[j];
                int ri = (i + k < n) ? rank[i + k] : -1;
                int rj = (j + k < n) ? rank[j + k] : -1;
                return ri < rj;
            };
            
            sort(suffixArray.begin(), suffixArray.end(), cmp);
            
            tempRank[suffixArray[0]] = 0;
            for (int i = 1; i < n; i++) {
                tempRank[suffixArray[i]] = tempRank[suffixArray[i - 1]] + 
                    (cmp(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
            }
            rank = tempRank;
        }
    }

public:
    SuffixArray(const string& str) : text(str) {
        if (!text.empty()) {
            buildSuffixArray();
        }
    }

    vector<int> search(const string& pattern) {
        vector<int> positions;
        
        if (text.empty() || pattern.empty()) {
            return positions;
        }
        
        int n = text.size();
        int m = pattern.size();
        
        if (m > n) return positions;
        
        auto compare = [&](int idx) {
            for (int i = 0; i < m; i++) {
                if (idx + i >= n) return -1;
                if (text[idx + i] != pattern[i]) {
                    return static_cast<unsigned char>(text[idx + i]) - 
                           static_cast<unsigned char>(pattern[i]);
                }
            }
            return 0;
        };
        
        // Левая граница
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int cmp = compare(suffixArray[mid]);
            if (cmp >= 0) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        int start = left;
        
        // Правая граница
        right = n - 1;
        while (left <= right) {
            int mid = (left + right) / 2;
            int cmp = compare(suffixArray[mid]);
            if (cmp <= 0) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        int end = right;
        
        if (start <= end) {
            for (int i = start; i <= end; i++) {
                positions.push_back(suffixArray[i] + 1);
            }
            sort(positions.begin(), positions.end());
        }
        
        return positions;
    }
};

int main() {
    // Считываем текст (первая строка)
    string text = readLine();
    cout<<text.size()<<endl;
    text = toLowerEnglish(text);
    
    if (text.empty()) {
        return 0;
    }
    
    SuffixArray sa(text);
    
    int patternNum = 1;
    while (true) {
        string pattern = readLine();
        
        // Проверка конца файла
        if (pattern.empty() && feof(stdin)) {
            break;
        }
        
        // Пропускаем пустые строки, но продолжаем нумерацию
        if (pattern.empty()) {
            continue;
        }
        
        pattern = toLowerEnglish(pattern);
        vector<int> positions = sa.search(pattern);
        
        cout << patternNum << ": ";
        for (size_t i = 0; i < positions.size(); i++) {
            if (i > 0) cout << ", ";
            cout << positions[i];
        }
        cout << "\n";
        
        patternNum++;
    }
    
    return 0;
}