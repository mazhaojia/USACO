/*
ID: mazhaoj1
PROG: cowtour
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
using namespace std;

struct pasture
{
    int component;
    double x, y, longestpath;
}pastures[150];

bool visited[150];
int connected[150][150], num, compcnt = 0;
double value[150][150], diameter[150];

double pathlength(int i, int j)
{
    return sqrt( (pastures[i].x - pastures[j].x) * (pastures[i].x - pastures[j].x)
                + (pastures[i].y - pastures[j].y) * (pastures[i].y - pastures[j].y) );
}

void floodfill(int node)
{
    if(visited[node])
        return;
    pastures[node].component = compcnt;
    visited[node] = true;
    for(int i = 0; i < num; ++i)
        if(connected[node][i] == 1)
            floodfill(i);
}

int main()
{
    ifstream fin("cowtour.in");
    ofstream fout("cowtour.out");
    fout.setf(ios::fixed);
    fout.precision(6);
    fin >> num;
    for(int i = 0; i < num; ++i)
        fin >> pastures[i].x >> pastures[i].y;
    string str;
    for(int i = 0; i < num; ++i)
    {
        fin >> str;
        for(int j = 0; j < num; ++j)
        {
            connected[i][j] = str[j] - '0';
            if(connected[i][j] == 1)
                value[i][j] = pathlength(i, j);
            else
                value[i][j] = 10000000;
        }
    }

    for(int k = 0; k < num; ++k)
        for(int i = 0; i < num; ++i)
            for(int j = 0; j < num; ++j)
                if(value[i][k] + value[k][j] < value[i][j])
                    value[i][j] = value[i][k] + value[k][j];

    for(int i = 0; i < num; ++i)
    {
        floodfill(i);
        compcnt++;
    }

    for(int i = 0; i < num; ++i)
    {
        double longestpath = 0;
        for(int j = 0; j < num; ++j)
            if(pastures[i].component == pastures[j].component && i != j)    //i != j is important!
                if(longestpath < value[i][j])
                    longestpath = value[i][j];
        pastures[i].longestpath = longestpath;
        if(diameter[pastures[i].component] < pastures[i].longestpath)
            diameter[pastures[i].component] = pastures[i].longestpath;
    }

    double ans = 10000000;
    for(int i = 0; i < num; ++i)
    {
        for(int j = 0; j < num; ++j)
        {
            if(pastures[i].component != pastures[j].component)
            {
                double dis = pathlength(i, j) + pastures[i].longestpath + pastures[j].longestpath;
                if(dis < diameter[pastures[i].component])
                    dis = diameter[pastures[i].component];
                if(dis < diameter[pastures[j].component])
                    dis = diameter[pastures[j].component];
                if(ans > dis)
                    ans = dis;
            }
        }
    }

    fout << ans << endl;
    return 0;
}
