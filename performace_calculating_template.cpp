#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::clock_t;

int main()
{
    double elapsed_secs = 0;
    clock_t begin = clock();
    // place the algorithm here to calculate time taken
    clock_t end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << "\tTIME:\t" << elapsed_secs << endl;
    return 0;
}