/*
ID: mazhaoj1
PROG: packrec
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct rectangle
{
    int w, h;
}rec[4];

int minsize = 10000;

struct final
{
    int minsize, minw, minh;
}record[1536];

int recount = 0;

void judge(int w, int h)
{
    if(minsize >= w * h)
    {
        minsize = w * h;
        record[recount].minsize = minsize;
        if(w > h)
        {
            record[recount].minw = h;
            record[recount].minh = w;
        }
        else
        {
            record[recount].minw = w;
            record[recount].minh = h;
        }
        ++recount;
    }
}

void do1()
{
    int w = rec[0].w + rec[1].w + rec[2].w + rec[3].w;
    int h = max(max(max(rec[0].h, rec[1].h), rec[2].h), rec[3].h);
    judge(w, h);
}

void do2()
{
    int w = max(rec[0].w + rec[1].w + rec[2].w, rec[3].w);
    int h = rec[3].h + max(max(rec[0].h, rec[1].h), rec[2].h);
    judge(w, h);
}

void do3()
{
    int w = max(rec[0].w + rec[1].w, rec[3].w) + rec[2].w;
    int h = max(max(rec[0].h, rec[1].h) + rec[3].h, rec[2].h);
    judge(w, h);
}

void do4()
{
    int w = rec[0].w + max(rec[1].w, rec[3].w) + rec[2].w;
    int h = max(max(rec[0].h, rec[1].h + rec[3].h), rec[2].h);
    judge(w, h);
}

void do5()
{
    int w = max(rec[0].w, rec[3].w) + rec[1].w + rec[2].w;
    int h = max(max(rec[0].h + rec[3].h, rec[1].h), rec[2].h);
    judge(w, h);
}

void do6()
{
    int h = max(rec[0].h + rec[2].h, rec[1].h + rec[3].h);
    int w;
    if(rec[2].h >= rec[1].h + rec[3].h)
        w = max(max(rec[0].w, rec[2].w + rec[1].w), rec[2].w + rec[3].w);
    else if(rec[2].h > rec[3].h)
        w = max(max(rec[0].w + rec[1].w, rec[2].w + rec[1].w), rec[2].w + rec[3].w);
    else
        w = max(rec[0].w, rec[2].w) + max(rec[1].w, rec[3].w);
    judge(w, h);
}

void calc()
{
    do1();
    do2();
    do3();
    do4();
  //  do5();    actually 4 and 5 are the same.
    do6();
}

void swap(rectangle& r1, rectangle& r2)
{
    rectangle temp = r1;
    r1 = r2;
    r2 = temp;
}

void permute(int level)
{
    if(level == 4)
    {
        calc();
        return;
    }
    for(int i = level; i < 4; ++i)
    {
        swap(rec[i], rec[level]);
        permute(level + 1);
        swap(rec[i], rec[level]);
    }
}

void exchange(rectangle& r)
{
    int temp = r.w;
    r.w = r.h;
    r.h = temp;
}

void rotate()
{
    for(int i = 0; i < 16; ++i)
    {
        int j = 1;
        for(int k = 0; k < 4; ++k)
        {
            int v = j & i;
            if(v)
                exchange(rec[k]);
            j <<= 1;
        }
        permute(0);
        j = 1;
        for(int k = 0; k < 4; ++k)
        {
            int v = j & i;
            if(v)
                exchange(rec[k]);
            j <<= 1;
        }
    }
}

int comp(const void *p1, const void *p2)
{
    final* f1 = (final*)p1;
    final* f2 = (final*)p2;
    int value = f1->minsize - f2->minsize;
    if(value == 0)
        return f1->minw - f2->minw;
    return value;
}

int main()
{
    ofstream fout ("packrec.out");
    ifstream fin ("packrec.in");
    for(int i = 0; i < 4; ++i)
        fin >> rec[i].w >>rec[i].h;
    rotate();
    qsort(record, recount, sizeof(record[0]), comp);
    fout << minsize << endl;
    fout << record[0].minw << ' ' << record[0].minh << endl;
    for(int i = 1; i < recount; ++i)
    {
        if(record[i].minsize == record[i - 1].minsize)
        {
            if(record[i].minw > record[i - 1].minw)
                fout << record[i].minw << ' ' << record[i].minh << endl;
        }
        else
            break;
    }
    return 0;
}
