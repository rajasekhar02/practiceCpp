#include <iostream>
#include "file2.hpp"
namespace file2
{
    extern int x;
    void printX()
    {
        std::cout << x << std::endl;
    }
}
