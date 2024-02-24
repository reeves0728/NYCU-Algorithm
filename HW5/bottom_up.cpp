#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX_N = 1000;
int n;
int p[MAX_N];
int memo[MAX_N];
int memo_min[MAX_N];
vector<int> cuts[MAX_N];
vector<int> cuts_min[MAX_N];

int cut_rod()
{
    memo[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int max_profit = -1;
        for (int j = 1; j <= i; j++)
        {
            int profit = p[j] + memo[i - j];
            if (profit > max_profit)
            {
                max_profit = profit;
                cuts[i] = cuts[i - j];
                cuts[i].push_back(j);
            }
        }
        memo[i] = max_profit;
    }
    return memo[n];
}

int cut_rod_min()
{
    memo_min[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        int min_profit = INT_MAX;
        for (int j = 1; j <= i; j++)
        {
            int profit = p[j] + memo_min[i - j];
            if (profit < min_profit)
            {
                min_profit = profit;
                cuts_min[i] = cuts_min[i - j];
                cuts_min[i].push_back(j);
            }
        }
        memo_min[i] = min_profit;
    }
    return memo_min[n];
}

void print_cuts(vector<int> cuts)
{
    for (int i = 0; i < cuts.size(); i++)
    {
        cout << cuts[i];
        if (i < cuts.size() - 1)
        {
            cout << " + ";
        }
    }
    cout << endl;
}

int main()
{
    memset(memo, -1, sizeof(memo));
    memset(memo_min, -1, sizeof(memo_min));
    cout << "Please input rod length: " << endl;
    cin >> n;
    cout << "Please input 1~10 unit length's price in increasing order: " << endl;
    for (int i = 1; i <= n; i++)
    {
        cin >> p[i];
    }
    int max_profit = cut_rod();
    int min_profit = cut_rod_min();
    cout << "Using bottom up method:" << endl;
    cout << "Maximum Profit: " << max_profit << endl;
    cout << "Number of pieces: " << cuts[n].size() << endl;
    cout << "Cutting Method: ";
    print_cuts(cuts[n]);
    cout << "------------------------------------" << endl;
    cout << "Minimum Profit: " << min_profit << endl;
    cout << "Number of pieces: " << cuts_min[n].size() << endl;
    cout << "Cutting Method: ";
    print_cuts(cuts_min[n]);
    return 0;
}
