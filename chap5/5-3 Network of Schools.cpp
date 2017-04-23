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
[ת]����һ������ǿ��ͨ�������⡣
������������һ������ͼ�����Ƕ�֪������һ������ͼǿ��ͨ�����д�����һ�����㿪ʼ�����Ե���ǿ��ͨ������ÿ�����㡣�ɴ˿��԰Ѹ���������ǿ��ͨ���������ɷֱ�һ�����㣬�����Ϊ0�Ķ����������Ҫ���������������ѧУ��
�ڶ��ʾ��ǣ���������Ӷ������ߣ�����ʹԭͼǿ��ͨ��Ҳ�������������ͼ������Ӷ������ߣ�����ʹ֮ǿ��ͨ��
����֪����������һ���������Ϊ0���߳���Ϊ0��ʱ�򣬸�ͼһ������ǿ��ͨ�ġ�Ϊ��ʹ��ӵı����٣���Ӧ�ð����Ϊ0����ͳ���Ϊ0�Ķ���ÿ���������1���ߣ�ʹͼ�в��������Ϊ0����ͳ���Ϊ0�Ķ��㡣
�����Ϊ0�Ķ�����ڳ���Ϊ0�Ķ��㣬��Ӧ��ӵı���ӦΪ���Ϊ0�Ķ���ĸ�����������Ϊ0�Ķ�����ڳ����Ϊ0�Ķ��㣬��Ӧ��ӵı���ӦΪ����Ϊ0�Ķ���ĸ�����
�����Ϳ��Խ�������ˡ����ǲ�Ҫ���˻���������������ԭͼ�������ǿ��ͨ����ʱ��������һ�����㣬�ö�����Ⱥͳ��ȶ�Ϊ0������һ��ӦΪ1���ڶ���ӦΪ0��
���ҵ���ÿ��ǿ��ͨ��������Ϊһ�����㣬�����ͼ����r(x)Ϊx���ڵ�ǿ��ͬ�����Ĵ���ڵ㣬���ԭͼ�д��ڱ�e(x,y)����x,y������ͬһǿ��ͨ��������ô��ͼ���б�e(r(x),r(y)) ��Ȼ����ݵ���ڽӹ�ϵֱ��ͳ�Ƴ��Ⱥ���ȼ��ɡ�
*/

/*SOLVE1: floyd��ǿ��ͨ����, floydֻ�����ڽӾ���
int num;    //������
int component[100], compcnt;    //����i��Ӧ�ĵڼ���ǿ��ͨ����
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

// SOLVE2: �ڽӱ� + �߼��㷨��ǿ��ͨ����
// MAXV ��󶥵���
#define MAXV 100
int component[MAXV], compcnt;    //����i��Ӧ�ĵڼ���ǿ��ͨ����
int indegree[MAXV], outdegree[MAXV], indegree0, outdegree0;
bool visited[MAXV];
bool school[MAXV][MAXV];    //�ڽӾ����Ż�����Ĳ���
int num;    //������
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
            if(school[i][n] == false && i != n)   //ȥ���ظ�����
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
