/*
ID: mazhaoj1
PROG: window
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //记录各个window在z轴的先后顺序，然后用chap 3 Shaping Regions 类似的方法做

struct window
{
    int id;
    int llx, lly, urx, ury, size;
}zorder[62], tempw;
int top, ididx[62], id, sum;
char op, chid;
ofstream fout("window.out");

void calc(char op, char id)
{
    switch(op)
    {
        case 'w':
            break;
        case 't':
            break;
        case 'b':
            break;
        case 'd':
            break;
        case 's':
            break;
    }
}

void judge(window down, int pos)  //改自chap 3，Shaping Regions
{
    int i;
    for(i = pos + 1; i < top; ++i)
    {
        window up = zorder[i];
        if(!(down.llx >= up.urx || down.urx <= up.llx || down.lly >= up.ury || down.ury <= up.lly))    //if ! (not intersect), break
            break;
    }
    if(i == top)
    {
        sum += (down.urx - down.llx) * (down.ury - down.lly);
        return;
    }
    window up = zorder[i];
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
    window temp;
    if(up.llx >= down.llx)    // 1
    {
        temp = down;
        temp.urx = up.llx;
        down.llx = up.llx;
        if(temp.llx < temp.urx)
            judge(temp, i);
    }
    if(up.urx <= down.urx)    // 3
    {
        temp = down;
        temp.llx = up.urx;
        down.urx = up.urx;
        if(temp.llx < temp.urx)
            judge(temp, i);
    }
    if(up.lly >= down.lly)    // 4
    {
        temp = down;
        temp.ury = up.lly;
        if(temp.lly < temp.ury)
            judge(temp, i);
    }
    if(up.ury <= down.ury)    // 2
    {
        temp = down;
        temp.lly = up.ury;
        if(temp.lly < temp.ury)
            judge(temp, i);
    }
}

void parsecmd(char* str)
{
    int i, j, para1, para2, para3, para4;
    char temp[6];
    op = str[0];
    chid = str[2];
    if(chid >= 'a' && chid <= 'z')
        id = chid - 'a';
    else if(chid >= 'A' && chid <= 'Z')
        id = chid - 'A' + 26;
    else
        id = chid - '0' + 52;
    if(op == 'w' && ididx[id] == -1)
    {
        i = 4;
        memset(temp, 0, sizeof(temp));
        for(j = i; str[j] != ','; ++j)
            temp[j - i] += str[j];
        para1 = atoi(temp);
        i = j + 1;
        memset(temp, 0, sizeof(temp));
        for(j = i; str[j] != ','; ++j)
            temp[j - i] += str[j];
        para2 = atoi(temp);
        i = j + 1;
        memset(temp, 0, sizeof(temp));
        for(j = i; str[j] != ','; ++j)
            temp[j - i] += str[j];
        para3 = atoi(temp);
        i = j + 1;
        memset(temp, 0, sizeof(temp));
        for(j = i; str[j] != ')'; ++j)
            temp[j - i] += str[j];
        para4 = atoi(temp);
        if(para1 < para3)
        {
            zorder[top].llx = para1;
            zorder[top].urx = para3;
        }
        else
        {
            zorder[top].llx = para3;
            zorder[top].urx = para1;
        }
        if(para2 < para4)
        {
            zorder[top].lly = para2;
            zorder[top].ury = para4;
        }
        else
        {
            zorder[top].lly = para4;
            zorder[top].ury = para2;
        }
        zorder[top].id = id;
        zorder[top].size = (zorder[top].urx - zorder[top].llx) * (zorder[top].ury - zorder[top].lly);
        ididx[id] = top;
        top++;
    }
    else if(op == 't')
    {
        tempw = zorder[ididx[id]];
        for(i = ididx[id] + 1; i < top; ++i)
        {
            zorder[i - 1] = zorder[i];
            ididx[zorder[i].id]--;
        }
        zorder[top - 1] = tempw;
        ididx[tempw.id] = top - 1;
    }
    else if(op == 'b')
    {
        tempw = zorder[ididx[id]];
        for(i = ididx[id] - 1; i >= 0; --i)
        {
            zorder[i + 1] = zorder[i];
            ididx[zorder[i].id]++;
        }
        zorder[0] = tempw;
        ididx[tempw.id] = 0;
    }
    else if(op == 'd')
    {
        tempw = zorder[ididx[id]];
        for(i = ididx[id] + 1; i < top; ++i)
        {
            zorder[i - 1] = zorder[i];
            ididx[zorder[i].id]--;
        }
        ididx[tempw.id] = -1;
        top--;
    }
    else    //'s'
    {
        sum = 0;
        judge(zorder[ididx[id]], ididx[id]);
        fout << (double)sum / zorder[ididx[id]].size * 100 << endl;
    }
}

int main()
{
    ifstream fin("window.in");
    fout.setf(ios::fixed);
    fout.precision(3);
    char str[30];
    for(int i = 0; i < 62; ++i)
        ididx[i] = -1;
    while(fin.getline(str, 30) && str[0] != '\0')
        parsecmd(str);
    return 0;
}
