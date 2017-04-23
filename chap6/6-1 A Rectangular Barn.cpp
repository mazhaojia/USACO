/*
ID: mazhaoj1
PROG: rectbarn
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
�������ڸ�����������Σ��Ͳ�����big barn����dp�ˡ�
�뿴�����Ҽ�ѵ��2003���ļ���"<��֪����ǳ̸�ü���˼��������Ӿ�������>"
����ƪ������ָ���ϰ��ǵ㣬������ϰ�ȷʵһ��1*1�ľ��Σ�����ֻ��ȡ���µ�˼�룬��������Ҫ���Ρ�
��������α��ε��뿴nocow��
*/

#define maxn 3001
bool field[3001][3001];
int row, col, ans, temp;
int height[2][3001], leftt[2][3001], rightt[2][3001], stepl[3001], stepr[3002]; //ע�������3002

int main()
{
    ifstream fin("rectbarn.in");
    ofstream fout("rectbarn.out");
    int r, c, p, now = 0, last = 1;
    fin >> row >> col >> p;
    if(p == 0)
    {
        fout << row * col << endl;
        return 0;
    }
    while(p--)
    {
        fin >> r >> c;
        field[r][c] = true;
    }
    for(int i = 1; i <= col; ++i)
        leftt[0][i] = rightt[0][i] = maxn;  //û�������ʼ�����ڶ�����wa
    for(int i = 1; i <= row; ++i)
    {
        now ^= now;
        last ^= last;
        for(int j = 1; j <= col; ++j)
        {
            if(field[i][j])
                stepl[j] = 0;
            else
                stepl[j] = stepl[j - 1] + 1;
        }
        for(int j = col; j >= 1; --j)
        {
            if(field[i][j])
                stepr[j] = 0;
            else
                stepr[j] = stepr[j + 1] + 1;
        }
        for(int j = 1; j <= col; ++j)
        {
            if(field[i][j])
            {
                leftt[now][j] = rightt[now][j] = maxn;
                height[now][j] = 0;
            }
            else
            {
                leftt[now][j] = min(leftt[last][j], stepl[j]);
                rightt[now][j] = min(rightt[last][j], stepr[j]);
                height[now][j] = height[last][j] + 1;
                temp = height[now][j] * (leftt[now][j] + rightt[now][j] - 1);
                if(ans < temp)
                    ans = temp;
            }
        }
    }
    fout << ans << endl;
    return 0;
}
