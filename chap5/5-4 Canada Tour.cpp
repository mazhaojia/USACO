/*
ID: mazhaoj1
PROG: tour
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

/*下面是结合了google和自己的理解:
把返回的路线反向，那么就相当于有两个人分别从起点到终点进行旅行，那么整条路线就变成了两条不相交的从起点到终点的路线。
设f[i,j]为假定的甲乙两人，甲走到第i个城市，乙走到第j个城市时，两人走过的城市数目的和。则初始状态f[1,1] = 1
交换甲乙，则可知f[i,j]与f[j,i]等价。所以我们可以只考虑f[i,j]。
无论(i,j)处于什么城市，要么i>j，要么j>i,如果i>j,那么交换i,j可得j>i，所以可以只关注j>i的情况。
分析状态(i,j){i<j}，它只可能是从(i,k){k<j}中k到达j得到
1、如果i<k，那么状态(i,j)可以从(i,k){i<k<j}中k到达j得到，即f[i,j] = f[i,k] + 1
2、如果k<i,那么不符合i<j的前提条件，但是我们可以先交换i,k，然后状态(i,j)可以从(k,i)中k到达j得到(j,i)，再交换i,j得到,
   即f[i,j] = f[k,i] + 1
所以状态转移方程是：dp[i,j]=dp[j,i]=max{dp[i,k]+1(k,j可达且i<k<j), dp[k][i]+1(k,j可达且k<i)}。
为了求得2中的f[k,i]，可以在1中求出f[i,k]后，立即将f[k,i] = f[i,k]，具体可以看代码。
这样状态转移方程中的dp[k][i]和dp[i,k]就一样了。
所以最终的状态转移方程是：dp[i,j]=dp[j][i]=max{dp[i,k]+1(k,j可达且k<j, k = 1 到 n)}。
由于题中告知必须走到终点才能返回，输出结果一定是max{f[i,N]}(i到N存在飞机航线)。
*/

string name[100], temp1, temp2;     //注意样例名字后面可能有空格，所以这里用string最直接
bool flight[100][100];
int namecnt, flightcnt, s, d, ct, dp[100][100], maxi;

int main()
{
    ifstream fin("tour.in");
    ofstream fout("tour.out");
    fin >> namecnt >> flightcnt;
    for(int i = 0; i < namecnt; ++i)
        fin >> name[i];
    for(int i = 0; i < flightcnt; ++i)
    {
        fin >> temp1 >> temp2;
        ct = 0;
        for(int j = 0; j < namecnt; ++j)
        {
            if(temp1 == name[j])
            {
                s = j;
                ct++;
            }
            if(temp2 == name[j])
            {
                d = j;
                ct++;
            }
            if(ct == 2)
                break;
        }
        flight[s][d] = flight[d][s] = true;
    }
    dp[0][0] = 1;
    for(int i = 0; i < namecnt; ++i)
    {
        for(int j = i + 1; j < namecnt; ++j)
        {
            for(int k = 0; k < j; ++k)
                if(flight[k][j] && dp[i][k] > 0 && dp[i][j] < dp[i][k] + 1) //dp[i][k] > 0注意，因为这表示无解的情况
                    dp[i][j] = dp[i][k] + 1;
            dp[j][i] = dp[i][j];
        }
    }
    for(int i = 0; i < namecnt - 1; ++i)
        if(flight[i][namecnt - 1] && maxi < dp[i][namecnt - 1])
            maxi = dp[i][namecnt - 1];
    if(maxi == 0)   //无解，则只有源点可达
        maxi++;
    fout << maxi << endl;
    return 0;
}
