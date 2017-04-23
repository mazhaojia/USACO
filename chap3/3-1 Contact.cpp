/*
ID: mazhaoj1
PROG: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;    //the output for this problem is too complicated!
//貌似标程比较巧妙，我这里比较蠢。。。
struct node
{
     int sum;
     node* zero, *one;
     node()
     {
         zero = one = NULL;
         sum = 0;
     }
}root;

struct result
{
    int sum;
    char pattern[13];
    result()
    {
        sum = 0;
        pattern[0] = '\0';
    }
}ans[1 << 13];

void buildtree(int level, int height, node* parent)
{
    if(level == height)
        return;
    parent->zero = new node();
    parent->one = new node();
    buildtree(level + 1, height, parent->zero);
    buildtree(level + 1, height, parent->one);
}

char temp[13];
int cnt, tcnt;

void getresult(node* parent)
{
    node* p;
    if(parent->zero != NULL)
    {
        p = parent->zero;
        temp[tcnt++] = '0';
        temp[tcnt++] = '\0';
        ans[cnt].sum += p->sum;
        strcpy(ans[cnt].pattern, temp);
        cnt++;
        tcnt--;
        getresult(p);
        tcnt--;
    }
    if(parent->one != NULL)
    {
        p = parent->one;
        temp[tcnt++] = '1';
        temp[tcnt++] = '\0';
        ans[cnt].sum += p->sum;
        strcpy(ans[cnt].pattern, temp);
        cnt++;
        tcnt--;
        getresult(p);
        tcnt--;
    }
}

int comp(const void* a, const void* b)
{
    result* f = (result*)a;
    result* s = (result*)b;
    if(f->sum == s->sum)
    {
        int lenf = strlen(f->pattern);
        int lens = strlen(s->pattern);
        if(lenf == lens)
            return strcmp(f->pattern, s->pattern);
        return lenf - lens;
    }
    return s->sum - f->sum;
}

int main()
{
    ifstream fin("contact.in");
    ofstream fout("contact.out");
    int a, b, n, i, j;
    fin >> a >> b >> n;
    char line[81];
    char code[200001];
    memset(code, '\0', sizeof(code));
    buildtree(0, b, &root);
    while(fin.getline(line, 81, '\n'))
        strcat(code, line);
    int length = strlen(code);
    for(i = 0; i < length; ++i)
    {
        int end = i + b;
        node* p = &root;
        for(j = i; j < length && j < end; ++j)
        {
            if(code[j] == '0')
            {
                p = p->zero;
                p->sum++;
            }
            else
            {
                p = p->one;
                p->sum++;
            }
        }
    }
    getresult(&root);
    qsort(ans, cnt, sizeof(ans[0]), comp);
    for(i = 0; i < cnt && n > 0 && ans[i].sum > 0; ++i)
    {
        int len = strlen(ans[i].pattern);
        if(len >= a && len <= b)
        {
            fout << ans[i].sum << endl;
            fout << ans[i].pattern;
            if(i == cnt - 1)
                fout << endl;
            int linecnt = 1;
            for(j = i + 1; j < cnt; ++j)
            {
                if(ans[j].sum == ans[i].sum)
                {
                    len = strlen(ans[j].pattern);
                    if(len >= a && len <= b)
                    {
                        if(linecnt != 0)
                            fout << ' ' << ans[j].pattern;
                        else
                            fout << ans[j].pattern;
                        linecnt = (linecnt + 1) % 6;
                        if(linecnt == 0)
                            fout << endl;
                    }
                }
                else
                {
                    if(linecnt != 0)
                        fout << endl;
                    break;
                }
            }
            i = j - 1;
            n--;
        }
    }
    return 0;
}
