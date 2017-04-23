/*
ID: mazhaoj1
PROG: fence3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //http://www.byvoid.com/blog/usaco-522-electric-fences/

int n, maxx, maxy, step = 30, xx, yy;
double ans = 2147483647, x, y, dis;
struct lines
{
    int x1, y1, x2, y2;
}fence[150];

double length(int x1, int y1, int x2, int y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void add(int i, int j)
{
    dis = 0;
    for(int k = 0; k < n; ++k)
    {
        if(fence[k].x1 == fence[k].x2)
        {
            if(j >= fence[k].y1 && j <= fence[k].y2)
                dis += abs(fence[k].x1 - i);
            else if(j < fence[k].y1)
                dis += length(fence[k].x1, fence[k].y1, i, j);
            else if(j > fence[k].y2)
                dis += length(fence[k].x2, fence[k].y2, i, j);
        }
        else
        {
            if(i >= fence[k].x1 && i <= fence[k].x2)
                dis += abs(fence[k].y1 - j);
            else if(i < fence[k].x1)
                dis += length(fence[k].x1, fence[k].y1, i, j);
            else if(i > fence[k].x2)
                dis += length(fence[k].x2, fence[k].y2, i, j);
        }
    }
    if(ans > dis)
    {
        ans = dis;
        x = i;
        y = j;
    }
}

int main()
{
    ifstream fin("fence3.in");
    ofstream fout("fence3.out");
    fout.setf(ios::fixed);
    fout.precision(1);
    fin >> n;
    int temp;
    for(int i = 0; i < n; ++i)
    {
        fin >> fence[i].x1 >> fence[i].y1 >> fence[i].x2 >> fence[i].y2;
        fence[i].x1 *= 10;
        fence[i].y1 *= 10;
        fence[i].x2 *= 10;
        fence[i].y2 *= 10;
        if(fence[i].x1 > fence[i].x2)
        {
            temp = fence[i].x1;
            fence[i].x1 = fence[i].x2;
            fence[i].x2 = temp;
        }
        else if(fence[i].y1 > fence[i].y2)
        {
            temp = fence[i].y1;
            fence[i].y1 = fence[i].y2;
            fence[i].y2 = temp;
        }
        if(maxx < fence[i].x1)
            maxx = fence[i].x1;
        if(maxx < fence[i].x2)
            maxx = fence[i].x2;
        if(maxy < fence[i].y1)
            maxy = fence[i].y1;
        if(maxy == fence[i].y2)
            maxy = fence[i].y2;
    }
    for(int i = 0; i <= maxx; i += step)
        for(int j = 0; j <= maxy; j += step)
            add(i, j);
    xx = (int)x;
    yy = (int)y;
    for(int i = xx - step; i <= xx + step; ++i)
        for(int j = yy - step; j <= yy + step; ++j)
            add(i, j);
    ans /= 10;
    x /= 10;
    y /= 10;
    fout << x << ' ' << y << ' ' << ans << endl;
    return 0;
}
