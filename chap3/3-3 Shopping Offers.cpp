/*
ID: mazhaoj1
PROG: shopping
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

struct offers
{
    int code[5], cnt, num[5], price, seq[5];
}offer[99];
int total[6][6][6][6][6];
int code[1000], price[5], need[5];

int main()
{
    ifstream fin("shopping.in");
    ofstream fout("shopping.out");
    int s;
    fin >> s;
    for(int i = 0; i < s; ++i)
    {
        fin >> offer[i].cnt;
        for(int j = 0; j < offer[i].cnt; ++j)
            fin >> offer[i].code[j] >> offer[i].num[j];
        fin >> offer[i].price;
    }
    int b;
    fin >> b;
    for(int i = 0; i < b; ++i)
    {
        int codee;
        fin >> codee >> need[i] >> price[i];
        code[codee] = i;
    }
    for(int i = 0; i < s; ++i)
        for(int j = 0; j < offer[i].cnt; ++j)
            offer[i].seq[j] = code[offer[i].code[j]];
    for(int i = 0; i <= 5; ++i)
        for(int j = 0; j <= 5; ++j)
            for(int k = 0; k <= 5; ++k)
                for(int l = 0; l <= 5; ++l)
                    for(int m = 0; m <= 5; ++m) //如果这里<=用need[0], need[1]...need[5]，则当need[x] = 0时，无法进入下面的if的。。。
                    {
                        int min = 99999999;
                        for(int n = 0; n < s; ++n)
                        {
                            int t[5];
                            memset(t, 0, sizeof(t));    //因为offer[n].cnt可能小于5....
                            for(int o = 0; o < offer[n].cnt; ++o)
                                t[offer[n].seq[o]] = offer[n].num[o];
                            if(i - t[0] >= 0 && j - t[1] >= 0 && k - t[2] >= 0
                                && l - t[3] >= 0 && m - t[4] >= 0)
                            {
                                if(min > total[i - t[0]][j - t[1]][k - t[2]][l - t[3]][m - t[4]] + offer[n].price)
                                    min = total[i - t[0]][j - t[1]][k - t[2]][l - t[3]][m - t[4]] + offer[n].price;
                            }
                        }
                        if(min > i * price[0] + j * price[1] + k * price[2] + l * price[3] + m * price[4])
                            min = i * price[0] + j * price[1] + k * price[2] + l * price[3] + m * price[4];
                        total[i][j][k][l][m] = min;
                    }
    fout << total[need[0]][need[1]][need[2]][need[3]][need[4]] << endl;
    return 0;
}
