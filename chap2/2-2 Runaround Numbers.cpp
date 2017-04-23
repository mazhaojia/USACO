/*
ID: mazhaoj1
PROG: runround
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

int main()
{
    ofstream fout("runround.out");
    ifstream fin("runround.in");
    int m, digit[9], cnt, ans, temp, res, pos, nextpos, i;
    bool used[10], exit;
    fin >> m;
    ans = m + 1;
    while(ans <= 987654321)
    {
        cnt = 0;
        memset(used, false, sizeof(used));
        temp = ans;
        exit = false;
        while(temp > 0)
        {
            res = temp % 10;
            if(res == 0)
            {
                exit = true;
                break;
            }
            if(used[res] == false)
                used[res] = true;
            else
            {
                exit = true;
                break;
            }
            digit[cnt++] = res;
            temp = temp / 10;
        }
        if(exit == false)
        {
            memset(used, false, sizeof(used));
            pos = 0, nextpos = -1;
            while(nextpos != 0)
            {
                if(used[digit[cnt - 1 - pos]] == false)
                    used[digit[cnt - 1 - pos]] = true;
                else
                    break;
                nextpos = pos + digit[cnt - 1 - pos] - cnt;
                if(nextpos < 0)
                    nextpos += cnt;
                nextpos %= cnt;
                pos = nextpos;
            }
            if(nextpos == 0)
                for(i = 0; i < cnt; ++i)
                    if(used[digit[i]] == false)
                        break;
            if(i == cnt)
            {
                fout << ans << endl;
                return 0;
            }
        }
        ans++;
    }
    return 0;
}
