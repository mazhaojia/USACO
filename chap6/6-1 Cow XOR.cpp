/*
ID: mazhaoj1
PROG: cowxor
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
�뿴��ƪ����������Ϊ�������׶��Ľⷨ��http://blog.csdn.net/biran007/archive/2009/02/19/3911430.aspx
���ٲ���һ�£��������a[i]����ǰi����xor�Ľ����Ȼ�������a[i],a[j]����a[i] xor a[j]��
�������������д�i+1һֱ��j��ô�������е�ֵ��xor���������a[j],ֻҪ��0-1����������������a[i]���ɡ�
����������������������������i+1��ʼ�ģ���˵�һ��ֵ�޷�������������������������Ҫ�Ȳ���һ��0��
���ڼ���xor�����ֵ��ȣ���ô����������ͨ��a[j]��a[i]����a[i]��rank��i���϶������ģ�������������rank����ĿҪ��
��������ÿ�β��붼����֮ǰ��ͬ��ֵ�����ÿ��ֵ��������ֻ����һ�Σ�����ֻ�����ǿ���j�ĸ�����jԶ�ģ�
���������Ժ�ڵ��rank���С�����������ҵ��Ŀ϶����Ǳ�֮ǰ�ҵ��ĸ��ŵ�������С�
������ÿ�ζ�new�ڵ㣬�ڴ�ʹ��Ϊ16336����һ����ͱ��ڴ��ˡ���֪��ֱ�ӿ�����᲻��õ㡣
nocow��usaco��analysis��������ţ���������ⷨ����������
*/

struct tree01
{
    tree01* next[2];
    int idx, value;
    tree01():next(){next[0] = next[1] = NULL;}
}root, *p, *q;
int n, num, a[100001], maxxor = -1, start, end, temp;

int getbit(int value, int bit)
{
    return (value >> bit & 1);
}

void insertxor(int idx, int value)
{
    int t;
    p = &root;
    for(int i = 20; i >= 0; --i)
    {
        t = getbit(value, i);
        if(p->next[t] == NULL)
            p->next[t] = new tree01();
        p = p->next[t];
    }
    p->idx = idx;
    p->value = value;
}

tree01* findxor(int value)
{
    int t;
    p = &root;
    for(int i = 20; i >= 0; --i)
    {
        t = getbit(value, i);
        if(p->next[t ^ 1] != NULL)
            p = p->next[t ^ 1];
        else
            p = p->next[t];
    }
    return p;
}

int main()
{
    ifstream fin("cowxor.in");
    ofstream fout("cowxor.out");
    a[0] = 0;
    insertxor(0, 0);
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        fin >> num;
        a[i] = a[i - 1] ^ num;
        q = findxor(a[i]);
        temp = a[i] ^ q->value;
        if(maxxor < temp)    //ע������ֻ��С�ڼ���
        {
            maxxor = temp;
            start = q->idx + 1;
            end = i;
        }
        insertxor(i, a[i]);
    }
    fout << maxxor << ' ' << start << ' ' << end << endl;
    return 0;
}
