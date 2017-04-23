/*
ID: mazhaoj1
PROG: fact4
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int main()
{
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");
    int n, cnt = 1;
    fin >> n;
    for(int i = 2; i <= n; ++i)
    {
        int j = i, five = 0;
        while(j % 5 == 0)    //here we calculate how many '5', i have.
        {
            j /= 5;
            ++five;
        }
        cnt *= j;
        while(five--)
            cnt /= 2;
        cnt = cnt % 1000;   //within 1 to 4220, 3125 have five '5' at most, so we have to divide '2'
                            //at most five times,  the 2^5 = 32, so we keep 1000 here. because if we keep 100 here, when the remain like '30',
                            //is not enough to be divided by five '2'.
    }
    while(cnt % 10 == 0)
        cnt /= 10;
    fout << cnt % 10 << endl;
    return 0;
}


/*slove 2(±ê³Ì):
int main()
{
    ifstream fin("fact4.in");
    ofstream fout("fact4.out");
    int n, cnt = 1;
    fin >> n;
    int five = 0, two = 0;
    for(int i = 2; i <= n; ++i)
    {
        int j = i;
        while(j % 5 == 0)
        {
            j /= 5;
            ++five;
        }
        while(j % 2 == 0)
        {
            j /= 2;
            ++two;
        }
        cnt *= j;
        cnt %= 10;
    }
    int minus = two - five;
    while(minus--)
    {
        cnt *= 2;
        cnt %= 10;
    }
    fout << cnt << endl;
    return 0;
}
*/
