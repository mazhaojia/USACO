/*
ID: mazhaoj1
PROG: fence6
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //���ȹ����ͼ���ϲ��ظ��Ķ��㣬Ȼ��dijkstra����С������������ȥ��һ�ߺ�����·�����ټ������ȥ���ıߵĳ��ȣ����ö��ȡ��Сֵ��

struct linkedlist
{
    linkedlist* next;
    int value;
    linkedlist():next(NULL){}
}*lp, *pp;

struct edges
{
    linkedlist* lnext;
    linkedlist* rnext;
    int length;
    edges():lnext(NULL), rnext(NULL){}
}edge[101];

int n, node[201], arr[201][201], dist[201], maxdis = 999999999, ans = 999999999, nowi;
bool visited[201];

void dijkstra(int pt, int target)
{
    memset(visited, false, sizeof(visited));
    for(int i = 1; i <= 2 * n; ++i)
        dist[i] = arr[pt][i];
    dist[pt] = 0;
    visited[pt] = true;
    for(int i = 1; i < 2 * n; ++i)
    {
        int mindis = 999999999, minpos = -1;
        for(int j = 1; j <= 2 * n; ++j)
        {
            if(visited[j] == false && mindis > dist[j])
            {
                mindis = dist[j];
                minpos = j;
            }
        }
        visited[minpos] = true;
        if(minpos == target)
        {
            if(ans > dist[minpos] + edge[nowi].length)
                ans = dist[minpos] + edge[nowi].length;
            return;
        }
        if(minpos == -1)    //this is very important in dijkstra algorithm
            return;
        for(int j = 1; j <= 2 * n; ++j)
            if(visited[j] == false && dist[j] > dist[minpos] + arr[minpos][j])
                dist[j] = dist[minpos] + arr[minpos][j];
    }
}

int main()
{
    ifstream fin("fence6.in");
    ofstream fout("fence6.out");
    fin >> n;
    int num, length, llink, rlink, link;
    bool find;
    for(int i = 1; i <= n; ++i)
    {
        fin >> num >> length >> llink >> rlink;
        edge[num].length = length;

        fin >> link;
        lp = new linkedlist();
        lp->value = link;
        edge[num].lnext = lp;
        lp = edge[num].lnext;
        for(int j = 1; j < llink; ++j)
        {
            fin >> link;
            lp->next = new linkedlist();
            lp = lp->next;
            lp->value = link;
        }

        fin >> link;
        lp = new linkedlist();
        lp->value = link;
        edge[num].rnext = lp;
        lp = edge[num].rnext;
        for(int j = 1; j < rlink; ++j)
        {
            fin >> link;
            lp->next = new linkedlist();
            lp = lp->next;
            lp->value = link;
        }
    }

    for(int i = 1; i <= n * 2; ++i)     //ÿ����2�����㣬��һ����2����Ϊ1��2���ڶ�����Ϊ3��4��������
        node[i] = i;

    for(int i = 1; i <= n; ++i)
    {
        lp = edge[i].lnext;
        while(lp != NULL)
        {
            num = lp->value;
            if(num > i)
            {
                find = false;
                pp = edge[num].lnext;
                while(pp != NULL)
                {
                    if(pp->value == i)
                    {
                        find = true;
                        break;
                    }
                    pp = pp->next;
                }
                if(find == true)
                    node[num * 2 - 1] = node[i * 2 - 1];   //���¶��㣬����ڶ����ߵ�һ������ʵ�����һ���ߵ�һ�������غϣ���node[3]=1
                else
                    node[num * 2] = node[i * 2 - 1];
            }
            lp = lp->next;
        }

        lp = edge[i].rnext;
        while(lp != NULL)
        {
            num = lp->value;
            if(num > i)
            {
                find = false;
                pp = edge[num].lnext;
                while(pp != NULL)
                {
                    if(pp->value == i)
                    {
                        find = true;
                        break;
                    }
                    pp = pp->next;
                }
                if(find == true)
                    node[num * 2 - 1] = node[i * 2];   //���¶��㣬����ڶ����ߵ�һ������ʵ�����һ���ߵڶ��������غϣ���node[3]=2
                else
                    node[num * 2] = node[i * 2];
            }
            lp = lp->next;
        }
    }

    for(int i = 1; i <= n * 2; ++i)
        for(int j = 1; j <= n * 2; ++j)
            if(i != j)
                arr[i][j] = maxdis;

    for(int i = 1; i <= n; ++i)
    {
        arr[node[i * 2 - 1]][node[i * 2]] = edge[i].length;
        arr[node[i * 2]][node[i * 2 - 1]] = edge[i].length;
    }

    for(int i = 1; i <= n; ++i)
    {
        arr[node[i * 2 - 1]][node[i * 2]] = maxdis;
        arr[node[i * 2]][node[i * 2 - 1]] = maxdis;
        nowi = i;
        dijkstra(node[i * 2 - 1], node[i * 2]);
        arr[node[i * 2 - 1]][node[i * 2]] = edge[i].length;
        arr[node[i * 2]][node[i * 2 - 1]] = edge[i].length;
    }

    fout << ans << endl;
    return 0;
}
