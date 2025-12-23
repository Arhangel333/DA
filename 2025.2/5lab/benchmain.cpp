#include "bench.hpp"

void runSmallBenchmarks() {
    Benchmark bench;
    std::cout << "=== SMALL BENCHMARKS ===" << std::endl;
    
    for (int size : {100, 500, 1000}) {
        bench.benchmarkConstruction(size);
    }
    
    bench.benchmarkSearch(1000, 10, 100);
    bench.benchmarkMemoryUsage(1000);
}

void runMediumBenchmarks() {
    Benchmark bench;
    std::cout << "\n=== MEDIUM BENCHMARKS ===" << std::endl;
    
    for (int size : {5000, 10000}) {
        bench.benchmarkConstruction(size);
    }
    
    bench.benchmarkSearch(10000, 20, 50);
    bench.benchmarkMemoryUsage(10000);
}

void runLargeBenchmarks() {
    Benchmark bench;
    std::cout << "\n=== LARGE BENCHMARKS ===" << std::endl;
    
    for (int size : {50000, 100000}) {
        bench.benchmarkConstruction(size);
    }
    
    bench.benchmarkSearch(100000, 30, 20);
    bench.benchmarkMemoryUsage(100000);
}

void runPatternLengthBenchmark() {
    Benchmark bench;
    std::cout << "\n=== PATTERN LENGTH IMPACT ===" << std::endl;
    
    std::string text = bench.generateRandomString(10000);
    auto suffix_array = BuildArr(text + "$");
    
    for (int pattern_len : {5, 10, 20, 50, 100}) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 100; ++i) {
            auto pattern = bench.generateRandomString(pattern_len);
            auto result = Search(text, pattern, suffix_array);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        
        std::cout << "Pattern length " << pattern_len << ": " 
                  << duration.count() << " μs for 100 searches" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string mode = argv[1];
        if (mode == "small") runSmallBenchmarks();
        else if (mode == "medium") runMediumBenchmarks();
        else if (mode == "large") runLargeBenchmarks();
        else if (mode == "pattern") runPatternLengthBenchmark();
    } else {
        runSmallBenchmarks();
        runMediumBenchmarks();
        runLargeBenchmarks();
        runPatternLengthBenchmark();
    }
    
    return 0;
}