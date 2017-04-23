/*
ID: mazhaoj1
PROG: subset
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

/*  SOLVE 1:
    f[i][j]是i个数字（1, 2, 3, 4, .., i）能够组成和为j的个数，
    那么方程式是：f[i][j] = f[i - 1][j] + f[i - 1] [j - i]  (j > i)
                  f[i][j] = f[i - 1][j] + 1  (j == i)
                  f[i][j] = f[i - 1][j]  (j < i)
    j > i 时，f[i - 1][j]是原来不包含i时的集合数，包含了i后原来集合中元素和为j - i的集合加上i正好和为j。
    j == i 时，j这个数字本身构成一个符合条件的集合。
    初值为f[1][1] = 1;
*/

/*
int main()
{
    ofstream fout("subset.out");
    ifstream fin("subset.in");
    int n, need;
    long long ans[40][(39 + 1) * 39 / 2 / 2 + 1];
    fin >> n;
    need = (n + 1) * n / 2;
    if(need & 1)
    {
        fout << 0 << endl;
        return 0;
    }
    need /= 2;
    memset(ans, 0, sizeof(ans));
    ans[1][1] = 1;
    for(int i = 2; i <= n; ++i)
    {
        for(int j = 1; j <= need; ++j)
        {
            ans[i][j] = ans[i - 1][j];
            if(j > i)
                ans[i][j] += ans[i - 1][j - i];
            else if(j == i)
                ans[i][j] += 1;
        }
    }
    fout << ans[n][need] / 2 << endl;
    return 0;
}
*/

//  SOLVE 2: 将SOLVE 1的二维数组简化。
int main()
{
    ofstream fout("subset.out");
    ifstream fin("subset.in");
    int n, need;
    long long ans[(39 + 1) * 39 / 2 / 2 + 1];
    fin >> n;
    need = (n + 1) * n / 2;
    if(need & 1)
    {
        fout << 0 << endl;
        return 0;
    }
    need /= 2;
    memset(ans, 0, sizeof(ans));
    ans[1] = 1;
    for(int i = 2; i <= n; ++i)
    {
        for(int j = need; j >= 1; --j)
        {
            if(j < i)
                ans[j] = ans[j];
            else if(j == i)
                ans[j] += 1;
            else if(j > i)
                ans[j] += ans[j - i];
        }
    }
    fout << ans[need] / 2 << endl;
    return 0;
}
