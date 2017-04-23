/*
ID: mazhaoj1
PROG: vans
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

/*
看了nocow和几个神牛的blog，本题貌似有很多解法，连通性状态压缩DP有时间再看吧。
但我认为最简单易懂的解法是这个：
http://dfs35123.spaces.live.com/blog/cns!A6CB032EC0980F16!483.entry
*/

#define base 100000000
int n;
struct bignum
{
    int num[100];
    int len;
    void operator = (bignum& b)
    {
        for(int i = 0; i < b.len; ++i)
            num[i] = b.num[i];
        len = b.len;
    }
    void operator + (bignum& b)
    {
        int inc = 0, i, maxlen = len > b.len ? len : b.len;
        for(i = 0; i < maxlen; ++i)
        {
            num[i] = num[i] + b.num[i] + inc;
            inc = num[i] / base;
            num[i] %= base;
        }
        len = maxlen;
        if(inc > 0)
            num[len++] = inc;
    }
    void print(ofstream& fout)
    {
        fout << num[len - 1];
        for(int i = len - 2; i >= 0; --i)
        {
            int t = num[i] * 10;    //为了这里乘不溢出，base最大值只能为100000000
            while(t < base)
            {
                fout << 0;
                t *= 10;
            }
            fout << num[i];
        }
        fout << endl;
    }
    bignum():len(1){memset(num, 0, sizeof(num));}
}*f, *g, * temp;

int main()
{
    ifstream fin("vans.in");
    ofstream fout("vans.out");
    fin >> n;
    if(n == 1)
    {
        fout << 0 << endl;
        return 0;
    }
    f = new bignum[6];
    g = new bignum[6];
    f[1].num[0] = 1;
    f[2].num[0] = 1;
    for(int i = 2; i < n; ++i)  //以每隔右面那条列来代表那个格子
    {
        temp = g;
        g = f;
        f = temp;
        f[1] = g[2];
        f[1] + g[4];
        f[1] + g[5];
        f[1] + g[5];
        f[2] = g[2];
        f[2] + g[5];
        f[2] + g[5];
        f[3] = g[1];
        f[3] + g[3];
        f[4] = g[1];
        f[5] = g[1];
        f[5] + g[3];
    }
    f[1] + f[3];
    f[1] + f[1];
    f[1].print(fout);
    return 0;
}
