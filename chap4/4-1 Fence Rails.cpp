/*
ID: mazhaoj1
PROG: fence8
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

/*
1����rail��������board��Ϊboardsum��ֻ��ȡ����i��rail��ʹ��railsum[i]<=boardsum && railsum[i+1]>boardsum
2�������������������i��rail�����꣬��ֱ�ӽ���dfsid������ʱ��board��rail�������ȽϿ졣
3����¼��ǰi����һ�ε�������i+1ʱ��ѡ���ĸ�board����Ϊb�����rail[i] == rail[i+1]�������rail[i]ֱ�Ӵ�b��ʼѡboard��
4����ǰi��rail�ĺ�Ϊrailsum����boardsum-railsumΪ�����ʣ�µķ��ϵ����ֵmaxwaste����searchʱ����ÿ��boardʣ��ķ����ܺͣ���
   �ܺʹ���maxwaste�����֦(�ؼ���)��
*/

int n, r, board[50], rail[1023], i;
int boardsum, railsum, rcnt, cuted, maxwaste;
int lastboard[1023], startdepth, nowwaste;
bool found;

void dfsid(int depth)
{
    int i = 0;
    if(depth == -1)
    {
        if(cuted == startdepth + 1)
            found = true;
        return;
    }
    if(found)
        return;
    if(depth < startdepth && rail[depth] == rail[depth + 1])
        i = lastboard[depth + 1];
    for(; i < n; ++i)
    {
        if(board[i] >= rail[depth])
        {
            lastboard[depth] = i;
            board[i] -= rail[depth];
            if(board[i] < rail[0])
            {
                nowwaste += board[i];
                if(nowwaste > maxwaste)
                {
                    nowwaste -= board[i];
                    board[i] += rail[depth];
                    continue;
                }
            }
            cuted++;
            dfsid(depth - 1);
            cuted--;
            if(board[i] < rail[0])
                nowwaste -= board[i];
            board[i] += rail[depth];
        }
    }
}

int main()
{
    ifstream fin("fence8.in");
    ofstream fout("fence8.out");
    fin >> n;
    for(i = 0; i < n; ++i)
    {
        fin >> board[i];
        boardsum += board[i];
    }
    sort(board, board + n);
    fin >> r;
    for(i = 0 ; i < r; ++i)
        fin >> rail[i];
    sort(rail, rail + r);
    for(i = 0; i < r; ++i)
    {
        if(railsum + rail[i] > boardsum)
            break;
        railsum += rail[i];
    }
    rcnt = i;
    for(startdepth = rcnt - 1; startdepth >= 0; --startdepth)
    {
        maxwaste = boardsum - railsum;
        dfsid(startdepth);
        if(found)
            break;
        railsum -= rail[i];
    }
    fout << startdepth + 1 << endl;
    return 0;
}
