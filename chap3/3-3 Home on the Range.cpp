/*
ID: mazhaoj1
PROG: range
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

/*  不会，抄的dp
dp题。用dp[i][j][m]表示左上角为(i,j)，边长为m的正方形是否完整。那么
如果dp[i][j][m]完整，则当且仅当dp[i][j][m-1],dp[i+1][j][m-1],dp[i][j+1][m-1],dp[i+1][j+1][m-1]的
正方形也是完整的(画个图就很清晰了)。由于我们从上到下，从左到右扫描每个点，在每一轮i,j用过一次，
就不会再使用，所以只需用二维数组保存dp[i][j]，即可。
时间复杂度为O(n^3),空间复杂度为O(n^2)。analysis中有个时间复杂度为O(n^2),空间O(n)的解法。
*/

int main()
{
    ifstream fin("range.in");
    ofstream fout("range.out");
    int n, cnt;
    char square[250][250];
    bool issquare[250][250];
    memset(issquare, false, sizeof(issquare));
    fin >> n;
    for(int i = 0 ; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            fin >> square[i][j];
            if(square[i][j] == '1')
                issquare[i][j] = true;
        }
    }
    for(int k = 2; k <= n; ++k)
    {
        cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i + k <= n && j + k <= n)
                {
                    issquare[i][j] = issquare[i][j] && issquare[i + 1][j]
                                    && issquare[i][j + 1] && issquare[i + 1][j + 1];
                    if(issquare[i][j])
                        cnt++;
                }
            }
        }
        if(cnt != 0)
            fout << k << ' ' << cnt << endl;
    }
    return 0;
}
