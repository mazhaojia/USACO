/*
ID: mazhaoj1
PROG: nuggets
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;    //Ïê¼ûusacoµÄanalysis

int gcd(int a, int b)
{
    int t;
    if(a < b)
    {
        t = a;
        a = b;
        b = t;
    }
    while(b > 0)
    {
        t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main()
{
    ifstream fin("nuggets.in");
    ofstream fout("nuggets.out");
    int n, num[10], cnt = 0, temp, i, j, maxi = 0, maxi2 = 0;
    bool exist[257 * 257 + 257];
    memset(exist, false, sizeof(exist));
    fin >> n;
    for(i = 0; i < n; ++i)
    {
        fin >> temp;
        if(temp == 1)
        {
            fout << 0 << endl;
            return 0;
        }
        for(j = 0; j < cnt; ++j)
            if(temp % num[j] == 0)
                break;
        if(j == cnt)
        {
            num[cnt++] = temp;
            if(maxi < temp)
                maxi = temp;
        }
    }
    if(cnt == 1)
    {
        fout << 0 << endl;
        return 0;
    }
    for(int i = 0; i < cnt; ++i)
        if(maxi2 < num[i] && num[i] < maxi)
            maxi2 = num[i];
    temp = gcd(num[0], num[1]);
    for(int i = 2; i < cnt; ++i)
        temp = gcd(num[i], temp);
    if(temp > 1)
    {
        fout << 0 << endl;
        return 0;
    }
    maxi = maxi * maxi2 - maxi - maxi2;
    for(int i = 0; i <= maxi; ++i)
        for(int j = 0; j < cnt; ++j)
            if((i - num[j] > 0 && exist[i - num[j]] == true) || (i - num[j] == 0))
                exist[i] = true;
    for(int i = maxi; i >= 0; --i)
    {
        if(exist[i] == false)
        {
            fout << i << endl;
            break;
        }
    }
    return 0;
}
