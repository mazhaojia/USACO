/*
ID: mazhaoj1
PROG: friday
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fout("friday.out");
    ifstream fin("friday.in");
    int nums;
    fin>>nums;
    int size = 1900 + nums;
    int week[8] = {0};
    int redundant[13] = {0, 3, 0, 3, 2, 3, 2, 3, 3, 2, 3, 2, 3};
    int day = 6;
    week[6] = 1;
    int remain = 0;
    for(int j = 2; j <= 12; ++j)
    {
        remain = (redundant[j - 1] + remain) % 7;
        day = (6 + remain) % 7;
        if(day == 0)
            day = 7;
        week[day]++;
    }
    for(int i = 1901; i < size; ++i)
    {
        remain = (redundant[12] % 7 + remain) % 7;
        day = (6 + remain) % 7;
        if(day == 0)
            day = 7;
        week[day]++;
        remain = (redundant[1] % 7 + remain) % 7;
        day = (6 + remain) % 7;
        if(day == 0)
            day = 7;
        week[day]++;
        if(i % 400 == 0 || (i % 4 == 0 && i % 100 != 0))
            remain++;
        remain = (redundant[2] % 7 + remain) % 7;
        day = (6 + remain) % 7;
        if(day == 0)
            day = 7;
        week[day]++;
        for(int j = 4; j <= 12; ++j)
        {
            remain = (redundant[j - 1] + remain) % 7;
            day = (6 + remain) % 7;
            if(day == 0)
            day = 7;
            week[day]++;
        }
    }
    for(int i = 6; i <= 7; ++i)
        fout << week[i] << ' ';
    for(int i = 1; i <= 4; ++i)
        fout << week[i] << ' ';
    fout << week[5] << endl;
    return 0;
}
