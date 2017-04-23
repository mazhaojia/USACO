/*
ID: mazhaoj1
PROG: milk4
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //没想到数据这么弱。。。。我太弱了，不会DP。。。。

int q, p, pails[100], pail[100], pcnt, result[100], ans[100], acnt, foundtimes;
bool canuse[100];

int cmp(const void* aa, const void* bb)
{
    int* a = (int*)aa;
    int* b = (int*)bb;
    return *a - *b;
}

void solve(int pos, int total, int nowlen, int len)
{
    int loop, i, j, temp;
    if(nowlen == len)
    {
        if(q % total == 0)
        {
            foundtimes++;
            if(foundtimes == 1)
                for(i = 0; i < len; ++i)
                    ans[i] = result[i];
            else
            {
                for(i = 0; i < len; ++i)
                {
                    if(ans[i] < result[i])
                        return;
                    if(ans[i] > result[i])
                        break;
                }
                if(i != len)
                    for(i = 0; i < len; ++i)
                        ans[i] = result[i];
            }
        }
        return;
    }
    for(i = pos; i < pcnt; ++i)
    {
        loop = q / pail[i];
        temp = total;
        for(j = 0; j < loop; ++j)
        {
            total += pail[i];
            if(total > q)
                break;
            result[nowlen] = pail[i];
            solve(i + 1, total, nowlen + 1, len);
        }
        total = temp;
    }
}

int main()
{
    ifstream fin("milk4.in");
    ofstream fout("milk4.out");
    fin >> q >> p;
    for(int i = 0; i < p; ++i)
        fin >> pails[i];
    qsort(pails, p, sizeof(pails[0]), cmp);
    memset(canuse, true, sizeof(canuse));
    for(int i = 0; i < p; ++i)
        for(int j = i + 1; j < p; ++j)
            if(canuse[j] == true && pails[j] % pails[i] == 0)
                canuse[j] = false;
    for(int i = 0; i < p; ++i)
        if(canuse[i] == true)
            pail[pcnt++] = pails[i];
    for(int i = 0; i < pcnt; ++i)
    {
        solve(0, 0, 0, i + 1);
        if(foundtimes > 0)
        {
            acnt = i + 1;
            break;
        }
    }
    fout << acnt;
    for(int i = 0; i < acnt; ++i)
        fout <<  ' ' << ans[i];
    fout << endl;
    return 0;
}
