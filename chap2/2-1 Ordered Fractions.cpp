/*
ID: mazhaoj1
PROG: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

//there exists another super fast solution, please see the analysis webpage in USACO.
int arr[161][161];
int n, anscnt;
struct answer
{
    int a, b;
    double value;
}ans[160 * 160];

int cmp(const void* a, const void* b)
{
    answer* one = (answer*)a;
    answer* two = (answer*)b;
    if(one->value - two->value > 0.00001)
        return 1;
    else
        return -1;
}

int main()
{
    ofstream fout("frac1.out");
    ifstream fin("frac1.in");
    fin >> n;
    int m = n - 1, temp1, temp2;
    for(int i = 1; i <= m; ++i)
    {
        for(int j = i + 1; j <= n; ++j)
        {
            if(arr[i][j] != 1)
            {
                arr[i][j] = 1;
                ans[anscnt].a = i;
                ans[anscnt].b = j;
                ans[anscnt].value = i / (double)j;
                ++anscnt;
                temp1 = i + i;
                temp2 = j + j;
                while(temp1 <= n && temp2 <= n)
                {
                    arr[temp1][temp2] = 1;
                    temp1 += i;
                    temp2 += j;
                }
            }
        }
    }
    qsort(ans, anscnt, sizeof(ans[0]), cmp);
    fout << "0/1" << endl;
    for(int i = 0; i < anscnt; ++i)
        fout << ans[i].a << '/' << ans[i].b << endl;
    fout << "1/1" << endl;
    return 0;
}
