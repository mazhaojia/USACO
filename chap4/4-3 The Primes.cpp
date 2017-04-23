/*
ID: mazhaoj1
PROG: prime3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //¼ûÌâ½â http://dfs35123.spaces.live.com/blog/cns!A6CB032EC0980F16!274.entry

int total, first, bd[5][5], anscnt;
bool prime[100000];
char ans[10000][26];

bool isprime(int a, int b, int c, int d, int e)
{
    if(prime[a * 10000 + b * 1000 + c * 100 + d * 10 + e])
        return true;
    return false;
}

int cmp(const void* a, const void* b)
{
    char* c = (char*)a;
    char* d = (char*)b;
    return strcmp(c, d);
}

int main()
{
    ifstream fin("prime3.in");
    ofstream fout("prime3.out");
    fin >> total >> first;
    bd[0][0] = first;
    memset(prime, true, sizeof(prime));
    prime[0] = prime[1] = false;
    for(int i = 2; i < 100000; i += 1)
    {
        if(prime[i] == false)
            continue;
        for(int j = i + i; j < 100000; j += i)
            prime[j] = false;
    }
    int temp;
    for(int a = 0; a <= 9; ++a) //1
    {
        bd[1][1] = a;
        for(int b = 0; b <= 9; ++b) //2
        {
            bd[2][2] = b;
            for(int c = 0; c <= 9; ++c) //3
            {
                bd[3][3] = c;
                temp = total - bd[0][0] - bd[1][1] - bd[2][2] - bd[3][3];
                if(temp < 0 || temp > 9 || !isprime(bd[0][0], bd[1][1], bd[2][2], bd[3][3], temp))
                    continue;
                bd[4][4] = temp;    //4
                for(int d = 1; d <= 9; ++d) //5
                {
                    bd[4][0] = d;
                    for(int e = 0; e <= 9; ++e) //6
                    {
                        bd[3][1] = e;
                        for(int f = 0; f <= 9; ++f) //7
                        {
                            bd[1][3] = f;
                            temp = total - bd[4][0] - bd[3][1] - bd[2][2] - bd[1][3];
                            if(temp <= 0 || temp > 9 || !isprime(bd[4][0], bd[3][1], bd[2][2], bd[1][3], temp))
                                continue;
                            bd[0][4] = temp;    //8
                            for(int g = 1; g <= 9; ++g) //9
                            {
                                bd[2][0] = g;
                                for(int h = 0; h <= 9; ++h) //10
                                {
                                    bd[2][1] = h;
                                    for(int i = 0; i <= 9; ++i) //11
                                    {
                                        bd[2][3] = i;
                                        temp = total - bd[2][0] - bd[2][1] - bd[2][2] - bd[2][3];
                                        if(temp < 0 || temp > 9 || !isprime(bd[2][0], bd[2][1], bd[2][2], bd[2][3], temp))
                                            continue;
                                        bd[2][4] = temp;    //12
                                        for(int j = 1; j <= 9; ++j) //13
                                        {
                                            bd[1][0] = j;
                                            temp = total - bd[0][0] - bd[1][0] - bd[2][0] - bd[4][0];
                                            if(temp <= 0 || temp > 9 || !isprime(bd[0][0], bd[1][0], bd[2][0], temp, bd[4][0]))
                                                continue;
                                            bd[3][0] = temp;    //14
                                            for(int k = 0; k <= 9; ++k) //15
                                            {
                                                bd[1][4] = k;
                                                temp = total - bd[0][4] - bd[1][4] - bd[2][4] - bd[4][4];
                                                if(temp < 0 || temp > 9 || !isprime(bd[0][4], bd[1][4], bd[2][4], temp, bd[4][4]))
                                                    continue;
                                                bd[3][4] = temp;    //16
                                                temp = total - bd[1][0] - bd[1][1] - bd[1][3] - bd[1][4];
                                                if(temp < 0 || temp > 9 || !isprime(bd[1][0], bd[1][1], temp, bd[1][3], bd[1][4]))
                                                    continue;
                                                bd[1][2] = temp;    //17
                                                temp = total - bd[3][0] - bd[3][1] - bd[3][3] - bd[3][4];
                                                if(temp < 0 || temp > 9 || !isprime(bd[3][0], bd[3][1], temp, bd[3][3], bd[3][4]))
                                                    continue;
                                                bd[3][2] = temp;    //18
                                                for(int l = 1; l <= 9; ++l) //19
                                                {
                                                    bd[0][1] = l;
                                                    temp = total - bd[0][1] - bd[1][1] - bd[2][1] - bd[3][1];
                                                    if(temp < 0 || temp > 9 || !isprime(bd[0][1], bd[1][1], bd[2][1], bd[3][1], temp))
                                                        continue;
                                                    bd[4][1] = temp;    //20
                                                    for(int m = 1; m <= 9; ++m) //21
                                                    {
                                                        bd[0][2] = m;
                                                        temp = total - bd[0][2] - bd[1][2] - bd[2][2] - bd[3][2];
                                                        if(temp < 0 || temp > 9 || !isprime(bd[0][2], bd[1][2], bd[2][2], bd[3][2], temp))
                                                            continue;
                                                        bd[4][2] = temp;    //22
                                                        temp = total - bd[0][0] - bd[0][1] - bd[0][2] - bd[0][4];
                                                        if(temp <= 0 || temp > 9 || !isprime(bd[0][0], bd[0][1], bd[0][2], temp, bd[0][4]))
                                                            continue;
                                                        bd[0][3] = temp;    //23
                                                        temp = total - bd[0][3] - bd[1][3] - bd[2][3] - bd[3][3];
                                                        if(temp < 0 || temp > 9 || !isprime(bd[0][3], bd[1][3], bd[2][3], bd[3][3], temp))
                                                            continue;
                                                        if(temp != total - bd[4][0] - bd[4][1] - bd[4][2] - bd[4][4])
                                                            continue;
                                                        if(!isprime(bd[4][0], bd[4][1], bd[4][2], temp, bd[4][4]))
                                                            continue;
                                                        bd[4][3] = temp;    //24
                                                        for(int n = 0; n < 5; ++n)
                                                            for(int o = 0; o < 5; ++o)
                                                                ans[anscnt][n * 5 + o] = bd[n][o] + '0';
                                                        ans[anscnt][25] = '\0';
                                                        anscnt++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    qsort(ans, anscnt, sizeof(ans[0]), cmp);
    for(int j = 0; j < 5; ++j)
    {
        for(int k = 0; k < 5; ++k)
            fout << ans[0][j * 5 + k];
        fout << endl;
    }
    for(int i = 1; i < anscnt; ++i)
    {
        fout << endl;
        for(int j = 0; j < 5; ++j)
        {
            for(int k = 0; k < 5; ++k)
                fout << ans[i][j * 5 + k];
            fout << endl;
        }
    }
    return 0;
}
