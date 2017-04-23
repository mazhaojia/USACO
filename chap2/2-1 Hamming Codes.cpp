/*
ID: mazhaoj1
PROG: hamming
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ofstream fout("hamming.out");
    ifstream fin("hamming.in");
    int n, b, d;
    fin >> n >> b >> d;
    int count = (1 << b) - 1;
    int ans[64], anscnt = 1, i, j;
    ans[0] = 0;
    for(i = 1; i <= count && anscnt < n; ++i)
    {
        for(j = 0; j < anscnt; ++j)
        {
            int r = i ^ ans[j];
            int dis = 0;
            while(r != 0)
            {
                if(r & 1)
                    dis++;
                r >>= 1;
            }
            if(dis < d)
                break;
        }
        if(j == anscnt)
            ans[anscnt++] = i;
    }
    for(i = 0; i < anscnt / 10; ++i)
    {
        for(j = 0; j < 9; ++j)
            fout << ans[i * 10 + j] << ' ';
        fout << ans[i * 10 + j] << endl;
    }
    for(j = 0; j < anscnt % 10 - 1; ++j)
        fout << ans[i * 10 + j] << ' ';
    if(anscnt % 10 > 0)
        fout << ans[i * 10 + j] << endl;
    return 0;
}
