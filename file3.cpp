#include "file1.hpp"
#include "file2.hpp"
#include <iostream>
using namespace std;
int x = 10;
int main()
{
    // int x = 10;
    // cout << x << endl;
    file1::printX(x);
    file1::printY();
    file2::printX();
    return 0;
}