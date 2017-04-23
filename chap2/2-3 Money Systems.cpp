/*
ID: mazhaoj1
PROG: money
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ifstream fin("money.in");
    ofstream fout("money.out");
    int v, n;
    int types[26];
    long long ans[26][10001];
    memset(ans, 0, sizeof(ans));
    fin >> v >> n;
    for(int i = 1; i <= v; ++i)
        fin >> types[i];
    int j = types[1];
    while(j <= n)
    {
        ans[1][j] = 1;
        j += types[1];
    }
    for(int i = 2; i <= v; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            if(j > types[i])
                ans[i][j] = ans[i - 1][j] + ans[i][j - types[i]];
            else if(j == types[i])
                ans[i][j] = ans[i - 1][j] + 1;  //我就是不从0开始dp，我就是不从0开始dp！所以这里要判断
            else
                ans[i][j] = ans[i - 1][j];
        }
    }
    for(int i = 1; i <= v; ++i)
    {
        for(int j = 1; j <= n; ++j)
            cout << ans[i][j] << ' ';
        cout << endl;
    }
    fout << ans[v][n] << endl;
    return 0;
}
