/*
ID: mazhaoj1
PROG: gift1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
    ofstream fout("gift1.out");
    ifstream fin("gift1.in");
    int nums;
    map<string, int> mp;
    vector<string> vec;
    pair<string, int> pa;
    string name;
    vector<string>::iterator it;

    fin>>nums;
    pa.second = 0;
    for(int i = 0; i < nums; ++i)
    {
        fin>>pa.first;
        mp.insert(pa);
        vec.push_back(pa.first);
    }
    string giver;
    while(fin>>giver)
    {
        int money, people;
        fin>>money>>people;
        int avg;
        if(people != 0)
        {
            avg = money / people;
            mp[giver] -= (people * avg);
        }
        for(int i = 0; i < people; ++i)
        {
            fin>>name;
            mp[name] += avg;
        }
    }
    int size = vec.size();
    for(int  i = 0; i < size; ++i)
         fout << vec[i] << ' ' << mp[vec[i]] << endl;
    return 0;
}
