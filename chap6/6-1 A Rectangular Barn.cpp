/*
ID: mazhaoj1
PROG: rectbarn
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
本题由于给出的是求矩形，就不能像big barn那样dp了。
请看：国家集训队2003论文集："<王知昆：浅谈用极大化思想解决最大子矩形问题>"
但这篇文章所指的障碍是点，这里的障碍确实一个1*1的矩形，所以只能取文章的思想，方法还需要变形。
方法是如何变形的请看nocow。
*/

#define maxn 3001
bool field[3001][3001];
int row, col, ans, temp;
int height[2][3001], leftt[2][3001], rightt[2][3001], stepl[3001], stepr[3002]; //注意这里的3002

int main()
{
    ifstream fin("rectbarn.in");
    ofstream fout("rectbarn.out");
    int r, c, p, now = 0, last = 1;
    fin >> row >> col >> p;
    if(p == 0)
    {
        fout << row * col << endl;
        return 0;
    }
    while(p--)
    {
        fin >> r >> c;
        field[r][c] = true;
    }
    for(int i = 1; i <= col; ++i)
        leftt[0][i] = rightt[0][i] = maxn;  //没有这个初始化，第二个点wa
    for(int i = 1; i <= row; ++i)
    {
        now ^= now;
        last ^= last;
        for(int j = 1; j <= col; ++j)
        {
            if(field[i][j])
                stepl[j] = 0;
            else
                stepl[j] = stepl[j - 1] + 1;
        }
        for(int j = col; j >= 1; --j)
        {
            if(field[i][j])
                stepr[j] = 0;
            else
                stepr[j] = stepr[j + 1] + 1;
        }
        for(int j = 1; j <= col; ++j)
        {
            if(field[i][j])
            {
                leftt[now][j] = rightt[now][j] = maxn;
                height[now][j] = 0;
            }
            else
            {
                leftt[now][j] = min(leftt[last][j], stepl[j]);
                rightt[now][j] = min(rightt[last][j], stepr[j]);
                height[now][j] = height[last][j] + 1;
                temp = height[now][j] * (leftt[now][j] + rightt[now][j] - 1);
                if(ans < temp)
                    ans = temp;
            }
        }
    }
    fout << ans << endl;
    return 0;
}
