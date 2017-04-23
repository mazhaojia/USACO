/*
ID: mazhaoj1
PROG: buylow
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
��̬�滮�⣬������½��������⡣��һ�ʿ�����O(N^2)���㷨�����
s[i]Ϊ�����е�i���ֵ��MaxLength[i]Ϊ�Ե�i��Ϊĩβ����½����г��ȡ�
״̬ת�Ʒ���Ϊ
MaxLength[i]=max{MaxLength[j]}+1 (j=1..i-1 and s[j]>s[i])
��ʼ����
MaxLength[1]=1
���ڵڶ�������½����е�����������ͨ�����һ�ʵĹ��̽������MaxCnt[i]Ϊ��i��Ϊĩβ����½����еĸ�����
�������е�j(1��j��i-1)�����(s[j]>s[i] ���� MaxLength[j]+1>MaxLength[i])��MaxCnt[i]=MaxCnt[j]���������(MaxLength[j]+1==MaxLength[i])�����üӷ�ԭ��MaxCnt[i]=MaxCnt[i]+MaxCnt[j]��
���ǵ���Ŀ��˵�Ĳ������ظ������У����ǿ�������һ����Next[i]��ʾ����i����i�����Next[i]ʹ�õ�Next[i]�������i������ͬ���������������������Next[i]=0������������DP��ʱ���������Next[i]��Ϊ0��Next[j]<i��ֱ��������
��������ݹ�ģ�ܴ���Ҫ�õ��߾��ȼ��㣬����ֻ�Ǽӷ���
zma������������ַ�������߾����ˡ�������
*/

ofstream fout("buylow.out");

struct bignum
{
    char c[100];
    int cnt;
    bignum()
    {
        cnt = 1;
        memset(c, '0', sizeof(c));
        c[0] = '1';
    }
    bignum& operator = (bignum num)
    {
        cnt = num.cnt;
        memcpy(c, num.c, sizeof(char) * cnt);
        return *this;
    }
    bignum& operator + (bignum num)
    {
        int len = cnt < num.cnt ? cnt : num.cnt;
        int a, b, inc = 0, sum;
        for(int i = 0; i < len; ++i)
        {
            a = c[i] - '0';
            b = num.c[i] - '0';
            sum = a + b + inc;
            inc = 0;
            if(sum > 9)
            {
                inc = 1;
                sum -= 10;
            }
            c[i] = sum + '0';
        }
        if(cnt > len)
        {
            for(int i = len; i < cnt; ++i)
            {
                a = c[i] - '0';
                sum = a + inc;
                inc = 0;
                if(sum > 9)
                {
                    inc = 1;
                    sum -= 10;
                }
                c[i] = sum + '0';
            }
        }
        else if(num.cnt > len)
        {
            for(int i = len; i < num.cnt; ++i)
            {
                a = num.c[i] - '0';
                sum = a + inc;
                inc = 0;
                if(sum > 9)
                {
                    inc = 1;
                    sum -= 10;
                }
                c[i] = sum + '0';
            }
            cnt = num.cnt;
        }
        if(inc)
            c[cnt++] = '1';
        return *this;
    }
    void print()
    {
        int j;
        for(j = cnt - 1; j >= 0; --j)
            if(c[j] != '0')
                break;
        for(int i = j; i >= 0; --i)
            fout << c[i];
    }
}cnt[5001];

int main()
{
    ifstream fin("buylow.in");
    int n, price[5001], ans[5001], next[5001];
    fin >> n;
    for(int i = 0; i < n; ++i)
        fin >> price[i];
    price[n] = 0;   //�ڱ�������������ȷ���� 10 9 8 7 6 ... 1 ʱ�����Ϊ10�������
    for(int i = 0; i <= n; ++i)
    {
        ans[i] = 1;
        next[i] = -1;
        for(int j = i + 1; j < n; ++j)
        {
            if(price[i] == price[j])
            {
                next[i] = j;
                break;
            }
        }
    }
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            if(next[j] != -1 && next[j] < i)
                continue;
            if(price[j] > price[i])
            {
                if(ans[j] + 1 > ans[i])
                {
                    ans[i] = ans[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if(ans[j] + 1 == ans[i])   //�˴�������maxans��maxcnt����¼����Ϊcnt[i]��Ӵ��С��
                    cnt[i] = cnt[i] + cnt[j];
            }
        }
    }
    fout << ans[n] - 1 << ' ';
    cnt[n].print();
    fout << endl;
    return 0;
}

