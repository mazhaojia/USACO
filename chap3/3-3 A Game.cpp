/*
ID: mazhaoj1
PROG: game1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

/*设sum(s,t)为区间s,t中的数字之和，gain(s,t)为按最优策略能获得的最大得分，那么，有两种数字的方式，
1.取s，则给对手余下区间(s+1,t)，对手的收益将是gain(s+1,t);
2.或者取t，则给对手留下区间(s,t-1)，对手的收益将是gain(s,t-1);
无论如何，自身得分是sum(s,t)-对手得分，从而：
gain(s,t)=sum(s,t)-min{gain(s+1,t),gain(s,t-1)}. */

int main()
{
    ifstream fin("game1.in");
    ofstream fout("game1.out");
    int score[101][101];
    int sum[101];
    memset(score, 0, sizeof(score));
    memset(sum, 0, sizeof(sum));
    int n;
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        fin >> score[i][i];
        sum[i] = sum[i - 1] + score[i][i];
    }
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= n - i + 1; ++j)
            score[j][j + i - 1] = sum[j + i - 1] - sum[j - 1] - min(score[j + 1][j + i - 1], score[j][j + i - 2]);
    fout << score[1][n] << ' ' << sum[n] - score[1][n] << endl;
    return 0;
}
