#include <iostream>

namespace N 
{
    int i = 4;
    extern int j;
}

int i = 2;
int N::j = i;

int main()
{ 
    std::cout << N::j << std::endl;
}
