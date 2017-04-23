/*
ID: mazhaoj1
PROG: telecow
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
本题网上的解释都有遗漏，还是USACO的Analysis说的最全，需要注意i拆为i1和i2后i1和i2间连的是
bidirectional的边。需要注意源点不是s，而是s拆成2点后的第二个点，即出点s2。汇点是d拆成2点后的
第一个点，即是入点d1。
*/

#define MAXV 200
#define MAXE 2400

int n, m, s, e;  //n: edge num, m: vertex num
int infinity = 2147483647 / 20; //注意这里要拆点需要设max边，如果设为2147483647可能会溢出
int prev[MAXV];
int maxflow, nowflow, ans[100], anscnt;
bool cuted[MAXV];   //已经发现的最小割中的点
struct adjlist
{
    int vertex, value;
    adjlist* next;
    adjlist():next(NULL){}
}adj[MAXV], *p, *q;
struct edges
{
    int seq, left, right;
}edge[MAXE];

//speed rank 2:
int depth[MAXV];
bool dinic_bfs(int source, int sink)
{
    int front = 0, end = 0, qu[MAXV], now;
    for(int i = 0; i < m + m; ++i)  //注意本题拆点后这里再也不是m了
        depth[i] = -1;
    depth[source] = 0;
    qu[end++] = source;
    while(front != end)
    {
        now = qu[front++];
        p = adj[now].next;
        while(p != NULL)
        {
            if(depth[p->vertex] == -1)
            {
                depth[p->vertex] = depth[now] + 1;
                qu[end++] = p->vertex;
            }
            p = p->next;
        }
    }
    if(depth[sink] == -1)
        return false;
    return true;
}

int dinic_dfs(int source, int sink)
{
    int ans = 0, minvalue, curnode, prenode, nextstartnode;
    bool deleted[MAXV], added;
    for(int i = 0; i < m + m; ++i)  //注意本题拆点后这里再也不是m了
    {
        deleted[i] = false;
        prev[i] = -1;
    }
    curnode = source;
    while(curnode != -1)
    {
        p = adj[curnode].next;
        q = &adj[curnode];
        while(p != NULL)
        {
            if(depth[p->vertex] == depth[curnode] + 1 && !deleted[p->vertex])        //不检查为0的边
            {
                prev[p->vertex] = curnode;
                q->next = p->next;                        //当前弧优化，找prev的时候可以不必遍历
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
            deleted[curnode] = true;
            curnode = prev[curnode];
        }
        if(curnode == sink)
        {
            minvalue = infinity;
            while(curnode != source)
            {
                prenode = prev[curnode];
                p = adj[prenode].next;
                if(minvalue > p->value)        //有了当前弧优化，所以不必遍历
                    minvalue = p->value;
                curnode = prenode;
            }
            curnode = sink;
            while(curnode != source)
            {
                prenode = prev[curnode];
                p = adj[prenode].next;
                p->value -= minvalue;            //有了当前弧优化，所以不必遍历
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
                        p->value += minvalue;        //此处不能进行当前弧优化，否则会wa
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
            while(curnode != nextstartnode && curnode != -1)    //退栈优化，不退到起始节点
                curnode = prev[curnode];
            ans += minvalue;
        }
    }
    return ans;
}

int dinic(int source, int sink) //speed rank 2 algorithm entry
{
    int ans = 0, flow;
    while(dinic_bfs(source, sink))
    {
        flow = dinic_dfs(source, sink);
        if(flow == 0)
            break;
        ans += flow;
    }
    return ans;
}

void setadj()
{
    int left, right, maxvalue = infinity;
    memset(adj, 0, sizeof(adj));
    for(int i = 0; i < m; ++i)
    {
        p = new adjlist();
        p->value = 1;
        p->vertex = i + m;
        p->next = adj[i].next;
        adj[i].next = p;

        p = new adjlist();
        p->value = 1;
        p->vertex = i;
        p->next = adj[i + m].next;
        adj[i + m].next = p;
    }
    for(int i = 0; i < n; ++i)
    {
        left = edge[i].left;
        right = edge[i].right;

        p = new adjlist();
        p->value = maxvalue;
        p->vertex = right;
        p->next = adj[left + m].next;
        adj[left + m].next = p;

        p = new adjlist();
        p->value = maxvalue;
        p->vertex = left;
        p->next = adj[right + m].next;
        adj[right + m].next = p;
    }
}

int cmp(const void* aa, const void* bb)
{
    int* a = (int*)aa;
    int* b = (int*)bb;
    return *a - *b;
}

void cutnode(int i)
{
    p = &adj[i];
    while(p->next != NULL)
    {
        if(p->next->vertex == i + m)
        {
            p->next = p->next->next;
            break;
        }
        p = p->next;
    }
    p = &adj[i + m];
    while(p->next != NULL)
    {
        if(p->next->vertex == i)
        {
            p->next = p->next->next;
            break;
        }
        p = p->next;
    }
}

void solve()
{
    for(int i = 0; i < m; ++i)
    {
        if(i == s || i == e || cuted[i] == true)    //已经发现的点或者是2个端点
            continue;
        setadj();   //重设边
        for(int j = 0; j < anscnt; ++j) //剪掉已经发现的点
            cutnode(ans[j]);
        cutnode(i); //尝试剪掉一个点
        nowflow = dinic(s + m, e);
        if(maxflow - nowflow == 1)  //找到一个点属于最小割
        {
            ans[anscnt++] = i;
            cuted[i] = true;
            maxflow = nowflow;
            if(maxflow == 0)
                return;
        }
    }
}

int main()
{
    ifstream fin("telecow.in");
    ofstream fout("telecow.out");
    fin >> m >> n >> s >> e;
    s--;
    e--;
    for(int i = 0; i < n; ++i)
    {
        fin >> edge[i].left >> edge[i].right;
        edge[i].left--;
        edge[i].right--;
        edge[i].seq = i + 1;
    }
    setadj();
    maxflow = dinic(s + m, e);
    fout << maxflow << endl;
    solve();
    qsort(ans, anscnt, sizeof(ans[0]), cmp);
    for(int i = 0; i < anscnt - 1; ++i)
        fout << ans[i] + 1 << ' ';
    fout << ans[anscnt - 1] + 1 << endl;
    return 0;
}
