/*
ID: mazhaoj1
PROG: betsy
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //���nocow�����ô�ѵĶ��������벻������

int n, nn, ans, dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool visited[9][9];

int getfree(int i, int j)
{
    int v = -1;     //���������dfs����ǰû��visited��Ϊtrue����v = -1�����dfs����ǰ����visitedΪtrue����v = 0
    for(int k = 0; k < 4; ++k)
        if(!visited[i + dir[k][0]][j + dir[k][1]])
            v++;
    return v;
}

void dfs(int i, int j, int cnt)
{
    int k, newi, newj, f, cntf = 0, ki, kj;
    if(i == n && j == 1)
    {
        if(cnt == nn)   //������жϷ���������Ż��ٶ�
            ans++;
        return;
    }
    //�Ż�1
    if(visited[i - 1][j] && visited[i + 1][j] && !visited[i][j - 1] && !visited[i][j + 1])
        return;
    if(!visited[i - 1][j] && !visited[i + 1][j] && visited[i][j - 1] && visited[i][j + 1])
        return;
    if(!visited[i - 1][j - 1] && visited[i - 1][j] && visited[i][j - 1])
        return;
    if(!visited[i - 1][j + 1] && visited[i - 1][j] && visited[i][j + 1])
        return;
    if(!visited[i + 1][j + 1] && visited[i + 1][j] && visited[i][j + 1])
        return;
    if(!visited[i + 1][j - 1] && visited[i + 1][j] && visited[i][j - 1])
        return;
    //�Ż�2
    for(k = 0; k < 4; ++k)
    {
        newi = i + dir[k][0];
        newj = j + dir[k][1];
        if(visited[newi][newj] || (newi == n && newj == 1))  //�������㱻��������Զ�޷�����Ŀ���ˡ�����
            continue;
        f = getfree(newi, newj);
        if(f < 2)
        {
            cntf++;
            ki = newi;
            kj = newj;
        }
    }
    if(cntf > 1)
        return;
    else
    {
        visited[i][j] = true;
        if(cntf == 1)
            dfs(ki, kj, cnt + 1);   //������dfs����ǰû��visited��Ϊtrue
        else
        {
            for(k = 0; k < 4; ++k)
            {
                newi = i + dir[k][0];
                newj = j + dir[k][1];
                if(!visited[newi][newj])    //������dfs����ǰû��visited��Ϊtrue
                    dfs(newi, newj, cnt + 1);
            }
        }
        visited[i][j] = false;
    }
}

int main()
{
    ifstream fin("betsy.in");
    ofstream fout("betsy.out");
    fin >> n;
    nn = n * n;
    for(int i = 0; i <= n + 1; ++i)
    {
        visited[0][i] = true;
        visited[i][0] = true;
        visited[n + 1][i] = true;
        visited[i][n + 1] = true;
    }
    dfs(1, 1, 1);
    fout << ans << endl;
    return 0;
}

