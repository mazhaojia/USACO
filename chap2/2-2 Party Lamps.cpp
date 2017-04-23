/*
ID: mazhaoj1
PROG: lamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//见Analysis中的解答。。。。
//Any even number of switch presses greater than four might as well just be four switch presses,
//and and any odd number greater than three might as well just be three presses.

int n, c, final[101], lcnt = 1, rcnt;
bool lamp[16][101], result[16][101];
ofstream fout("lamps.out");
ifstream fin("lamps.in");

void method1(int cnt)
{
    for(int i = 1; i <= n; ++i)
        lamp[cnt][i] = !lamp[cnt][i];
}

void method2(int cnt)
{
    for(int i = 1; i <= n; i += 2)
        lamp[cnt][i] = !lamp[cnt][i];
}

void method3(int cnt)
{
    for(int i = 2; i <= n; i += 2)
        lamp[cnt][i] = !lamp[cnt][i];
}

void method4(int cnt)
{
    for(int i = 1, k = 0; i <= n; ++k, i = 3 * k + 1)
        lamp[cnt][i] = !lamp[cnt][i];
}

void (*p[4])(int);

void count()
{
    for(int i = 0; i < 4; ++i)
    {
        p[i](lcnt);
        lcnt++;
    }
    for(int i = 0; i < 4; ++i)
    {
        for(int j = i + 1; j < 4; ++j)
        {
            p[i](lcnt);
            p[j](lcnt);
            lcnt++;
        }
    }
    for(int i = 0 ; i < 4; ++i)
    {
        for(int j = i + 1; j < 4; ++j)
        {
            for(int k = j + 1; k < 4; ++k)
            {
                p[i](lcnt);
                p[j](lcnt);
                p[k](lcnt);
                lcnt++;
            }
        }
    }
    p[0](lcnt);
    p[1](lcnt);
    p[2](lcnt);
    p[3](lcnt);
    lcnt++;
}

void match(int num)
{
    int i, j;
    for(i = 0; i < rcnt; ++i)
    {
        for(j = 1; j <= n; ++j)
            if(result[i][j] != lamp[num][j])
                break;
        if(j == n + 1)
            break;
    }
    if(i == rcnt)
    {
        for(j = 1; j <= n; ++j)
            result[rcnt][j] = lamp[num][j];
        rcnt++;
    }
}

void judge(int end)
{
    int i, j;
    for(i = 0; i <= end; ++i)
    {
        for(j = 1; j <= n; ++j)
            if(!
                  (
                      ( lamp[i][j] == true  && (final[j] == 1  || final[j] == 0) )
                  ||
                      ( lamp[i][j] == false && (final[j] == -1 || final[j] == 0) )
                  )
              )
                break;
        if(j == n + 1)
            match(i);
    }
}

int cmp(const void* aa, const void* bb)
{
    int* a = (int*)aa;
    int* b = (int*)bb;
    for(int i = 1; i <= n; ++i)
        if(a[i] != b[i])
            return a[i] - b[i];
    return -1;
}

int main()
{
    p[0] = method1;
    p[1] = method2;
    p[2] = method3;
    p[3] = method4;
    fin >> n >> c;
    int on, off;
    memset(lamp, true, sizeof(lamp));
    while(fin >> on && on != -1)
        final[on] = 1;
    while(fin >> off && off != -1)
        final[off] = -1;
    count();
    if(c > 4 && c % 2 == 0)
        c = 4;
    else if(c > 4)
        c = 3;
    if(c == 0)
        judge(0);
    else if(c == 1)
        judge(4);
    else if(c == 2)
        judge(10);
    else if(c == 3)
        judge(14);
    else if(c == 4)
        judge(15);
    qsort(result, rcnt, sizeof(result[0]), cmp);
    for(int i = 0; i < rcnt; ++i)
    {
        for(int j = 1; j <= n; ++j)
            fout << result[i][j];
        fout << endl;
    }
    if(rcnt == 0)
        fout << "IMPOSSIBLE" << endl;
    return 0;
}
