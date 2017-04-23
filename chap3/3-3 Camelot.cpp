/*
ID: mazhaoj1
PROG: camelot
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;	//i can't solve it by myself, so i have to study others' solutions first.....

int row, col, path[30][26][30][26], cnt, front, end;
bool visited[30][26];
struct knights
{
    int row, col;
}knight[30 * 26], king, p, q, qu[30 * 26];
int dir[8][2] = {{-1, -2}, {-2, -1}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {2, -1}, {1, -2}};

void bfsall()
{
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            memset(visited, false, sizeof(visited));
            front = end = 0;
            path[i][j][i][j] = 0;
            p.row = i;
            p.col = j;
            qu[end++] = p;
            visited[p.row][p.col] = true;
            while(front != end)
            {
                p = qu[front];
                front++;
                for(int k = 0; k < 8; ++k)
                {
                    int newrow = dir[k][0] + p.row;
                    int newcol = dir[k][1] + p.col;
                    if(newrow >= 0 && newrow < row && newcol >= 0 && newcol < col && !visited[newrow][newcol])
                    {
                        q.row = newrow;
                        q.col = newcol;
                        qu[end++] = q;
                        path[i][j][newrow][newcol] = path[i][j][p.row][p.col] + 1;
                        visited[newrow][newcol] = true;
                    }
                }
            }
        }
    }
}

int kingtopos(int row, int col)
{
    return max(abs(king.row - row), abs(king.col - col));
}

int sum, sum2, ans = 99999999, catchlen, krow, kcol, kinglen, temp;
void solve()
{
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            sum = 0;
            int k;
            for(k = 0; k < cnt; ++k)
            {
                if(path[i][j][knight[k].row][knight[k].col] == -1)
                    break;
                else
                    sum += path[i][j][knight[k].row][knight[k].col];
            }
            if(k != cnt || sum >= ans)
                continue;
            kinglen= kingtopos(i, j);
            sum += kinglen;
            sum2 = sum;
            for(int m = -2; m <= 2; ++m)
            {
                for(int n = -2; n <= 2; ++n)
                {
                    krow = king.row + m;
                    kcol = king.col + n;
                    if(krow >= 0 && krow < row && kcol >= 0 && kcol < col)
                    {
                        for(int v = 0; v < cnt; ++v)
                        {
                            if(path[knight[v].row][knight[v].col][krow][kcol] != -1)
                            {
                                catchlen = path[knight[v].row][knight[v].col][krow][kcol] + kingtopos(krow, kcol) + path[krow][kcol][i][j];
                                if(sum2 > sum - path[knight[v].row][knight[v].col][i][j] - kinglen + catchlen)
                                    sum2 = sum - path[knight[v].row][knight[v].col][i][j] - kinglen + catchlen;
                            }
                        }
                    }
                }
            }
            if(sum2 < ans)
                ans = sum2;
        }
    }
}

int main()
{
    ifstream fin("camelot.in");
    ofstream fout("camelot.out");
    fin >> row >> col;
    char ccol;
    fin >> ccol >> king.row;
    king.row--;
    king.col = ccol - 'A' + 0;
    while(fin >> ccol)
    {
        fin >> knight[cnt].row;
        knight[cnt].row--;
        knight[cnt].col = ccol - 'A' + 0;
        cnt++;
    }
    for(int i = 0; i < row; ++i)
        for(int j = 0; j < col; ++j)
            for(int k = 0; k < row; ++k)
                for(int l = 0; l < col; ++l)
                    path[i][j][k][l] = -1;
    bfsall();
    solve();
    fout << ans << endl;
    return 0;
}
