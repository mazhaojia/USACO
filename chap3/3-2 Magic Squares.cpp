/*
ID: mazhaoj1
PROG: msquare
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
using namespace std;

int square[8] = {1, 2, 3, 4, 5, 6, 7, 8}, target[8], fact[9], front, end, cnt;
bool visited[40320];
char result[40320];

struct queue
{
    int num[8];
}qu[40320], p, q;

struct answer
{
    char op;
    int pre;
}ans[40320];

void doa(int* square)
{
    int temp;
    for(int j = 0, k = 7; j < 4; ++j, --k)
    {
        temp = square[j];
        square[j] = square[k];
        square[k] = temp;
    }
}

void dob(int* square)
{
    int up, down;
    up = square[3];
    down = square[4];
    for(int j = 2, k = 5; j >= 0; --j, ++k)
    {
        square[j + 1] = square[j];
        square[k - 1] = square[k];
    }
    square[0] = up;
    square[7] = down;
}

void doc(int* square)
{
    int temp = square[6];
    square[6] = square[5];
    square[5] = square[2];
    square[2] = square[1];
    square[1] = temp;
}

bool match(int* square)
{
    for(int i = 0; i < 8; ++i)
        if(square[i] != target[i])
            return false;
    return true;
}

void calcfact(int n)
{
    fact[0] = 1;
    for(int i = 1; i <= n; ++i)
        fact[i] = i * fact[i - 1];
}

int cantorHash(int* num, int len)   //康托展开, num为一串连续的各不相同的数字排列，结果为其为第几大的排列, hash = [0, len!)
{
    int hash = 0, total;
    for(int i = 0; i < len - 1; i++)
    {
        total = 0;
        for(int j = i + 1; j < len; ++j)
            if(num[j] < num[i])
                ++total;
        hash += total * fact[len - i - 1];
    }
    return hash;
}

void solve()
{
    int size = sizeof(int) * 8;
    while(front != end)
    {
        int pos = front;
        memcpy(p.num, qu[pos].num, size);
        if(match(p.num))
            return;
        front++;
        int value;
        memcpy(q.num, p.num, size);
        doa(q.num);
        value = cantorHash(q.num, 8);
        if(visited[value] == false)
        {
            visited[value] = true;
            memcpy(qu[end].num, q.num, size);
            ans[end].op = 'A';
            ans[end].pre = pos;
            end++;
        }
        memcpy(q.num, p.num, size);
        dob(q.num);
        value = cantorHash(q.num, 8);
        if(visited[value] == false)
        {
            visited[value] = true;
            memcpy(qu[end].num, q.num, size);
            ans[end].op = 'B';
            ans[end].pre = pos;
            end++;
        }
        memcpy(q.num, p.num, size);
        doc(q.num);
        value = cantorHash(q.num, 8);
        if(visited[value] == false)
        {
            visited[value] = true;
            memcpy(qu[end].num, q.num, size);
            ans[end].op = 'C';
            ans[end].pre = pos;
            end++;
        }
    }
}

void answer()
{
    int pos = front, temp;
    while(ans[pos].pre != -1)
    {
        result[cnt++] = ans[pos].op;
        pos = ans[pos].pre;
    }
    for(int i = 0, j = cnt - 1; i < j; ++i, --j)
    {
        temp = result[i];
        result[i] = result[j];
        result[j] = temp;
    }
    result[cnt] = '\0';
}

int main()
{
    ifstream fin("msquare.in");
    ofstream fout("msquare.out");
    for(int j = 0; j < 8; ++j)
        fin >> target[j];
    calcfact(8);
    memcpy(p.num, square, sizeof(int) * 8);
    memcpy(qu[end].num, p.num, sizeof(int) * 8);
    visited[cantorHash(p.num, 8)] = true;
    ans[0].pre = -1;
    ans[0].op = '\0';
    end++;
    solve();
    answer();
    fout << cnt << endl;
    fout << result << endl;
    return 0;
}
