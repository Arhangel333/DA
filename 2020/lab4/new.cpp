#include <iostream>



int main(){
    char a = 0;


    for (size_t i = 0; i < 200; i++)
    {
       printf("%c - %d\n", a, (int)a);
       a++;
    }
    return 0;
}