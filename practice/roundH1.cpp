#include <bits/stdc++.h>
using namespace std;
void solve1()
{
    int t;
    cin >> t;
    int cases = t;
    cin.ignore();
    while (cases--)
    {
        string S;
        string F;
        cin >> S >> F;
        int ans = 0;
        for (int i = 0; i < S.length(); i++)
        {
            int distance = 99999999;
            for (int j = 0; j < F.length(); j++)
            {
                distance = min(distance, min(abs(F[j] - S[i]), (26 - abs(F[j] - S[i]))));
            }
            ans += distance;
        }
        printf("Case #%d: %d\n", t - cases, ans);
    }
}
void solve2()
{
    ifstream fin("ts1_input.txt");
    int t;
    fin >> t;
    cout<<t<<endl;
    int cases = t;
    while (cases--)
    {
        string S;
        string F;
        fin >> S >> F;
        int ans = 0;
        for (int i = 0; i < S.length(); i++)
        {
            int distance = 99999999;
            for (int j = 0; j < F.length(); j++)
            {
                distance = min(distance, min(abs(F[j] - S[i]), (26-abs(F[j] - S[i]))));
            }
            ans += distance;
        }
        printf("Case #%d: %d\n", t - cases, ans);
    }
    fin.close();
}
int main(int argc, char **argv)
{
    solve2();
    return 0;
}