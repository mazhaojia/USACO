/*
ID: mazhaoj1
PROG: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

set<string> dict;
string num;
char mp[8][3] =
{
    {'A', 'B', 'C'},
    {'D', 'E', 'F'},
    {'G', 'H', 'I'},
    {'J', 'K', 'L'},
    {'M', 'N', 'O'},
    {'P', 'R', 'S'},
    {'T', 'U', 'V'},
    {'W', 'X', 'Y'}
};
string result;
int found = 0;

void compute(int pos, int len, ofstream& fout)
{
    if(pos == len)
    {
        if(dict.find(result) != dict.end())
        {
            found = 1;
            fout << result << endl;
        }
        return;
    }
    int loc = num[pos] - '0' - 2;
    string ori = result;
    for(int i = 0; i < 3; ++i)
    {
        result += mp[loc][i];
        compute(pos + 1, len, fout);
        result = ori;
    }
}

int main()
{
    ofstream fout("namenum.out");
    ifstream fin("namenum.in");
    ifstream fdic("dict.txt");
    string name;
    while(fdic >> name)
        dict.insert(name);
    fin >> num;
    int len = num.size();
    found = 0;
    compute(0, len, fout);
    if(found == 0)
        fout << "NONE" <<endl;
    return 0;
}
