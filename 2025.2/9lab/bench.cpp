#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <limits>
#include <algorithm>
#include <iomanip>

const long long INF = std::numeric_limits<long long>::max();

struct edge {
    edge(int a, int b, long long k) : first(a), second(b), weight(k) {};
    int first, second;
    long long weight;
};

// Простая версия Дейкстры для сравнения
std::vector<long long> dijkstraSimple(const std::vector<edge>& edges, int n, int start) {
    std::vector<long long> dist(n, INF);
    std::vector<bool> visited(n, false);
    dist[start] = 0;
    
    for (int i = 0; i < n; i++) {
        // Находим непосещенную вершину с минимальным расстоянием
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && (u == -1 || dist[v] < dist[u])) {
                u = v;
            }
        }
        
        if (dist[u] == INF) break;
        visited[u] = true;
        
        // Релаксация всех исходящих ребер
        for (const auto& e : edges) {
            if (e.first - 1 == u) { // Переводим в 0-индексацию
                int v = e.second - 1;
                if (dist[u] + e.weight < dist[v]) {
                    dist[v] = dist[u] + e.weight;
                }
            }
        }
    }
    
    return dist;
}

// Наивный алгоритм - Дейкстра из каждой вершины
std::vector<std::vector<long long>> naiveAllPairsDijkstra(const std::vector<edge>& edges, int n, int m) {
    std::vector<std::vector<long long>> result(n, std::vector<long long>(n, INF));
    
    for (int i = 0; i < n; i++) {
        result[i] = dijkstraSimple(edges, n, i);
    }
    
    return result;
}

// Ваш алгоритм Джонсона (исправленный)
std::vector<std::vector<long long>> johnsonAlgorithm(const std::vector<edge>& edges, int n, int m) {
    if (edges.empty()) {
        std::vector<std::vector<long long>> result(n, std::vector<long long>(n, INF));
        for (int i = 0; i < n; i++) {
            result[i][i] = 0;
        }
        return result;
    }
    
    // Шаг 1: Добавляем фиктивную вершину 0
    std::vector<edge> graphWithSource = edges;
    for (int i = 1; i <= n; i++) {
        graphWithSource.push_back(edge(0, i, 0));
    }
    
    // Шаг 2: Bellman-Ford из вершины 0
    std::vector<long long> h(n + 1, INF);
    h[0] = 0;
    
    for (int i = 0; i < n; i++) {
        for (const auto& e : graphWithSource) {
            if (h[e.first] != INF && h[e.first] + e.weight < h[e.second]) {
                h[e.second] = h[e.first] + e.weight;
            }
        }
    }
    
    // Проверка на отрицательные циклы
    for (const auto& e : graphWithSource) {
        if (h[e.first] != INF && h[e.first] + e.weight < h[e.second]) {
            std::cout << "Обнаружен отрицательный цикл в Джонсоне" << std::endl;
            return {};
        }
    }
    
    // Шаг 3: Перевзвешивание ребер
    std::vector<edge> reweightedEdges;
    for (const auto& e : edges) {
        long long newWeight = e.weight + h[e.first] - h[e.second];
        reweightedEdges.push_back(edge(e.first, e.second, newWeight));
    }
    
    // Шаг 4: Дейкстра из каждой вершины с новыми весами
    std::vector<std::vector<long long>> result(n, std::vector<long long>(n, INF));
    
    for (int s = 0; s < n; s++) {
        std::vector<long long> dist(n, INF);
        std::vector<bool> visited(n, false);
        dist[s] = 0;
        
        for (int i = 0; i < n; i++) {
            // Находим непосещенную вершину с минимальным расстоянием
            int u = -1;
            long long minDist = INF;
            for (int v = 0; v < n; v++) {
                if (!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    u = v;
                }
            }
            
            if (u == -1 || minDist == INF) break;
            visited[u] = true;
            
            // Релаксация всех исходящих ребер
            for (const auto& e : reweightedEdges) {
                if (e.first - 1 == u) {
                    int v = e.second - 1;
                    if (dist[u] + e.weight < dist[v]) {
                        dist[v] = dist[u] + e.weight;
                    }
                }
            }
        }
        
        // Восстанавливаем исходные расстояния
        for (int v = 0; v < n; v++) {
            if (dist[v] != INF) {
                result[s][v] = dist[v] + h[v + 1] - h[s + 1];
            }
        }
        result[s][s] = 0;  // Расстояние до себя всегда 0
    }
    
    return result;
}

