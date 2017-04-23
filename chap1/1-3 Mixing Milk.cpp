/*
ID: mazhaoj1
PROG: milk
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct farmer
{
    int total, price;
}f[5000];
int comp(const void *p1, const void *p2)
{
    const farmer* f1 = (farmer*)p1;
    const farmer* f2 = (farmer*)p2;
    return f1->price - f2->price;
}
int main() {
    ofstream fout ("milk.out");
    ifstream fin ("milk.in");
    int need, num, spend = 0;
    fin>>need>>num;
    for(int i = 0; i < num; ++i)
        fin>>f[i].price>>f[i].total;
    qsort(f, num, sizeof(farmer), comp);
    for(int i = 0; i < num; ++i)
    {
        if(need > f[i].total)
        {
            spend += f[i].total * f[i].price;
            need -= f[i].total;
        }
        else
        {
            spend += f[i].price * need;
            break;
        }
    }
    fout << spend << endl;
    return 0;
}
