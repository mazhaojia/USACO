/*
ID: mazhaoj1
PROG: fence
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

struct node
{
    int vertex;
    node* next;
    node():next(NULL){}
}s[500], *p, *q;

int maxnode, stack[1024 + 1], cnt, ans[1024 + 1], anscnt;   //1025 is the size of max edge(1024) + 1
ofstream fout("fence.out");

void eulerian_circle(int location)
{
    node* p, *q;
    int nextlocation = location;
    stack[cnt++] = location;
    while(cnt != 0)
    {
        location = stack[cnt - 1];
        p = &s[location];
        while(p->next != NULL)
        {
            nextlocation = p->next->vertex;
            q = &s[nextlocation];
            p->next = p->next->next;
            p = q;
            while(q->next != NULL && q->next->vertex != location)
                q = q->next;
            q->next = q->next->next;
            stack[cnt++] = nextlocation;
            location = nextlocation;
        }
        ans[anscnt++] = location + 1;
        cnt--;
    }
}

int main()
{
    ifstream fin("fence.in");
    int f, l, r, i;
    fin >> f;
    for(i = 0; i < f; ++i)
    {
        fin >> l >> r;
        if(maxnode < l)
            maxnode = l;
        if(maxnode < r)
            maxnode = r;
        l--;
        r--;

        s[l].vertex++;
        p = &s[l];
        while(p->next != NULL && p->next->vertex < r)
            p = p->next;
        q = p->next;
        p->next = new node();
        p->next->vertex = r;
        p->next->next = q;

        s[r].vertex++;
        p = &s[r];
        while(p->next != NULL && p->next->vertex < l)
            p = p->next;
        q = p->next;
        p->next = new node();
        p->next->vertex = l;
        p->next->next = q;
    }
    for(i = 0; i < maxnode; ++i)
    {
        if((s[i].vertex & 1) != 0)
        {
            eulerian_circle(i);
            break;
        }
    }
    if(i == maxnode)
    {
        for(i = 0; i < maxnode; ++i)
        {
            if(s[i].vertex != 0)
            {
                eulerian_circle(i);
                break;
            }
        }
    }
    for(i = anscnt - 1; i >= 0; --i)    //the answer is in reverse order.
        fout << ans[i] << endl;
    return 0;
}
