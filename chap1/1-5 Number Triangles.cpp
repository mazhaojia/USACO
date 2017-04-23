/*
ID: mazhaoj1
PROG: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int tri[1000][1000];
int maxtri[1000][1000];

int main()
{
    ofstream fout ("numtri.out");
    ifstream fin ("numtri.in");
    int num;
    fin >> num;
    for(int i = 0; i < num; ++i)
        for(int j = 0; j <= i; ++j)
            fin >> tri[i][j];
    for(int i = 0; i < num; ++i)
        maxtri[num - 1][i] = tri[num - 1][i];
    for(int i = num - 2; i >= 0; --i)
        for(int j = 0; j <= i; ++j)
            maxtri[i][j] = (maxtri[i + 1][j] > maxtri[i + 1][j + 1] ? maxtri[i + 1][j] : maxtri[i + 1][j + 1]) + tri[i][j];
    fout << maxtri[0][0] << endl;
    return 0;
}
