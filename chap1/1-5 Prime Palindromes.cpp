/*
ID: mazhaoj1
PROG: pprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

char isprime[10000];
int prime[10000];
int primecnt;

int judge(int pa)
{
    int sqpa = (int) sqrt((double)pa);
    for(int i = 0; i < primecnt && prime[i] <= sqpa; ++i)
        if(pa % prime[i] == 0)
            return 0;
    return 1;
}

int main()
{
    ofstream fout("pprime.out");
    ifstream fin("pprime.in");
    int a, b;
    fin >> a >> b;
    int palindrome, d1, d2, d3, d4, d5;
    memset(isprime, 1, sizeof(isprime));
    isprime[0] = isprime[1] = 0;
    for(int i = 2; i <= 10000; ++i)
        for(int j = 2, mul = i + i; mul <= 10000; ++j, mul = mul + i)
            isprime[mul] = 0;
    for(int i = 0; i <= 10000; ++i)
        if(isprime[i])
            prime[primecnt++] = i;

    /* only odd; evens aren't so prime */
    for(d1 = 1; d1 <= 9; d1 +=2)     //1 digit
    {
        palindrome = d1;
        if(palindrome >= a && palindrome <= b && judge(palindrome))
            fout << palindrome << endl;
        else if(palindrome > b)
            return 0;
    }

    if(11 >= a && 11 <= b)      //special 2 digit number
        fout << 11 << endl;

    for(d1 = 1; d1 <= 9; d1 +=2)     //3 digit
    {
        for(d2 = 0; d2 <= 9; d2++)
        {
            palindrome = 100 * d1 + 10 * d2 + d1;
            if(palindrome >= a && palindrome <= b && judge(palindrome))
                fout << palindrome << endl;
            else if(palindrome > b)
                return 0;
        }
    }

    for (d1 = 1; d1 <= 9; d1 += 2)  //5 digit
    {
        for (d2 = 0; d2 <= 9; d2++)
        {
            for (d3 = 0; d3 <= 9; d3++)
            {
                palindrome = 10000 * d1 + 1000 * d2 + 100 * d3 + 10 * d2 + d1;
                if(palindrome >= a && palindrome <= b && judge(palindrome))
                    fout << palindrome << endl;
                else if(palindrome > b)
                    return 0;
            }
        }
    }

    for(d1 = 1; d1 <= 9; d1 += 2)   //7 digit
    {
        for(d2 = 0; d2 <= 9; d2++)
        {
            for(d3 = 0; d3 <= 9; d3++)
            {
                for(d4 = 0; d4 <= 9; d4++)
                {
                    palindrome = 1000000 * d1 + 100000 * d2 + 10000 * d3 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
                    if(palindrome >= a && palindrome <= b && judge(palindrome))
                        fout << palindrome << endl;
                    else if(palindrome > b)
                        return 0;
                }
            }
        }
    }

    for(d1 = 1; d1 <= 9; d1 += 2)   //9 digit
    {
        for(d2 = 0; d2 <= 9; d2++)
        {
            for(d3 = 0; d3 <= 9; d3++)
            {
                for(d4 = 0; d4 <= 9; d4++)
                {
                    for(d5 = 0; d5 <= 9; d5++)
                    {
                        palindrome = 100000000 * d1 + 10000000 * d2 + 1000000 * d3 + 100000 * d4 + 10000 * d5 + 1000 * d4 + 100 * d3 + 10 * d2 + d1;
                        if(palindrome >= a && palindrome <= b && judge(palindrome))
                            fout << palindrome << endl;
                        else if(palindrome > b)
                            return 0;
                    }
                }
            }
        }
    }

    return 0;
}
