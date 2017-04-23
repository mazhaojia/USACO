/*
ID: mazhaoj1
PROG: charrec
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
题目的目的就是要找出输入文件的每一行对应font文件的哪一个图案。输入文件的图案可能会比font文件的图案少一行，不多不少，多复制一行(多复制的一行紧跟着被复制的一行)。
为了表示上面的3种情况，设c[0][i], c[1][i], c[2][i]，分别表示从输入文件的第i行开始向下共扫描19行，20行，21行得到的图案，和27个正确的图案比较后，总差距的最小值。
letter[0][i], letter[1][i], letter[2][i]为找到的c[0][i], c[1][i], c[2][i]最小值所对应的正确图案的字母。

为了求得c[1][i]，我们直接枚举输入文件第i行开始的20行，和27个正确图案求出差距和并取最小值即可。

记pre[k]为前k行的错误数，tail[k]为后k行的错误数，则c[i,19]=min(pre[k]+tail[19-k]);

考虑c[0][i]，则此时输入的第i行开始的19行为图像，将第i行和正确图案的第一行匹配，记pre[k]为前k行的错误数。将最后一行(i + 18)和正确图案的最后一行匹配，记tail[k]为后k行的错误数。
则有c[0][i] = min(pre[k]+tail[19-k])

考虑c[2][i]，则此时输入的第i行开始的21行为图像，将第i行和正确图案的第一行匹配，记pre[k]为前k行的错误数。将最后一行(i + 20)和正确图案的最后一行匹配，记tail[k]为后k行的错误数。
因为多出了一行，所以这里k从1迭代到20行即可。则有c[2][i] = min(pre[k]+tail[20-k])

设dif[i][j][k]为font.in的第i个图案的第j行与输入文件第k行的差距值。则求pre，tail的时候可以直接利用dif。

设f[i]为输入文件第i行(i > 0)以及其下所有行的差距和的最小值，则：
可得f[i] = min{c[0][i] + f[i + 19], c[1][i] + f[i + 20], c[2][i] + f[i + 21]} (0 <= i <= 行数 - 21)
f[i]的初值可见SOLVE2代码。SOLVE1中是通过增加数组长度来取巧做的。

最后，设h[i]为在计算f[i]时，记录下f[i]取得最小值时用的c[x][i]的x，然后从输入文件第1行开始取出letter[h[i]]，即为第一行代表的图案，接下来可以直接枚举第h[i] + 19行。如此就可得到所有的解。
此外题目要求无法判断输出'?'，而题意又明确说明每一个都有唯一解，因此只有在输入文件行数小于19行时才能输出'?'，但题目明确说明了行数至少19行，所以这里没有判断'?'号。
我认为如果某个字符为'?'，那么按该DP算法，接下去的所有字符都没法继续判断了。
*/

#define INF 10000000

/*  SOLVE 1: 下标从1开始的，修改自疾走考拉的pascal题解
string font[28][21];
string let = "  abcdefghijklmnopqrstuvwxyz";
int line;
int f[1222];
int h[1201];
int dif[28][21][1201];
int c[1201][22];
int pre[22];
int tail[22];
char letter[1201][22];

int main()
{
    ifstream fin("charrec.in");
    ofstream fout("charrec.out");
    ifstream fontin("font.in");
    string temp;
    int mini;

    for(int i = 1; i <= 1200; ++i)      //设初值
        for(int j = 19; j <= 21; ++j)
            c[i][j] = INF;

    fontin >> line;
    for(int i = 1; i <= 27; ++i)
        for(int j = 1; j <= 20; ++j)    //读入font.in
            fontin >> font[i][j];

    fin >> line;
    for(int i = 1; i <= line + 22; ++i)     //设f初值
        f[i] = INF;
    f[line + 1] = 0;
    for(int i = 1; i <= line; ++i)
    {
        fin >> temp;
        for(int j = 1; j <= 27; ++j)
            for(int k = 1; k <= 20; ++k)
                for(int l = 0; l <= 20; ++l)
                    if(temp[l] != font[j][k][l])    //预处理计算dif
                        dif[j][k][i]++;
    }

    for(int i = 1; i <= line; ++i)
    {
        for(int j = 1; j <= 27; ++j)
        {
            if(i + 18 > line)   //计算少一行的情况
                continue;
            pre[0] = tail[0] = 0;
            for(int k = 1; k <= 19; ++k)
            {
                pre[k] = pre[k - 1] + dif[j][k][i + k - 1];
                tail[k] = tail[k - 1] + dif[j][21 - k][i + 19 - k];
            }
            mini = INF;
            for(int k = 1; k <= 19; ++k)
                if(mini > pre[k] + tail[19 - k])
                    mini = pre[k] + tail[19 - k];
            if(c[i][19] > mini)
            {
                c[i][19] = mini;
                letter[i][19] = let[j];
            }

            if(i + 19 > line)   //行数相等时的情况
                continue;
            mini = 0;
            for(int k = 1; k <= 20; ++k)
                mini += dif[j][k][i + k - 1];
            if(c[i][20] > mini)
            {
                c[i][20] = mini;
                letter[i][20] = let[j];
            }

            if(i + 20 > line)   //多一行时的情况
                continue;
            pre[0] = tail[0] = 0;
            for(int k = 1; k <= 20; ++k)
            {
                pre[k] = pre[k - 1] + dif[j][k][i + k - 1];
                tail[k] = tail[k - 1] + dif[j][21 - k][i + 21 - k];
            }
            mini = INF;
            for(int k = 1; k <= 20; ++k)
                if(mini > pre[k] + tail[20 - k])
                    mini = pre[k] + tail[20 - k];
            if(c[i][21] > mini)
            {
                c[i][21] = mini;
                letter[i][21] = let[j];
            }
        }
    }
    for(int i = line; i >= 1; --i)  //DP求f
    {
        for(int j = 19; j <= 21; ++j)
        {
            if(f[i + j] + c[i][j] < f[i])
            {
                f[i] = f[i + j] + c[i][j];
                h[i] = j;
            }
        }
    }
    int i = 1;
    while(i != line + 1)
    {
        fout << letter[i][h[i]];    //出解
        i = i + h[i];
    }
    fout << endl;
    return 0;
}
*/

