/*
ID: mazhaoj1
PROG: dualpal
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int func(int num, int base)
{
    char ch[30];
    int len = 0;
    while(num != 0)
    {
        ch[len] = num % base + '0';
        len++;
        num /= base;
    }
    int j, k;
    for(j = 0, k = len - 1; j < k; ++j, --k)
        if(ch[j] != ch[k])
            return 0;
    return 1;
}

int main()
{
    ofstream fout("dualpal.out");
    ifstream fin("dualpal.in");
    int n, s;
    fin >> n >> s;
    int found = 0, match;
    for(int i = s + 1; found < n; ++i)
    {
        match = 0;
        for(int j = 2; j <= 10 && match < 2; ++j)
            if(func(i, j))
                ++match;
        if(match == 2)
        {
            ++found;
            fout << i << endl;
        }
    }
    return 0;
}
