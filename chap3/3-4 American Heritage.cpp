/*
ID: mazhaoj1
PROG: heritage
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

char pre[27];
char in[27];
int preinpos[27];
int level[27];
int len, maxlevel;
ofstream fout("heritage.out");

void post(int rootlevel, int left, int right)
{
    if(left == right)
    {
        fout << in[left];
        return;
    }
    int i;
    for(i = left; i <= right; ++i)
        if(level[i] == rootlevel)
            break;
    if(i - 1 >= 0 && i - 1 >= left)     //这里的判断必须非常小心
        post(rootlevel + 1, left, i - 1);
    if(i + 1 < len && i + 1 <= right)
        post(rootlevel + 1, i + 1, right);
    fout << in[i];
}

int main()
{
    ifstream fin("heritage.in");
    fin.getline(in, 27);
    fin.getline(pre, 27);
    len = strlen(in);
    for(int i = 0; i < len; ++i)
    {
        for(int j = 0; j < len; ++j)
        {
            if(pre[i] == in[j])
            {
                preinpos[i] = j;
                break;
            }
        }
    }
    for(int i = 0; i < len; ++i)    //先求出每个节点所在的层次
    {
        int k = preinpos[i];
        for(int j = k - 1; j >= 0 && level[j] == level[k]; --j)
            level[j] = level[k] + 1;
        for(int j = k + 1; j < len && level[j] == level[k]; ++j)
            level[j] = level[k] + 1;
    }
    for(int i = 0; i < len; ++i)
        if(maxlevel < level[i])
            maxlevel = level[i];
    post(0, 0, len - 1);
    fout << endl;
    return 0;
}
