<<<<<<< HEAD
#include <iostream>
#include <cstdio>

int main(){
    int k = 0;
    char a = 0;
    freopen("pro.txt", "w+", stdout);
    srand(time(NULL));
    k = rand();
    for (size_t i = 0; i < 100000; i++)
    {
        srand(k);
            k = rand();
            a = k%(122 - 97) + 97;
            std::cout<< a;
        if(i % 15 ==0){
            std::cout<<" ";
        }
        if(i % 45 ==0){
            std::cout<<std::endl;
        }
    }
    
=======
#include <iostream>
#include <cstdio>

int main(){
    int k = 0;
    char a = 0;
    freopen("pro.txt", "w+", stdout);
    srand(time(NULL));
    k = rand();
    for (size_t i = 0; i < 100000; i++)
    {
        srand(k);
            k = rand();
            a = k%(122 - 97) + 97;
            std::cout<< a;
        if(i % 15 ==0){
            std::cout<<" ";
        }
        if(i % 45 ==0){
            std::cout<<std::endl;
        }
    }
    
>>>>>>> 017b9db (8 9 fiished)
}