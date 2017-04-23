/*
ID: mazhaoj1
PROG: milk3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

int used[21][21][21];
int cap[3];
int bucket[3];
int ans[21];

int pour(int from, int to)
{
    int r = 0;
    if(bucket[from] > 0 && bucket[to] < cap[to])
    {
        int need = cap[to] - bucket[to];
        if(bucket[from] < need)
        {
            bucket[to] += bucket[from];
            bucket[from] = 0;
        }
        else
        {
            bucket[from] -= need;
            bucket[to] = cap[to];
        }
        r = 1;
    }
    return r;
}

void doit()
{
    if(bucket[0] == 0)
        ans[bucket[2]] = 1;
    if(used[bucket[0]][bucket[1]][bucket[2]] == 1)
        return;
    used[bucket[0]][bucket[1]][bucket[2]] = 1;
    for(int i = 0; i <= 2; ++i)
    {
        for(int j = 0; j <= 2; ++j)
        {
            if(i != j)
            {
                int orifrom = bucket[i];
                int orito = bucket[j];
                if(pour(i, j))
                {
                    doit();
                    bucket[i] = orifrom;
                    bucket[j] = orito;
                }
            }
        }
    }
    used[bucket[0]][bucket[1]][bucket[2]] = 0;
}

int main()
{
    ofstream fout("milk3.out");
    ifstream fin("milk3.in");
    fin >> cap[0] >> cap[1] >> cap[2];
    bucket[0] = bucket[1] = 0;
    bucket[2] = cap[2];
    doit();
    int anscnt = 0;
    for(int i = 0; i < 21; ++i)
    {
        if(ans[i])
        {
            if(anscnt == 0)
            {
                fout << i;
                anscnt++;
            }
            else
                fout << " " << i;
        }
    }
    fout << endl;
    return 0;
}