/*
ID: mazhaoj1
PROG: frameup
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
���ȼ�������п�����½ŵ�����Ͻǵ���꣬�����Ϳ���֪������ĸ��߿�ķ�Χ��
�������ڲ������ǣ���ô�ڷ�˳���Ⱥ�û��ϵ������������ȷ����ġ�
����ֻ�迼�ǿ���ı���û�б����ǾͿ����ˣ������ó�һ��ͼ��
Ȼ���������򣬵���Ҫ������е�����������������dfs������н����ע������Ľ�������������н⻹Ҫ������
������Ǹ��ǵĵ������ǵ���һ���ߣ����Ƿ�������ͼ��
��ôֻҪ��֤ͼ���ڽӱ���������ǰ�˳��ģ�Ӧ�õõ�һ����Ϳ���ֱ������ˡ�
*/

int h, w, cnt, ans[26], ancnt;
char frame[30][30], an[6000][27];   //������ݵĽ����5900����
bool cover[26][26], showed[26];
struct rectangle
{
    int llr, llc, urr, urc;
    rectangle()
    {
        llr = -1;
        llc = 30;
        urr = 30;
        urc = -1;
    }
}rec[26];
struct adjlist
{
    int vertex;
    adjlist* next;
    adjlist():next(NULL){}
}adj[26], *p, *q;
ofstream fout("frameup.out");

void dfstopsort(int level)
{
    if(level == cnt)
    {
        for(int i = cnt - 1, j = 0; i >= 0; --i, ++j)
            an[ancnt][j] = ans[i] + 'A';
        ancnt++;
        return;
    }
    for(int i = 0; i < 26; ++i)
    {
        if(adj[i].vertex == 0 && showed[i])   // && showed[i] is important
        {
            adjlist* q = adj[i].next;
            while(q != NULL)
            {
                adj[q->vertex].vertex--;
                q = q->next;
            }
            adj[i].vertex = 32767;	//���ø�i���´�dfsʱ�ٴα�dfs��
            ans[level] = i;
            dfstopsort(level + 1);
            adj[i].vertex = 0;
            q = adj[i].next;
            while(q != NULL)
            {
                adj[q->vertex].vertex++;
                q = q->next;
            }
        }
    }
}

void setadj(int row, int col, int i)
{
    int t = frame[row][col] - 'A';
    if(frame[row][col] == '.' || t == i)
        return;
    if(cover[t][i] == false)
    {
        cover[t][i] = true;
        p = new adjlist();
        p->vertex = i;
        q = &adj[t];
        while(q->next != NULL && q->next->vertex < i)	//����������Բ�������
            q = q->next;
        p->next = q->next;
        q->next = p;
        adj[i].vertex++;
    }
}

int cmp(const void* aa, const void* bb)
{
    char* a = (char*)aa;
    char* b = (char*)bb;
    return strcmp(a, b);
}

int main()
{
    ifstream fin("frameup.in");
    fin >> h >> w;
    char ch;
    int t;
    for(int i = 0; i < h; ++i)
    {
        for(int j = 0; j < w; ++j)
        {
            fin >> ch;
            frame[i][j] = ch;
            if(ch == '.')
                continue;
            t = ch - 'A';
            showed[t] = true;
            if(rec[t].llr < i)	//�������о��εķ�Χ
                rec[t].llr = i;
            if(rec[t].urr > i)
                rec[t].urr = i;
            if(rec[t].llc > j)
                rec[t].llc = j;
            if(rec[t].urc < j)
                rec[t].urc = j;
        }
    }
    for(int i = 0; i < 26; ++i)
        if(rec[i].llr != -1)
            cnt++;
    for(int i = 0; i < 26; ++i)
    {
        if(rec[i].llr == -1)
            continue;
        for(int j = rec[i].llc; j <= rec[i].urc; ++j)
        {
            setadj(rec[i].urr, j, i);   //����һ����û�б�����
            setadj(rec[i].llr, j, i);   //���һ��
        }
        for(int j = rec[i].urr; j <= rec[i].llr; ++j)
        {
            setadj(j, rec[i].llc, i);    //��һ��
            setadj(j, rec[i].urc, i);    //���һ��
        }
    }
    dfstopsort(0);
    qsort(an, ancnt, sizeof(an[0]), cmp);
    for(int i = 0; i < ancnt; ++i)
        fout << an[i] << endl;
    return 0;
}
