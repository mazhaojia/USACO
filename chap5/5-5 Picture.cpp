/*
ID: mazhaoj1
PROG: picture
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //解法太精妙了！详见nocow题解，主要思想是统计每个线段被覆盖的次数，题解中的level为[-10000, 10000]的区间

struct line
{
    int s, e, pos;
    bool start;
}linex[10000], liney[10000];
int n, ans;
ifstream fin("picture.in");
ofstream fout("picture.out");

int cmp(const void* aa, const void* bb)
{
    line* a = (line*)aa;
    line* b = (line*)bb;
    if(a->pos == b->pos)
        return a->start == true ? -1 : 1;
    return a->pos - b->pos;
}

/*SOLVE 1:  不用线段树 O(n^2)
int* levels;

void scan(line* lines)
{
    memset(levels, 0, sizeof(int) * 20001); //注意这里直接sizeof(levels) == 4，因为levels是指针
    int* level = levels + 10000;    //注意这个技巧
    for(int i = 0; i < n * 2; ++i)
    {
        if(lines[i].start)
        {
            for(int j = lines[i].s; j < lines[i].e; ++j)    //注意这里的小于，因为线段[1,3]长度为2，所以我们只统计一点开始长度为1的线段
            {
                level[j]++;
                if(level[j] == 1)
                    ans++;
            }
        }
        else
        {
            for(int j = lines[i].s; j < lines[i].e; ++j)    //注意这里的小于，因为线段[1,3]长度为2，所以我们只统计一点开始长度为1的线段
            {
                level[j]--;
                if(level[j] == 0)
                    ans++;
            }
        }
    }
}

void init()
{
    int x1, y1, x2, y2;
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> x1 >> y1 >> x2 >> y2;    //i入边，i+n出边
        linex[i].s = x1;
        linex[i].e = x2;
        linex[i].pos = y1;
        linex[i].start = true;
        linex[i + n].s = x1;
        linex[i + n].e = x2;
        linex[i + n].pos = y2;
        linex[i + n].start = false;     //或者还有一种是linex[i * 2 - 1], linex[i * 2], 下标从1开始
        liney[i].s = y1;
        liney[i].e = y2;
        liney[i].pos = x1;
        liney[i].start = true;
        liney[i + n].s = y1;
        liney[i + n].e = y2;
        liney[i + n].pos = x2;
        liney[i + n].start = false;
    }
    qsort(linex, n * 2, sizeof(linex[0]), cmp);
    qsort(liney, n * 2, sizeof(liney[0]), cmp);
}

int main()
{
    init();
    levels = new int[20001];
    scan(linex);
    scan(liney);
    fout << ans << endl;
    return 0;
}
*/

//SLOVE 2: 线段树O(nlogn)，精妙的地方在于那个insert递归。
#define MAX 20001

struct tre                          //线段树第一种变化，叶结点线段长度为1
{
    int left, right;                  //当前的范围
    tre* leftchild, *rightchild;       //左，右孩子
    int c, m;                       //覆盖数（上文提到的level）、线段区间内还能看到的线段的总长度
}tree[MAX*2];      //线段树大小，至少为线段长度的2倍。或者最方便的为题目中给出的(最大值+1)*2，
                    //可避免0的问题
int pos;           //当前的tree的位置，为当前tree的大小减一

void construct(int lt,int rt)
{
    int mid,p;
    tree[pos].left = lt;
    tree[pos].right = rt;
    tree[pos].c = tree[pos].m = 0;
    if(lt + 1 == rt)
    {
        tree[pos].leftchild = NULL;
        tree[pos].rightchild = NULL;
    }
    else
    {
        p = pos;
        mid=(lt + rt) >> 1;                    //特别注意mid如何生成
        tree[p].leftchild = &tree[++pos];
        construct(lt, mid);                 //特别注意参数
        tree[p].rightchild = &tree[++pos];
        construct(mid, rt);                  //特别注意参数
    }
}

void insert(tre* t,int lt,int rt, int c)   //将长度为lt到rt的线段插入(c=1)，删除(c=-1)tree的t结点
{
    int mid;
    if(lt == t->left && rt == t->right)
    {
        t->c += c;
        t->m = t->right - t->left;
    }
    else
    {
        mid = (t->left + t->right) >> 1;     //特别注意mid如何生成
        if(rt <= mid)
            insert(t->leftchild, lt, rt, c);  //特别注意参数
        else if(lt >= mid)
            insert(t->rightchild, lt, rt, c);  //特别注意参数
        else
        {
            insert(t->leftchild, lt, mid, c);  //特别注意参数
            insert(t->rightchild, mid, rt, c);  //特别注意参数
        }
    }
    if(t->c == 0)   //长度为t的的线段还未被插入和删除过或者插入和删除的次数相同
    {
        if(t->left + 1 == t->right)     //这个设为0很精妙，表明这个长度为1的叶节点线段正好作为入边和出边出现了0次或n次，所以正好看不见了
            t->m = 0;
        else    //找出这条线段还看得见的部分
            t->m = t->leftchild->m + t->rightchild->m;
    }
}

void init()
{
    int x1, y1, x2, y2;
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> x1 >> y1 >> x2 >> y2;    //i入边，i+n出边
        x1 += 10000;
        x2 += 10000;
        y1 += 10000;
        y2 += 10000;
        linex[i].s = x1;
        linex[i].e = x2;
        linex[i].pos = y1;
        linex[i].start = true;
        linex[i + n].s = x1;
        linex[i + n].e = x2;
        linex[i + n].pos = y2;
        linex[i + n].start = false;     //或者还有一种是linex[i * 2 - 1], linex[i * 2], 下标从1开始
        liney[i].s = y1;
        liney[i].e = y2;
        liney[i].pos = x1;
        liney[i].start = true;
        liney[i + n].s = y1;
        liney[i + n].e = y2;
        liney[i + n].pos = x2;
        liney[i + n].start = false;
    }
    qsort(linex, n * 2, sizeof(linex[0]), cmp);
    qsort(liney, n * 2, sizeof(liney[0]), cmp);
}

int main()
{
    int oldans;
    init();
    pos = 0;             //此句初始化不能忘记
    construct(0, 20000);  //紧接着这句初始化
    for(int i = 0; i < n * 2; ++i)  //由于i<n时c都是+1，i>n时c都是-1，可知在这个循环中oldans先增后减，每次的增量就是上面解1的level由0变1，每次的减量就是上面解1的level由1变0
    {
        oldans = tree[0].m;
        insert(&tree[0], linex[i].s, linex[i].e, (linex[i].start == true ? 1 : -1));
        ans += abs(oldans - tree[0].m);
    }
    for(int i = 0; i < n * 2; ++i)
    {
        oldans = tree[0].m;
        insert(&tree[0], liney[i].s, liney[i].e, (liney[i].start == true ? 1 : -1));
        ans += abs(oldans - tree[0].m);
    }
    fout << ans << endl;
}
