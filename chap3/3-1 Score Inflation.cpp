/*
ID: mazhaoj1
PROG: inflate
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("inflate.in");
    ofstream fout("inflate.out");
    int m, n, points[10000], minutes[10000], dp[10001], minmin = 99999999, minpos = 0;
    fin >> m >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> points[i] >> minutes[i];
        if(minmin > minutes[i])
        {
            minmin = minutes[i];
            minpos = i;
        }
    }
    memset(dp, 0, sizeof(dp));
    dp[minmin] = points[minpos];
    for(int i = minmin + 1; i <= m; ++i)
    {
        dp[i] = dp[i - 1];
        for(int j = 0; j < n; ++j)
            if(i - minutes[j] >= 0 && dp[i] < dp[i - minutes[j]] + points[j])
                dp[i] = dp[i - minutes[j]] + points[j];
    }
    fout << dp[m] << endl;
    return 0;
}
