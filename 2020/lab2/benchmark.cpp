#include <iostream>
#include <chrono>
#include <algorithm>
#include "solution.c"
using duration_t = std::chrono::microseconds;
const std::string DURATION_PREFIX = "us";
/*using duration_t = std::chrono::milliseconds;
const std::string DURATION_PREFIX = "ms";*/
int main()
{
    NVector::TVector<TData> input;
    NVector::TVector<TData> input_stl;
    double key;
    std::string value;
    //freopen("100.txt", "r", stdin);
    while (std::cin >> key >> value)
    {
        input.PushBack(TPair<NSort::TKey, NSort::TValue>(key, value));
        //std::cout << key << value << std::endl;
    }
    input_stl = input;
    std::cout << "Count of lines is " << input.Size() << std::endl;

    // Измеряем время работы сортировки карманами.
    std::chrono::time_point<std::chrono::system_clock> start_ts = std::chrono::system_clock::now();

    NSort::BSort(input);
    auto end_ts = std::chrono::system_clock::now();
    uint64_t pocket_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();

    int s = input_stl.Size();

    // Измеряем время работы stl сортировки.
    start_ts = std::chrono::system_clock::now();
    
    std::stable_sort(input_stl.Begin(), input_stl.End());
    end_ts = std::chrono::system_clock::now();
    uint64_t stl_sort_ts = std::chrono::duration_cast<duration_t>(end_ts - start_ts).count();
    std::cout << "Pocket sort time: " << pocket_sort_ts << DURATION_PREFIX << std::endl;
    std::cout << "STL stable sort time: " << stl_sort_ts << DURATION_PREFIX << std::endl;
    return 0;
}
