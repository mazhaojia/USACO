/*
ID: mazhaoj1
PROG: buylow
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
动态规划题，就是最长下降序列问题。第一问可以用O(N^2)的算法解决。
s[i]为序列中第i项的值，MaxLength[i]为以第i项为末尾中最长下降序列长度。
状态转移方程为
MaxLength[i]=max{MaxLength[j]}+1 (j=1..i-1 and s[j]>s[i])
初始条件
MaxLength[1]=1
对于第二问求最长下降序列的数量，可以通过求第一问的过程解决。设MaxCnt[i]为第i项为末尾中最长下降序列的个数。
对于所有的j(1≤j≤i-1)如果有(s[j]>s[i] 并且 MaxLength[j]+1>MaxLength[i])则MaxCnt[i]=MaxCnt[j]，否则如果(MaxLength[j]+1==MaxLength[i])可利用加法原理，MaxCnt[i]=MaxCnt[i]+MaxCnt[j]。
考虑到题目中说的不能又重复的序列，我们可以增加一个域Next[i]表示大于i且离i最近的Next[i]使得第Next[i]个数与第i个数相同。如果不存在这样的数则Next[i]=0。这样我们在DP的时候如果出现Next[i]不为0且Next[j]<i可直接跳过。
这个题数据规模很大，需要用到高精度计算，还好只是加法。
zma：我这里就先字符串替代高精度了。。。。
*/

ofstream fout("buylow.out");

struct bignum
{
    char c[100];
    int cnt;
    bignum()
    {
        cnt = 1;
        memset(c, '0', sizeof(c));
        c[0] = '1';
    }
    bignum& operator = (bignum num)
    {
        cnt = num.cnt;
        memcpy(c, num.c, sizeof(char) * cnt);
        return *this;
    }
    bignum& operator + (bignum num)
    {
        int len = cnt < num.cnt ? cnt : num.cnt;
        int a, b, inc = 0, sum;
        for(int i = 0; i < len; ++i)
        {
            a = c[i] - '0';
            b = num.c[i] - '0';
            sum = a + b + inc;
            inc = 0;
            if(sum > 9)
            {
                inc = 1;
                sum -= 10;
            }
            c[i] = sum + '0';
        }
        if(cnt > len)
        {
            for(int i = len; i < cnt; ++i)
            {
                a = c[i] - '0';
                sum = a + inc;
                inc = 0;
                if(sum > 9)
                {
                    inc = 1;
                    sum -= 10;
                }
                c[i] = sum + '0';
            }
        }
        else if(num.cnt > len)
        {
            for(int i = len; i < num.cnt; ++i)
            {
                a = num.c[i] - '0';
                sum = a + inc;
                inc = 0;
                if(sum > 9)
                {
                    inc = 1;
                    sum -= 10;
                }
                c[i] = sum + '0';
            }
            cnt = num.cnt;
        }
        if(inc)
            c[cnt++] = '1';
        return *this;
    }
    void print()
    {
        int j;
        for(j = cnt - 1; j >= 0; --j)
            if(c[j] != '0')
                break;
        for(int i = j; i >= 0; --i)
            fout << c[i];
    }
}cnt[5001];

int main()
{
    ifstream fin("buylow.in");
    int n, price[5001], ans[5001], next[5001];
    fin >> n;
    for(int i = 0; i < n; ++i)
        fin >> price[i];
    price[n] = 0;   //哨兵，这样才能正确处理 10 9 8 7 6 ... 1 时组合数为10的情况。
    for(int i = 0; i <= n; ++i)
    {
        ans[i] = 1;
        next[i] = -1;
        for(int j = i + 1; j < n; ++j)
        {
            if(price[i] == price[j])
            {
                next[i] = j;
                break;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(next[j] != -1 && next[j] < i)
                continue;
            if(price[j] > price[i])
            {
                if(ans[j] + 1 > ans[i])
                {
                    ans[i] = ans[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(ans[j] + 1 == ans[i])   //此处不能用maxans，maxcnt来记录，因为cnt[i]会从大变小。
                    cnt[i] = cnt[i] + cnt[j];
            }
        }
    }
    fout << ans[n] - 1 << ' ';
    cnt[n].print();
    fout << endl;
    return 0;
}