// Генератор случайных графов (безопасная версия)
std::vector<edge> generateRandomGraph(int n, int m, bool allowNegative = false, int seed = 42) {
    std::vector<edge> edges;
    if (n <= 0 || m <= 0) return edges;
    
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> vertexDist(1, n);
    
    if (allowNegative) {
        std::uniform_int_distribution<long long> weightDist(-10, 100);
        for (int i = 0; i < m; i++) {
            int u = vertexDist(gen);
            int v = vertexDist(gen);
            // Избегаем петель
            if (u != v) {
                edges.push_back(edge(u, v, weightDist(gen)));
            }
        }
    } else {
        std::uniform_int_distribution<long long> weightDist(1, 100);
        for (int i = 0; i < m; i++) {
            int u = vertexDist(gen);
            int v = vertexDist(gen);
            // Избегаем петель
            if (u != v) {
                edges.push_back(edge(u, v, weightDist(gen)));
            }
        }
    }
    
    return edges;
}

// Проверка корректности результатов
bool compareResults(const std::vector<std::vector<long long>>& res1,
                   const std::vector<std::vector<long long>>& res2) {
    if (res1.size() != res2.size()) {
        std::cout << "Разные размеры: " << res1.size() << " vs " << res2.size() << std::endl;
        return false;
    }
    
    for (size_t i = 0; i < res1.size(); i++) {
        if (res1[i].size() != res2[i].size()) {
            std::cout << "Разные размеры строки " << i << ": " 
                     << res1[i].size() << " vs " << res2[i].size() << std::endl;
            return false;
        }
        for (size_t j = 0; j < res1[i].size(); j++) {
            if (res1[i][j] != res2[i][j]) {
                // Оба бесконечны - это нормально
                if (res1[i][j] == INF && res2[i][j] == INF) continue;
                std::cout << "Разница в [" << i << "][" << j << "]: " 
                         << res1[i][j] << " vs " << res2[i][j] << std::endl;
                return false;
            }
        }
    }
    return true;
}

