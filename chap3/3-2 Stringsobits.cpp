/*
ID: mazhaoj1
PROG: kimbits
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

/*用dp[i][j]表示i位数中，"1的个数小于等于j"的个数。则若i的最高位为0，dp[i][j] = dp[i - 1][j]；若i的最高位为1，dp[i][j] = dp[i - 1][j - 1];
若j > i, dp[i][j] = dp[i][i]; 我们从最左边开始，如果dp[i-1][j]的数大于n，说明第一位为0，如果小于n，说明第一位为1，既然第一位已经是1了，接下来的i-1位组成的数的1的个数只能小于等于n-1位了。迭代输出每一位即可。
只是要注意溢出的问题以及dp[0][1]。
*/

int main()
{
    ifstream fin("kimbits.in");
    ofstream fout("kimbits.out");
    unsigned int len, one, cnt;
    fin >> len >> one >> cnt;
    unsigned int dp[32][32];
    for(int i = 0; i < 32; ++i)
    {
        dp[i][0] = 1;
        dp[0][i] = 1;
    }
    for(int i = 1; i < 32; ++i)
    {
        for(int j = 1; j < 32; ++j)
        {
            if(j > i)
                dp[i][j] = dp[i][i];
            else
                dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }
    for(int i = len; i > 0; --i)
    {
        if(dp[i - 1][one] >= cnt)
            fout << '0';
        else
        {
            fout << '1';
            cnt -= dp[i - 1][one];
            one--;
        }
    }
    fout << endl;
    return 0;
}
