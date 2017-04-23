/*
ID: mazhaoj1
PROG: humble
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <climits>
using namespace std;

/*
���ѷ��֣�ÿ����������֮ǰ����ĳ�����һ�����������Ļ���
hum��¼��õĳ�����pp��¼����������
Ϊ�����i��������ÿ����pp�е�ÿ������hum�е�ÿ������ˣ�������С��һ�����������ڵ�i-1��������������ǵ�i��������
���������ᳬʱ��
���Ƿ��֣�ÿ�������ں�hum�е�ĳ����k�˺��´��ٳ�k�϶����������������ڵ�i-1�����������϶��Ǳ�k���ĳ������
��dex��¼ÿ������i�ϴ����˵�������hum�е�λ�á�
ÿ������Сֵʱ����pp[i]��hum[dex[i]]��ʼ�Գˣ������Ǵ���ͷ��ʼ��
Ϊ�˷�����㣬��1��Ϊ��һ��������
*/

int main()
{
    ifstream fin("humble.in");
    ofstream fout("humble.out");
    int k, n, humble[100000], prime[100], cnt, last[100];
    fin >> k >> n;
    for(int i = 0; i < k; ++i)
        fin >> prime[i];
    humble[0] = 1;
    cnt = 1;
    memset(last, 0, sizeof(last));
    while(cnt <= n)
    {
        int minm = INT_MAX, temp;
        for(int i = 0; i < k; ++i)
        {
            temp = prime[i] * humble[last[i]];
            while(temp <= humble[cnt - 1])
            {
                ++last[i];
                temp = prime[i] * humble[last[i]];
            }
            if(minm > temp)
                minm = temp;
        }
        humble[cnt++] = minm;
    }
    fout << humble[n] << endl;
    return 0;
}
