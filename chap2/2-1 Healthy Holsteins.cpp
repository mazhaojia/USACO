/*
ID: mazhaoj1
PROG: holstein
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int v, vitamin[25], f, feed[15][25], noweat[25], seq[15], seqcnt = 16, step[15], stepcnt;

int check()
{
    for(int i = 0; i < v; ++i)
        if(noweat[i] < vitamin[i])
            return 0;
    return 1;
}

void setresult()
{
    seqcnt = stepcnt;
    for(int i = 0; i < stepcnt; ++i)
        seq[i] = step[i];
}

void setvalue(int level, int setback)
{
    if(!setback)
        for(int i = 0; i < v; ++i)
            noweat[i] += feed[level][i];
    else
        for(int i = 0; i < v; ++i)
            noweat[i] -= feed[level][i];
}

void solve(int level)
{
    if(check())
    {
        if(stepcnt < seqcnt)
            setresult();
        return;
    }
    if(level == f)
        return;

    step[stepcnt++] = level;    //feed this scoop
    setvalue(level, 0);
    solve(level + 1);
    setvalue(level, 1);
    stepcnt--;

    solve(level + 1);   //not feed this scoop
}

int main()
{
    ofstream fout("holstein.out");
    ifstream fin("holstein.in");
    fin >> v;
    for(int i = 0; i < v; ++i)
        fin>> vitamin[i];
    fin >> f;
    for(int i = 0; i < f; ++i)
        for(int j = 0; j < v; ++j)
            fin >>feed[i][j];
    solve(0);
    fout << seqcnt;
    for(int i = 0; i < seqcnt; ++i)
        fout <<  ' ' << seq[i] + 1;
    fout << endl;
    return 0;
}
