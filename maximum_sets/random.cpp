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
    char *getDotNodeFormat()
    {
        char *s;
        int stringLen = snprintf(NULL, 0, "struct%d [shape=record, label=\"%f|I%d|%f\"];", this->index, this->leftValue, this->index, this->rightValue);
        s = (char *)malloc(sizeof(char) * stringLen);
        snprintf(s, stringLen, "struct%d [shape=record, label=\"%f|I%d|%f\"];", this->index, this->leftValue, this->index, this->rightValue);
        return s;
    }
    bool operator<(interval otherInterval) const
    {
        return this->rightValue < otherInterval.rightValue;
    }
};

vector<vector<int>> getAdjacencyListForGivenIntervals(vector<interval> intervals, bool undirectional)
{
    int totalLength = intervals.size();
    vector<vector<int>> adjacencyList(totalLength, vector<int>());
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
            if (undirectional)
            {
                adjacencyList[j].push_back(i);
            }
        }
    }
    return adjacencyList;
}
void printAdjacencyList(vector<vector<int>> adjacencyList)
{
    for (int i = 0; i < adjacencyList.size(); i++)
    {
        printf("[%d]: ", i);
        for (int j = 0; j < adjacencyList[i].size(); j++)
        {
            cout << " -> " << adjacencyList[i][j];
        }
        cout << endl;
    }
}
void printDOTFormat(vector<interval> intervals, vector<vector<int>> adjacencyList)
{
    char filename[] = "./example1.dot"; // filename
    ofstream fout(filename);
    fout << "graph IntervalGraph {" << endl;
    for (int i = 0; i < intervals.size(); i++)
    {
        fout << intervals[i].getDotNodeFormat() << endl;
    }
    for (int i = 0; i < intervals.size(); i++)
    {
        if (adjacencyList[i].size() == 0)
        {
            fout << " struct" << i << ";" << endl;
        }

        for (int j = 0; j < adjacencyList[i].size(); j++)
        {
            fout << " struct" << i << " -- "
                 << "struct" << adjacencyList[i][j] << ";" << endl;
        }
    }
    fout << "}" << endl;
    // a node has two values
    fout.close();
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
    double tValue = possibleValuesForT[1] + 10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    for (int i = 0; i < n; i++)
    {
        intervalsV[i].index = i;
        intervalsV[i].leftValue = distr1(urbg);
        double vi = tDirstr1(urbg);
        intervalsV[i].rightValue = min(intervalsV[i].leftValue + vi, 1.0);
        leftIntervals[i] = make_pair(intervalsV[i].leftValue, intervalsV[i].index);
        rightIntervals[i] = make_pair(intervalsV[i].rightValue, intervalsV[i].index);
    }
    sort(leftIntervals.begin(), leftIntervals.end());
    sort(rightIntervals.begin(), rightIntervals.end());
    vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenIntervals(intervalsV, false);
    vector<vector<int>> adjacencyList1 = getAdjacencyListForGivenIntervals(intervalsV, true);
    // vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenSortedIntervalParts(intervalsV, leftIntervals, rightIntervals);
    printAdjacencyList(adjacencyList1);
    printDOTFormat(intervalsV, adjacencyList2);
    return 0;
}