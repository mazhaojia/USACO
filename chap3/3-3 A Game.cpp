/*
ID: mazhaoj1
PROG: game1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

/*��sum(s,t)Ϊ����s,t�е�����֮�ͣ�gain(s,t)Ϊ�����Ų����ܻ�õ����÷֣���ô�����������ֵķ�ʽ��
1.ȡs�����������������(s+1,t)�����ֵ����潫��gain(s+1,t);
2.����ȡt�����������������(s,t-1)�����ֵ����潫��gain(s,t-1);
������Σ�����÷���sum(s,t)-���ֵ÷֣��Ӷ���
gain(s,t)=sum(s,t)-min{gain(s+1,t),gain(s,t-1)}. */

int main()
{
    ifstream fin("game1.in");
    ofstream fout("game1.out");
    int score[101][101];
    int sum[101];
    memset(score, 0, sizeof(score));
    memset(sum, 0, sizeof(sum));
    int n;
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        fin >> score[i][i];
        sum[i] = sum[i - 1] + score[i][i];
    }
    for(int i = 2; i <= n; ++i)
        for(int j = 1; j <= n - i + 1; ++j)
            score[j][j + i - 1] = sum[j + i - 1] - sum[j - 1] - min(score[j + 1][j + i - 1], score[j][j + i - 2]);
    fout << score[1][n] << ' ' << sum[n] - score[1][n] << endl;
    return 0;
}
