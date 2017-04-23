/*
ID: mazhaoj1
PROG: checker
LANG: C++
*/

//SOLVE 1:
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int placed[13], len, cnt, total;
int colused[13], useddiaglr[26], useddiagrl[26], result[3][13];
ofstream fout;
ifstream fin;

void queen(int row)
{
    int i, k, diaglr, diagrl;
    if(row == len)
    {
        total++;
        if(cnt < 3)
        {
            for(int i = 0 ;i < len; ++i)
                result[cnt][i] =  placed[i] + 1;
            cnt++;
        }
        return;
    }
    for(i = 0; i < len; ++i)
    {
        if(colused[i] == 0)     //col i
        {
            diaglr = row - i + len - 1;
            if(useddiaglr[diaglr] == 0)     // '\' diag
            {
                diagrl = row + i;
                if(useddiagrl[diagrl] == 0)     // '/' diag
                {
                    useddiaglr[diaglr] = 1;    // '\' diag
                    useddiagrl[diagrl] = 1;   // '/' diag
                    colused[i] = 1;
                    k = placed[row];
                    placed[row] = i;
                    queen(row + 1);
                    placed[row] = k;
                    colused[i] = 0;
                    useddiagrl[diagrl] = 0;
                    useddiaglr[diaglr] = 0;
                }
            }
        }
    }
}

int main()
{
    fout.open("checker.out");
    fin.open("checker.in");
    fin >> len;
    int s = len / 2;
    for(int i = 0; i < s; ++i)
    {
        placed[0] = i;
        colused[i] = 1;
        int diaglr = 0 - i + len - 1;
        useddiaglr[diaglr] = 1;    // '\' diag
        int diagrl = 0 + i;
        useddiagrl[diagrl] = 1;   // '/' diag
        queen(1);
        useddiaglr[diaglr] = 0;
        useddiagrl[diagrl] = 0;
        colused[i] = 0;
    }
    int all = total * 2;
    total = 0;
    if(len % 2 != 0)    //must calc singlely, because may have symmentric col values if directly mirrored
    {
        placed[0] = s;
        colused[s] = 1;
        int diaglr = 0 - s + len - 1;
        useddiaglr[diaglr] = 1;    // '\' diag
        int diagrl = 0 + s;
        useddiagrl[diagrl] = 1;   // '/' diag
        queen(1);
        useddiaglr[diaglr] = 0;
        useddiagrl[diagrl] = 0;
        colused[s] = 0;
    }
    all += total;
    if(cnt != 3)
    {
        int need = 3 - cnt;
        for(int i = cnt - 1; need > 0; --need, --i)
        {
            for(int j = 0 ; j < len ; ++j)
                result[cnt][j] = len - result[i][j] + 1;
            cnt++;
        }
    }
    for(int i = 0; i < 3; ++i)
    {
        fout << result[i][0];
        for(int j = 1; j < len; ++j)
            fout <<  ' ' << result[i][j];
        fout << endl;
    }
    fout << all << endl;
    return 0;
}


/*SOLVE 2:
// a very fast bit operation answer, really fast!
int upperlim, len, sum;
ofstream fout;
ifstream fin;

void test(int row, int ld, int rd)
{
    int pos, p;
    if(row != upperlim)
    {
        pos = upperlim & ~(row | ld | rd);  //bit 1 in row, ld, rd means occupide by queen's power
        while(pos != 0)     // bit 1 in pos means can put a queen here
        {
            p = pos & -pos;    //p = pos & !(pos + 1), extract the last bit 1
            pos = pos - p;
            test(row | p, (ld | p) << 1, (rd | p) >> 1);
        }
    }
    else
        sum++;
}

int main()
{
    fout.open("checker.out");
    fin.open("checker.in");
    fin >> len;
    upperlim = (1 << len) - 1;
    test(0, 0, 0);
    fout << sum << endl;    // need used SOLVE 1 to generate first 3 answers, or store every col in a row[] array, omitted here.
}
*/
