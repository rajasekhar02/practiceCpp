#include <iostream>
#include <string>
#include <random>
#include<algorithm>
using namespace std;
// auto const seed = 123;
auto const hes = std::random_device{}();
mt19937 urbg = mt19937{};

struct interval{
    double leftValue;
    double rightValue;
    int index;
    interval(){
        this->leftValue = 0.0;
        this->rightValue = 0.0;
        this->index=0;
    }
    bool operator<(interval otherInterval) const {
        return this->rightValue < otherInterval.rightValue;
    }
};

int main(int argc, char **argv)
{
    int n = atoi((argv[1]));
    urbg.seed(hes);
    uniform_real_distribution<double> distr1{0, 1};
    double possibleValuesForT[4] = {(double)(1 / n), (double)(1 / sqrt(n)), (double)(1 / log(n)), 0.25f};
    vector<interval> v(n);
    vector<pair<double,int>> leftIntervals(n);
    vector<pair<double,int>> rightIntervals(n);
    double tValue = possibleValuesForT[1]+10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    for (int i = 0; i < n; i++)
    {
        v[i].index = i;
        v[i].leftValue = distr1(urbg);
        double vi = tDirstr1(urbg);
        v[i].rightValue = min(v[i].leftValue+vi ,1.0);
        leftIntervals[i] = make_pair(v[i].leftValue, v[i].index);
        rightIntervals[i] = make_pair(v[i].rightValue, v[i].index);
        // cout << v[i].leftValue <<" "<< v[i].rightValue << " "<<((v[i].rightValue - v[i].leftValue) < tValue) << endl;
    }
    sort(leftIntervals.begin(),leftIntervals.end());
    sort(rightIntervals.begin(),rightIntervals.end());
   for(int i=0;i<leftIntervals.size();i++){
       
   }
    return 0;
}