/*
ID: mazhaoj1
PROG: range
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

/*  ���ᣬ����dp
dp�⡣��dp[i][j][m]��ʾ���Ͻ�Ϊ(i,j)���߳�Ϊm���������Ƿ���������ô
���dp[i][j][m]���������ҽ���dp[i][j][m-1],dp[i+1][j][m-1],dp[i][j+1][m-1],dp[i+1][j+1][m-1]��
������Ҳ��������(����ͼ�ͺ�������)���������Ǵ��ϵ��£�������ɨ��ÿ���㣬��ÿһ��i,j�ù�һ�Σ�
�Ͳ�����ʹ�ã�����ֻ���ö�ά���鱣��dp[i][j]�����ɡ�
ʱ�临�Ӷ�ΪO(n^3),�ռ临�Ӷ�ΪO(n^2)��analysis���и�ʱ�临�Ӷ�ΪO(n^2),�ռ�O(n)�Ľⷨ��
*/

int main()
{
    ifstream fin("range.in");
    ofstream fout("range.out");
    int n, cnt;
    char square[250][250];
    bool issquare[250][250];
    memset(issquare, false, sizeof(issquare));
    fin >> n;
    for(int i = 0 ; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            fin >> square[i][j];
            if(square[i][j] == '1')
                issquare[i][j] = true;
        }
    }
    for(int k = 2; k <= n; ++k)
    {
        cnt = 0;
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(i + k <= n && j + k <= n)
                {
                    issquare[i][j] = issquare[i][j] && issquare[i + 1][j]
                                    && issquare[i][j + 1] && issquare[i + 1][j + 1];
                    if(issquare[i][j])
                        cnt++;
                }
            }
        }
        if(cnt != 0)
            fout << k << ' ' << cnt << endl;
    }
    return 0;
}
