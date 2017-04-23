/*
ID: mazhaoj1
PROG: palsquare
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    ofstream fout("palsquare.out");
    ifstream fin("palsquare.in");
    int base;
    fin >> base;
    char ch[30];
    for(int i = 1; i <= 300; ++i)
    {
        int square = i * i;
        int len = 0;
        int temp;
        while(square != 0)
        {
            temp = square % base;
            if(temp < 10)
                ch[len] = temp + '0';
            else
                ch[len] = temp - 10 + 'A';
            len++;
            square /= base;
        }
        int match = 1;
        int j, k;
        for(j = 0, k = len - 1; j < k; ++j, --k)
        {
            if(ch[j] != ch[k])
            {
                match = 0;
                break;
            }
        }
        if(match)
        {
            ch[len] = '\0';
            char chn[10];
            int lenn = 0;
            k = i;
            while(k != 0)
            {
                temp = k % base;
                if(temp < 10)
                    chn[lenn] = temp + '0';
                else
                    chn[lenn] = temp - 10 + 'A';
                lenn++;
                k /= base;
            }
            for(j = lenn - 1; j >= 0; --j)
                fout << chn[j];
            fout << ' ' << ch << endl;
        }
    }
    return 0;
}
