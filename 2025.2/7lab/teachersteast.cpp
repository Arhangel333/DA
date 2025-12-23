#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/* int longestCommonSubsequence(string text1, string text2) {
    if (text1.empty() || text2.empty()) {
        return 0;
    }
    
    int m = text1.length();
    int n = text2.length();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    return dp[m][n];
} */

vector<int> longestCommonSubsequence(const vector<string>& a, const vector<string>& b) {
    int m = a.size();
    int n = b.size();
    
    // Используем только 2 строки вместо полной матрицы
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        int current = i % 2;      // Текущая строка (0 или 1)
        int previous = 1 - current; // Предыдущая строка
        
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                // Слова совпали - увеличиваем длину LCS
                dp[current][j] = dp[previous][j - 1] + 1;
            } else {
                // Выбираем максимальную длину из двух вариантов
                dp[current][j] = max(dp[previous][j], dp[current][j - 1]);
            }
        }
    }
    
    // Возвращаем последнюю заполненную строку
    return dp[m % 2];
}

// Примеры использования:
int main() {
    cout << longestCommonSubsequence("abcde", "ace") << endl;  // 3
    cout << longestCommonSubsequence("abc", "abc") << endl;    // 3
    cout << longestCommonSubsequence("abc", "def") << endl;    // 0
    
    return 0;
}