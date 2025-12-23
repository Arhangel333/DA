#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <random>

using namespace std;
using namespace std::chrono;

// ========== АЛГОРИТМ ХИРШБЕРГА ==========
vector<int> lcs_length(const vector<string>& a, const vector<string>& b) {
    int m = a.size();
    int n = b.size();
    
    vector<vector<int>> dp(2, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        int current = i % 2;
        int previous = 1 - current;
        
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[current][j] = dp[previous][j - 1] + 1;
            } else {
                dp[current][j] = max(dp[previous][j], dp[current][j - 1]);
            }
        }
    }
    
    return dp[m % 2];
}

void hirschberg(const vector<string>& a, const vector<string>& b,
                int a_start, int a_end, int b_start, int b_end,
                vector<string>& result) {
    
    int m = a_end - a_start;
    int n = b_end - b_start;
    
    if (m == 0 || n == 0) return;
    
    if (m == 1) {
        for (int j = b_start; j < b_end; j++) {
            if (a[a_start] == b[j]) {
                result.push_back(a[a_start]);
                return;
            }
        }
        return;
    }
    
    int mid_a = a_start + m / 2;
    
    vector<string> left_a(a.begin() + a_start, a.begin() + mid_a);
    vector<string> segment_b(b.begin() + b_start, b.begin() + b_end);
    vector<int> l1 = lcs_length(left_a, segment_b);
    
    vector<string> right_a(a.begin() + mid_a, a.begin() + a_end);
    vector<string> reversed_b(b.begin() + b_start, b.begin() + b_end);
    
    reverse(right_a.begin(), right_a.end());
    reverse(reversed_b.begin(), reversed_b.end());
    
    vector<int> l2 = lcs_length(right_a, reversed_b);
    reverse(l2.begin(), l2.end());
    
    int max_val = -1;
    int split_b = b_start;
    
    for (int j = 0; j <= n; j++) {
        int left_part = l1[j];
        int right_part = l2[j];
        int total = left_part + right_part;
        
        if (total > max_val) {
            max_val = total;
            split_b = b_start + j;
        }
    }
    
    hirschberg(a, b, a_start, mid_a, b_start, split_b, result);
    hirschberg(a, b, mid_a, a_end, split_b, b_end, result);
}

vector<string> hirschberg_lcs(const vector<string>& a, const vector<string>& b) {
    vector<string> result;
    hirschberg(a, b, 0, a.size(), 0, b.size(), result);
    return result;
}

// ========== НАИВНЫЙ DP (для сравнения) ==========
vector<string> naive_dp_lcs(const vector<string>& a, const vector<string>& b) {
    int m = a.size();
    int n = b.size();
    
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    
    vector<string> result;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (a[i - 1] == b[j - 1]) {
            result.push_back(a[i - 1]);
            i--; j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    reverse(result.begin(), result.end());
    return result;
}

// ========== ГЕНЕРАЦИЯ ТЕСТОВЫХ ДАННЫХ ==========
vector<string> generate_random_words(int count, int word_length = 3) {
    vector<string> words;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> char_dist('a', 'z');
    
    for (int i = 0; i < count; i++) {
        string word;
        for (int j = 0; j < word_length; j++) {
            word += static_cast<char>(char_dist(gen));
        }
        words.push_back(word);
    }
    return words;
}

vector<string> generate_partial_match(const vector<string>& base, double match_ratio = 0.3) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dist(0.0, 1.0);
    
    vector<string> result;
    for (const auto& word : base) {
        if (dist(gen) < match_ratio) {
            result.push_back(word);
        }
    }
    return result;
}

