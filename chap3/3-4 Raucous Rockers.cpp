/*
ID: mazhaoj1
PROG: rockers
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;    //there is a dp solution!

int n, t, m, song[20], disk[20], ans, recorded;

void solve(int depth, int lastdisk)    //i copyed this search idea..... this is what i need to learn
{
    if(depth == n)
    {
        if(ans < recorded)
            ans = recorded;
        return;
    }
    if(recorded + n - depth <= ans)     //如果后面所有的歌曲都加上还比最优值小，剪枝
        return;
    for(int i = lastdisk; i < m; ++i)
    {
        if(disk[i] >= song[depth])
        {
            disk[i] -= song[depth];
            recorded++;
            solve(depth + 1, i);     //如果当前歌曲需要刻录，那只需刻在第一张能装得下的光盘上。
            recorded--;
            disk[i] += song[depth];
            break;
        }
    }
    solve(depth + 1, lastdisk);     // 不刻当前歌曲
}

int main()
{
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");
    fin >> n >> t >> m;
    for(int i = 0; i < n; ++i)
        fin >> song[i];
    for(int i = 0; i < m; ++i)
        disk[i] = t;
    solve(0, 0);
    fout << ans << endl;
    return 0;
}
