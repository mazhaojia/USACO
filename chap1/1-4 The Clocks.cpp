/*
ID: mazhaoj1
PROG: clocks
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int clocks[9];
int move[9][9] = {0};
int moved[9] = {0};
char ans[37] = {'9'};

void initmove()
{
    move[0][0] = move[0][1] = move[0][3] = move[0][4] = 1;
    move[1][0] = move[1][1] = move[1][2] = 1;
    move[2][1] = move[2][2] = move[2][4] = move[2][5] = 1;
    move[3][0] = move[3][3] = move[3][6] = 1;
    move[4][1] = move[4][3] = move[4][4] = move[4][5] = move[4][7] = 1;
    move[5][2] = move[5][5] = move[5][8] = 1;
    move[6][3] = move[6][4] = move[6][6] = move[6][7] = 1;
    move[7][6] = move[7][7] = move[7][8] = 1;
    move[8][4] = move[8][5] = move[8][7] = move[8][8] = 1;
}

void domove(int index)
{
    for(int i = 0; i < 9; ++i)
        if(move[index][i])
            clocks[i] = (clocks[i] + 3) %  12;
}

void domoveback(int index)
{
    for(int i = 0; i < 9; ++i)
        if(move[index][i])
            clocks[i] = (clocks[i] + 12 - 3) %  12;
}

int match()
{
    for(int i = 0; i < 9; ++i)
        if(clocks[i] != 0)
            return 0;
    return 1;
}

void setmin()
{
    char num[37];
    int cnt = 0;
    for(int i = 0; i < 9; ++i)
        for(int j = 0; j < moved[i]; ++j)
            num[cnt++] = (i + 1) + '0';
    num[cnt] = '\0';
    if(strcmp(ans, num) > 0)
        strcpy(ans, num);
}

void compute(int level)
{
    if(level == -1)
        return;
    for(int i = 0; i < 4; ++i)
    {
        domove(level);
        moved[level] = (moved[level] + 1) % 4 ;
        compute(level - 1);
        if(match())
            setmin();
    }
}

int main()
{
    ofstream fout("clocks.out");
    ifstream fin("clocks.in");
    for(int i = 0; i < 9; ++i)
    {
        fin >> clocks[i];
        if(clocks[i] == 12)
            clocks[i] = 0;
    }
    initmove();
    compute(8);
    int len = strlen(ans);
    for(int i = 0; i < len - 1; ++i)
        fout << ans[i] << ' ';
    fout << ans[len - 1] << endl;
    return 0;
}
