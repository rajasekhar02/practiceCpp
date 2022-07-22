#include <bits/stdc++.h>

using namespace std;

vector<int> nums;

int countSubsetsSum(int pos, int sum)
{
    if (sum == 0)
    {
        return 1;
    }
    int subsetCount = 0;
    for (int i = pos; i < nums.size(); i++)
    {
        if (sum - nums[i] < 0)
            continue;
        int value = countSubsetsSum(i + 1, sum - nums[i]);
        if (value > 0)
        {
            subsetCount += value;
        }
    }
    return subsetCount;
}

int countSubsetsSumWithBug(int pos, int sum)
{
    if (sum == 0)
    {
        return 1;
    }
    int subsetCount = 0;
    for (int i = pos; i < nums.size(); i++)
    {
        if (sum - nums[i] < 0)
            continue;
        int value = countSubsetsSum(i + 1, sum - nums[i]);
        if (value > 0)
        {
            // this is a bug. because if it only counting once for all the solutions under the subtree
            subsetCount++;
        }
    }
    return subsetCount;
}

int main()
{
    int sum = 15;
    nums = vector<int>{8, 6, 7, 5, 3, 10, 9};
    sort(nums.begin(), nums.end());
    cout << countSubsetsSum(0, sum) << endl;
    return 0;
}