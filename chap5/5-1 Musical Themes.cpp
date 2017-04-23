/*
ID: mazhaoj1
PROG: theme
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
[转]这个题考虑到相同的旋律之间的差是常数，可以把读入的序列变换一下。就是每个元素与其前一个元素做差。
例如原序列{3,5,7,3,4,4,6,8,4}，做差后是{2,2,-4,1,0,2,2,-4}。这样就可以再变换后的序列中直接查找最长的重复序列即可。
上述例子中是2,2,-4，长度为3，对应原序列中3,5,7,3，长度为4。
寻找最长的重复序列，我采用了一种O(N^3)的算法。就是枚举两个序列的开头的序列的长度。但对于5000，O(N^3)还是难以过全的。
于是采用了一个优化：每次枚举末端那一位时都从开始的一位加上当前最大长度开始枚举，前一个序列开头只用枚举到(N-当前的最大长度)即可。
这个优化的力度很大，加上这个优化就全过了，而且很快。
提醒一下，Pascal的For循环 for i=1 to n-ans，当ans再循环中改变时，循环次数不会随之变化，也就是说一开始循环的次数就算好了。
而C和C++中 for(i=1;i<=n-ans;i++)会每次计算n-ans，所以ans改变时循环的次数也会改变。

注：Analysis的DP解更精妙。
*/

int main()
{
    ifstream fin("theme.in");
    ofstream fout("theme.out");
    int num, music[5000], ans = 3, gap;     //ans = 3, theme at least length 5
    fin >> num;
    for(int i = 0; i < num; ++i)
        fin >> music[i];
    num--;
    for(int i = 0; i < num; ++i)
        music[i] = music[i + 1] - music[i];
    for(int i = 0; i < num - ans; ++i) //num - ans is a speed up policy
    {
        for(int j = i + ans; j < num - ans; ++j)  //themes are disjoint
        {
            if(music[i] == music[j])
            {
                for(gap = 1; music[i + gap] == music[j + gap] && i + gap + 1 < j; gap++);  //ensure not overlap
                if(gap > ans)
                    ans = gap;
            }
        }
    }
    if(ans == 3)
        ans = 0;
    else
        ans++;
    fout << ans << endl;
    return 0;
}
