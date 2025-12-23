#include "naive.hpp"
#include "main.hpp"


// ИСПРАВЛЕННЫЙ эффективный алгоритм
int64_t countPalindromesDP(const string& s) {
    int n = s.size();
    vector<vector<int64_t>> dp(n, vector<int64_t>(n, 0));
    
    // Инициализация для подстрок длиной 1
    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }
    
    // Обработка подстрок длиной 2
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            dp[i][i + 1] = 3; // a, b, aa (если "aa")
        } else {
            dp[i][i + 1] = 2; // a, b
        }
    }
    
    // Обработка подстрок длиной >= 3
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j]) {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1] + 1;
            } else {
                dp[i][j] = dp[i + 1][j] + dp[i][j - 1] - dp[i + 1][j - 1];
            }
        }
    }
    
    return dp[0][n - 1];
}

// Альтернативный корректный алгоритм через булевы палиндромы
int64_t countPalindromesDP2(const string& s) {
    int n = s.size();
    vector<vector<bool>> isPal(n, vector<bool>(n, false));
    vector<vector<int64_t>> count(n, vector<int64_t>(n, 0));
    
    // Заполняем таблицу isPal
    for (int i = 0; i < n; i++) {
        isPal[i][i] = true;
        count[i][i] = 1;
    }
    
    for (int i = 0; i < n - 1; i++) {
        if (s[i] == s[i + 1]) {
            isPal[i][i + 1] = true;
            count[i][i + 1] = 3;
        } else {
            count[i][i + 1] = 2;
        }
    }
    
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && isPal[i + 1][j - 1]) {
                isPal[i][j] = true;
            }
            count[i][j] = count[i + 1][j] + count[i][j - 1] - count[i + 1][j - 1] + (isPal[i][j] ? 1 : 0);
        }
    }
    
    return count[0][n - 1];
}

// Наивный алгоритм O(n³) - ПРОВЕРЕННЫЙ
bool isPalindrome(const string& s, int start, int end) {
    while (start < end) {
        if (s[start] != s[end]) return false;
        start++;
        end--;
    }
    return true;
}

int64_t countPalindromesNaive(const string& s) {
    int64_t count = 0;
    int n = s.size();
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (isPalindrome(s, i, j)) {
                count++;
            }
        }
    }
    
    return count;
}

// Генератор тестовых строк
string generateRandomString(int length, int alphabetSize = 4) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, alphabetSize - 1);
    
    string result;
    for (int i = 0; i < length; i++) {
        result += 'a' + dis(gen);
    }
    return result;
}

// Функция для измерения времени
template<typename Func>
long long measureTime(Func func, const string& s, int64_t& result) {
    auto start = high_resolution_clock::now();
    result = func(s);
    auto stop = high_resolution_clock::now();
    return duration_cast<microseconds>(stop - start).count();
}

void validateAlgorithms() {
    vector<string> testCases = {
        "a", "aa", "ab", "aaa", "aba", "abc", 
        "aab", "baobab", "racecar", "level"
    };
    
    cout << "=== ПРОВЕРКА КОРРЕКТНОСТИ ===\n";
    cout << "Строка\t\t| Naive\t| DP1\t| DP2\t| Статус\n";
    cout << "----------------|-------|-------|-------|--------\n";
    
    for (const string& testStr : testCases) {
        int64_t naive = countPalindromesNaive(testStr);
        int64_t dp1 = countPalindromesDP(testStr);
        int64_t dp2 = countPalindromesDP2(testStr);
        
        cout << testStr << "\t\t| " << naive << "\t| " << dp1 << "\t| " << dp2 << "\t| ";
        
        if (naive == dp1 && naive == dp2) {
            cout << "✓" << endl;
        } else {
            cout << "✗" << endl;
        }
    }
}

void runBenchmark() {
    vector<int> testSizes = {10, 20, 50, 100, 200, 500};
    
    cout << "\n=== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ===\n";
    cout << "Размер | Naive (мкс) | DP (мкс) | Результат\n";
    cout << "-------|-------------|-----------|----------\n";
    
    for (int size : testSizes) {
        string testStr = generateRandomString(size, 3);
        
        int64_t resultNaive, resultDP1, resultDP2;
        long long timeNaive, timeDP1, timeDP2;
        
        if (size <= 100) {
            timeNaive = measureTime(NaivePoliFind, testStr, resultNaive);
        } else {
            timeNaive = -1;
            resultNaive = -1;
        }
        
        timeDP1 = measureTime(polifind, testStr, resultDP1);
        
        printf("%6d |", size);
        
        if (timeNaive > 0) {
            printf("%12lld |", timeNaive);
        } else {
            cout << "\t N/A | ";
        }
        
        cout << timeDP1 << "\t |";
        cout << resultDP1 << endl;
    }
}

int main() {

    runBenchmark();

    
    return 0;
}