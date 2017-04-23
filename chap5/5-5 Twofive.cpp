/*
ID: mazhaoj1
PROG: twofive
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
本题实在是太太太太太太难了，不过对照解题报告看代码还是可以搞懂的。
解题报告：http://hi.baidu.com/winterlegend/blog/item/21e465255c90e53ac89559fc.html，以及nocow和其他神牛的blog
下面的代码修改自：http://hi.baidu.com/selfcontroler/blog/item/aa310fd88269026bd1164efa.html
神牛们的代码都太短了，变量名太短很难看懂，所以我这里用实际意义做变量名应该会好懂很多。
*/

int num, ans_w;
char str[26], op, ans_n[26];
int placed[6][6][6][6][6];  //第1,2,3,4,5行已经放置i,j,k,l,m个字母后,符合题意的方案个数
char maxr[5], maxc[5];  //每行最大的字母，每列最大的字母
char placecnt[5];   //每行已经放置的字母个数
bool used[26];  //字母是否已经被放置了，递归用

int calc(int line1cnt, int line2cnt, int line3cnt, int line4cnt, int line5cnt, char ch)
{
    int& now = placed[line1cnt][line2cnt][line3cnt][line4cnt][line5cnt];    //注意'&'符号
    if(now > 0)
        return now;
    if(used[ch - 'A'])
        return calc(line1cnt, line2cnt, line3cnt, line4cnt, line5cnt, ch + 1);
    if(line1cnt < 5 && ch > maxr[0] && ch > maxc[line1cnt])
        now += calc(line1cnt + 1, line2cnt, line3cnt, line4cnt, line5cnt, ch + 1);
    if(line1cnt > line2cnt && ch > maxr[1] && ch > maxc[line2cnt])
        now += calc(line1cnt, line2cnt + 1, line3cnt, line4cnt, line5cnt, ch + 1);
    if(line2cnt > line3cnt && ch > maxr[2] && ch > maxc[line3cnt])
        now += calc(line1cnt, line2cnt, line3cnt + 1, line4cnt, line5cnt, ch + 1);
    if(line3cnt > line4cnt && ch > maxr[3] && ch > maxc[line4cnt])
        now += calc(line1cnt, line2cnt, line3cnt, line4cnt + 1, line5cnt, ch + 1);
    if(line4cnt > line5cnt && ch > maxr[4] && ch > maxc[line5cnt])
        now += calc(line1cnt, line2cnt, line3cnt, line4cnt, line5cnt + 1, ch + 1);
    return now;
}

void place(int row, int col, char ch)
{
    memset(placed, 0, sizeof(placed));
    placed[5][5][5][5][5] = 1;
    maxr[row] = maxc[col] = ch;
    used[ch - 'A'] = true;
}

void solve_n()
{
    int totalcnt;
    char j;
    for(int i = 0; i < 25; ++i)
    {
        placecnt[i / 5]++;  //这一行要放序列的第一个字母
        for(j = 'A'; j <= 'Z'; ++j)    //枚举以每一个字母开头，这里char做循环里的变量某些编译器可能过不了！！
        {
            if(!used[j - 'A'] && j > maxr[i / 5] && j > maxc[i % 5])  //确保j可以放在i的位置
            {
                place(i / 5, i % 5, j); //放j
                totalcnt = calc(placecnt[0], placecnt[1], placecnt[2], placecnt[3], placecnt[4], 'A');   //在每行已经放置了这么多个的情况下从A开始递归看还能得到多少方案
                if(num <= totalcnt) //找到了一个序列，它的总数大于num
                    break;
                else
                    num -= totalcnt;   //还要枚举下一个字母作为序列的最后一个字母
                used[j - 'A'] = false;  //恢复used数组
            }
        }
        ans_n[i] = j;   //找到了i位所对应的字母
    }
}

void solve_w()
{
    ans_w = 0;
    char j;
    for(int i = 0; i < 25; ++i)
    {
        placecnt[i / 5]++;
        for(j = 'A'; j < str[i]; ++j)  //枚举每一个比当前位置的字母小的字母，找到所有方案数累加
        {
            if(!used[j - 'A'] && j > maxr[i / 5] && j > maxc[i % 5])
            {
                place(i / 5, i % 5, j);
                ans_w += calc(placecnt[0], placecnt[1], placecnt[2], placecnt[3], placecnt[4], 'A');
                used[j - 'A'] = false;
            }
        }
        used[j - 'A'] = true;
        maxr[i / 5] = maxc[i % 5] = j;
    }
    ans_w++;    //+1之后最后一个字符才是当前字符，所以才是正确的解。
}

int main()
{
    ifstream fin("twofive.in");
    ofstream fout("twofive.out");
    fin >> op;
    if(op == 'N')
    {
        fin >> num;
        solve_n();
        fout << ans_n << endl;
    }
    else
    {
        fin >> str;
        solve_w();
        fout << ans_w << endl;
    }
    return 0;
}
