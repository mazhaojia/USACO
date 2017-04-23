/*
ID: mazhaoj1
PROG: shuttle
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //貌似USACO的analysis很精妙

struct node
{
    char board[26];
    int pre, bpos, move;
    void operator = (node& nd)
    {
        strcpy(board, nd.board);
        pre = nd.pre;
        bpos = nd.bpos;
        move = nd.move;
    }
}qu[1 << 18], p, q; //1 << 18 只能在不超出内存的情况下粗略估计了。。
char dest[26], start[26];
int num, front, end, ans[1 << 9], anscnt;

int main()
{
    ifstream fin("shuttle.in");
    ofstream fout("shuttle.out");
    fin >> num;
    for(int i = 0; i < num; ++i)
    {
        start[i] = 'W';
        dest[i] = 'B';
    }
    dest[num] = start[num] = ' ';
    for(int i = num + 1; i < num * 2 + 1; ++i)
    {
        start[i] = 'B';
        dest[i] = 'W';
    }
    strcpy(qu[end].board, start);
    qu[end].bpos = num;
    qu[end].move = -1;
    qu[end].pre = -1;
    end++;
    num = 2 * num + 1;
    while(front != end)
    {
        p = qu[front++];
        if(strcmp(p.board, dest) == 0)
        {
            while(p.pre != -1)
            {
                ans[anscnt++] = p.move;
                p = qu[p.pre];
            }
            break;
        }
        else
        {
            if(p.bpos - 2 >= 0 && p.board[p.bpos - 1] == 'B' && p.board[p.bpos - 2] == 'W')
            {
                q = p;
                q.board[q.bpos - 2] = ' ';
                q.board[q.bpos] = 'W';
                q.bpos -= 2;
                q.move = p.bpos - 1;
                q.pre = front - 1;
                qu[end++] = q;
            }
            if(p.bpos - 1 >= 0 && p.board[p.bpos - 1] == 'W')
            {
                q = p;
                q.board[q.bpos - 1] = ' ';
                q.board[q.bpos] = 'W';
                q.bpos--;
                q.move = p.bpos;
                q.pre = front - 1;
                qu[end++] = q;
            }
            if(p.bpos + 1 < num && p.board[p.bpos + 1] == 'B')
            {
                q = p;
                q.board[q.bpos + 1] = ' ';
                q.board[q.bpos] = 'B';
                q.bpos++;
                q.move = p.bpos + 2;
                q.pre = front - 1;
                qu[end++] = q;
            }
            if(p.bpos + 2 < num && p.board[p.bpos + 1] == 'W' && p.board[p.bpos + 2] == 'B')
            {
                q = p;
                q.board[q.bpos + 2] = ' ';
                q.board[q.bpos] = 'B';
                q.bpos += 2;
                q.move = p.bpos + 3;
                q.pre = front - 1;
                qu[end++] = q;
            }
        }
    }
    int temp;
    for(int i = 0, j = anscnt - 1; i < j; ++i, --j)
    {
        temp = ans[i];
        ans[i] = ans[j];
        ans[j] = temp;
    }
    int lines = anscnt / 20;
    for(int i = 0; i < lines; ++i)
    {
        for(int j = 0; j < 19; ++j)
            fout << ans[i * 20 + j] << ' ';
        fout << ans[i * 20 + 19] << endl;
    }
    if(anscnt % 20 != 0)
    {
        for(int i = lines * 20; i < anscnt - 1; ++i)
            fout << ans[i] << ' ';
        fout << ans[anscnt - 1] << endl;
    }
    return 0;
}
