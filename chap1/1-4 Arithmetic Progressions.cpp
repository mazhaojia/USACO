/*
ID: mazhaoj1
PROG: ariprog
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>
using namespace std;

short int all[250 * 250 + 250 * 250];
set<int> st;
struct value
{
    int seq;
    int dif;
}values[10000];
int vcnt = 0;

int comp(const void* p1, const void* p2)
{
    value* v1 = (value*)p1;
    value* v2 = (value*)p2;
    if(v1->dif == v2->dif)
        return v1->seq - v2->seq;
    else
        return v1->dif - v2->dif;
}

int main()
{
    ofstream fout("ariprog.out");
    ifstream fin("ariprog.in");
    int len, limit;
    fin >> len >> limit;
    for(int i = 0; i <= limit; ++i)
    {
        for(int j = i; j <= limit; ++j)
        {
            st.insert(i * i + j * j);
            all[i * i + j * j] = 1;
        }
    }
    int found = 0;
    int seq;
    int intr = limit * limit + limit * limit;
    set<int>::iterator it, it2;
    for(it = st.begin(); it != st.end(); ++it)  //a
    {
        seq = *it;
        for(int j = 1; j < intr; ++j)   //b
        {
            found = 1;
            if(seq + (len - 1) * j > intr)
                break;
            for(int k = *it + j;  k <= intr; k += j)
            {
                if(all[k] == 1)
                {
                    found++;
                    if(found == len)
                    {
                        values[vcnt].seq = seq;
                        values[vcnt].dif = j;
                        vcnt++;
                        break;
                    }
                }
                else
                    break;
            }
        }
    }
    if(vcnt == 0)
        fout << "NONE" << endl;
    else
    {
        qsort(values, vcnt, sizeof(values[0]), comp);
        for(int i = 0 ; i < vcnt; ++i)
            fout << values[i].seq << ' ' << values[i].dif << endl;
    }
    return 0;
}