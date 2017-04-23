/*
ID: mazhaoj1
PROG: bigbrn
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

//��f[i,j]Ϊ�Ե�(i,j)Ϊ���½ǵ���������Ρ���tree[i,j]=true����f[i,j]=0��
//����f[i,j]=min(f[i-1,j],f[i,j-1],f[i-1,j-1])+1������chap 3-3 Home on the Range

bool farm[1001][1001];
int dp[1001][1001], ans;

int main()
{
    ifstream fin("bigbrn.in");
    ofstream fout("bigbrn.out");
    int n, t, row, col;
    fin >> n >> t;
    for(int i = 0; i < t; ++i)
    {
        fin >> row >> col;
        farm[row][col] = true;
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(farm[i][j] == false)
            {
                if(dp[i - 1][j] < dp[i][j -1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j -1];
                if(dp[i][j] > dp[i - 1][j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                dp[i][j]++;
                if(ans < dp[i][j])
                    ans = dp[i][j];
            }
        }
    }
    fout << ans << endl;
    return 0;
}
