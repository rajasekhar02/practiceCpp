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
bool areTwoNodesAdjacent(int node1, int node2, vector<vector<int>> adjacencyList)
{
    vector<int> nodesAdjacent = adjacencyList[node1];
    return find(nodesAdjacent.begin(), nodesAdjacent.end(), node2) != nodesAdjacent.end();
}
int getMaximumIndependentSet(vector<interval> intervals, vector<vector<int>> adjacencyList)
{
    vector<int> maxIndependentSet;
    vector<int> markedIntervals(intervals.size());
    vector<pair<double, int>> rightIntervals;
    int count = 0;
    cout << "asdf" << endl;
    while (count != (intervals.size() - 1))
    {
        rightIntervals = vector<pair<double, int>>();
        for (int i = 0; i < intervals.size(); i++)
        {
            if (markedIntervals[i] == 0)
            {
                rightIntervals.push_back(make_pair(intervals[i].rightValue, i));
            }
        }
        sort(rightIntervals.begin(), rightIntervals.end());
        if (rightIntervals.size() == 0)
        {
            break;
        }
        int index = rightIntervals[0].second;
        maxIndependentSet.push_back(index);
        vector<int> overlappingIntervals = adjacencyList[index];
        markedIntervals[index] = 1;
        for (int i = 0; i < overlappingIntervals.size(); i++)
        {
            markedIntervals[overlappingIntervals[i]] = 1;
        }
        count = 0;
        for (int i = 0; i < intervals.size(); i++)
        {
            if (markedIntervals[i] == 1)
            {
                count++;
            }
        }
    }
    cout << intervals.size() << endl;
    for (int i = 0; i < maxIndependentSet.size(); i++)
    {
        cout << maxIndependentSet[i] << endl;
    }
    return maxIndependentSet.size();
}
int main(int argc, char **argv)
{
    int n = atoi((argv[1]));
    urbg.seed(hes);
    uniform_real_distribution<double> distr1{0, 1};
    double possibleValuesForT[4] = {(double)(1 / n), (double)(1 / sqrt(n)), (double)(1 / log(n)), 0.25f};
    vector<interval> intervalsV(n);
    vector<pair<double, int>> linearIntervals(2 * n);
    double tValue = possibleValuesForT[1] + 10e-10;
    uniform_real_distribution<double> tDirstr1{0, tValue};
    for (int i = 0; i < n; i++)
    {
        intervalsV[i].index = i;
        intervalsV[i].leftValue = distr1(urbg);
        double vi = tDirstr1(urbg);
        intervalsV[i].rightValue = min(intervalsV[i].leftValue + vi, 1.0);
        linearIntervals[2 * i] = make_pair(intervalsV[i].leftValue, intervalsV[i].index);
        linearIntervals[2 * i + 1] = make_pair(intervalsV[i].rightValue, intervalsV[i].index);
    }
    sort(linearIntervals.begin(), linearIntervals.end());

    vector<vector<int>> adjacencyList1 = getAdjacencyListForGivenIntervals(intervalsV, true);
    vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenIntervals(intervalsV, false);
    printDOTFormat(intervalsV, adjacencyList2);
    // vector<vector<int>> adjacencyList2 = getAdjacencyListForGivenSortedIntervalParts(intervalsV, leftIntervals, rightIntervals);
    // printAdjacencyList(adjacencyList1);
    cout << getMaximumIndependentSet(intervalsV, adjacencyList1) << endl;
    return 0;
}