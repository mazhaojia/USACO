/*
ID: mazhaoj1
PROG: concom
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int own[101][101], value[101];
bool control[101][101], visited[101];

void floodfill(int node)
{
    if(visited[node])   //不把visited放在循环里的if前判断可以确保当有A->C, B->C时A->C和B->C的值都能加到C上。
        return;
    visited[node] = true;
    for(int i = 1; i <= 100; ++i)
    {
        if(i != node)
        {
            value[i] += own[node][i];
            if(value[i] > 50)
                floodfill(i);
        }
    }
}

int main()
{
    ifstream fin("concom.in");
    ofstream fout("concom.out");
    int num;
    fin >> num;
    while(num--)
    {
        int a, b, p;
        fin >> a >> b >>p;
        own[a][b] = p;
        if(p > 50)
            control[a][b] = true;
    }
    for(int i = 1; i <= 100; ++i)
    {
        control[i][i] = true;
        own[i][i] = 100;
    }
    for(int i = 1; i <= 100; ++i)
    {
        floodfill(i);
        for(int j = 1; j <= 100; ++j)
            if(value[j] > 50)
                control[i][j] = true;
        memset(value, 0, sizeof(value));
        memset(visited, false, sizeof(visited));
    }
    for(int i = 1; i <= 100; ++i)
        for(int j = 1; j <= 100; ++j)
            if(i != j && control[i][j] == true)
                fout << i << ' ' << j << endl;
    return 0;
}
