/*
ID: mazhaoj1
PROG: latin
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
[转]这道题直接搜索是不行的，剪枝可以包括：
1．对第一列也固定为1,2,3,…n，最后考虑到每种方案都可以通过把第二行到第n行重排得到，所以求得的方案数乘以(n-1)!就可以了。
2．最后一行可以不用搜，必定有解。
3. Maigo的超强剪枝：
  1 2 3 4 5
  2 1 4 5 3
  此时可以得到2个置换圈(1,2)(3,4,5)
  1 2 3 4 5
  2 3 1 5 4
  另一种情况，此时为(1,2,3)(4,5)
此时把后两列放在前3列之前，则其和第一种情况是等价的，而列的改变不影响解，所以它的解的个数和第一种情况相等。
这样，我们只需记录一次情况的解的个数，对于之后等价的情况，直接把记录的值加到总数里即可。
两个情况等价当且仅当置换圈的个数相同，且所有置换圈的长度排序后相等。可以用Hash来判断是否等价，
Hash[i,j]表示置换圈个数为i，所有置换圈长度的积为j时解的个数，则不会出现冲突。
*/

int n, table[8][8], mulsum, cntsum, circlelen, hash[8][50];
long long ans;
bool markrow[8][8], markcol[8][8], calced[8];

int searchh(int row, int col)
{
    int temp, result = 0;
    if(row == n)
        return 1;
    if(row == 3 && col == 2)    //这里计算所谓的第二行和第一行(1234567)的置换圈
    {
        memset(calced, false, sizeof(calced));
        cntsum = 0;
        mulsum = 1;
        for(int i = 1; i <= n; ++i)
        {
            if(calced[i])
                continue;
            calced[i] = true;
            circlelen = 1;
            for(int j = table[2][i]; j != i; j = table[2][j])
            {
                calced[j] = true;
                circlelen++;
            }
            cntsum++;
            mulsum *= circlelen;
        }
        if(hash[cntsum][mulsum] != 0)
            return hash[cntsum][mulsum];
    }
    for(int i = 1; i <= n; ++i)
    {
        if(markrow[row][i] || markcol[col][i])
            continue;
        temp = table[row][col];
        table[row][col] = i;
        markrow[row][i] = true;
        markcol[col][i] = true;
        if(col == n)
            result += searchh(row + 1, 2);
        else
            result += searchh(row, col + 1);
        markrow[row][i] = false;
        markcol[col][i] = false;
        table[row][col] = temp;
    }
    if(row == 3 && col == 2)
        hash[cntsum][mulsum] = result;
    return result;
}

int main()
{
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        table[1][i] = i;
        markrow[1][i] = true;
        markcol[i][i] = true;
        table[i][1] = i;
        markrow[i][i] = true;
        markcol[1][i] = true;
    }
    ans = searchh(2, 2);
    for(int i = n - 1; i >= 2; --i)
        ans *= i;
    fout << ans << endl;
    return 0;
}
