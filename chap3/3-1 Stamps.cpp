/*
ID: mazhaoj1
PROG: stamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int value[2000001];

int main()
{
    ifstream fin("stamps.in");
    ofstream fout("stamps.out");
    int k, n, type[50];
    fin >> k >> n;
    int i;
    for(i = 0; i < n; ++i)
        fin >> type[i];
    for(i = 1; i <= 2000000; ++i)
    {
        int min = 2000000;
        for(int j = 0; j < n; ++j)
            if(i - type[j] >= 0 && min > value[i - type[j]] + 1)
                min = value[i - type[j]] + 1;
        if(min > k)
            break;
        value[i] = min;
    }
    fout << i - 1 << endl;
    return 0;
}
