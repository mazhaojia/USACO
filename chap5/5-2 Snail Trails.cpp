/*
ID: mazhaoj1
PROG: snail
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //搞了半天没想到直接深搜就可以了。。。不知道这种题复杂度该怎么预测呢？

bool board[120][120];
bool visited[120][120];
int n, num, maxlen, temp;
char str[5];

//这个搜索也不是很easy啊
void dfs(int row, int col, int cnt, int dir)    //dir: 1 right, 2 down, 3 left, 4 up
{
    if(visited[row][col])
        return;
    visited[row][col] = true;
    cnt++;
    if(maxlen < cnt)
        maxlen = cnt;
    if(dir == 1)
    {
        if(col + 1 < n && board[row][col + 1] == false)
            dfs(row, col + 1, cnt, dir);
        else
        {
            if(row - 1 >= 0 && board[row - 1][col] == false)
                dfs(row - 1, col, cnt, 4);
            if(row + 1 < n && board[row + 1][col] == false)
                dfs(row + 1, col, cnt, 2);
        }
    }
    else if(dir == 2)
    {
        if(row + 1 < n && board[row + 1][col] == false)
            dfs(row + 1, col, cnt, dir);
        else
        {
            if(col - 1 >= 0 && board[row][col - 1] == false)
                dfs(row, col - 1, cnt, 3);
            if(col + 1 < n && board[row][col + 1] == false)
                dfs(row, col + 1, cnt, 1);
        }
    }
    else if(dir == 3)
    {
        if(col - 1 >= 0 && board[row][col - 1] == false)
            dfs(row, col - 1, cnt, dir);
        else
        {
            if(row - 1 >= 0 && board[row - 1][col] == false)
                dfs(row - 1, col, cnt, 4);
            if(row + 1 < n && board[row + 1][col] == false)
                dfs(row + 1, col, cnt, 2);
        }
    }
    else if(dir == 4)
    {
        if(row - 1 >= 0 && board[row - 1][col] == false)
            dfs(row - 1, col, cnt, dir);
        else
        {
            if(col - 1 >= 0 && board[row][col - 1] == false)
                dfs(row, col - 1, cnt, 3);
            if(col + 1 < n && board[row][col + 1] == false)
                dfs(row, col + 1, cnt, 1);
        }
    }
    visited[row][col] = false;
    cnt--;
}

int main()
{
    ifstream fin("snail.in");
    ofstream fout("snail.out");
    fin >> n >> num;
    fin.getline(str, 3);
    for(int i = 0; i < num; ++i)
    {
        fin.getline(str, 5);
        temp = atoi(str + 1);
        board[temp - 1][str[0] - 'A'] = true;
    }
    dfs(0, 0, 0, 1);
    memset(visited, false, sizeof(visited));
    dfs(0, 0, 0, 2);
    fout << maxlen << endl;
    return 0;
}
