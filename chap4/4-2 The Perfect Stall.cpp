/*
ID: mazhaoj1
PROG: stall4
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

#define MAXV 402

int infinity = 2147483647, m;
int prev[MAXV];
struct adjlist
{
    int vertex, value;
    adjlist* next;
    adjlist():value(1),next(NULL){}
}adj[MAXV], *p, *q;

//speed rank 3:
int MCPA(int source, int sink)  //Maximum Capacity Path Algorithm
{
    bool visited[MAXV];
    int flow[MAXV];  //come in max flow
    int maxflow, maxloc = -1, minvalue;
    pair<int, int> pa;
    priority_queue<pair<int, int> > qu;
    for(int i = 0; i <= m; ++i)
    {
        visited[i] = false;
        flow[i] = 0;
        prev[i] = -1;
    }
    flow[source] = infinity;
    qu.push(make_pair(flow[source], source));
    while(!qu.empty())
    {
        pa = qu.top();
        qu.pop();
        maxloc = pa.second;
        if(visited[maxloc])
            continue;
        maxflow = pa.first;
        if(maxloc == sink)
            break;
        visited[maxloc] = true;
        p = adj[maxloc].next;
        while(p != NULL)
        {
            minvalue = min(maxflow, p->value);
            if(flow[p->vertex] < minvalue)
            {
                flow[p->vertex] = minvalue;
                prev[p->vertex] = maxloc;
                qu.push(make_pair(minvalue, p->vertex));
            }
            p = p->next;
        }
    }
    return flow[sink];
}

int ford_fulkerson(int source, int sink)    //speed rank 3,4 algorithm entry
{
    int totalflow = 0, pathcapacity, curnode, prenode;
    bool added;
    if(source == sink)
        return infinity;
    while(true)
    {
        pathcapacity = MCPA(source, sink);
        if(pathcapacity == 0)
            break;
        totalflow += pathcapacity;
        curnode = sink;
        while(curnode != source)
        {
            prenode = prev[curnode];
            p = adj[prenode].next;
            q = &adj[prenode];
            while(p != NULL)
            {
                if(p->vertex == curnode)
                {
                    p->value -= pathcapacity;
                    if(p->value == 0)
                        q->next = p->next;
                    break;
                }
                else
                {
                    p = p->next;
                    q = q->next;
                }
            }
            added = false;
            p = &adj[curnode];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == prenode)
                {
                    p->value += pathcapacity;
                    added = true;
                    break;
                }
            }
            if(!added)
            {
                p->next = new adjlist();
                p = p->next;
                p->vertex = prenode;
                p->value = pathcapacity;
            }
            curnode = prenode;
        }
    }
    return totalflow;
}

int main()
{
    ifstream fin("stall4.in");
    ofstream fout("stall4.out");
    int n, s, c;
    fin >> n >> m;
    m += n + 1;
    for(int i = 1; i <= n; ++i)
    {
        fin >> s;
        p = new adjlist();
        p->vertex = i;
        p->next = adj[0].next;
        adj[0].next = p;
        for(int j = 0; j < s; ++j)
        {
            fin >> c;
            p = new adjlist();
            p->vertex = c + n;
            p->next = adj[i].next;
            adj[i].next = p;
        }
    }
    for(int i = n + 1; i < m; ++i)
    {
        p = new adjlist();
        p->vertex = m;
        adj[i].next = p;
    }
    fout << ford_fulkerson(0, m) << endl;
    return 0;
}
