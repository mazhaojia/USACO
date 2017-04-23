/*
ID: mazhaoj1
PROG: preface
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

//The USACO analysis page gives some other very clever solutions!

int main()
{
    ofstream fout("preface.out");
    ifstream fin("preface.in");
    int n, cnt = 0, num, C, D, I, L, M, V, X;
    char ans[30 * 3500];
    fin >> n;
    for(int a = 1; a <= n; ++a)
    {
        int b = a;
        num = b / 1000;
        if(num > 0)
        {
            for(int i = 0; i < num; ++i)
                ans[cnt++] = 'M';
            b = b - 1000 * num;
        }
        num = b / 100;
        if(num > 0)
        {
            if(num <= 3)
                for(int i = 0; i < num; ++i)
                    ans[cnt++] = 'C';
            else if(num <= 5)
            {
                for(int i = 0; i < 5 - num; ++i)
                    ans[cnt++] = 'C';
                ans[cnt++] = 'D';
            }
            else if(num <= 8)
            {
                ans[cnt++] = 'D';
                for(int i = 5; i < num; ++i)
                    ans[cnt++] = 'C';
            }
            else if(num == 9)
            {
                ans[cnt++] = 'C';
                ans[cnt++] = 'M';
            }
            b = b - 100 * num;
        }
        num = b / 10;
        if(num > 0)
        {
            if(num <= 3)
                for(int i = 0; i < num; ++i)
                    ans[cnt++] = 'X';
            else if(num <= 5)
            {
                for(int i = 0; i < 5 - num; ++i)
                    ans[cnt++] = 'X';
                ans[cnt++] = 'L';
            }
            else if(num <= 8)
            {
                ans[cnt++] = 'L';
                for(int i = 5; i < num; ++i)
                    ans[cnt++] = 'X';
            }
            else if(num == 9)
            {
                ans[cnt++] = 'X';
                ans[cnt++] = 'C';
            }
            b = b - 10 * num;
        }
        num = b;
        if(num > 0)
        {
            if(num <= 3)
                for(int i = 0; i < num; ++i)
                    ans[cnt++] = 'I';
            else if(num <= 5)
            {
                for(int i = 0; i < 5 - num; ++i)
                    ans[cnt++] = 'I';
                ans[cnt++] = 'V';
            }
            else if(num <= 8)
            {
                ans[cnt++] = 'V';
                for(int i = 5; i < num; ++i)
                    ans[cnt++] = 'I';
            }
            else if(num == 9)
            {
                ans[cnt++] = 'I';
                ans[cnt++] = 'X';
            }
        }
    }
    C = D = I = L = M = V = X = 0;
    for(int i = 0; i < cnt; ++i)
    {
        if(ans[i] == 'C')
            C++;
        else if(ans[i] == 'D')
            D++;
        else if(ans[i] == 'I')
            I++;
        else if(ans[i] == 'L')
            L++;
        else if(ans[i] == 'M')
            M++;
        else if(ans[i] == 'V')
            V++;
        else if(ans[i] == 'X')
            X++;
    }
    if(I > 0)
        fout << "I " << I << endl;
    if(V > 0)
        fout << "V " << V << endl;
    if(X > 0)
        fout << "X " << X << endl;
    if(L > 0)
        fout << "L " << L << endl;
    if(C > 0)
        fout << "C " << C << endl;
    if(D > 0)
        fout << "D " << D << endl;
    if(M > 0)
        fout << "M " << M << endl;
    return 0;
}
