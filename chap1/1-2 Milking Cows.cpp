/*
ID: mazhaoj1
PROG: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct gap
{
    int x, y;
}gp, gp2;

bool lessmark(const gap& s1, const gap& s2)
{
    if(s1.x == s2.x)
        return s1.y < s2.y;
    else
        return s1.x < s2.x;
}

int main()
{
    ofstream fout("milk2.out");
    ifstream fin("milk2.in");
    int maxyes,maxno,yes;
    int num;
    vector<gap> vec;
    fin >> num;
    while(num--)
    {
        fin>>gp.x>>gp.y;
        vec.push_back(gp);
    }
    sort(vec.begin(), vec.end(), lessmark);
    int size = vec.size();
    gp = vec[0];
    maxyes = yes = gp.y - gp.x;
    maxno = 0;
    for(int i = 1; i < size; ++i)
    {
        gp2 = vec[i];
        if(gp2.x >= gp.x && gp2.x <= gp.y)
        {
            if(gp2.y > gp.y)
            {
                yes+=gp2.y-gp.y;
                gp.y = gp2.y;
            }
        }
        else if(gp2.x > gp.y)
        {
            if(maxno < gp2.x - gp.y)
                maxno = gp2.x - gp.y;
            if(maxyes < yes)
                maxyes = yes;
            yes = gp2.y - gp2.x;
            gp = gp2;
        }
    }
    if(maxyes < yes)
        maxyes = yes;
    fout<<maxyes<<' '<<maxno<<endl;
    return 0;
}