//  SOLVE 2: 下标从0开始的版本(除了pre，tail到20)，计算f的时候没有像上面那个那样取巧，使用了更为严格的方式。
string font[27][20];
string let = " abcdefghijklmnopqrstuvwxyz";
int line;
int f[1200];
int h[1200];
int dif[27][20][1200];
int c[3][1200];
int pre[21];
int tail[21];
char letter[3][1200];

int main()
{
    ifstream fin("charrec.in");
    ofstream fout("charrec.out");
    ifstream fontin("font.in");
    string temp;
    int mini;

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 1200; ++j)   //设初值
            c[i][j] = INF;

    fontin >> line;
    for(int i = 0; i < 27; ++i)
        for(int j = 0; j < 20; ++j)     ////读入font.in
            fontin >> font[i][j];

    fin >> line;
    for(int i = 0; i < line; ++i)   //设f初值
        f[i] = INF;

    for(int i = 0; i < line; ++i)
    {
        fin >> temp;
        for(int j = 0; j < 27; ++j)
            for(int k = 0; k < 20; ++k)
                for(int l = 0; l < 20; ++l)
                    if(temp[l] != font[j][k][l])    //预处理计算dif
                        dif[j][k][i]++;
    }

    for(int i = 0; i < line; ++i)
    {
        for(int j = 0; j < 27; ++j)
        {
            if(i + 19 > line)   //计算少一行的情况
                continue;
            pre[0] = tail[0] = 0;
            for(int k = 1; k <= 19; ++k)
            {
                pre[k] = pre[k - 1] + dif[j][k - 1][i + k - 1];
                tail[k] = tail[k - 1] + dif[j][20 - k][i + 19 - k];
            }
            mini = INF;
            for(int k = 1; k <= 19; ++k)
                if(mini > pre[k] + tail[19 - k])
                    mini = pre[k] + tail[19 - k];
            if(c[0][i] > mini)
            {
                c[0][i] = mini;
                letter[0][i] = let[j];
            }

            if(i + 20 > line)   //行数相等时的情况
                continue;
            mini = 0;
            for(int k = 0; k < 20; ++k)
                mini += dif[j][k][i + k];
            if(c[1][i] > mini)
            {
                c[1][i] = mini;
                letter[1][i] = let[j];
            }

            if(i + 21 > line)   //多一行时的情况
                continue;
            pre[0] = tail[0] = 0;
            for(int k = 1; k <= 20; ++k)
            {
                pre[k] = pre[k - 1] + dif[j][k - 1][i + k - 1];
                tail[k] = tail[k - 1] + dif[j][20 - k][i + 21 - k];
            }
            mini = INF;
            for(int k = 1; k <= 20; ++k)
                if(mini > pre[k] + tail[20 - k])
                    mini = pre[k] + tail[20 - k];
            if(c[2][i] > mini)
            {
                c[2][i] = mini;
                letter[2][i] = let[j];
            }
        }
    }
    f[line - 19] = c[0][line - 19];     //求f的DP的初始值
    h[line - 19] = 0;
    if(line > 19)
    {
        f[line - 20] = c[0][line - 20];
        h[line - 20] = 0;
        if(f[line - 20] > c[1][line - 20])
        {
            f[line - 20] = c[1][line - 20];
            h[line - 20] = 1;
        }
    }
    for(int i = line - 21; i >= 0; --i)     //DP求f
    {
        for(int j = 0; j <= 2; ++j)
        {
            if(f[i + j + 19] + c[j][i] < f[i])
            {
                f[i] = f[i + j + 19] + c[j][i];
                h[i] = j;
            }
        }
    }
    for(int i = 0; i <= line - 19; i += (h[i] + 19))    //出解
        fout << letter[h[i]][i];
    fout << endl;
    return 0;
}