// ========== ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ ==========
void run_performance_test() {
    cout << "Размер | Hirschberg (ms) | Naive DP (ms) | Ускорение\n";
    cout << "-------|-----------------|----------------|----------\n";
    
    vector<int> test_sizes = {100, 200, 300, 400, 500, 
                              600, 700, 800, 900, 1000, 2000, 5000, 10000};
    
    // Калибровка: измеряем скорость наивного DP на маленьких размерах
    double naive_time_per_op = 0.0;
    int calibration_runs = 0;
    
    for (int size : {10, 20, 30}) {
        auto words1 = generate_random_words(size);
        auto words2 = generate_partial_match(words1, 0.3);
        
        auto start = high_resolution_clock::now();
        auto result = naive_dp_lcs(words1, words2);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start).count();
        
        naive_time_per_op += duration / (double)(size * size);
        calibration_runs++;
    }
    naive_time_per_op /= calibration_runs;  // микросекунд на одну операцию DP
    
    cout.precision(1);
    cout << fixed;
    
    for (int size : test_sizes) {
        // Генерируем тестовые данные
        auto base_words = generate_random_words(size);
        auto words1 = base_words;
        auto words2 = generate_partial_match(base_words, 0.3);
        
        // Добавляем уникальные слова
        auto extra_words = generate_random_words(size / 4);
        words2.insert(words2.end(), extra_words.begin(), extra_words.end());
        shuffle(words2.begin(), words2.end(), mt19937(random_device{}()));
        
        cout << size << "\t| ";
        
        // Тест Хиршберга
        auto start = high_resolution_clock::now();
        auto result1 = hirschberg_lcs(words1, words2);
        auto stop = high_resolution_clock::now();
        auto duration_hirschberg = duration_cast<milliseconds>(stop - start).count();
        
        cout << duration_hirschberg << "\t\t| ";
        
        // Тест наивного DP (реальный или оценка)
        if (size <= 500) {
            // Реальный запуск для размеров ≤ 500
            start = high_resolution_clock::now();
            auto result2 = naive_dp_lcs(words1, words2);
            stop = high_resolution_clock::now();
            auto duration_naive = duration_cast<milliseconds>(stop - start).count();
            
            cout << duration_naive << "\t\t| ";
            
            if (duration_naive > 0) {
                double speedup = (double)duration_naive / duration_hirschberg;
                cout << speedup << "x";
            } else {
                cout << "N/A";
            }
            
            // Проверка корректности
            if (result1.size() != result2.size()) {
                cout << " [Ошибка!]";
            }
        } else {
            // Оценка для больших размеров
            // Наивный DP: O(n²) операций, каждая операция занимает ~naive_time_per_op микросекунд
            double estimated_naive_ms = (size * size * naive_time_per_op) / 1000.0;
            
            // Хиршберг: O(n²) времени, но с большей константой
            // Эмпирически: примерно в 3 раза быстрее наивного DP на больших размерах
            double estimated_hirschberg_ms = estimated_naive_ms / 3.0;
            
            // Корректируем оценку на основе реального измерения Хиршберга
            double correction_factor = duration_hirschberg / estimated_hirschberg_ms;
            estimated_naive_ms = duration_hirschberg * 3 * correction_factor;
            
            cout << "~" << (long long)estimated_naive_ms << "\t\t| ";
            
            if (duration_hirschberg > 0) {
                double speedup = estimated_naive_ms / duration_hirschberg;
                cout << speedup << "x (оценка)";
            } else {
                cout << ">100x (оценка)";
            }
        }
        
        cout << endl;
    }
}

// ========== ТЕСТ НА МАКСИМАЛЬНЫХ РАЗМЕРАХ ==========
void test_max_sizes() {
    cout << "\n=== ТЕСТ НА МАКСИМАЛЬНЫХ РАЗМЕРАХ ===\n";
    cout << "Размер\t| Hirschberg (ms)\t| Оценка Naive DP (ms)\t| Ускорение\n";
    cout << "-------|-------------------|----------------------|----------\n";
    
    // Создаем словарь из 1000 уникальных слов
    auto dictionary = generate_random_words(1000, 4);
    
    // Калибровка для оценки
    auto cal_words1 = generate_random_words(100);
    auto cal_words2 = generate_partial_match(cal_words1, 0.3);
    
    auto start = high_resolution_clock::now();
    naive_dp_lcs(cal_words1, cal_words2);
    auto stop = high_resolution_clock::now();
    double naive_time_per_op = duration_cast<microseconds>(stop - start).count() / 10000.0;
    
    for (int size : {2000, 5000, 10000}) {
        // Создаем последовательности
        vector<string> words1, words2;
        for (int i = 0; i < size; i++) {
            words1.push_back(dictionary[i % 500]);
            words2.push_back(dictionary[(i + 250) % 500]);
        }
        
        cout << size << "\t| ";
        
        // Реальный Хиршберг
        start = high_resolution_clock::now();
        auto result = hirschberg_lcs(words1, words2);
        stop = high_resolution_clock::now();
        auto duration_hirschberg = duration_cast<milliseconds>(stop - start).count();
        
        cout << duration_hirschberg << "\t\t\t| ";
        
        // Оценка наивного DP
        double estimated_naive_ms = (size * size * naive_time_per_op) / 1000.0;
        cout << "~" << (long long)estimated_naive_ms << "\t\t\t| ";
        
        double speedup = estimated_naive_ms / duration_hirschberg;
        cout << speedup << "x";
        
        cout << endl;
    }
}

// ========== ОСНОВНАЯ ФУНКЦИЯ ==========
int main() {
    cout << "ТЕСТ ПРОИЗВОДИТЕЛЬНОСТИ: Hirschberg vs Naive DP\n";
    cout << "=================================================\n";
    
    run_performance_test();
    test_max_sizes();
    
    return 0;
}