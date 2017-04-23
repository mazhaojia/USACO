/*
ID: mazhaoj1
PROG: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int t3[1000];

struct two
{
    int ten, one;
}t2[100];

int len3 = 0, len2 = 0, len;
int num[10] = {0};
int input[10];
int i, ii, p = 0, part[2];

void generate3(int level)
{
    if(level == 3)
    {
        t3[len3] = p;
        ++len3;
        return;
    }
    for(int i = 0; i < len; ++i)
    {
        int temp = p;
        p = p * 10 + input[i];
        generate3(level + 1);
        p = temp;
    }
}

void generate2(int level)
{
    if(level == 0)
        for(i = 0; i < len; ++i)
            generate2(level + 1);
    else if(level == 1)
        for(ii = 0; ii < len; ++ii)
        {
            t2[len2].ten = input[i];
            t2[len2].one = input[ii];
            ++len2;
        }
}

int setpart(int i, int j, int index)
{
    if(index == 0)
        part[index] = t2[j].one * t3[i];
    else
        part[index] = t2[j].ten * t3[i];
    int product = part[index];
    if(product > 999 || product < 100)
        return 0;
    while(product != 0)
    {
        int temp = product % 10;
        if(num[temp] == 0)
            return 0;
        product /= 10;
    }
    return 1;
}

int setresult()
{
    int result = part[0] + part[1] * 10;
    if(result > 9999 || result < 1000)
        return 0;
    while(result != 0)
    {
        int temp = result % 10;
        if(num[temp] == 0)
            return 0;
        result /= 10;
    }
    return 1;
}

int main()
{
    ofstream fout ("crypt1.out");
    ifstream fin ("crypt1.in");
    fin>>len;
    for(int i = 0; i < len; ++i)
    {
        fin>>input[i];
        num[input[i]] = 1;
    }
    generate3(0);
    generate2(0);
    int sols = 0;
    for(int i = 0; i < len3; ++i)
        for(int j = 0; j < len2; ++j)
            if(setpart(i, j, 0) && setpart(i, j, 1) && setresult())
                ++sols;
    fout << sols << endl;
    return 0;
}
