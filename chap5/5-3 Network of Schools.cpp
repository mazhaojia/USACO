/*
ID: mazhaoj1
PROG: schlnet
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
[转]这是一道收缩强连通分量的题。
该题描述的是一个有向图。我们都知道，在一个有向图强连通分量中从任意一个顶点开始，可以到达强连通分量的每个顶点。由此可以把该题中所有强连通分量收缩成分别一个顶点，则入度为0的顶点就是最少要接受新软件副本的学校。
第二问就是，问至少添加多少条边，才能使原图强连通。也就问在收缩后的图至少添加多少条边，才能使之强连通。
可以知道，当存在一个顶点入度为0或者出度为0的时候，该图一定不是强连通的。为了使添加的边最少，则应该把入度为0顶点和出度为0的顶点每个顶点添加1条边，使图中不存在入度为0顶点和出度为0的顶点。
当入度为0的顶点多于出度为0的顶点，则应添加的边数应为入度为0的顶点的个数。当出度为0的顶点多于出入度为0的顶点，则应添加的边数应为出度为0的顶点的个数。
这样就可以解决问题了。但是不要忘了还有特殊的情况，当原图本身就是强连通分量时，收缩成一个顶点，该顶点入度和出度都为0，但第一问应为1，第二问应为0。
把找到的每个强连通分量收缩为一个顶点，组成新图。设r(x)为x所在的强连同分量的代表节点，如果原图中存在边e(x,y)，且x,y不属于同一强连通分量，那么新图中有边e(r(x),r(y)) 。然后根据点的邻接关系直接统计出度和入度即可。
*/

/*SOLVE1: floyd求强连通分量, floyd只能用邻接矩阵
int num;    //顶点数
int component[100], compcnt;    //顶点i对应的第几个强连通分量
bool school[100][100], school2[100][100];
int indegree[100], outdegree[100], indegree0, outdegree0;

int main()
{
    ifstream fin("schlnet.in");
    ofstream fout("schlnet.out");
    int n;
    fin >> num;
    for(int i = 0; i < num; ++i)
        while(fin >> n && n != 0)
            school[i][n - 1] = school2[i][n - 1] = true;
    for(int k = 0; k < num; ++k)
        for(int i = 0; i < num; ++i)
            for(int j = 0; j < num; ++j)
                school2[i][j] = school2[i][j] || (school2[i][k] && school2[k][j]);  //use || in case i == k or k == j
    for(int i = 0; i < num; ++i)
        component[i] = -1;
    for(int i = 0; i < num; ++i)
    {
        if(component[i] != -1)
            continue;
        component[i] = compcnt;
        for(int j = i + 1; j < num; ++j)
            if(school2[i][j] && school2[j][i])
                component[j] = component[i];
        compcnt++;
    }
    for(int i = 0; i < num; ++i)
    {
        for(int j = 0; j < num; ++j)
        {
            if(school[i][j] && component[i] != component[j])
            {
                outdegree[component[i]]++;
                indegree[component[j]]++;
            }
        }
    }
    for(int i = 0; i < compcnt; ++i)
    {
        if(indegree[i] == 0)
            indegree0++;
        if(outdegree[i] == 0)
            outdegree0++;
    }
    fout << indegree0 << endl;
    if(compcnt == 1)
        fout << '0' << endl;
    else
        fout << max(indegree0, outdegree0) << endl;
    return 0;
}
*/

// SOLVE2: 邻接表 + 高级算法求强连通分量
// MAXV 最大顶点数
#define MAXV 100
int component[MAXV], compcnt;    //顶点i对应的第几个强连通分量
int indegree[MAXV], outdegree[MAXV], indegree0, outdegree0;
bool visited[MAXV];
bool school[MAXV][MAXV];    //邻接矩阵，优化本题的查找
int num;    //顶点数
struct adjlist
{
    int vertex;
    adjlist* next;
    adjlist():next(NULL){}
}adj[MAXV], *p;

//algorithm 2, tarjan:
int top, idx, low[MAXV], dfn[MAXV], stack[MAXV];
bool instack[MAXV];

void tarjandfs(int node)
{
	int j;
	dfn[node] = low[node] = ++idx;
	instack[node] = true;
	stack[top++] = node;
	adjlist* p = adj[node].next;
	while(p != NULL)
	{
        j = p->vertex;
		if(dfn[j] == 0)
		{
			tarjandfs(j);
			if(low[j] < low[node])
				low[node] = low[j];
		}
		else if(instack[j] && dfn[j] < low[node])
			low[node] = dfn[j];
	    p = p->next;
	}
	if(dfn[node] == low[node])
	{
		while(j != node)
		{
			j = stack[top - 1];
			top--;
			instack[j] = false;
			component[j] = compcnt;
		}
		compcnt++;
	}
}

void tarjan()
{
    int i;
	top = compcnt = idx = 0;
	memset(dfn, 0, sizeof(dfn));
	for(i = 0; i < num; ++i)
		if(dfn[i] == 0)
			tarjandfs(i);
}

int main()
{
    ifstream fin("schlnet.in");
    ofstream fout("schlnet.out");
    int n;
    fin >> num;
    for(int i = 0; i < num; ++i)
    {
        while(fin >> n && n != 0)
        {
            n--;
            if(school[i][n] == false && i != n)   //去掉重复输入
            {
                school[i][n] = true;
                p = new adjlist();
                p->vertex = n;
                p->next = adj[i].next;
                adj[i].next = p;
            }
        }
    }
    tarjan();
    for(int i = 0; i < num; ++i)
    {
        for(int j = 0; j < num; ++j)
        {
            if(school[i][j] && component[i] != component[j])
            {
                outdegree[component[i]]++;
                indegree[component[j]]++;
            }
        }
    }
    for(int i = 0; i < compcnt; ++i)
    {
        if(indegree[i] == 0)
            indegree0++;
        if(outdegree[i] == 0)
            outdegree0++;
    }
    fout << indegree0 << endl;
    if(compcnt == 1)
        fout << '0' << endl;
    else
        fout << max(indegree0, outdegree0) << endl;
    return 0;
}
