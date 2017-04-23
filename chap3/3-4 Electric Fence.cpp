/*
ID: mazhaoj1
PROG: fence9
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

//line 1: y = (m/n)*x, line 2: y = m(x-p)/(n-p)
//line 1: x = (n/m)y,  line 2: x = [(n-p)*y + m*p]/m

int main()
{
    ifstream fin("fence9.in");
    ofstream fout("fence9.out");
    int n, m, p, sum = 0;
    fin >> n >> m >> p;
    for(int y = 1; y < m; ++y)
    {
        double line1x = (n/(double)m)*y;
        double line2x = ((n-p)*y + m*p)/(double)m;
        int pos1 = (int)(line1x) + 1, pos2 = (int)line2x;
        if(abs(line1x - pos1) <= 0.000001)
            pos1++;
        if(abs(line2x - pos2) <= 0.000001)
            pos2--;
        sum += abs(pos2 - pos1 + 1);
    }
    fout << sum << endl;
    return 0;
}
