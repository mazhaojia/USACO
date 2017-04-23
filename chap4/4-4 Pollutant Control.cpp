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
���ȿ�������ⱨ�棬http://www.cppblog.com/xiongnanbin/articles/91833.html
��1001+1������̫ȡ���ˣ���û�ҵ�֤����������û�á�
���������ַ��������Ҫö�����������������С��ıߣ������Ǹ��Լ����Ϻܶ��һ��forѭ��ö�ٵķ����Ǵ���ġ�
��Ϊ�޷���֤ö�ٵ��Ľ�����ı������٣�NOCOW�ķ�����
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
����������Ա�������Ȼ�����������������С��ıߣ�������Щ�߿������ڲ�ͬ����С�Ȼ�����ٶ���forö����Щ����ıߣ�
�ҵ��������ٵ�һ����ϼ�Ϊ����ġ�
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
int depth[MAXV];    //������
int num[MAXV + 1];      //������Ϊdepth[i]�Ķ�����Ŀ

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
            if(depth[p->vertex] + 1 == depth[curnode])    //�����Ϊ0�ı�
            {
                prev[p->vertex] = curnode;
                q->next = p->next;                        //��ǰ���Ż�
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
            if(num[depth[curnode]] == 0)        //GAP�Ż�
                return ans;
            depth[curnode] = mind;
            if(mind != m)
            {
                p = q->next;
                q->next = p->next;
                p->next = adj[curnode].next;        //��ǰ���Ż�
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
                p = adj[prenode].next;            //���˵�ǰ���Ż������Բ��ر���
                if(minvalue > p->value)
                    minvalue = p->value;
                curnode = prenode;
            }
            curnode = sink;
            while(curnode != source)
            {
                prenode = prev[curnode];
                p = adj[prenode].next;
                p->value -= minvalue;        //���˵�ǰ���Ż������Բ��ر���
                if(p->value == 0)
                {
                    nextstartnode = prenode;
                    adj[prenode].next = p->next;        //ɾ��0�ߣ�����������Բ����
                }
                added = false;
                p = adj[curnode].next;
                while(p != NULL)
                {
                    if(p->vertex == prenode)
                    {
                        p->value += minvalue;            //�˴����ܽ��е�ǰ���Ż���������ܻ�wa��û���Թ���dinic������wa
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
                    adj[curnode].next = p;                //�ӵ���ͷ���ӿ��´η������е��ٶ�
                }
                curnode = prenode;
            }
            curnode = sink;
            while(curnode != nextstartnode && curnode != -1)        //��ջ�Ż������˵���ʼ�ڵ�
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
        if(edge[i].value > 0)   //Ϊ0�Ļ����ڴ�û���ã�ֱ������
        {
            added = false;
            p = &adj[edge[i].left];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == edge[i].right)
                {
                    p->value += edge[i].value;  //����һ�����ж������ߣ��������Ҫ������ô�����5����������Ҫ5�룬��ʱ
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

            //������ͼ
            added = false;
            p = &adjreverse[edge[i].right];
            while(p->next != NULL)
            {
                p = p->next;
                if(p->vertex == edge[i].left)
                {
                    p->value += edge[i].value;  //����һ�����ж�������
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
        p = &adj[edge[i].left];     //ö�ټ�����i����
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
        if(maxflow - nowflow == edge[i].value)  //�ҵ�һ����������С��
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
