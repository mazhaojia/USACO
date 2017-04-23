/*
ID: mazhaoj1
PROG: beads
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream fout ("beads.out");
    ifstream fin ("beads.in");
    int num, maxlen = 1, lenl, lenr, i, j, k;
    int changedl = -1, changedr = -1;
    char chl, chr;
    string str;
    fin >> num;
    fin >> str;
    for(i = 0 ; i < num; ++i)
    {
        lenr = 1;
        for(j = (i + 1) % num; j != i; j = (j + 1) % num)
        {
            if(str[j] == str[i] || str[j] == 'w')
                lenr++;
            else if(str[i] == 'w')
            {
                lenr++;
                chr = str[i];
                str[i] = str[j];
                changedr = i;
            }
            else
                break;
        }
        if(changedr != -1)
        {
            str[changedr] = chr;
            changedr = -1;
        }
        if(j == i)
        {
            maxlen = lenr;
            break;
        }
        j--;
        lenl = 1;
        for(k = (i - 2 + num) % num; k != (i - 1 + num) % num && k != j; k = (k - 1 + num) % num)
        {
            if(str[k] == str[(i - 1 + num) % num] || str[k] == 'w')
                lenl++;
            else if(str[(i - 1 + num) % num] == 'w')
            {
                lenl++;
                chl = str[(i - 1 + num) % num];
                str[(i - 1 + num) % num] = str[k];
                changedl = (i - 1 + num) % num;
            }
            else
                break;
        }
        if(changedl != -1)
        {
            str[changedl] = chl;
            changedl = -1;
        }
        if(maxlen < lenl + lenr)
            maxlen = lenl + lenr;
    }
    fout << maxlen << endl;
}
