/*
ID: mazhaoj1
PROG: barn1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct dists
{
    int loc;
    int dist;
}dis[200];
int comp(const void *p1, const void *p2)
{
    const dists* f1 = (dists*)p1;
    const dists* f2 = (dists*)p2;
    return f2->dist - f1->dist;
}
int comp2(const void *p1, const void *p2)
{
    const int* f1 = (int*)p1;
    const int* f2 = (int*)p2;
    return *f1 - *f2;
}
int main()
{
    ofstream fout ("barn1.out");
    ifstream fin ("barn1.in");
    int cow[200], board, stallnum, cows, i;
    fin>>board>>stallnum>>cows;
    for(i = 0; i < cows; ++i)
        fin>>cow[i];
    qsort(cow, cows, sizeof(cow[0]), comp2);
    if(board == 1)
    {
        fout << cow[cows - 1] - cow[0] + 1 << endl;
        return 0;
    }
    for(i = 1; i < cows; ++i)
    {
        dis[i-1].dist = cow[i] - cow[i-1];
        dis[i-1].loc = i-1;
    }
    qsort(dis, cows-1, sizeof(dis[0]), comp);
    int locs[200];
    for(i = 0; i < board - 1; ++i)
        locs[i] = cow[dis[i].loc];
    qsort(locs, board - 1, sizeof(locs[0]), comp2);
    int total = 1;
    int j = 1;
    for(i = 0; i < board - 1; ++i)
    {
        for(; j < cows; ++j)
        {
            if(cow[j] <= locs[i])
            {
                total += cow[j] - cow[j-1];
            }
            else
            {
                j++;
                total += 1;
                break;
            }
        }
    }
    for(; j < cows; ++j)
        total += cow[j] - cow[j-1];
    fout << total <<endl;
    return 0;
}
