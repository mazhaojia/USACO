/*
ID: mazhaoj1
PROG: job
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
����ܾ��䣬�������ϴ����һ�����������ת����һƪ����ϸ�ķ�����
http://magicalcode.blogbus.com/logs/37193487.html
�������ʵĵط����ɲ��ձ����������֤����

����1����Ŀ��һ�ʣ��������Ž�Ĺ��죨�����������������ʱ�����磩
ÿ�ΰ�����������ӳ�+�ӹ�ʱ�����ٵĻ����ϡ�֤����ȡ��֤�����Ź�ȥһ���õ���һ�����Ž⡣

����2��
Ҫ֤��һ�����ʣ���������ͼ��ʾ������ͼ�����Ž⣬һ�������ҵ�һ��Ϊ���߸���Ϊ���ŵ������
1WWWWWWWAAAAAAA                BBBBBBBW
2WWWWAAAA                       BBBBBWWWWW
3WWWWWWWWWWWAAAAAAA             BBBB
4AAAAAAA             BBBBBBBWWWWWWWWW
�����ɡ����š������ʾ����ġ������š���ζ�Ŷ�����N����Ʒ������Ľ���ʱ��������ģ�����1�������ȡ N=1��2��k,���Թ���֤�������k�������Ĳ�Ʒ�����ȷ����ŷ����������硣��˲��ᷢ���ص�����
����������ת��Ϊ�����Ž���������⡣

����3��
����������a[n],b[n], a[n]���������У�b[n]���������У�������c[i] = a[i] + b[i]����an��bn�ֱ��������к��ٴεõ� d[i] =a`[i]+b`[i]���� max(ci) <= max(di)��
���費�ǰ�����������,��ô��Ȼ���ڣ�С��С�������󣬴󣩵���ϣ�����ʹ���Ϊ��С���󣩣�����С��������������ޡ���������һ���������Գ�Ϊ���������С�
�ܽ᣺
����ؼ���ƽ��̰��˼������á�����Ҫ�뵽��һ��˳��ӹ��Ĺ���ת��Ϊ���������м�ӹ���
*/

struct machine
{
    int processtime, willfinishtime;
}a[30], b[30];

bool cmp(const int& a, const int& b)
{
    return a > b;
}

int main()
{
    ifstream fin("job.in");
    ofstream fout("job.out");
    int n, m1, m2, m1min, m2min, m1minpos, m2minpos, finishtimea[1000], finishtimeb[1000], ans = 0;
    fin >> n >> m1 >> m2;
    for(int i = 0; i < m1; ++i)
        fin >> a[i].processtime;
    for(int i = 0; i < m2; ++i)
        fin >> b[i].processtime;
    for(int i = 0; i < n; ++i)
    {
        m1min = m2min = 50000000;
        for(int j = 0; j < m1; ++j)
        {
            if(a[j].processtime + a[j].willfinishtime < m1min)
            {
                m1min = a[j].processtime + a[j].willfinishtime;
                m1minpos = j;
            }
        }
        a[m1minpos].willfinishtime = m1min;
        finishtimea[i] = m1min;
        for(int j = 0; j < m2; ++j)
        {
            if(b[j].processtime + b[j].willfinishtime < m2min)
            {
                m2min = b[j].processtime + b[j].willfinishtime;
                m2minpos = j;
            }
        }
        b[m2minpos].willfinishtime = m2min;
        finishtimeb[i] = m2min;
    }
    sort(finishtimea, finishtimea + n);
    sort(finishtimeb, finishtimeb + n, cmp);
    for(int i = 0; i < n; ++i)
        if(ans < finishtimea[i] + finishtimeb[i])
            ans = finishtimea[i] + finishtimeb[i];
    fout << finishtimea[n - 1] << ' ' << ans << endl;
    return 0;
}
