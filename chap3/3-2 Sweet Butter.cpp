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
using namespace std;    //邻接表加堆优化才能搞定这个问题。。。。下面要学习一下SPFA了。。。

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
        dist[node][i] = maxlen;     //注意这里和普通dijkstra的区别
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

SPFA算法有两个优化算法 SLF 和 LLL： SLF：Small Label First 策略，设要加入的节点是j，队首元素为i，若dist(j)<dist(i)，则将j插入队首，否则插入队尾。
LLL：Large Label Last 策略，设队首元素为i，队列中所有dist值的平均值为x，若dist(i)>x则将i插入到队尾，查找下一元素，直到找到某一i使得dist(i)<=x，
则将i出对进行松弛操作。 引用网上资料，SLF 可使速度提高 15 ~ 20%；SLF + LLL 可提高约 50%。 在实际的应用中SPFA的算法时间效率不是很稳定，
为了避免最坏情况的出现，通常使用效率更加稳定的Dijkstra算法。 

int front, end, qu[1450 * 800], inqueuetime[800]; //queue size = maxnode * maxedge
bool inqueue[800];
bool SPFA(int node)     //处理负边情况需要判断是否有点入队了V(节点总数)次。
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
                    if(inqueuetime[p->vertex] == 800)	//这里不是V就是V+1，未测试过
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
