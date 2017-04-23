/*
ID: mazhaoj1
PROG: starry
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

int width, height, clucnt = -1;
int dir[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
char sky[100][100];
bool visited[100][100];
struct stars
{
    int row, col;
};
struct clusters
{
    stars star[160];
    char ch;
    int cnt, minrow, mincol, maxrow, maxcol, width, height;
    clusters():ch(0), cnt(0), minrow(101), mincol(101), maxrow(0), maxcol(0){}
}cluster[500][8];

void addstar(int i, int j)
{
    int t = cluster[clucnt][0].cnt;
    cluster[clucnt][0].star[t].row = i;
    cluster[clucnt][0].star[t].col = j;
    cluster[clucnt][0].cnt++;
    if(cluster[clucnt][0].minrow > i)
        cluster[clucnt][0].minrow = i;
    if(cluster[clucnt][0].mincol > j)
        cluster[clucnt][0].mincol = j;
    if(cluster[clucnt][0].maxrow < i)
        cluster[clucnt][0].maxrow = i;
    if(cluster[clucnt][0].maxcol < j)
        cluster[clucnt][0].maxcol = j;
}

void dfs(int i, int j)
{
    for(int k = 0; k < 8; ++k)
    {
        int newi = i + dir[k][0];
        int newj = j + dir[k][1];
        if(newi >= 0 && newi < height && newj >= 0 && newj < width && sky[newi][newj] == '1' && !visited[newi][newj])
        {
            visited[newi][newj] = true;
            addstar(newi, newj);
            dfs(newi, newj);
        }
    }
}

int cmp(const void* aa, const void* bb)
{
    stars* a = (stars*)aa;
    stars* b = (stars*)bb;
    if(a->row == b->row)
        return a->col - b->col;
    return a->row - b->row;
}

void rotate(int n, int k)
{
    int t = height - 1, trow, tcol;
    for(int i = 0; i < cluster[n][k].cnt; ++i)
    {
        trow = cluster[n][k].star[i].row;
        tcol = cluster[n][k].star[i].col;
        cluster[n][k].star[i].row = tcol;
        cluster[n][k].star[i].col = t - trow;
    }
    t = cluster[n][k].height;
    cluster[n][k].height = cluster[n][k].width;
    cluster[n][k].width = t;
}

void reflect(int n, int k)
{
    double midcol = cluster[n][k].mincol + cluster[n][k].maxcol / 2.0;
    for(int i = 0; i < cluster[n][k].cnt; ++i)
    {
        int t = cluster[n][k].star[i].col;
        if(t < midcol)
            cluster[n][k].star[i].col += (int)((midcol - t) * 2);
        else if(t > midcol)
            cluster[n][k].star[i].col -= (int)((t - midcol) * 2);
    }
}

void generate(int n)
{
    for(int k = 1; k <= 3; ++k)
    {
        memcpy(&cluster[n][k], &cluster[n][k - 1], sizeof(clusters));
        rotate(n, k);
        qsort(cluster[n][k].star, cluster[n][k].cnt, sizeof(stars), cmp);
    }
    for(int k = 4; k <= 7; ++k)
    {
        memcpy(&cluster[n][k], &cluster[n][k - 4], sizeof(clusters));
        reflect(n, k);
        qsort(cluster[n][k].star, cluster[n][k].cnt, sizeof(stars), cmp);
    }
}

bool similar(int i, int j, int k)
{
    int disrow, discol, nowdisrow, nowdiscol;
    disrow = cluster[i][0].star[0].row - cluster[j][k].star[0].row;
    discol = cluster[i][0].star[0].col - cluster[j][k].star[0].col;
    for(int m = 1; m < cluster[i][0].cnt; ++m)
    {
        nowdisrow = cluster[i][0].star[m].row - cluster[j][k].star[m].row;
        nowdiscol = cluster[i][0].star[m].col - cluster[j][k].star[m].col;
        if(disrow != nowdisrow || discol != nowdiscol)
            return false;
    }
    return true;
}

bool checkshape(int i, int j)
{
    if(cluster[i][0].cnt != cluster[j][0].cnt)
        return false;
    if(cluster[i][0].height != cluster[j][0].height && cluster[i][0].height != cluster[j][0].width)
        return false;
    if(cluster[i][0].width != cluster[j][0].width && cluster[i][0].width != cluster[j][0].height)
        return false;
    for(int k = 0; k < 8; ++k)
        if(similar(i, j, k))
            return true;
    return false;
}

int main()
{
    ifstream fin("starry.in");
    ofstream fout("starry.out");
    fin >> width >> height;
    for(int i = 0 ; i < height; ++i)
        for(int j = 0; j < width; ++j)
            fin >> sky[i][j];
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            if(sky[i][j] == '0' || visited[i][j])
                continue;
            clucnt++;
            addstar(i, j);
            visited[i][j] = true;
            dfs(i, j);
        }
    }
    clucnt++;
    for(int i = 0; i < clucnt; ++i)
    {
        cluster[i][0].height = cluster[i][0].maxrow - cluster[i][0].minrow + 1;
        cluster[i][0].width = cluster[i][0].maxcol - cluster[i][0].mincol + 1;
        qsort(cluster[i][0].star, cluster[i][0].cnt, sizeof(stars), cmp);
        generate(i);
    }
    char letter = 'a';
    for(int i = 0; i < clucnt; ++i)
    {
        if(cluster[i][0].ch != '\0')
            continue;
        cluster[i][0].ch = letter;
        for(int j = i + 1; j < clucnt; ++j)
        {
            if(cluster[j][0].ch != '\0')
                continue;
            if(checkshape(i, j))
                cluster[j][0].ch = letter;
        }
        letter++;
    }
    for(int i = 0; i < clucnt; ++i)
        for(int j = 0; j < cluster[i][0].cnt; ++j)
            sky[cluster[i][0].star[j].row][cluster[i][0].star[j].col] = cluster[i][0].ch;
    for(int i = 0; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
            fout << sky[i][j];
        fout << endl;
    }
    return 0;
}
