#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <chrono>
#include <algorithm>
#include <random>
#include <iomanip>   // для std::setw, std::setprecision
#include <numeric>

std::vector<int> topo_sort_kahn(const int n, std::vector<std::pair<int, int>> &limits) {
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<int> links(n + 1, 0);

    for (const auto &[a, b] : limits) {
        graph[a].push_back(b);
        links[b]++;
    }

    std::queue<int> q;
    for (int i = 1; i <= n; ++i) {
        if (links[i] == 0) {
            q.push(i);
        }
    }

    std::vector<int> res;
    while (!q.empty()) {
        int nd = q.front();
        q.pop();
        res.push_back(nd);

        for (int neighbor : graph[nd]) {
            links[neighbor]--;
            if (links[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    if (res.size() != n) {
        return {-1};
    }

    return res;
}

// Наивная реализация (DFS-based с ручной проверкой)
std::vector<int> topo_sort_naive(const int n, std::vector<std::pair<int, int>> &limits) {
    std::vector<std::vector<int>> graph(n + 1);
    for (const auto &[a, b] : limits) {
        graph[a].push_back(b);
    }

    std::vector<int> in_degree(n + 1, 0);
    for (const auto &[a, b] : limits) {
        in_degree[b]++;
    }

    std::vector<int> result;
    std::vector<bool> visited(n + 1, false);
    
    for (int k = 0; k < n; ++k) {
        // Ищем вершину с нулевой степенью
        int node = -1;
        for (int i = 1; i <= n; ++i) {
            if (!visited[i] && in_degree[i] == 0) {
                node = i;
                break;
            }
        }
        
        if (node == -1) {
            // Есть цикл
            return {-1};
        }
        
        visited[node] = true;
        result.push_back(node);
        
        // Уменьшаем степени смежных вершин
        for (int neighbor : graph[node]) {
            in_degree[neighbor]--;
        }
    }
    
    return result;
}

// Генератор тестовых данных
std::vector<std::pair<int, int>> generate_test_data(int n, int m, bool has_cycle = false) {
    std::vector<std::pair<int, int>> edges;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n);
    
    if (has_cycle) {
        // Создаем цикл
        for (int i = 1; i <= n; ++i) {
            edges.push_back({i, (i % n) + 1});
        }
        m = std::max(m, n);
    }
    
    // Добавляем случайные ребра
    for (int i = 0; i < m; ++i) {
        int a = dist(gen);
        int b = dist(gen);
        if (a != b) {
            edges.push_back({a, b});
        }
    }
    
    return edges;
}

// Генератор DAG (без циклов)
std::vector<std::pair<int, int>> generate_dag_data(int n, int m) {
    std::vector<std::pair<int, int>> edges;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, n);
    
    // Генерируем случайную перестановку вершин
    std::vector<int> perm(n);
    std::iota(perm.begin(), perm.end(), 1);
    std::shuffle(perm.begin(), perm.end(), gen);
    
    // Создаем ребра только от меньших к большим в перестановке
    for (int i = 0; i < m; ++i) {
        int idx_a = dist(gen) - 1;
        int idx_b = dist(gen) - 1;
        
        if (idx_a != idx_b) {
            int a = perm[std::min(idx_a, idx_b)];
            int b = perm[std::max(idx_a, idx_b)];
            if (a != b) {
                edges.push_back({a, b});
            }
        }
    }
    
    return edges;
}

void run_benchmark() {
    std::cout << "=== Бенчмарк Топологической Сортировки ===\n\n";
    
    // Тестовые случаи
    std::vector<std::pair<std::string, std::pair<int, int>>> test_cases = {
        {"Маленький граф", {10, 15}},
        {"Средний граф", {100, 300}},
        {"Большой граф", {1000, 5000}},
        {"Очень большой граф", {5000, 20000}},
        {"Плотный граф", {200, 10000}}
    };
    
    const int iterations = 10;
    
    for (const auto& [name, params] : test_cases) {
        int n = params.first;
        int m = params.second;
        
        std::cout << "Тест: " << name << " (n=" << n << ", m=" << m << ")\n";
        std::cout << std::string(50, '-') << "\n";
        
        // Генерируем DAG для теста
        auto edges = generate_dag_data(n, m);
        
        // Тестируем алгоритм Кана
        long long total_kahn = 0;
        bool kahn_valid = true;
        
        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto result = topo_sort_kahn(n, edges);
            auto end = std::chrono::high_resolution_clock::now();
            
            if (result.size() == 1 && result[0] == -1) {
                kahn_valid = false;
            }
            
            total_kahn += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        
        // Тестируем наивный алгоритм
        long long total_naive = 0;
        bool naive_valid = true;
        
        for (int i = 0; i < iterations; ++i) {
            auto start = std::chrono::high_resolution_clock::now();
            auto result = topo_sort_naive(n, edges);
            auto end = std::chrono::high_resolution_clock::now();
            
            if (result.size() == 1 && result[0] == -1) {
                naive_valid = true;
            }
            
            total_naive += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        }
        
        double avg_kahn = total_kahn / (double)iterations;
        double avg_naive = total_naive / (double)iterations;
        
        std::cout << "Алгоритм Кана: " << avg_kahn << " мкс\n";
        std::cout << "Наивный алгоритм: " << avg_naive << " мкс\n";
        std::cout << "Ускорение: " << (avg_naive / avg_kahn) << "x\n";
        std::cout << "Корректность: " << (kahn_valid ? "ок" : "no") << " | " << (naive_valid ? "ок" : "no") << "\n\n";
    }
    
    // Тест с циклом
    std::cout << "=== Тест с циклом в графе ===\n";
    std::cout << std::string(50, '-') << "\n";
    
    int n = 100;
    auto cyclic_edges = generate_test_data(n, 200, true);
    
    auto start = std::chrono::high_resolution_clock::now();
    auto result_kahn = topo_sort_kahn(n, cyclic_edges);
    auto end = std::chrono::high_resolution_clock::now();
    auto time_kahn = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    start = std::chrono::high_resolution_clock::now();
    auto result_naive = topo_sort_naive(n, cyclic_edges);
    end = std::chrono::high_resolution_clock::now();
    auto time_naive = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    std::cout << "Алгоритм Кана: " << time_kahn << " мкс, обнаружил цикл: " 
              << (result_kahn.size() == 1 && result_kahn[0] == -1 ? "ок" : "no") << "\n";
    std::cout << "Наивный алгоритм: " << time_naive << " мкс, обнаружил цикл: " 
              << (result_naive.size() == 1 && result_naive[0] == -1 ? "ок" : "no") << "\n\n";
    
    // Тест производительности при увеличении размера
    std::cout << "=== Масштабируемость ===\n";
    std::cout << std::string(50, '-') << "\n";
    
    std::cout << std::setw(10) << "n" << std::setw(15) << "m" 
              << std::setw(20) << "       Кана (мкс)" << std::setw(20) << "     Наивный (мкс)" 
              << std::setw(15) << "    Ускорение" << "\n";
    
    std::vector<int> sizes = {50, 100, 200, 500, 1000, 2000};
    for (int n_size : sizes) {
        int m_size = n_size * 5;  // Примерное соотношение
        auto test_edges = generate_dag_data(n_size, m_size);
        
        // Измеряем время для алгоритма Кана
        start = std::chrono::high_resolution_clock::now();
        auto res1 = topo_sort_kahn(n_size, test_edges);
        end = std::chrono::high_resolution_clock::now();
        auto t1 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        // Измеряем время для наивного алгоритма
        start = std::chrono::high_resolution_clock::now();
        auto res2 = topo_sort_naive(n_size, test_edges);
        end = std::chrono::high_resolution_clock::now();
        auto t2 = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
        
        std::cout << std::setw(10) << n_size 
                  << std::setw(15) << m_size 
                  << std::setw(20) << t1 
                  << std::setw(20) << t2 
                  << std::setw(15) << std::fixed << std::setprecision(2) << (t2 / (double)t1) << "x\n";
    }
}

int main() {
    run_benchmark();
    return 0;
}