#include <iostream>

int main()
{
    double var = 22;
    double *p;
    p = &var;
    
    std::cout << std::endl << sizeof(p) << std::endl << p << std::endl;
}
