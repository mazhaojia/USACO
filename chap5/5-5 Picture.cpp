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
using namespace std;    //�̫ⷨ�����ˣ����nocow��⣬��Ҫ˼����ͳ��ÿ���߶α����ǵĴ���������е�levelΪ[-10000, 10000]������

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

/*SOLVE 1:  �����߶��� O(n^2)
int* levels;

void scan(line* lines)
{
    memset(levels, 0, sizeof(int) * 20001); //ע������ֱ��sizeof(levels) == 4����Ϊlevels��ָ��
    int* level = levels + 10000;    //ע���������
    for(int i = 0; i < n * 2; ++i)
    {
        if(lines[i].start)
        {
            for(int j = lines[i].s; j < lines[i].e; ++j)    //ע�������С�ڣ���Ϊ�߶�[1,3]����Ϊ2����������ֻͳ��һ�㿪ʼ����Ϊ1���߶�
            {
                level[j]++;
                if(level[j] == 1)
                    ans++;
            }
        }
        else
        {
            for(int j = lines[i].s; j < lines[i].e; ++j)    //ע�������С�ڣ���Ϊ�߶�[1,3]����Ϊ2����������ֻͳ��һ�㿪ʼ����Ϊ1���߶�
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
        fin >> x1 >> y1 >> x2 >> y2;    //i��ߣ�i+n����
        linex[i].s = x1;
        linex[i].e = x2;
        linex[i].pos = y1;
        linex[i].start = true;
        linex[i + n].s = x1;
        linex[i + n].e = x2;
        linex[i + n].pos = y2;
        linex[i + n].start = false;     //���߻���һ����linex[i * 2 - 1], linex[i * 2], �±��1��ʼ
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

//SLOVE 2: �߶���O(nlogn)������ĵط������Ǹ�insert�ݹ顣
#define MAX 20001

struct tre                          //�߶�����һ�ֱ仯��Ҷ����߶γ���Ϊ1
{
    int left, right;                  //��ǰ�ķ�Χ
    tre* leftchild, *rightchild;       //���Һ���
    int c, m;                       //�������������ᵽ��level�����߶������ڻ��ܿ������߶ε��ܳ���
}tree[MAX*2];      //�߶�����С������Ϊ�߶γ��ȵ�2������������Ϊ��Ŀ�и�����(���ֵ+1)*2��
                    //�ɱ���0������
int pos;           //��ǰ��tree��λ�ã�Ϊ��ǰtree�Ĵ�С��һ

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
        mid=(lt + rt) >> 1;                    //�ر�ע��mid�������
        tree[p].leftchild = &tree[++pos];
        construct(lt, mid);                 //�ر�ע�����
        tree[p].rightchild = &tree[++pos];
        construct(mid, rt);                  //�ر�ע�����
    }
}

void insert(tre* t,int lt,int rt, int c)   //������Ϊlt��rt���߶β���(c=1)��ɾ��(c=-1)tree��t���
{
    int mid;
    if(lt == t->left && rt == t->right)
    {
        t->c += c;
        t->m = t->right - t->left;
    }
    else
    {
        mid = (t->left + t->right) >> 1;     //�ر�ע��mid�������
        if(rt <= mid)
            insert(t->leftchild, lt, rt, c);  //�ر�ע�����
        else if(lt >= mid)
            insert(t->rightchild, lt, rt, c);  //�ر�ע�����
        else
        {
            insert(t->leftchild, lt, mid, c);  //�ر�ע�����
            insert(t->rightchild, mid, rt, c);  //�ر�ע�����
        }
    }
    if(t->c == 0)   //����Ϊt�ĵ��߶λ�δ�������ɾ�������߲����ɾ���Ĵ�����ͬ
    {
        if(t->left + 1 == t->right)     //�����Ϊ0�ܾ�������������Ϊ1��Ҷ�ڵ��߶�������Ϊ��ߺͳ��߳�����0�λ�n�Σ��������ÿ�������
            t->m = 0;
        else    //�ҳ������߶λ����ü��Ĳ���
            t->m = t->leftchild->m + t->rightchild->m;
    }
}

void init()
{
    int x1, y1, x2, y2;
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> x1 >> y1 >> x2 >> y2;    //i��ߣ�i+n����
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
        linex[i + n].start = false;     //���߻���һ����linex[i * 2 - 1], linex[i * 2], �±��1��ʼ
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
    pos = 0;             //�˾��ʼ����������
    construct(0, 20000);  //����������ʼ��
    for(int i = 0; i < n * 2; ++i)  //����i<nʱc����+1��i>nʱc����-1����֪�����ѭ����oldans���������ÿ�ε��������������1��level��0��1��ÿ�εļ������������1��level��1��0
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
