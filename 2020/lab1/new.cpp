#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include "main.hpp"

std::vector<int32_t> merge(const std::vector<int32_t> &l1, const std::vector<int32_t> &l2)
{
    std::vector<int32_t> res;
    size_t i = 0, j = 0 ;
    
    while(i < l1.size() && j < l2.size()){
        if(l1[i] < l2[j]){
            ++i;
        }else if(l1[i] > l2[j]){
            ++j;
        }else{
            if(res.back() != l1[i])
            res.push_back(l1[i]);
            
        }
        ++i;
        ++j;
    }
    return res;
}

int main(){

    std::vector<int32_t> l1 = {1, 2, 5, 5, 6, 10};
    std::vector<int32_t> l2 = {2, 5, 8, 10, 20};
    
    std::vector<int32_t> merged = merge(l1, l2);
    
    std::cout << "[";
    for (size_t i = 0; i < merged.size(); ++i) {
        std::cout << merged[i];
        if (i != merged.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]" << std::endl;


    return 0;

}