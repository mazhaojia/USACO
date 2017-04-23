/*
ID: mazhaoj1
PROG: ditch
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

#define MAXV 200
#define MAXE 200

int n, m, s, e, c;  //n: edge num, m: vertex num, here max edge num = 200, max vertex num = 200.
int infinity = 2147483647;
int prev[MAXV];
struct adjlist
{
    int vertex, value;
    adjlist* next;
    adjlist():next(NULL){}
}adj[MAXV], adjreverse[MAXV], *p, *q;

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


int main()
{
    ifstream fin("ditch.in");
    ofstream fout("ditch.out");
    bool added;
    fin >> n >> m;
    for(int i = 0; i < n; ++i)
    {
        fin >> s >> e >> c;
        s--;
        e--;
        if(c > 0)   //c must bigger than zero.  NOTICE: 插入的弧的值必须大于0
        {
            added = false;
            p = &adj[s];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == e)
                {
                    p->value += c;  //处理一个点有多条出边
                    added = true;
                    break;
                }
            }
            if(!added)
            {
                p->next = new adjlist();
                p = p->next;
                p->vertex = e;
                p->value = c;
            }

            //构造逆图
            added = false;
            p = &adjreverse[e];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == s)
                {
                    p->value += c;  //处理一个点有多条出边
                    added = true;
                    break;
                }
            }
            if(!added)
            {
                p->next = new adjlist();
                p = p->next;
                p->vertex = s;
                p->value = c;
            }
        }
    }
    fout << ISAP(0, m - 1) << endl;
    return 0;
}
