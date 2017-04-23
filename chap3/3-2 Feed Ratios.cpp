/*
ID: mazhaoj1
PROG: ratios
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int target[3], ratio[3][3];

int main()
{
    ifstream fin("ratios.in");
    ofstream fout("ratios.out");
    fin >> target[0] >> target[1] >> target[2];
    for(int i = 0; i < 3; ++i)
        fin >> ratio[i][0] >> ratio[i][1] >> ratio[i][2];
    int x, y, z, mini = 200, minj = 200, mink = 200, minl;
    if(target[0] == 0 && target[1] == 0 && target[2] == 0)
    {
        fout << "0 0 0 0" << endl;
        return 0;
    }
    int tarsum = target[0] + target[1] + target[2];
    for(int i = 0; i <= 100; ++i)
    {
        for(int j = 0; j <= 100; ++j)
        {
            for(int k = 1; k <= 100; ++k)
            {
                x = i * ratio[0][0] + j * ratio[1][0] + k * ratio[2][0];
                y = i * ratio[0][1] + j * ratio[1][1] + k * ratio[2][1];
                z = i * ratio[0][2] + j * ratio[1][2] + k * ratio[2][2];
                int sum = x + y + z;    //this technique is very useful!
                int div = sum / tarsum;
                if(target[0] * div == x && target[1] * div == y && target[2] * div == z)
                {
                    if(i + j + k < mini + minj + mink)
                    {
                        mini = i;
                        minj = j;
                        mink = k;
                        minl = x / target[0];
                    }
                }
            }
        }
    }
    if(mini != 200)
        fout << mini << ' ' << minj << ' ' << mink << ' ' << minl << endl;
    else
        fout << "NONE" << endl;
    return 0;
}
