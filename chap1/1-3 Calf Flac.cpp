/*
ID: mazhaoj1
PROG: calfflac
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
struct s
{
    int oripos;
    char value;
}compute[20000];
int main()
{
    ofstream fout ("calfflac.out");
    ifstream fin ("calfflac.in");
    char buf[20000], ch;
    int len = 0, lencp = 0;
    fin.unsetf(ios::skipws);
    while(fin>>ch)
    {
        buf[len] = ch;
        if(ch >= 'A' && ch <='Z')
            ch = ch + 'a' - 'A';
        if(ch >= 'a' && ch <= 'z')
        {
            compute[lencp].oripos = len;
            compute[lencp].value = ch;
            ++lencp;
        }
        ++len;
    }
    int maxlen = 0, left, right;
    for(int i = 0; i + maxlen < lencp; ++i)
    {
        int j = i - 1, k = i + 1, count = 0;
        for(; j >= 0 && k < lencp; --j, ++k)
        {
            if(compute[j].value != compute[k].value)
                break;
            ++count;
        }
        if(maxlen < count * 2 + 1)
        {
            maxlen = count * 2 + 1;
            left = compute[j + 1].oripos;
            right = compute[k - 1].oripos;
        }
        count = 0;
        j = i;
        k = i + 1;
        for(; j >= 0 && k < lencp; --j, ++k)
        {
            if(compute[j].value != compute[k].value)
                break;
            ++count;
        }
        if(maxlen < count * 2)
        {
            maxlen = count * 2;
            left = compute[j + 1].oripos;
            right = compute[k - 1].oripos;
        }
    }
    fout << maxlen << endl;
    for(int i = left; i <= right; ++i)
        fout << buf[i];
    fout << endl;
    return 0;
}
