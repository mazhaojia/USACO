/*
ID: mazhaoj1
PROG: spin
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

struct wedge
{
    int start, extent;
};

int speed[5], wedgescnt[5];
wedge wedges[5][5];

int check()
{
    int tmp[360];
    memset(tmp, 0, sizeof(tmp));
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < wedgescnt[i]; ++j)
            for(int k = 0; k <= wedges[i][j].extent; ++k)
                tmp[(wedges[i][j].start + k) % 360]++;
    for(int i = 0; i < 360; ++i)
        if(tmp[i] == 5)
            return 1;
    return 0;
}

int main()
{
    ifstream fin("spin.in");
    ofstream fout("spin.out");
    for(int i = 0; i < 5; ++i)
    {
        fin >> speed[i] >> wedgescnt[i];
        for(int j = 0; j < wedgescnt[i]; ++j)
            fin >> wedges[i][j].start >> wedges[i][j].extent;
    }
    for(int i = 0; i < 360; ++i)
    {
        if(check())
        {
            fout << i << endl;
            return 0;
        }
        for(int j = 0; j < 5; ++j)
            for(int k = 0; k < wedgescnt[j]; ++k)
                wedges[j][k].start = (wedges[j][k].start + speed[j]) % 360;
    }
    fout << "none" << endl;
    return 0;
}
