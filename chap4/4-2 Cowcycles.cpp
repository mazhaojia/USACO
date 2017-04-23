/*
ID: mazhaoj1
PROG: cowcycle
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

int f, r, f1, f2, r1, r2, fs[80], rs[40], rcnt, dcnt, ansf[80], ansr[40];
double ratio[81][41], ratios[3300], diff[3300], mean, variance, ans = 99999999;

void calc()
{
    if(fs[f - 1] * rs[r - 1] < 3 * fs[0] * rs[0])
        return;
    rcnt = dcnt = 0;
    for(int i = 0; i < f; ++i)
        for(int j = 0; j < r; ++j)
            ratios[rcnt++] = ratio[fs[i]][rs[j]];
    sort(ratios, ratios + rcnt);
    for(int i = 1; i < rcnt; ++i)
        diff[dcnt++] = ratios[i] - ratios[i - 1];
    mean = diff[0];
    for(int i = 1; i < dcnt; ++i)
        mean += diff[i];
    mean /= dcnt;
    variance = (diff[0] - mean) * (diff[0] - mean);
    for(int i = 1; i < dcnt; ++i)
        variance += (diff[i] - mean) * (diff[i] - mean);
    variance /= dcnt;
    if(ans > variance)
    {
        ans = variance;
        memcpy(ansf, fs, sizeof(int) * f);
        memcpy(ansr, rs, sizeof(int) * r);
    }
}

void iterateR(int s, int total)
{
    if(total == r)
    {
        calc();
        return;
    }
    for(int i = s + 1; i <= r2; ++i)
    {
        rs[total] = i;
        iterateR(i, total + 1);
    }
}

void iterateF(int s, int total)
{
    if(total == f)
    {
        iterateR(r1 - 1, 0);
        return;
    }
    for(int i = s + 1; i <= f2; ++i)
    {
        fs[total] = i;
        iterateF(i, total + 1);
    }
}

int main()
{
    ifstream fin("cowcycle.in");
    ofstream fout("cowcycle.out");
    fin >> f >> r >> f1 >> f2 >> r1 >> r2;
    for(int i = f1; i <= f2; ++i)
        for(int j = r1; j <= r2; ++j)
            ratio[i][j] = (double)i / j;
    iterateF(f1 - 1, 0);
    fout << ansf[0];
    for(int i = 1; i < f; ++i)
        fout << ' ' << ansf[i];
    fout <<endl;
    fout << ansr[0];
    for(int i = 1; i < r; ++i)
        fout << ' ' << ansr[i];
    fout << endl;
    return 0;
}
