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

��������������ֱ𱣴�������������û��������飬Ȼ���ٸ����������жϣ�
��ǰ���λ����Ӧ���Ƿ�ʲô������ʵ���Ϸŵ���ʲô�����������λ������Ҫ�Ķ������ǶԷ����еģ�
��ô������õģ�����ѭ�������������ֵĶ���������Ȼ���ۼƽ���������
������������ôһ�����������λ����Ҫ�ķֱ���1, 2, 3���������еķֱ���3, 1, 2; 2, 3, 1; ��ʱ��Ҫ���������ˣ�
��Ȼ���������ܲ�ֹһ�ԣ����Ծ��ۼ���Ҫ�ĺ�ӵ�еĲ���ͬ����Щ��ͳ���������������ٳ��Զ������ǽ�������������ͳ����ˡ�

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

"�����������̰�ģ���һ���н�̰���㷨ʱ�����������㷨��
��ʵ����ͳ�Ƴ�1��2��3�ĸ�������1��λ���ϳ��ֵ�2��Ϊn12����2λ���ϳ��ֵ�1��Ϊn21����ˡ�
���n12==n21����ô˵��������λ���ϵ�����ֻҪһ�ν������ܵõ����ٵĽ����������������ĳһ���ϴ�
��ô��С���Ǹ����Ϳ���ͨ��һ�ν����õ�������λ��ͬ��
�ѿ��Խ���һ�εõ��ĸ������ڸ����м�ȥ����ôʣ�µ����бض�ÿ3�����磨3��2��1�������п���ͨ�����ν�������ã�
���ԣ���ʣ���n(i,j)������ͣ��ٳ���2����3���õ������ӵ�sum�ϼ��ɡ���"
��Ҫע����ǵ�������ȫһ��ʱ���0����SOLVE1�ĺô��ǲ���Ҫ�����ˡ�
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
