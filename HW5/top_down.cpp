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

int cut_rod(int length)
{
    if (length == 0)
    {
        return 0;
    }
    if (memo[length] != -1)
    {
        return memo[length];
    }
    int max_profit = -1;
    for (int i = 1; i <= length; i++)
    {
        int profit = p[i] + cut_rod(length - i);
        if (profit > max_profit)
        {
            max_profit = profit;
            cuts[length] = cuts[length - i];
            cuts[length].push_back(i);
        }
    }
    memo[length] = max_profit;
    return max_profit;
}

int cut_rod_min(int length)
{
    if (length == 0)
    {
        return 0;
    }
    if (memo_min[length] != -1)
    {
        return memo_min[length];
    }
    int min_profit = INT_MAX;
    for (int i = 1; i <= length; i++)
    {
        int profit = p[i] + cut_rod_min(length - i);
        if (profit < min_profit)
        {
            min_profit = profit;
            cuts_min[length] = cuts_min[length - i];
            cuts_min[length].push_back(i);
        }
    }
    memo_min[length] = min_profit;
    return min_profit;
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
    for (int i = 1; i <= 10; i++)
    {
        cin >> p[i];
    }
    int max_profit = cut_rod(n);
    int min_profit = cut_rod_min(n);
    cout << "Using top-down method" << endl;
    cout << "total length: " << n << endl;
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
