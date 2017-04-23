/*
ID: mazhaoj1
PROG: milk6
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
首先看这个解题报告，http://www.cppblog.com/xiongnanbin/articles/91833.html
乘1001+1的做法太取巧了，且没找到证明，所以我没用。
无论用哪种方法，最后都要枚举来求满足题意的最小割的边，上面那个以及网上很多的一次for循环枚举的方法是错误的。
因为无法保证枚举到的解包含的边数最少，NOCOW的反例：
9 11
1 2 4
1 3 3
2 4 100
3 4 100
4 5 5
4 6 1
4 7 1
5 8 100
6 8 100
7 8 100
8 9 100
所以我这里对边先排序，然后先求出所有属于最小割的边，但是这些边可能属于不同的最小割，然后我再二重for枚举这些求出的边，
找到边数最少的一个组合即为所求的。
*/

#define MAXV 32
#define MAXE 1000

int n, m;  //n: edge num, m: vertex num, here max edge num = 200, max vertex num = 200.
int infinity = 2147483647;
int prev[MAXV];
int maxflow, nowflow, ans[MAXE], anscnt, mincnt = 2000, minans[MAXE], sum;
struct adjlist
{
    int vertex, value;
    adjlist* next;
    adjlist():next(NULL){}
}adj[MAXV], adjreverse[MAXV], *p, *q;
struct edges
{
    int seq, left, right, value;
}edge[MAXE];

//speed rank 1:
int depth[MAXV];    //距离标号
int num[MAXV + 1];      //距离标号为depth[i]的顶点数目

bool init_isap(int source, int sink)
{
    int qu[MAXV], front = 0, end = 0, now;
    for(int i = 0; i < m; ++i)
    {
        depth[i] = m;
        num[i] = 0;
    }
    depth[sink] = 0;
    num[depth[sink]]++;
    qu[end++] = sink;
    while(front != end)
    {
        now = qu[front++];
        p = adjreverse[now].next;
        while(p != NULL)
        {
            if(depth[p->vertex] >= m)
            {
                depth[p->vertex] = depth[now] + 1;
                num[depth[p->vertex]]++;
                qu[end++] = p->vertex;
            }
            p = p->next;
        }
    }
    if(depth[source] == m)
        return false;
    return true;
}

int ISAP(int source, int sink)  //Improved Shortest Augmenting Path
{
    int minvalue, ans = 0, curnode = source, prenode, mind, nextstartnode;
    bool added;
    if(!init_isap(source, sink))
        return 0;
    for(int i = 0; i < m; ++i)
        prev[i] = -1;
    while(depth[source] < m)
    {
        p = adj[curnode].next;
        q = &adj[curnode];
        while(p != NULL)
        {
            if(depth[p->vertex] + 1 == depth[curnode])    //不检查为0的边
            {
                prev[p->vertex] = curnode;
                q->next = p->next;                        //当前弧优化
                p->next = adj[curnode].next;
                adj[curnode].next = p;
                curnode = p->vertex;
                break;
            }
            else
            {
                p = p->next;
                q = q->next;
            }
        }
        if(p == NULL)
        {
            mind = infinity;
            p = &adj[curnode];
            while(p ->next != NULL)
            {
                if(depth[p->next->vertex] + 1 < mind)
                {
                    mind = depth[p->next->vertex] + 1;
                    q = p;
                }
                p = p->next;
            }
            if(mind == infinity)
                mind = m;
            num[mind]++;
            num[depth[curnode]]--;
            if(num[depth[curnode]] == 0)        //GAP优化
                return ans;
            depth[curnode] = mind;
            if(mind != m)
            {
                p = q->next;
                q->next = p->next;
                p->next = adj[curnode].next;        //当前弧优化
                adj[curnode].next = p;
            }
            if(curnode != source)
                curnode = prev[curnode];
        }
        if(curnode == sink)
        {
            minvalue = infinity;
            while(curnode != source)
            {
                prenode = prev[curnode];
                p = adj[prenode].next;            //有了当前弧优化，所以不必遍历
                if(minvalue > p->value)
                    minvalue = p->value;
                curnode = prenode;
            }
            curnode = sink;
            while(curnode != source)
            {
                prenode = prev[curnode];
                p = adj[prenode].next;
                p->value -= minvalue;        //有了当前弧优化，所以不必遍历
                if(p->value == 0)
                {
                    nextstartnode = prenode;
                    adj[prenode].next = p->next;        //删除0边，这样上面可以不检查
                }
                added = false;
                p = adj[curnode].next;
                while(p != NULL)
                {
                    if(p->vertex == prenode)
                    {
                        p->value += minvalue;            //此处不能进行当前弧优化，否则可能会wa，没尝试过，dinic反正会wa
                        added = true;
                        break;
                    }
                    p = p->next;
                }
                if(!added)
                {
                    p = new adjlist();
                    p->vertex = prenode;
                    p->value = minvalue;
                    p->next = adj[curnode].next;
                    adj[curnode].next = p;                //加到开头，加块下次访问命中的速度
                }
                curnode = prenode;
            }
            curnode = sink;
            while(curnode != nextstartnode && curnode != -1)        //退栈优化，不退到起始节点
                curnode = prev[curnode];
            ans += minvalue;
        }
    }
    return ans;
}

