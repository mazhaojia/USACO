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
��Ŀ��Ŀ�ľ���Ҫ�ҳ������ļ���ÿһ�ж�Ӧfont�ļ�����һ��ͼ���������ļ���ͼ�����ܻ��font�ļ���ͼ����һ�У����಻�٣��ิ��һ��(�ิ�Ƶ�һ�н����ű����Ƶ�һ��)��
Ϊ�˱�ʾ�����3���������c[0][i], c[1][i], c[2][i]���ֱ��ʾ�������ļ��ĵ�i�п�ʼ���¹�ɨ��19�У�20�У�21�еõ���ͼ������27����ȷ��ͼ���ȽϺ��ܲ�����Сֵ��
letter[0][i], letter[1][i], letter[2][i]Ϊ�ҵ���c[0][i], c[1][i], c[2][i]��Сֵ����Ӧ����ȷͼ������ĸ��

Ϊ�����c[1][i]������ֱ��ö�������ļ���i�п�ʼ��20�У���27����ȷͼ��������Ͳ�ȡ��Сֵ���ɡ�

��pre[k]Ϊǰk�еĴ�������tail[k]Ϊ��k�еĴ���������c[i,19]=min(pre[k]+tail[19-k]);

����c[0][i]�����ʱ����ĵ�i�п�ʼ��19��Ϊͼ�񣬽���i�к���ȷͼ���ĵ�һ��ƥ�䣬��pre[k]Ϊǰk�еĴ������������һ��(i + 18)����ȷͼ�������һ��ƥ�䣬��tail[k]Ϊ��k�еĴ�������
����c[0][i] = min(pre[k]+tail[19-k])

����c[2][i]�����ʱ����ĵ�i�п�ʼ��21��Ϊͼ�񣬽���i�к���ȷͼ���ĵ�һ��ƥ�䣬��pre[k]Ϊǰk�еĴ������������һ��(i + 20)����ȷͼ�������һ��ƥ�䣬��tail[k]Ϊ��k�еĴ�������
��Ϊ�����һ�У���������k��1������20�м��ɡ�����c[2][i] = min(pre[k]+tail[20-k])

��dif[i][j][k]Ϊfont.in�ĵ�i��ͼ���ĵ�j���������ļ���k�еĲ��ֵ������pre��tail��ʱ�����ֱ������dif��

��f[i]Ϊ�����ļ���i��(i > 0)�Լ����������еĲ��͵���Сֵ����
�ɵ�f[i] = min{c[0][i] + f[i + 19], c[1][i] + f[i + 20], c[2][i] + f[i + 21]} (0 <= i <= ���� - 21)
f[i]�ĳ�ֵ�ɼ�SOLVE2���롣SOLVE1����ͨ���������鳤����ȡ�����ġ�

�����h[i]Ϊ�ڼ���f[i]ʱ����¼��f[i]ȡ����Сֵʱ�õ�c[x][i]��x��Ȼ��������ļ���1�п�ʼȡ��letter[h[i]]����Ϊ��һ�д����ͼ��������������ֱ��ö�ٵ�h[i] + 19�С���˾Ϳɵõ����еĽ⡣
������ĿҪ���޷��ж����'?'������������ȷ˵��ÿһ������Ψһ�⣬���ֻ���������ļ�����С��19��ʱ�������'?'������Ŀ��ȷ˵������������19�У���������û���ж�'?'�š�
����Ϊ���ĳ���ַ�Ϊ'?'����ô����DP�㷨������ȥ�������ַ���û�������ж��ˡ�
*/

#define INF 10000000

/*  SOLVE 1: �±��1��ʼ�ģ��޸��Լ��߿�����pascal���
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

    for(int i = 1; i <= 1200; ++i)      //���ֵ
        for(int j = 19; j <= 21; ++j)
            c[i][j] = INF;

    fontin >> line;
    for(int i = 1; i <= 27; ++i)
        for(int j = 1; j <= 20; ++j)    //����font.in
            fontin >> font[i][j];

    fin >> line;
    for(int i = 1; i <= line + 22; ++i)     //��f��ֵ
        f[i] = INF;
    f[line + 1] = 0;
    for(int i = 1; i <= line; ++i)
    {
        fin >> temp;
        for(int j = 1; j <= 27; ++j)
            for(int k = 1; k <= 20; ++k)
                for(int l = 0; l <= 20; ++l)
                    if(temp[l] != font[j][k][l])    //Ԥ�������dif
                        dif[j][k][i]++;
    }

    for(int i = 1; i <= line; ++i)
    {
        for(int j = 1; j <= 27; ++j)
        {
            if(i + 18 > line)   //������һ�е����
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

            if(i + 19 > line)   //�������ʱ�����
                continue;
            mini = 0;
            for(int k = 1; k <= 20; ++k)
                mini += dif[j][k][i + k - 1];
            if(c[i][20] > mini)
            {
                c[i][20] = mini;
                letter[i][20] = let[j];
            }

            if(i + 20 > line)   //��һ��ʱ�����
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
    for(int i = line; i >= 1; --i)  //DP��f
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
        fout << letter[i][h[i]];    //����
        i = i + h[i];
    }
    fout << endl;
    return 0;
}
*/

//  SOLVE 2: �±��0��ʼ�İ汾(����pre��tail��20)������f��ʱ��û���������Ǹ�����ȡ�ɣ�ʹ���˸�Ϊ�ϸ�ķ�ʽ��
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
        for(int j = 0; j < 1200; ++j)   //���ֵ
            c[i][j] = INF;

    fontin >> line;
    for(int i = 0; i < 27; ++i)
        for(int j = 0; j < 20; ++j)     ////����font.in
            fontin >> font[i][j];

    fin >> line;
    for(int i = 0; i < line; ++i)   //��f��ֵ
        f[i] = INF;

    for(int i = 0; i < line; ++i)
    {
        fin >> temp;
        for(int j = 0; j < 27; ++j)
            for(int k = 0; k < 20; ++k)
                for(int l = 0; l < 20; ++l)
                    if(temp[l] != font[j][k][l])    //Ԥ�������dif
                        dif[j][k][i]++;
    }

    for(int i = 0; i < line; ++i)
    {
        for(int j = 0; j < 27; ++j)
        {
            if(i + 19 > line)   //������һ�е����
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

            if(i + 20 > line)   //�������ʱ�����
                continue;
            mini = 0;
            for(int k = 0; k < 20; ++k)
                mini += dif[j][k][i + k];
            if(c[1][i] > mini)
            {
                c[1][i] = mini;
                letter[1][i] = let[j];
            }

            if(i + 21 > line)   //��һ��ʱ�����
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
    f[line - 19] = c[0][line - 19];     //��f��DP�ĳ�ʼֵ
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
    for(int i = line - 21; i >= 0; --i)     //DP��f
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
    for(int i = 0; i <= line - 19; i += (h[i] + 19))    //����
        fout << letter[h[i]][i];
    fout << endl;
    return 0;
}
