/*
ID: mazhaoj1
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;    //the problem is very, very difficult.....

struct rect
{
    int llx, lly, urx, ury, color;
}rec[1001];

int a, b, n, sum[2500];

void judge(rect down, int pos)
{
    int i;
    for(i = pos + 1; i <= n; ++i)
    {
        rect up = rec[i];
        if(!(down.llx > up.urx || down.urx < up.llx || down.lly > up.ury || down.ury < up.lly))    //if ! (not intersect), break
            break;
    }
    if(i == n + 1)
    {
        sum[down.color] += (down.urx - down.llx + 1) * (down.ury - down.lly + 1);
        return;
    }
    rect up = rec[i];
    if(down.llx >= up.llx && down.lly >= up.lly && down.urx <= up.urx && down.ury <= up.ury)    //up fully covered down
        return;

    /*judge intersect, inner is up, outside is down
        +--------+      +-+--+--+
        |        |      | |2 |  |
        |        |      + +--+  |
        |  +-+   |  --> | |  |  |
        |  +-+   |      |1|  |3 |
        |        |      | +--+  |
        |        |      | | 4|  |
        +--------+      +-+--+--+
    */
    rect temp;
    if(up.llx >= down.llx)    // 1
    {
        temp = down;
        temp.urx = up.llx - 1;
        down.llx = up.llx;
        if(temp.llx <= temp.urx)
            judge(temp, i);
    }
    if(up.urx <= down.urx)    // 3
    {
        temp = down;
        temp.llx = up.urx + 1;
        down.urx = up.urx;
        if(temp.llx <= temp.urx)
            judge(temp, i);
    }
    if(up.lly >= down.lly)    // 4
    {
        temp = down;
        temp.ury = up.lly - 1;
        if(temp.lly <= temp.ury)
            judge(temp, i);
    }
    if(up.ury <= down.ury)    // 2
    {
        temp = down;
        temp.lly = up.ury + 1;
        if(temp.lly <= temp.ury)
            judge(temp, i);
    }
}

int main()
{
    ifstream fin("rect1.in");
    ofstream fout("rect1.out");
    int maxcolor = 1;
    fin >> a >> b >> n;
    rec[0].llx = rec[0].lly = 0;
    rec[0].urx = a - 1;
    rec[0].ury = b - 1;
    rec[0].color = 1;
    for(int i = 1; i <= n; ++i)
    {
        fin >> rec[i].llx >> rec[i].lly >> rec[i].urx >> rec[i].ury >> rec[i].color;
        rec[i].urx--;
        rec[i].ury--;
        if(maxcolor < rec[i].color)
            maxcolor = rec[i].color;
    }
    sum[rec[n].color] = (rec[n].urx - rec[n].llx + 1) * (rec[n].ury - rec[n].lly + 1);
    for(int i = n - 1; i >= 0; --i)
        judge(rec[i], i);
    for(int i = 1; i <= maxcolor; ++i)
        if(sum[i] != 0)
            fout << i << ' ' << sum[i] << endl;
    return 0;
}
