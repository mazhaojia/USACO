/*
ID: mazhaoj1
PROG: wissqu
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //无优化爆搜。。。。dir里漏了最后一个值，检查了4小时。。。人累的时候编程很容易出错。。。

char board[4][4];
int ans, newrow, newcol, puted[5];
bool done[4][4];
int dir[9][2] = {{0, 0}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
ofstream fout("wissqu.out");
struct result
{
    char ch;
    int row, col;
}r[16];

void dfs(int level)
{
    int k;
    char temp, place;
    if(level == 16)
    {
        ans++;
        return;
    }
    for(int ch = 0; ch < 5; ++ch)
    {
        if(puted[ch] == 3)
            continue;
        place = (char)('A' + ch);
        for(int i = 0; i < 4; ++i)
        {
            for(int j = 0; j < 4; ++j)
            {
                if(done[i][j])
                    continue;
                for(k = 0; k < 9; ++k)
                {
                    newrow = i + dir[k][0];
                    newcol = j + dir[k][1];
                    if(newrow >= 0 && newrow < 4 && newcol >= 0 && newcol < 4)
                        if(board[newrow][newcol] == place)
                            break;
                }
                if(k == 9)
                {
                    temp = board[i][j];
                    board[i][j] = place;
                    done[i][j] = true;
                    puted[ch]++;
                    if(ans == 0)
                    {
                        r[level].ch = place;
                        r[level].row = i + 1;
                        r[level].col = j + 1;
                    }
                    dfs(level + 1);
                    puted[ch]--;
                    done[i][j] = false;
                    board[i][j] = temp;
                }
            }
        }
    }
}

int main()
{
    ifstream fin("wissqu.in");
    char str[5];
    for(int i = 0; i < 4; ++i)
    {
        fin.getline(str, 5);
        for(int j = 0; j < 4; ++j)
            board[i][j] = str[j];
    }
    int k;
    char temp;
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            for(k = 0; k < 9; ++k)
            {
                newrow = i + dir[k][0];
                newcol = j + dir[k][1];
                if(newrow >= 0 && newrow < 4 && newcol >= 0 && newcol < 4)
                    if(board[newrow][newcol] == 'D')
                        break;
            }
            if(k == 9)
            {
                temp = board[i][j];
                board[i][j] = 'D';
                done[i][j] = true;
                if(ans == 0)
                {
                    r[0].ch = 'D';
                    r[0].row = i + 1;
                    r[0].col = j + 1;
                }
                dfs(1);
                done[i][j] = false;
                board[i][j] = temp;
            }
        }
    }
    for(int i = 0; i < 16; ++i)
        fout << r[i].ch << ' ' << r[i].row << ' ' << r[i].col << endl;
    fout << ans << endl;
    return 0;
}
