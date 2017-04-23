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
1、对rail升序排序，board和为boardsum，只需取到第i个rail，使得railsum[i]<=boardsum && railsum[i+1]>boardsum
2、逆序迭代加深，如果对于i个rail能切完，则直接结束dfsid。迭代时对board和rail都降序会比较快。
3、记录当前i的上一次迭代，即i+1时是选的哪个board，设为b，如果rail[i] == rail[i+1]，则对于rail[i]直接从b开始选board。
4、若前i个rail的和为railsum，则boardsum-railsum为切完后剩下的废料的最大值maxwaste，则search时计算每块board剩余的废料总和，若
   总和大于maxwaste，则剪枝(关键！)。
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
