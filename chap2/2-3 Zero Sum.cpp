/*
ID: mazhaoj1
PROG: zerosum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

int n, cnt = -1;
char num[19];
ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

void calc()
{
    int sum = num[1] - '0';
    int i = 2;
    while(num[i] == ' ')
    {
        sum = sum * 10 + num[i + 1] - '0';
        i += 2;
    }
    for(; i <= cnt; i += 2)
    {
        if(num[i] == '+' || num[i] == '-')
        {
            int follow = num[i + 1] - '0';
            int k = i + 2;
            while(num[k] == ' ')
            {
                follow = follow * 10 + num[k + 1] - '0';
                k += 2;
            }
            if(num[i] == '+')
                sum += follow;
            else
                sum -= follow;
            i = k - 2;
        }
    }
    if(sum == 0)
    {
        for(int i = 1; i <= cnt; ++i)
            fout << num[i];
        fout << endl;
    }
}

void solve(int pos)
{
    if(pos == cnt)
    {
        calc();
        return;
    }
    num[pos + 1] = ' ';
    solve(pos + 2);
    num[pos + 1] = '+';
    solve(pos + 2);
    num[pos + 1] = '-';
    solve(pos + 2);
    num[pos + 1] = 0;
}

int main()
{
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        cnt += 2;
        num[cnt] = '0' + i;
    }
    solve(1);
    return 0;
}
