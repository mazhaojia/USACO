/*
ID: mazhaoj1
PROG: transform
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void nintydegreetrans(const string ori[], string aftertrans[], const int size)
{
    int num = size - 1;
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            aftertrans[j][num - i] = ori[i][j];
}

void onehundredeightydegreetrans(const string ori[], string aftertrans[], const int size)
{
    nintydegreetrans(ori, aftertrans, size);
    string aftertrans2[10];
    for(int i = 0; i < size; ++i)
        aftertrans2[i] = ori[i];
    nintydegreetrans(aftertrans, aftertrans2, size);
    for(int i = 0; i < size; ++i)
        aftertrans[i] = aftertrans2[i];
}

void twohundredseventydegreetrans(const string ori[], string aftertrans[], const int size)
{
    onehundredeightydegreetrans(ori, aftertrans, size);
    string aftertrans3[10];
    for(int i = 0; i < size; ++i)
        aftertrans3[i] = ori[i];
    nintydegreetrans(aftertrans, aftertrans3, size);
    for(int i = 0; i < size; ++i)
        aftertrans[i] = aftertrans3[i];
}

void reflectiontrans(const string ori[], string aftertrans[], const int size)
{
    int num = size - 1;
    for(int i = 0; i < size; ++i)
        for(int j = 0; j < size; ++j)
            aftertrans[i][num - j] = ori[i][j];
}

void combinationtrans(const string ori[], string aftertrans[], const int size, const int seq)
{
    reflectiontrans(ori, aftertrans, size);
    string aftertrans4[10];
    for(int i = 0; i < size; ++i)
        aftertrans4[i] = ori[i];
    if(seq == 1)
        nintydegreetrans(aftertrans, aftertrans4, size);
    else if(seq == 2)
        onehundredeightydegreetrans(aftertrans, aftertrans4, size);
    else
        twohundredseventydegreetrans(aftertrans, aftertrans4, size);
    for(int i = 0; i < size; ++i)
        aftertrans[i] = aftertrans4[i];
}

int compare(const string* first, const string* second, const int size)
{
    for(int i = 0; i < size; ++i)
        if(first[i] != second[i])
            return 0;
    return 1;
}

int transform(const string ori[], const string trans[], int size)
{
    string aftertrans[10];
    for(int i = 0 ; i < size; ++i)
        aftertrans[i] = ori[i];
    nintydegreetrans(ori, aftertrans, size);
    if(compare(aftertrans, trans, size))
        return 1;
    onehundredeightydegreetrans(ori, aftertrans, size);
    if(compare(aftertrans, trans, size))
        return 2;
    twohundredseventydegreetrans(ori, aftertrans, size);
    if(compare(aftertrans, trans, size))
        return 3;
    reflectiontrans(ori, aftertrans, size);
    if(compare(aftertrans, trans, size))
        return 4;
    for(int i = 1; i <= 3; ++i)
    {
        combinationtrans(ori, aftertrans, size, i);
        if(compare(aftertrans, trans, size))
            return 5;
    }
    if(compare(ori, trans, size))
        return 6;
    return 7;
}

int main()
{
    ofstream fout("transform.out");
    ifstream fin("transform.in");
    int num;
    string ori[10];
    string trans[10];
    fin >> num;
    getline(fin, ori[0]);
    for(int i = 0 ;i < num; ++i)
    {
        getline(fin, ori[i]);
    }
    for(int i = 0 ;i < num; ++i)
    {
        getline(fin, trans[i]);
    }
    fout << transform(ori, trans, num) << endl;
}
