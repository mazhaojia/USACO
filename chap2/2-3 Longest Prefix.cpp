/*
ID: mazhaoj1
PROG: prefix
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct node
{
    node* children[26];
    bool isend;
    node()
    {
        for(int i = 0; i < 26; ++i)
            children[i] = NULL;
        isend = false;
    }
}root;

string srch;
int prefix[200000];

bool find()
{
    int size = srch.size();
    node* p = &root;
    for(int i = 0; i < size; ++i)
    {
        int pos = srch[i] - 'A';
        p = p->children[pos];
        if(p == NULL)
            return false;
    }
    if(p->isend == true)
        return true;
    return false;
}

int main()
{
    ifstream fin("prefix.in");
    ofstream fout("prefix.out");
    string primitive, content, temp;
    fin >> primitive;
    int maxlen = 0;
    while(primitive != ".")
    {
        int size = primitive.size();
        if(maxlen < size)
            maxlen = size;
        node *p = &root;
        for(int i = 0; i < size; ++i)
        {
            int pos = primitive[i] - 'A';
            if(p->children[pos] == NULL)
            {
                node* pp = new node;
                p->children[pos] = pp;
            }
            p = p->children[pos];
        }
        p->isend = true;
        fin >> primitive;
    }
    while(fin >> temp)
        content += temp;
    int size = content.size();
    srch = content[0];
    if(find())
        prefix[0] = 1;
    int i, j, k;
    for(i = 1; i < size; ++i)
    {
        int left = i - maxlen + 1;
        if(left < 0)
            left = 0;
        prefix[i] = prefix[i - 1];
        if(i - (prefix[i] - 1) > maxlen)
            break;
        for(j = left; j <= i; ++j)
        {
            srch = "";
            for(k = j; k <= i; ++k)
                srch += content[k];
            if(find() && ((j > 0 && prefix[j - 1] == j) || j == 0))
            {
                prefix[i] = i + 1;
                break;
            }
        }
    }
    if(i == size)
        --i;
    fout << prefix[i] << endl;
    return 0;
}
