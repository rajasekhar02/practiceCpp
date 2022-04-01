#include "file1.hpp"
#include <iostream>
extern int x;
namespace file1
{
    void printY()
    {
        std::cout << x << "method y" << std::endl;
    }
    void printX(int x)
    {
        std::cout << x << "method x" << std::endl;
    }
}
