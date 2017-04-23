/*
ID: mazhaoj1
PROG: comehome
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("comehome.in");
    ofstream fout("comehome.out");
    int num, dis, dist[52], arr[52][52];
    for(int i = 0; i < 52; ++i)
        for(int j = 0; j < 52; ++j)
            arr[i][j] = 90000000;
    fin >> num;
    char from, to;
    int f, t;
    for(int i = 0; i < num; ++i)
    {
        fin >> from >> to >> dis;
        if(from >= 'A' && from <= 'Z')
            f = from - 'A';
        else
            f = from - 'a' + 26;
        if(to >= 'A' && to <= 'Z')
            t = to - 'A';
        else
            t = to - 'a' + 26;
        if(from != to && dis < arr[f][t])   //faint, ÔÚdis < arr[f][t]´íÁËºÃ¾Ã¡£¡£¡£
        {
            arr[f][t] = dis;
            arr[t][f] = dis;
        }
    }
    bool found[52];
    int mindis, minpos;
    memset(found, false, sizeof(found));
    for(int i = 0; i < 52; ++i)
        dist[i] = arr[25][i];
    found[25] = true;
    for(int i = 0; i < 51; ++i)
    {
        mindis = 90000000;
        minpos = -1;
        for(int j = 0; j < 52; ++j)
        {
            if(dist[j] < mindis && !found[j])
            {
                mindis = dist[j];
                minpos = j;
            }
        }
        if(minpos == -1)
            break;
        found[minpos] = true;
        for(int j = 0; j < 52; ++j)
            if(found[j] == false && dist[minpos] + arr[minpos][j] < dist[j])
                dist[j] = dist[minpos] + arr[minpos][j];
    }
    int ans = 90000000;
    char anspos = 'a';
    for(int i = 0; i < 25; ++i)
    {
        if(ans > dist[i])
        {
            ans = dist[i];
            anspos = i + 'A';
        }
    }
    fout << anspos << ' ' << ans << endl;
    return 0;
}
