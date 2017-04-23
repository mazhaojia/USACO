/*
ID: mazhaoj1
PROG: sprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;

int prime[8][10000];
int primecnt[8];
char sieve[10000];
int pris[10000];
int pricnt;

int isprime(int pa)
{
    int sq = (int)sqrt((double)pa);
    for(int i = 0; i < pricnt && pris[i] <= sq; i++)
        if(pa % pris[i] == 0)
            return 0;
    return 1;
}

int main()
{
    ofstream fout("sprime.out");
    ifstream fin("sprime.in");
    int len;
    fin >> len;
    memset(sieve, 1, sizeof(sieve));
    sieve[2] = 1;
    pris[pricnt++] = 2;
    for(int i = 3; i < 10000; i += 2)
    {
        if(sieve[i])
            pris[pricnt++] = i;
        for(int mul = i + i; mul < 10000; mul += i)
            sieve[mul] = 0;
    }
    prime[0][primecnt[0]++] = 2;
    prime[0][primecnt[0]++] = 3;
    prime[0][primecnt[0]++] = 5;
    prime[0][primecnt[0]++] = 7;
    for(int i = 1; i < len; ++i)
    {
        for(int j = 0; j < primecnt[i - 1]; ++j)
        {
            for(int k = 1; k <= 9; k += 2)
            {
                int temp = prime[i-1][j] * 10 + k;
                if(isprime(temp))
                    prime[i][primecnt[i]++] = temp;
            }
        }
    }
    for(int i = 0; i < primecnt[len - 1]; ++i)
        fout << prime[len - 1][i] << endl;
    return 0;
}
