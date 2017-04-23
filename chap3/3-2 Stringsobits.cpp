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

/*��dp[i][j]��ʾiλ���У�"1�ĸ���С�ڵ���j"�ĸ���������i�����λΪ0��dp[i][j] = dp[i - 1][j]����i�����λΪ1��dp[i][j] = dp[i - 1][j - 1];
��j > i, dp[i][j] = dp[i][i]; ���Ǵ�����߿�ʼ�����dp[i-1][j]��������n��˵����һλΪ0�����С��n��˵����һλΪ1����Ȼ��һλ�Ѿ���1�ˣ���������i-1λ��ɵ�����1�ĸ���ֻ��С�ڵ���n-1λ�ˡ��������ÿһλ���ɡ�
ֻ��Ҫע������������Լ�dp[0][1]��
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
