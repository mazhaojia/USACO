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
[ת]����⿼�ǵ���ͬ������֮��Ĳ��ǳ��������԰Ѷ�������б任һ�¡�����ÿ��Ԫ������ǰһ��Ԫ�����
����ԭ����{3,5,7,3,4,4,6,8,4}���������{2,2,-4,1,0,2,2,-4}�������Ϳ����ٱ任���������ֱ�Ӳ�������ظ����м��ɡ�
������������2,2,-4������Ϊ3����Ӧԭ������3,5,7,3������Ϊ4��
Ѱ������ظ����У��Ҳ�����һ��O(N^3)���㷨������ö���������еĿ�ͷ�����еĳ��ȡ�������5000��O(N^3)�������Թ�ȫ�ġ�
���ǲ�����һ���Ż���ÿ��ö��ĩ����һλʱ���ӿ�ʼ��һλ���ϵ�ǰ��󳤶ȿ�ʼö�٣�ǰһ�����п�ͷֻ��ö�ٵ�(N-��ǰ����󳤶�)���ɡ�
����Ż������Ⱥܴ󣬼�������Ż���ȫ���ˣ����Һܿ졣
����һ�£�Pascal��Forѭ�� for i=1 to n-ans����ans��ѭ���иı�ʱ��ѭ������������֮�仯��Ҳ����˵һ��ʼѭ���Ĵ���������ˡ�
��C��C++�� for(i=1;i<=n-ans;i++)��ÿ�μ���n-ans������ans�ı�ʱѭ���Ĵ���Ҳ��ı䡣

ע��Analysis��DP������
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
