/*
ID: mazhaoj1
PROG: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*SOLVE 1:

首先用两个数组分别保存排了序的数组和没排序的数组，然后再根据这两个判断，
当前这个位置上应该是放什么数，而实际上放的是什么数，如果两个位置上需要的都正好是对方所有的，
那么这是最好的，进行循环，把所有这种的都交换掉，然后累计交换次数。
但是最后会有这么一种情况，三个位置需要的分别是1, 2, 3，而他们有的分别是3, 1, 2; 2, 3, 1; 这时就要交换两次了，
当然，对数可能不止一对，所以就累计需要的和拥有的不相同的那些，统计起来，处以三再乘以二，就是交换次数，结果就出来了。

int a[1000], b[1000], n, cnt;

int cmp(const void* a, const void* b)
{
    return *(int*)a - *(int*)b;
}

int main()
{
    ofstream fout("sort3.out");
    ifstream fin("sort3.in");
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> a[i];
        b[i] = a[i];
    }
    qsort(b, n, sizeof(b[0]), cmp);
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < n; ++j)
        {
            if(a[i] != b[i] && a[j] != b[j] && a[i] == b[j] && b[i] == a[j])
            {
                ++cnt;
                a[i] = b[i];
                a[j] = b[j];
            }
        }
    }
    int nomatch = 0;
    for(int i = 0; i < n; ++i)
        if(a[i] != b[i])
            ++nomatch;
    cnt += nomatch / 3 * 2;     //here / and * order is not important, because only remain 3, 1, 2 or 2, 3, 1 situation
    fout << cnt << endl;
    return 0;
}

*/

/*SOLVE 2:

"这道题很神奇的贪心，第一章中讲贪心算法时讲过这个题的算法。
其实就是统计出1，2，3的个数，在1的位置上出现的2记为n12，在2位置上出现的1记为n21，如此。
如果n12==n21，那么说明这两个位置上的数字只要一次交换就能得到最少的交换次数，如果其中某一个较大，
那么较小的那个数就可以通过一次交换得到。其他位置同理。
把可以交换一次得到的个数都在各自中减去，那么剩下的序列必定每3个形如（3，2，1）的序列可以通过两次交换排序好，
所以，对剩余的n(i,j)进行求和，再乘以2除以3，得到的数加到sum上即可……"
需要注意的是当所有数全一样时输出0。比SOLVE1的好处是不需要排序了。
*/

int a[1000], number[4], pos[4][4], minimum, remain, cnt, n;

int main()
{
    ofstream fout("sort3.out");
    ifstream fin("sort3.in");
    fin >> n;
    for(int i = 0; i < n; ++i)
    {
        fin >> a[i];
        ++number[a[i]];
    }
    number[2] = number[1] + number[2];
    number[3] = number[2] + number[3];
    for(int i = 0, j = 1; i < n; ++i)
    {
        if(i == number[j])
            ++j;
        if(a[i] != j)
            ++pos[j][a[i]];
    }
    for(int i = 1; i <= 2; ++i)
    {
        for(int j = i + 1; j <= 3; ++j)
        {
            minimum = min(pos[i][j], pos[j][i]);
            cnt += minimum;
            pos[i][j] -= minimum;
            pos[j][i] -= minimum;
            remain += pos[i][j] + pos[j][i];
        }
    }
    cnt += remain / 3 * 2;
    fout << cnt << endl;
    return 0;
}
