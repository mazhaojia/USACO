/*
ID: mazhaoj1
PROG: agrinet
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("agrinet.in");
    ofstream fout("agrinet.out");
    int n, arr[100][100], dist[100];
    bool visited[100];
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            fin >> arr[i][j];
            if(arr[i][j] == 0)
                arr[i][j] = 100000000;
        }
    }
    memset(visited, false, sizeof(visited));
    for(int i = 0; i < n ; ++i)
        dist[i] = arr[0][i];
    visited[0] = true;
    for(int i = 0; i < n - 1; ++i)
    {
        int minmin = 100000000, minpos = 0;
        for(int j = 0; j < n; ++j)
        {
            if(visited[j] == false && minmin > dist[j])
            {
                minmin = dist[j];
                minpos = j;
            }
        }
        visited[minpos] = true;
        for(int j = 0; j < n; ++j)
            if(visited[j] == false && dist[j] > arr[minpos][j])
                dist[j] = arr[minpos][j];
    }
    int ans = 0;
    for(int i = 0; i < n; ++i)
        if(dist[i] != 100000000)
            ans += dist[i];
    fout << ans << endl;
    return 0;
}
