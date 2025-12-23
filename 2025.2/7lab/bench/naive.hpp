#include "libs.hpp"

int64_t NaivePoliFind(const string& s) {
    int n = s.size();
    int64_t count = 0;
    
    // Перебираем все возможные маски подпоследовательностей (2^n вариантов)
    for (int mask = 1; mask < (1 << n); mask++) {
        string subsequence;
        
        // Собираем подпоследовательность по маске
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subsequence += s[i];
            }
        }
        
        // Проверяем, является ли палиндромом
        bool isPalindrome = true;
        int left = 0, right = subsequence.size() - 1;
        
        while (left < right) {
            if (subsequence[left] != subsequence[right]) {
                isPalindrome = false;
                break;
            }
            left++;
            right--;
        }
        
        if (isPalindrome) {
            count++;
        }
    }
    
    return count;
}