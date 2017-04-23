/*
ID: mazhaoj1
PROG: nocows
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("nocows.in");
    ofstream fout("nocows.out");
    int num, height;
    long long dp[200][100];
    fin >> num >> height;
    memset(dp, 0, sizeof(dp));
    dp[1][1] = 1;
    for(int i = 3; i <= num; i += 2)
    {
        int minh = (int)log2((double)i) + 1;
        for(int j = minh; j <= height; ++j)
        {
            int minnode = 1;
            int maxnode = i - 1 - minnode;
            for(int k = minnode; k <= maxnode; k += 2)
            {
                int nodemaxh = (k + 1) / 2, maxleft = 0, maxright = 0;
                if(j - 1 > nodemaxh)
                    maxleft = dp[k][nodemaxh];
                else
                    maxleft = dp[k][j - 1];
                nodemaxh = (i - 1 - k + 1) / 2;
                if(j - 1 > nodemaxh)
                    maxright = dp[i - 1 - k][nodemaxh];
                else
                    maxright = dp[i - 1 - k][j - 1];
                dp[i][j] += (maxleft * maxright) % 9901;
                dp[i][j] = dp[i][j] % 9901;
            }
        }
    }
    int result = dp[num][height] - dp[num][height - 1];
    if(result < 0)
        result += 9901;
    fout << result << endl;
    return 0;
}
