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
请看此篇解析，我认为是最容易懂的解法：http://blog.csdn.net/biran007/archive/2009/02/19/3911430.aspx
我再补充一下，首先求出a[i]，即前i个数xor的结果，然后假设有a[i],a[j]，则a[i] xor a[j]即
等于输入数据中从i+1一直到j这么长的序列的值的xor结果。有了a[j],只要在0-1树里找满足条件的a[i]即可。
但是上面的做法由于求出的序列是i+1开始的，因此第一个值无法包含在求出的序列里，所以树中要先插入一个0。
现在假设xor的最大值相等，那么由于我们是通过a[j]找a[i]，而a[i]的rank即i，肯定是最大的，所以满足最大的rank的题目要求。
由于我们每次插入都覆盖之前相同的值，因此每个值在数里面只出现一次，而且只可能是靠近j的覆盖离j远的，
这样覆盖以后节点的rank会变小，所以这样找到的肯定不是比之前找到的更优的最短序列。
这里我每次都new节点，内存使用为16336，差一点点点就爆内存了。不知道直接开数组会不会好点。
nocow，usaco的analysis及其他神牛还有其他解法。。。。。
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
        if(maxxor < temp)    //注意这里只需小于即可
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
