/*
ID: mazhaoj1
PROG: fracdec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int main()  //这题比较烦，要找规律，先有余数再余数*10再有商的。。。
{
    ifstream fin("fracdec.in");
    ofstream fout("fracdec.out");
    int divider, divident, result, remainder, cnt = 0, scnt = 0, loop = -1, record[100001];
    char ans[1000001], small[100001];
    bool visited[100001];
    memset(visited, false, sizeof(visited));
    fin >> divider >> divident;
    result = divider / divident;
    int digit;
    for(digit = 1; digit * 10 <= result; digit *= 10);
    while(result >= 10)
    {
        int temp = result / digit;
        ans[cnt++] = temp + '0';
        result = result % digit;
        digit /= 10;
    }
    ans[cnt++] = result + '0';
    remainder = divider % divident;
    ans[cnt++] = '.';
    if(remainder == 0)
        ans[cnt++] = '0';
    int temp;
    visited[remainder] = true;
    while(remainder != 0)
    {
        divider = remainder * 10;
        temp = divider / divident;
        remainder = divider % divident;
        small[scnt] = temp + '0';
        record[scnt] = remainder;
        scnt++;
        if(visited[remainder])
        {
            loop = scnt - 1;
            break;
        }
        visited[remainder] = true;
    }
    if(loop != -1)
    {
        int pos = loop - 1;
        while(pos >= 0 && record[pos] != record[loop])
            pos--;
        for(int i = 0; i <= pos; ++i)
            ans[cnt++] = small[i];
        ans[cnt++] = '(';
        for(int i = pos + 1; i <= loop; ++i)
            ans[cnt++] = small[i];
        ans[cnt++] = ')';
    }
    else
        for(int i = 0; i < scnt; ++i)
            ans[cnt++] = small[i];
    int lines = cnt / 76;
    int cols = cnt % 76;
    if(lines == 0)
    {
        for(int i = 0; i < cols; ++i)
            fout << ans[i];
        fout << endl;
    }
    else
    {
        int k = 0;
        for(int i = 0; i < lines; ++i)
        {
            for(int j = 0; j < 76; ++j)
                fout << ans[k++];
            fout << endl;
        }
        for(int j = 0; j < cols; ++j)
            fout << ans[k++];
        fout << endl;
    }
    return 0;
}
