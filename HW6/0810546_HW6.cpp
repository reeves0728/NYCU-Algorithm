#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

vector<vector<vector<int>>> lcs;

int LCSLength(const vector<double> &X, const vector<double> &Y, const vector<double> &Z)
{
    int N1 = X.size();
    int N2 = Y.size();
    int N3 = Z.size();

    // init
    lcs.resize(N1 + 1, vector<vector<int>>(N2 + 1, vector<int>(N3 + 1, 0)));

    // calculate LCS length
    for (int i = 1; i <= N1; i++)
    {
        for (int j = 1; j <= N2; j++)
        {
            for (int k = 1; k <= N3; k++)
            {
                if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1])
                {
                    lcs[i][j][k] = lcs[i - 1][j - 1][k - 1] + 1;
                }
                else
                {
                    lcs[i][j][k] = max({lcs[i - 1][j][k], lcs[i][j - 1][k], lcs[i][j][k - 1]});
                }
            }
        }
    }

    return lcs[N1][N2][N3];
}

vector<double> LCS(const vector<double> &X, const vector<double> &Y, const vector<double> &Z)
{
    int N1 = X.size();
    int N2 = Y.size();
    int N3 = Z.size();

    vector<double> W;

    int i = N1, j = N2, k = N3;
    while (i > 0 && j > 0 && k > 0)
    {
        if (X[i - 1] == Y[j - 1] && Y[j - 1] == Z[k - 1])
        {
            W.push_back(X[i - 1]);
            i--;
            j--;
            k--;
        }
        else if (lcs[i - 1][j][k] >= lcs[i][j - 1][k] && lcs[i - 1][j][k] >= lcs[i][j][k - 1])
        {
            i--;
        }
        else if (lcs[i][j - 1][k] >= lcs[i - 1][j][k] && lcs[i][j - 1][k] >= lcs[i][j][k - 1])
        {
            j--;
        }
        else
        {
            k--;
        }
    }

    reverse(W.begin(), W.end());

    return W;
}

int main()
{
    double num;
    int N1;
    cout << "Please input XYZ's length: ";
    cin >> N1;

    vector<double> X;
    vector<double> Y;
    vector<double> Z;

    for (int i = 0; i < N1; i++)
    {
        num = rand() % 10;
        // cout << "num = " << num;
        X.push_back(num);
    }

    // cout << "X = " << endl;
    // for (int i = 0; i < N1; i++)
    // {
    //     cout << X[i] << " ";
    // }
    // cout << endl;

    for (int i = 0; i < N1; i++)
    {
        num = rand() % 10;
        Y.push_back(num);
    }

    // cout << "Y = " << endl;
    // for (int i = 0; i < N1; i++)
    // {
    //     cout << Y[i] << " ";
    // }
    // cout << endl;

    // 输入Z序列
    for (int i = 0; i < N1; i++)
    {
        num = rand() % 10;
        Z.push_back(num);
    }

    // cout << "Z = " << endl;
    // for (int i = 0; i < N1; i++)
    // {
    //     cout << Z[i] << " ";
    // }
    // cout << endl;

    int lcsLength = LCSLength(X, Y, Z);
    vector<double> lcsSeq = LCS(X, Y, Z);

    cout << "Length of Longest Common Subsequence: " << lcsLength << endl;
    cout << "Longest Common Subsequence: ";
    for (double num : lcsSeq)
    {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
