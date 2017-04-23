/*
ID: mazhaoj1
PROG: castle
LANG: C++
*/

#include <iostream>
#include <fstream>
using namespace std;

int col,row, arr[50][50][5];
int component[2501], compcnt;   //2501, not 2500, it really matters!

void floodfill(int i, int j)
{
    arr[i][j][4] = compcnt;
    ++component[compcnt];
    if(arr[i][j][0] == 0 && arr[i][j - 1][4] == 0)
        floodfill(i, j - 1);
    if(arr[i][j][1] == 0 && arr[i - 1][j][4] == 0)
        floodfill(i - 1, j);
    if(arr[i][j][2] == 0 && arr[i][j + 1][4] == 0)
        floodfill(i, j + 1);
    if(arr[i][j][3] == 0 && arr[i + 1][j][4] == 0)
        floodfill(i + 1, j);
}

int main()
{
    ofstream fout("castle.out");
    ifstream fin("castle.in");
    fin >> col >> row;
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            int temp;
            fin >> temp;
            if((temp & 1) != 0)
                arr[i][j][0] = 1;
            if((temp & 2) != 0)
                arr[i][j][1] = 1;
            if((temp & 4) != 0)
                arr[i][j][2] = 1;
            if((temp & 8) != 0)
                arr[i][j][3] = 1;
        }
    }
    compcnt = 1;
    for(int i = 0; i < row; ++i)
    {
        for(int j = 0; j < col; ++j)
        {
            if(arr[i][j][4] == 0)
            {
                floodfill(i, j);
                compcnt++;
            }
        }
    }
    --compcnt;
    fout << compcnt << endl;
    int maxcomp = 0, maxrow, maxcol;
    for(int i = 1; i <= compcnt; ++i)
        if(component[i] > maxcomp)
            maxcomp = component[i];
    fout << maxcomp << endl;
    char direction;
    maxcomp = 0;    //this line matters if there is only one component!
    for(int j = 0; j < col; ++j)    //the order of row and col matters!
    {
        for(int i = row - 1; i >= 0; --i)
        {
            int temp;
            if(arr[i][j][1] == 1 && i - 1 >= 0 && arr[i][j][4] != arr[i - 1][j][4])
            {
                temp = component[arr[i][j][4]] + component[arr[i - 1][j][4]];
                if(temp > maxcomp)
                {
                    maxcomp = temp;
                    maxrow = i;
                    maxcol = j;
                    direction = 'N';
                }
            }   //the order of 'N' and 'E' matters!
            if(arr[i][j][2] == 1 && j + 1 < col && arr[i][j][4] != arr[i][j + 1][4])
            {
                temp = component[arr[i][j][4]] + component[arr[i][j + 1][4]];
                if(temp > maxcomp)
                {
                    maxcomp = temp;
                    maxrow = i;
                    maxcol = j;
                    direction = 'E';
                }
            }
        }
    }
    fout << maxcomp << endl;
    fout << maxrow + 1 << ' ' << maxcol + 1 << ' ' << direction << endl;
    return 0;
}
