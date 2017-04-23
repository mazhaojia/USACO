/*
ID: mazhaoj1
PROG: rockers
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;    //there is a dp solution!

int n, t, m, song[20], disk[20], ans, recorded;

void solve(int depth, int lastdisk)    //i copyed this search idea..... this is what i need to learn
{
    if(depth == n)
    {
        if(ans < recorded)
            ans = recorded;
        return;
    }
    if(recorded + n - depth <= ans)     //����������еĸ��������ϻ�������ֵС����֦
        return;
    for(int i = lastdisk; i < m; ++i)
    {
        if(disk[i] >= song[depth])
        {
            disk[i] -= song[depth];
            recorded++;
            solve(depth + 1, i);     //�����ǰ������Ҫ��¼����ֻ����ڵ�һ����װ���µĹ����ϡ�
            recorded--;
            disk[i] += song[depth];
            break;
        }
    }
    solve(depth + 1, lastdisk);     // ���̵�ǰ����
}

int main()
{
    ifstream fin("rockers.in");
    ofstream fout("rockers.out");
    fin >> n >> t >> m;
    for(int i = 0; i < n; ++i)
        fin >> song[i];
    for(int i = 0; i < m; ++i)
        disk[i] = t;
    solve(0, 0);
    fout << ans << endl;
    return 0;
}