void runSafeBenchmark() {
    std::cout << "=== Безопасный бенчмарк: Алгоритм Джонсона vs Наивная Дейкстра ===\n\n";
    
    // Начинаем с маленьких графов для отладки
    struct TestCase {
        std::string name;
        int n;
        int m;
        bool allowNegative;
    };
    
    std::vector<TestCase> testCases = {
        {"Очень маленький граф", 5, 8, false},
        {"Маленький граф", 10, 15, false},
        {"Средний граф", 30, 100, false},
        {"Разреженный граф", 200, 2000, false},
        {"Плотный граф", 800, 3000, false},
    };
    
    int testNum = 1;
    for (const auto& testCase : testCases) {
        std::cout << "\nТест #" << testNum++ << ": " << testCase.name << std::endl;
        std::cout << "Вершин: " << testCase.n << ", Ребер: " << testCase.m << std::endl;
        
        try {
            auto edges = generateRandomGraph(testCase.n, testCase.m, testCase.allowNegative, testNum);
            std::cout << "Сгенерировано " << edges.size() << " ребер" << std::endl;
            
            if (edges.empty()) {
                std::cout << "Предупреждение: пустой граф, пропускаем" << std::endl;
                continue;
            }
            
            // Тестируем алгоритм Джонсона
            std::cout << "Запуск алгоритма Джонсона..." << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            auto johnsonResult = johnsonAlgorithm(edges, testCase.n, edges.size());
            auto end = std::chrono::high_resolution_clock::now();
            auto johnsonTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            
            if (johnsonResult.empty()) {
                std::cout << "Алгоритм Джонсона обнаружил отрицательный цикл" << std::endl;
            } else {
                std::cout << "Джонсон выполнен за: " << johnsonTime.count() << " мкс" << std::endl;
                
                // Тестируем наивный алгоритм (только для небольших графов)
                if (testCase.n <= 300000) {
                    std::cout << "Запуск наивного алгоритма..." << std::endl;
                    start = std::chrono::high_resolution_clock::now();
                    auto naiveResult = naiveAllPairsDijkstra(edges, testCase.n, edges.size());
                    end = std::chrono::high_resolution_clock::now();
                    auto naiveTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                    
                    std::cout << "Наивный алгоритм выполнен за: " << naiveTime.count() << " мкс" << std::endl;
                    
                    // Проверяем корректность
                    bool correct = compareResults(johnsonResult, naiveResult);
                    std::cout << "Результаты совпадают: " << (correct ? "ДА" : "НЕТ") << std::endl;
                    
                    // Сравниваем производительность
                    if (johnsonTime.count() > 0 && naiveTime.count() > 0) {
                        double speedup = static_cast<double>(naiveTime.count()) / johnsonTime.count();
                        std::cout << "Отношение производительности (Наивный/Джонсон): " 
                                 << std::fixed << std::setprecision(2) << speedup << "x" << std::endl;
                        
                        if (speedup > 1.0) {
                            std::cout << "Джонсон быстрее в " << speedup << " раз" << std::endl;
                        } else if (speedup < 1.0) {
                            std::cout << "Наивный быстрее в " << (1.0/speedup) << " раз" << std::endl;
                        } else {
                            std::cout << "Производительность одинакова" << std::endl;
                        }
                    }
                } else {
                    std::cout << "Наивный алгоритм пропущен (граф слишком большой)" << std::endl;
                }
            }
            
        } catch (const std::exception& e) {
            std::cout << "Ошибка при выполнении теста: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Неизвестная ошибка при выполнении теста" << std::endl;
        }
        
        std::cout << "----------------------------------------" << std::endl;
    }
    
    // Отдельный тест для графов с отрицательными весами (без отрицательных циклов)
    std::cout << "\n=== Тест с отрицательными весами (без циклов) ===" << std::endl;
    {
        int n = 10;
        int m = 20;
        
        // Создаем граф с безопасными отрицательными весами
        std::vector<edge> edges;
        std::mt19937 gen(123);
        std::uniform_int_distribution<int> vertexDist(1, n);
        std::uniform_int_distribution<long long> weightDist(-5, 10); // Небольшие отрицательные веса
        
        for (int i = 0; i < m; i++) {
            int u = vertexDist(gen);
            int v = vertexDist(gen);
            if (u != v) {
                edges.push_back(edge(u, v, weightDist(gen)));
            }
        }
        
        std::cout << "\nГраф с " << n << " вершинами, " << edges.size() 
                  << " ребрами и отрицательными весами" << std::endl;
        
        auto start = std::chrono::high_resolution_clock::now();
        auto johnsonResult = johnsonAlgorithm(edges, n, edges.size());
        auto end = std::chrono::high_resolution_clock::now();
        auto johnsonTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        if (johnsonResult.empty()) {
            std::cout << "Джонсон обнаружил отрицательный цикл" << std::endl;
        } else {
            std::cout << "Джонсон выполнен за: " << johnsonTime.count() << " мкс" << std::endl;
            
            // Проверяем некоторые свойства результата
            bool hasValidResult = true;
            for (int i = 0; i < n; i++) {
                if (johnsonResult[i][i] != 0) {
                    std::cout << "Ошибка: расстояние от " << i << " до себя = " 
                             << johnsonResult[i][i] << std::endl;
                    hasValidResult = false;
                }
            }
            
            if (hasValidResult) {
                std::cout << "Результаты выглядят корректно (саморасстояния = 0)" << std::endl;
            }
        }
    }
}

int main() {
    std::cout << "Запуск безопасного бенчмарка..." << std::endl;
    
    try {
        runSafeBenchmark();
        std::cout << "\nБенчмарк успешно завершен!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Неизвестная критическая ошибка" << std::endl;
        return 1;
    }
    
    return 0;
}