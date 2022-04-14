#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <utility>
#include <fstream>
using namespace std;
// auto const seed = 123;
auto const hes = std::random_device{}();
mt19937 urbg = mt19937{};

struct interval
{
    double leftValue;
    double rightValue;
    int index;
    interval()
    {
        this->leftValue = 0.0;
        this->rightValue = 0.0;
        this->index = 0;
    }
    bool operator<(interval otherInterval) const
    {
        return this->rightValue < otherInterval.rightValue;
    }
};

vector<vector<int>> getAdjacencyListForGivenIntervals(vector<interval> intervals)
{
    int totalLength = intervals.size();
    vector<vector<int>> adjacencyList(totalLength);
    for (int i = 0; i < totalLength; i++)
    {
        interval x = intervals[i];
        for (int j = i + 1; j < totalLength; j++)
        {
            interval y = intervals[j];
            if (y.leftValue > x.leftValue && y.leftValue > x.rightValue)
                continue;
            if (y.rightValue < x.leftValue && y.rightValue < x.rightValue)
                continue;
            adjacencyList[i].push_back(j);
            adjacencyList[j].push_back(i);
        }
    }
}
void printDOTFormat(vector<interval> intervals, vector<vector<int>> adjacencyList)
{
    char filename[] = "./example1.dot"; // filename
    ofstream fout(filename);
    fout << "digraph g{" << endl;
    for (int i = 0; i < intervals.size(); i++)
    {
        fout << "node [shape = record,height = .1];" << endl;
    }
    // a node has two values
}
int main(int argc, char **argv)
{
    int n = atoi((argv[1]));
    urbg.seed(hes);
    uniform_real_distribution<double> distr1{0, 1};
    double possibleValuesForT[4] = {(double)(1 / n), (double)(1 / sqrt(n)), (double)(1 / log(n)), 0.25f};
    vector<interval> intervalsV(n);
    vector<pair<double, int>> leftIntervals(n);
    vector<pair<double, int>> rightIntervals(n);
    interval intervalsA[n];
    double tValue = possibleValuesForT[1] + 10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    for (int i = 0; i < n; i++)
    {
        intervalsV[i].index = i;
        intervalsV[i].leftValue = distr1(urbg);
        intervalsA[i].leftValue = intervalsV[i].leftValue;
        double vi = tDirstr1(urbg);
        intervalsV[i].rightValue = min(intervalsV[i].leftValue + vi, 1.0);
        intervalsA[i].rightValue = intervalsV[i].rightValue;
        leftIntervals[i] = make_pair(intervalsV[i].leftValue, intervalsV[i].index);
        rightIntervals[i] = make_pair(intervalsV[i].rightValue, intervalsV[i].index);
        cout << intervalsV[i].leftValue << " " << intervalsV[i].rightValue << " " << ((intervalsV[i].rightValue - intervalsV[i].leftValue) < tValue) << endl;
    }
    sort(leftIntervals.begin(), leftIntervals.end());
    sort(rightIntervals.begin(), rightIntervals.end());
    vector<vector<int>> adjacencyList = getAdjacencyListForGivenIntervals(intervalsV);
    // printDOTFormat(intervals, adjacencyList);
    return 0;
}