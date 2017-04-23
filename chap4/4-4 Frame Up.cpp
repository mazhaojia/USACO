/*
ID: mazhaoj1
PROG: frameup
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
首先计算出所有框的最下脚点和右上角点左标，这样就可以知道框的四个边框的范围。
如果框的内部被覆盖，那么摆放顺序先后都没关系，而题意是有确定解的。
所以只需考虑框的四边有没有被覆盖就可以了，这样得出一个图。
然后拓扑排序，但是要求出所有的拓扑排序，所以利用dfs求出所有结果。注意求出的解是逆序，最后所有解还要再排序。
如果不是覆盖的到被覆盖的做一条边，而是反过来作图，
那么只要保证图的邻接表顶点的链表是按顺序的，应该得到一个解就可以直接输出了。
*/

int h, w, cnt, ans[26], ancnt;
char frame[30][30], an[6000][27];   //最大数据的结果是5900左右
bool cover[26][26], showed[26];
struct rectangle
{
    int llr, llc, urr, urc;
    rectangle()
    {
        llr = -1;
        llc = 30;
        urr = 30;
        urc = -1;
    }
}rec[26];
struct adjlist
{
    int vertex;
    adjlist* next;
    adjlist():next(NULL){}
}adj[26], *p, *q;
ofstream fout("frameup.out");

void dfstopsort(int level)
{
    if(level == cnt)
    {
        for(int i = cnt - 1, j = 0; i >= 0; --i, ++j)
            an[ancnt][j] = ans[i] + 'A';
        ancnt++;
        return;
    }
    for(int i = 0; i < 26; ++i)
    {
        if(adj[i].vertex == 0 && showed[i])   // && showed[i] is important
        {
            adjlist* q = adj[i].next;
            while(q != NULL)
            {
                adj[q->vertex].vertex--;
                q = q->next;
            }
            adj[i].vertex = 32767;	//不让该i在下次dfs时再次被dfs到
            ans[level] = i;
            dfstopsort(level + 1);
            adj[i].vertex = 0;
            q = adj[i].next;
            while(q != NULL)
            {
                adj[q->vertex].vertex++;
                q = q->next;
            }
        }
    }
}

void setadj(int row, int col, int i)
{
    int t = frame[row][col] - 'A';
    if(frame[row][col] == '.' || t == i)
        return;
    if(cover[t][i] == false)
    {
        cover[t][i] = true;
        p = new adjlist();
        p->vertex = i;
        q = &adj[t];
        while(q->next != NULL && q->next->vertex < i)	//这样输出可以不必排序
            q = q->next;
        p->next = q->next;
        q->next = p;
        adj[i].vertex++;
    }
}

int cmp(const void* aa, const void* bb)
{
    char* a = (char*)aa;
    char* b = (char*)bb;
    return strcmp(a, b);
}

int main()
{
    ifstream fin("frameup.in");
    fin >> h >> w;
    char ch;
    int t;
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            fin >> ch;
            frame[i][j] = ch;
            if(ch == '.')
                continue;
            t = ch - 'A';
            showed[t] = true;
            if(rec[t].llr < i)	//计算所有矩形的范围
                rec[t].llr = i;
            if(rec[t].urr > i)
                rec[t].urr = i;
            if(rec[t].llc > j)
                rec[t].llc = j;
            if(rec[t].urc < j)
                rec[t].urc = j;
        }
    }
    for(int i = 0; i < 26; ++i)
        if(rec[i].llr != -1)
            cnt++;
    for(int i = 0; i < 26; ++i)
    {
        if(rec[i].llr == -1)
            continue;
        for(int j = rec[i].llc; j <= rec[i].urc; ++j)
        {
            setadj(rec[i].urr, j, i);   //检查第一行有没有被覆盖
            setadj(rec[i].llr, j, i);   //最后一行
        }
        for(int j = rec[i].urr; j <= rec[i].llr; ++j)
        {
            setadj(j, rec[i].llc, i);    //第一列
            setadj(j, rec[i].urc, i);    //最后一列
        }
    }
    dfstopsort(0);
    qsort(an, ancnt, sizeof(an[0]), cmp);
    for(int i = 0; i < ancnt; ++i)
        fout << an[i] << endl;
    return 0;
}
