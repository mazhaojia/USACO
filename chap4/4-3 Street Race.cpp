/*
ID: mazhaoj1
PROG: race3
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

struct adjlist
{
    int vertex;
    adjlist* next;
    adjlist():next(NULL){}
}adj[50], *p;
int cnt, ans1[50], ans1cnt, ans2[50], ans2cnt;
bool visited[50], found;

void dfs(int s)
{
    if(s == cnt)
    {
        found = true;
        return;
    }
    adjlist* p = &adj[s];
    while(p->next != NULL)
    {
        p = p->next;
        if(visited[p->vertex] == false)
        {
            visited[p->vertex] = true;
            dfs(p->vertex);
        }
        if(found)
            return;
    }
}

void dfs2(int s, int num)
{
    if(s < num)
    {
        found = true;
        return;
    }
    adjlist* p = &adj[s];
    while(p->next != NULL)
    {
        p = p->next;
        if(visited[p->vertex] == false)
        {
            visited[p->vertex] = true;
            dfs2(p->vertex, num);
        }
        if(found)
            return;
    }
}

int main()
{
    ifstream fin("race3.in");
    ofstream fout("race3.out");
    int num;
    while(true)
    {
        fin >> num;
        if(num == -1)
            break;
        while(num != -2)
        {
            if(num != cnt)  //ignore self-loop
            {
                p = new adjlist();
                p->vertex = num;
                p->next = adj[cnt].next;
                adj[cnt].next = p;
            }
            fin >> num;
        }
        cnt++;
    }
    cnt--;
    for(int i = 1; i < cnt; ++i)
    {
        memset(visited, false, sizeof(visited));
        visited[i] = true;
        visited[0] = true;
        found = false;
        dfs(0);
        if(found == false)
            ans1[ans1cnt++] = i;
    }
    fout << ans1cnt;
    for(int i = 0; i < ans1cnt; ++i)
        fout << ' ' << ans1[i];
    fout << endl;
    for(int i = 0; i < ans1cnt; ++i)
    {
        memset(visited, false, sizeof(visited));
        visited[ans1[i]] = true;
        found = false;
        dfs2(ans1[i], ans1[i]);
        if(found == false)
            ans2[ans2cnt++] = ans1[i];
    }
    fout << ans2cnt;
    for(int i = 0; i < ans2cnt; ++i)
        fout << ' ' << ans2[i];
    fout << endl;
    return 0;
}
