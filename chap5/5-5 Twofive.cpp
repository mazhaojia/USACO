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
����ʵ����̫̫̫̫̫̫���ˣ��������ս��ⱨ�濴���뻹�ǿ��Ը㶮�ġ�
���ⱨ�棺http://hi.baidu.com/winterlegend/blog/item/21e465255c90e53ac89559fc.html���Լ�nocow��������ţ��blog
����Ĵ����޸��ԣ�http://hi.baidu.com/selfcontroler/blog/item/aa310fd88269026bd1164efa.html
��ţ�ǵĴ��붼̫���ˣ�������̫�̺��ѿ�����������������ʵ��������������Ӧ�û�ö��ܶࡣ
*/

int num, ans_w;
char str[26], op, ans_n[26];
int placed[6][6][6][6][6];  //��1,2,3,4,5���Ѿ�����i,j,k,l,m����ĸ��,��������ķ�������
char maxr[5], maxc[5];  //ÿ��������ĸ��ÿ��������ĸ
char placecnt[5];   //ÿ���Ѿ����õ���ĸ����
bool used[26];  //��ĸ�Ƿ��Ѿ��������ˣ��ݹ���

int calc(int line1cnt, int line2cnt, int line3cnt, int line4cnt, int line5cnt, char ch)
{
    int& now = placed[line1cnt][line2cnt][line3cnt][line4cnt][line5cnt];    //ע��'&'����
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
        placecnt[i / 5]++;  //��һ��Ҫ�����еĵ�һ����ĸ
        for(j = 'A'; j <= 'Z'; ++j)    //ö����ÿһ����ĸ��ͷ������char��ѭ����ı���ĳЩ���������ܹ����ˣ���
        {
            if(!used[j - 'A'] && j > maxr[i / 5] && j > maxc[i % 5])  //ȷ��j���Է���i��λ��
            {
                place(i / 5, i % 5, j); //��j
                totalcnt = calc(placecnt[0], placecnt[1], placecnt[2], placecnt[3], placecnt[4], 'A');   //��ÿ���Ѿ���������ô���������´�A��ʼ�ݹ鿴���ܵõ����ٷ���
                if(num <= totalcnt) //�ҵ���һ�����У�������������num
                    break;
                else
                    num -= totalcnt;   //��Ҫö����һ����ĸ��Ϊ���е����һ����ĸ
                used[j - 'A'] = false;  //�ָ�used����
            }
        }
        ans_n[i] = j;   //�ҵ���iλ����Ӧ����ĸ
    }
}

void solve_w()
{
    ans_w = 0;
    char j;
    for(int i = 0; i < 25; ++i)
    {
        placecnt[i / 5]++;
        for(j = 'A'; j < str[i]; ++j)  //ö��ÿһ���ȵ�ǰλ�õ���ĸС����ĸ���ҵ����з������ۼ�
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
    ans_w++;    //+1֮�����һ���ַ����ǵ�ǰ�ַ������Բ�����ȷ�Ľ⡣
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
