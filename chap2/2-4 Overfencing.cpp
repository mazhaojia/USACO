/*
ID: mazhaoj1
PROG: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int w, h, front, end;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
char maze[100 * 2 + 1][38 * 2 + 1];
int shorta[100 * 2 + 1][38 * 2 + 1], shortb[100 * 2 + 1][38 * 2 + 1];
bool visited[100 * 2 + 1][38 * 2 + 1];
struct point
{
    int row, col, shorta, shortb;
}exitpos[2], p, pp, queue[(100 * 2 + 1) * (38 * 2 + 1)];

int main()
{
    ifstream fin("maze1.in");
    ofstream fout("maze1.out");
    fin >> w >> h;
    fin.unsetf(ios::skipws);
    h = h * 2 + 1;
    w = w * 2 + 1;
    int exitcnt = 0;
    int i, j;
    for(i = 0; i < h; ++i)
    {
        fin.get();
        for(j = 0; j < w; ++j)
        {
            fin >> maze[i][j];
            if(maze[i][j] == '+' || maze[i][j] == '-' || maze[i][j] == '|')
                shorta[i][j] = shortb[i][j] = -1;
            else if(i == 0 || i == h - 1 || j == 0 || j == w - 1)
            {
                exitpos[exitcnt].row = i;
                exitpos[exitcnt].col = j;
                exitcnt++;
            }
        }
    }
    p = exitpos[0];
    visited[p.row][p.col] = true;
    int newrow, newcol;
    for(i = 0; i < 4; ++i)
    {
        pp = p;
        newrow = pp.row + dir[i][0];
        newcol = pp.col + dir[i][1];
        if(newrow >= 0 && newrow < h && newcol >= 0 && newcol < w && maze[newrow][newcol] == ' ')
        {
            pp.row = newrow;
            pp.col = newcol;
            pp.shorta++;
            shorta[pp.row][pp.col] = pp.shorta;
            visited[pp.row][pp.col] = true;
            queue[end++] = pp;
        }
    }
    while(front != end)
    {
        p = queue[front];
        front++;
        for(i = 0; i < 4; ++i)
        {
            pp = p;
            newrow = pp.row + dir[i][0];
            newcol = pp.col + dir[i][1];
            if(newrow >= 0 && newrow < h && newcol >= 0 && newcol < w && visited[newrow][newcol] == false && maze[newrow][newcol] == ' ')
            {
                pp.row = newrow;
                pp.col = newcol;
                pp.shorta++;
                shorta[pp.row][pp.col] = pp.shorta;
                visited[pp.row][pp.col] = true;
                queue[end++] = pp;
            }
        }
    }
    memset(visited, false, sizeof(visited));
    front = end = 0;
    p = exitpos[1];
    visited[p.row][p.col] = true;
    for(i = 0; i < 4; ++i)
    {
        pp = p;
        newrow = pp.row + dir[i][0];
        newcol = pp.col + dir[i][1];
        if(newrow >= 0 && newrow < h && newcol >= 0 && newcol < w && maze[newrow][newcol] == ' ')
        {
            pp.row = newrow;
            pp.col = newcol;
            pp.shortb++;
            shortb[pp.row][pp.col] = pp.shortb;
            visited[pp.row][pp.col] = true;
            queue[end++] = pp;
        }
    }
    while(front != end)
    {
        p = queue[front];
        front++;
        for(i = 0; i < 4; ++i)
        {
            pp = p;
            newrow = pp.row + dir[i][0];
            newcol = pp.col + dir[i][1];
            if(newrow >= 0 && newrow < h && newcol >= 0 && newcol < w && visited[newrow][newcol] == false && maze[newrow][newcol] == ' ')
            {
                pp.row = newrow;
                pp.col = newcol;
                pp.shortb++;
                shortb[pp.row][pp.col] = pp.shortb;
                visited[pp.row][pp.col] = true;
                queue[end++] = pp;
            }
        }
    }
    int ans = 0;
    for(i = 0; i < h; ++i)
    {
        for(j = 0; j < w; ++j)
        {
            if(shorta[i][j] != -1 && shortb[i][j] != -1 && shorta[i][j] != 0 && shortb[i][j] != 0)
            {
                int minimum = min(shorta[i][j], shortb[i][j]);
                if(ans < minimum)
                    ans = minimum;
            }
        }
    }
    fout << (ans + 1) / 2 << endl;
    return 0;
}
