#include "file1.hpp"
#include <iostream>
namespace file1
{
    extern int x;
    void printX()
    {
        std::cout << x << std::endl;
    }
}
