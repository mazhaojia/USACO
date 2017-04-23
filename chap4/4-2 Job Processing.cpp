/*
ID: mazhaoj1
PROG: job
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
这题很经典，网上资料大多是一带而过，因此转载了一篇较详细的分析。
http://magicalcode.blogbus.com/logs/37193487.html
若有疑问的地方，可参照本文中引理的证明。

引理1：题目第一问，单个最优解的构造（即让最晚零件结束的时间最早）
每次把零件安排在延迟+加工时间最少的机器上。证明采取反证，安排过去一定得到另一个最优解。

引理2：
要证明一个性质，假设如下图所示的流程图是最优解，一定可以找到一个为两边各自为最优的情况。
1WWWWWWWAAAAAAA                BBBBBBBW
2WWWWAAAA                       BBBBBWWWWW
3WWWWWWWWWWWAAAAAAA             BBBB
4AAAAAAA             BBBBBBBWWWWWWWWW
这是由“最优”的性质决定的。“最优”意味着对任意N个产品，最晚的结束时间是最早的（引理1）。因此取 N=1，2…k,可以归纳证得任意第k个结束的产品，都比非最优方案结束的早。因此不会发生重叠现象。
这样把问题转化为了最优解的排列问题。

引理3：
对于两数组a[n],b[n], a[n]按升序排列，b[n]按降序排列，设数组c[i] = a[i] + b[i]，则将an和bn分别重新排列后，再次得到 d[i] =a`[i]+b`[i]，则 max(ci) <= max(di)，
假设不是按升降序排列,那么必然存在（小，小），（大，大）的组合，交换使其成为（小，大），（大，小），不会提高上限。这样交换一定次数可以成为升降序排列。
总结：
这题关键是平均贪心思想的运用。还有要想到把一个顺序加工的过程转化为从两边向中间加工。
*/

struct machine
{
    int processtime, willfinishtime;
}a[30], b[30];

bool cmp(const int& a, const int& b)
{
    return a > b;
}

int main()
{
    ifstream fin("job.in");
    ofstream fout("job.out");
    int n, m1, m2, m1min, m2min, m1minpos, m2minpos, finishtimea[1000], finishtimeb[1000], ans = 0;
    fin >> n >> m1 >> m2;
    for(int i = 0; i < m1; ++i)
        fin >> a[i].processtime;
    for(int i = 0; i < m2; ++i)
        fin >> b[i].processtime;
    for(int i = 0; i < n; ++i)
    {
        m1min = m2min = 50000000;
        for(int j = 0; j < m1; ++j)
        {
            if(a[j].processtime + a[j].willfinishtime < m1min)
            {
                m1min = a[j].processtime + a[j].willfinishtime;
                m1minpos = j;
            }
        }
        a[m1minpos].willfinishtime = m1min;
        finishtimea[i] = m1min;
        for(int j = 0; j < m2; ++j)
        {
            if(b[j].processtime + b[j].willfinishtime < m2min)
            {
                m2min = b[j].processtime + b[j].willfinishtime;
                m2minpos = j;
            }
        }
        b[m2minpos].willfinishtime = m2min;
        finishtimeb[i] = m2min;
    }
    sort(finishtimea, finishtimea + n);
    sort(finishtimeb, finishtimeb + n, cmp);
    for(int i = 0; i < n; ++i)
        if(ans < finishtimea[i] + finishtimeb[i])
            ans = finishtimea[i] + finishtimeb[i];
    fout << finishtimea[n - 1] << ' ' << ans << endl;
    return 0;
}
