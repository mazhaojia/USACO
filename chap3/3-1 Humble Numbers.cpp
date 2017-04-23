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
不难发现，每个丑数都是之前求出的丑数与一个所给质数的积。
hum记录求得的丑数，pp记录所给质数。
为了求第i个丑数，每次用pp中的每个数和hum中的每个数相乘，其中最小的一个，且它大于第i-1个丑数，则这就是第i个丑数。
但这样做会超时。
我们发现，每个质数在和hum中的某个数k乘后，下次再乘k肯定不满足条件（大于第i-1个丑数），肯定是比k大的某个数。
用dex记录每个质数i上次所乘的质数在hum中的位置。
每次找最小值时，用pp[i]和hum[dex[i]]开始试乘，而不是从最头开始。
为了方便计算，将1作为第一个丑数。
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
