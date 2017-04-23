/*
ID: mazhaoj1
PROG: tour
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

/*�����ǽ����google���Լ������:
�ѷ��ص�·�߷�����ô���൱���������˷ֱ����㵽�յ�������У���ô����·�߾ͱ�����������ཻ�Ĵ���㵽�յ��·�ߡ�
��f[i,j]Ϊ�ٶ��ļ������ˣ����ߵ���i�����У����ߵ���j������ʱ�������߹��ĳ�����Ŀ�ĺ͡����ʼ״̬f[1,1] = 1
�������ң����֪f[i,j]��f[j,i]�ȼۡ��������ǿ���ֻ����f[i,j]��
����(i,j)����ʲô���У�Ҫôi>j��Ҫôj>i,���i>j,��ô����i,j�ɵ�j>i�����Կ���ֻ��עj>i�������
����״̬(i,j){i<j}����ֻ�����Ǵ�(i,k){k<j}��k����j�õ�
1�����i<k����ô״̬(i,j)���Դ�(i,k){i<k<j}��k����j�õ�����f[i,j] = f[i,k] + 1
2�����k<i,��ô������i<j��ǰ���������������ǿ����Ƚ���i,k��Ȼ��״̬(i,j)���Դ�(k,i)��k����j�õ�(j,i)���ٽ���i,j�õ�,
   ��f[i,j] = f[k,i] + 1
����״̬ת�Ʒ����ǣ�dp[i,j]=dp[j,i]=max{dp[i,k]+1(k,j�ɴ���i<k<j), dp[k][i]+1(k,j�ɴ���k<i)}��
Ϊ�����2�е�f[k,i]��������1�����f[i,k]��������f[k,i] = f[i,k]��������Կ����롣
����״̬ת�Ʒ����е�dp[k][i]��dp[i,k]��һ���ˡ�
�������յ�״̬ת�Ʒ����ǣ�dp[i,j]=dp[j][i]=max{dp[i,k]+1(k,j�ɴ���k<j, k = 1 �� n)}��
�������и�֪�����ߵ��յ���ܷ��أ�������һ����max{f[i,N]}(i��N���ڷɻ�����)��
*/

string name[100], temp1, temp2;     //ע���������ֺ�������пո�����������string��ֱ��
bool flight[100][100];
int namecnt, flightcnt, s, d, ct, dp[100][100], maxi;

int main()
{
    ifstream fin("tour.in");
    ofstream fout("tour.out");
    fin >> namecnt >> flightcnt;
    for(int i = 0; i < namecnt; ++i)
        fin >> name[i];
    for(int i = 0; i < flightcnt; ++i)
    {
        fin >> temp1 >> temp2;
        ct = 0;
        for(int j = 0; j < namecnt; ++j)
        {
            if(temp1 == name[j])
            {
                s = j;
                ct++;
            }
            if(temp2 == name[j])
            {
                d = j;
                ct++;
            }
            if(ct == 2)
                break;
        }
        flight[s][d] = flight[d][s] = true;
    }
    dp[0][0] = 1;
    for(int i = 0; i < namecnt; ++i)
    {
        for(int j = i + 1; j < namecnt; ++j)
        {
            for(int k = 0; k < j; ++k)
                if(flight[k][j] && dp[i][k] > 0 && dp[i][j] < dp[i][k] + 1) //dp[i][k] > 0ע�⣬��Ϊ���ʾ�޽�����
                    dp[i][j] = dp[i][k] + 1;
            dp[j][i] = dp[i][j];
        }
    }
    for(int i = 0; i < namecnt - 1; ++i)
        if(flight[i][namecnt - 1] && maxi < dp[i][namecnt - 1])
            maxi = dp[i][namecnt - 1];
    if(maxi == 0)   //�޽⣬��ֻ��Դ��ɴ�
        maxi++;
    fout << maxi << endl;
    return 0;
}
