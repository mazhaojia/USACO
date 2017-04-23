/*
ID: mazhaoj1
PROG: butter
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;    //�ڽӱ�Ӷ��Ż����ܸ㶨������⡣����������Ҫѧϰһ��SPFA�ˡ�����

int cowcnt, nodecnt, c, cowpos[500];
int maxlen = 90000000, l, r, value, dist[800][800];
bool visited[800], calced[800];
typedef pair<int, int> pa;
pa elem;

struct node
{
    int vertex, value;
    node* next;
    node():next(NULL){}
}path[800];
node* p;

//SOLUTION 1: dijkstra with heap optimize, must use adjecent list, or will TLE even use heap.
void dijkstra_heap(int node)
{
    priority_queue<pa, vector<pa>, greater<pa> > qu;
    memset(visited, false, sizeof(visited));
    for(int i = 0; i < nodecnt; ++i)
        dist[node][i] = maxlen;     //ע���������ͨdijkstra������
    dist[node][node] = 0;
    qu.push(make_pair(dist[node][node], node));
    while(!qu.empty())
    {
        elem = qu.top();
        qu.pop();
        if(visited[elem.second] == false)
        {
            visited[elem.second] = true;
            p = path[elem.second].next;
            while(p != NULL)
            {
                if(visited[p->vertex] == false)
                {
                    int dis = elem.first + p->value;
                    if(dist[node][p->vertex] > dis)
                    {
                        dist[node][p->vertex] = dis;
                        qu.push(make_pair(dist[node][p->vertex], p->vertex));
                    }
                }
                p = p->next;
            }
        }
    }
}

/*
SOLUTION 2: bellman_ford, just a little slower than solution 1.
int bellman_ford(int node)
{
    for(int i = 0; i < nodecnt; ++i)
        dist[node][i] = maxlen;
    dist[node][node] = 0;
    for(int i = 0; i < nodecnt - 1; ++i)
    {
        bool flag = false;
        for(int j = 0; j < nodecnt; ++j)
        {
            p = path[j].next;
            while(p != NULL)
            {
                if(dist[node][j] + p->value < dist[node][p->vertex])
                {
                    dist[node][p->vertex] = dist[node][j] + p->value;
                    flag = true;
                }
                p = p->next;
            }
        }
        if(flag == false)
            return 0;
    }
    for(int i = 0; i < nodecnt; ++i)
    {
        p = path[i].next;
        while(p != NULL)
            if(dist[node][i] + p->value < dist[node][p->vertex])
                return -1;  //negative circle
    }
    return 0;
}
*/

/*
SOLUTION 3: SPFA, fastest in this problem, but not stable, performed not good at dense graph, worst case is still same as bellman_ford, O(VE)!

SPFA�㷨�������Ż��㷨 SLF �� LLL�� SLF��Small Label First ���ԣ���Ҫ����Ľڵ���j������Ԫ��Ϊi����dist(j)<dist(i)����j������ף���������β��
LLL��Large Label Last ���ԣ������Ԫ��Ϊi������������distֵ��ƽ��ֵΪx����dist(i)>x��i���뵽��β��������һԪ�أ�ֱ���ҵ�ĳһiʹ��dist(i)<=x��
��i���Խ����ɳڲ����� �����������ϣ�SLF ��ʹ�ٶ���� 15 ~ 20%��SLF + LLL �����Լ 50%�� ��ʵ�ʵ�Ӧ����SPFA���㷨ʱ��Ч�ʲ��Ǻ��ȶ���
Ϊ�˱��������ĳ��֣�ͨ��ʹ��Ч�ʸ����ȶ���Dijkstra�㷨�� 

int front, end, qu[1450 * 800], inqueuetime[800]; //queue size = maxnode * maxedge
bool inqueue[800];
bool SPFA(int node)     //�����������Ҫ�ж��Ƿ��е������V(�ڵ�����)�Ρ�
{
    memset(inqueuetime, 0, sizeof(inqueuetime));
    front = end = 0;
    for(int i = 0; i < nodecnt; ++i)
        dist[node][i] = maxlen;
    dist[node][node] = 0;
    qu[end++] = node;
    inqueue[node] = true;
    inqueuetime[node]++;
    while(front != end)
    {
        int temp = qu[front];
        front++;
        inqueue[temp] = false;
        p = path[temp].next;
        while(p != NULL)
        {
            if(dist[node][temp] + p->value < dist[node][p->vertex])
            {
                dist[node][p->vertex] = dist[node][temp] + p->value;
                if(inqueue[p->vertex] == false)
                {
                    qu[end++] = p->vertex;
                    inqueue[p->vertex] = true;
                    inqueuetime[p->vertex]++;
                    if(inqueuetime[p->vertex] == 800)	//���ﲻ��V����V+1��δ���Թ�
                        return false;   //negative circle
                }
            }
            p = p->next;
        }
    }
    return true;
}
*/

int main()
{
    ifstream fin("butter.in");
    ofstream fout("butter.out");
    memset(path, 0, sizeof(path));
    fin >> cowcnt >> nodecnt >> c;
    for(int i = 0; i < cowcnt; ++i)
    {
        fin >> cowpos[i];
        cowpos[i]--;
    }
    for(int i = 0; i < c; ++i)
    {
        fin >> l >> r >> value;
        l--;
        r--;
        p = &path[l];
        while(p->next != NULL)
            p = p->next;
        p->next = new node();
        p = p->next;
        p->vertex = r;
        p->value = value;
        p = &path[r];
        while(p->next != NULL)
            p = p->next;
        p->next = new node();
        p = p->next;
        p->vertex = l;
        p->value = value;
    }
    for(int i = 0; i < cowcnt; ++i)
    {
        if(calced[cowpos[i]] == false)
        {
            dijkstra_heap(cowpos[i]);
            calced[cowpos[i]] = true;
        }
    }
    int sum = maxlen, temp;
    for(int i = 0; i < nodecnt; ++i)
    {
        temp = 0;
        for(int j = 0; j < cowcnt; ++j)
            temp += dist[cowpos[j]][i];
        if(sum > temp)
            sum = temp;
    }
    fout << sum << endl;
    return 0;
}
