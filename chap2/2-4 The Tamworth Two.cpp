/*
ID: mazhaoj1
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

char maze[10][10];
bool visited[10][10][4][10][10][4];     //Ç°3Î¬farmer£¬ºó3Î¬cow

struct position
{
    int frow, fcol, fface;     //face: 0 north, 1 east, 2 south, 3 west
    int crow, ccol, cface;
    int times;
}p, pp, queue[30000];

int front, end, i;
int dir[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

int main()
{
    ifstream fin("ttwo.in");
    ofstream fout("ttwo.out");
    string in;
    for(i = 0; i < 10; ++i)
    {
        fin >> in;
        for(int j = 0; j < 10; ++j)
        {
            maze[i][j] = in[j];
            if(in[j] == 'F')
            {
                p.frow = i;
                p.fcol = j;
                p.fface = 0;
            }
            else if(in[j] == 'C')
            {
                p.crow = i;
                p.ccol = j;
                p.cface = 0;
            }
        }
    }
    p.times = 0;
    queue[end++] = p;
    while(front != end)
    {
        pp = queue[front++];
        if(visited[pp.frow][pp.fcol][pp.fface][pp.crow][pp.ccol][pp.cface] == true)
        {
            fout << '0' << endl;
            return 0;
        }
        else if(pp.frow == pp.crow && pp.fcol == pp.ccol)
        {
            fout << pp.times << endl;
            return 0;
        }
        visited[pp.frow][pp.fcol][pp.fface][pp.crow][pp.ccol][pp.cface] = true;
        for(i = 0; i < 4; ++i)
            if(pp.fface == i)
                break;
        int newrow = pp.frow + dir[i][0];
        int newcol = pp.fcol + dir[i][1];
        if(newrow >= 0 && newrow < 10 && newcol >= 0 && newcol < 10
            && maze[newrow][newcol] != '*')
        {
            pp.frow = newrow;
            pp.fcol = newcol;
        }
        else
            pp.fface = (pp.fface + 1) % 4;
        for(i = 0; i < 4; ++i)
            if(pp.cface == i)
                break;
        newrow = pp.crow + dir[i][0];
        newcol = pp.ccol + dir[i][1];
        if(newrow >= 0 && newrow < 10 && newcol >= 0 && newcol < 10
            && maze[newrow][newcol] != '*')
        {
            pp.crow = newrow;
            pp.ccol = newcol;
        }
        else
            pp.cface = (pp.cface + 1) % 4;
        ++pp.times;
        queue[end++] = pp;
    }
    fout << "fuck" << endl;
    return 0;
}