void setadj()
{
    memset(adj, 0, sizeof(adj));
    bool added;
    for(int i = 0; i < n; ++i)
    {
        if(edge[i].value > 0)   //为0的弧对于答案没有用，直接舍弃
        {
            added = false;
            p = &adj[edge[i].left];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == edge[i].right)
                {
                    p->value += edge[i].value;  //处理一个点有多条出边，这个很重要，不这么处理第5个数据运行要5秒，超时
                    added = true;
                    break;
                }
            }
            if(!added)
            {
                p->next = new adjlist();
                p = p->next;
                p->vertex = edge[i].right;
                p->value = edge[i].value;
            }

            //构造逆图
            added = false;
            p = &adjreverse[edge[i].right];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == edge[i].left)
                {
                    p->value += edge[i].value;  //处理一个点有多条出边
                    added = true;
                    break;
                }
            }
            if(!added)
            {
                p->next = new adjlist();
                p = p->next;
                p->vertex = edge[i].left;
                p->value = edge[i].value;
            }
        }
    }
}

int cmp(const void* aa, const void* bb)
{
    edges* a = (edges*)aa;
    edges* b = (edges*)bb;
    if(a->value == b->value)
        return a->seq - b->seq;
    return b->value - a->value;
}

int cmpp(const void* aa, const void* bb)
{
    int* a = (int*)aa;
    int* b = (int*)bb;
    return *a - *b;
}

void solve()
{
    for(int i = 0; i < n; ++i)
    {
        setadj();
        p = &adj[edge[i].left];     //枚举剪掉第i条边
        while(p->next != NULL)
        {
            if(p->next->vertex == edge[i].right)
            {
                p->next->value -= edge[i].value;
                if(p->next->value == 0)
                    p->next = p->next->next;
                break;
            }
            p = p->next;
        }
        p = &adjreverse[edge[i].right];
        while(p->next != NULL)
        {
            if(p->next->vertex == edge[i].left)
            {
                p->next->value -= edge[i].value;
                if(p->next->value == 0)
                    p->next = p->next->next;
                break;
            }
            p = p->next;
        }
        nowflow = ISAP(0, m - 1);
        if(maxflow - nowflow == edge[i].value)  //找到一条边属于最小割
            ans[anscnt++] = i;
    }
}

void calc()
{
    for(int i = 0; i < anscnt; ++i)
    {
        sum = 0;
        for(int j = i; j < anscnt; ++j)
        {
            sum += edge[ans[j]].value;
            if(sum > maxflow)
                break;
            if(sum == maxflow)
            {
                if(mincnt > j - i + 1)
                {
                    mincnt = j - i + 1;
                    memcpy(minans, ans + i, sizeof(int) * (j - i + 1));
                }
            }
        }
    }
}

int main()
{
    ifstream fin("milk6.in");
    ofstream fout("milk6.out");
    fin >> m >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> edge[i].left >> edge[i].right >> edge[i].value;
        edge[i].left--;
        edge[i].right--;
        edge[i].seq = i;
    }
    qsort(edge, n, sizeof(edge[0]), cmp);
    setadj();
    maxflow = ISAP(0, m - 1);
    fout << maxflow;
    solve();
    calc();
    if(mincnt == 2000)  //no answer
        mincnt = 0;
    fout << ' ' << mincnt << endl;
    for(int i = 0; i < mincnt; ++i)
        minans[i] = edge[minans[i]].seq + 1;
    qsort(minans, mincnt, sizeof(minans[0]), cmpp);
    for(int i = 0; i < mincnt; ++i)
        fout << minans[i] << endl;
    return 0;
}
