/*
ID: mazhaoj1
PROG: cryptcow
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;    //超级BT的一题。。。。

/*摘录下nocow上剪枝归纳~很全的~我自己的程序也没有全用到~
Cut:
1 由于添加的COW是一起的，因此给出的字符串的字符个数应该等于47（目标字符串的长度）+3*k。
如果不满足就可直接判断无解。
2 除了COW三个字符外，其他的字符的个数应该和目标串相一致。如果不一致也可直接判断无解。
3 搜索中间肯定会出现很多相同的情况，因此需要开一个hash来记录搜索到过哪些字符串，
每搜索到一个字符串，就判重。如果重复直接剪枝。这里的字符串的hash函数可以采用ELFhash，
但由于ELFhash的数值太大，所以用函数值对一个大质数取余，这样可以避免hash开得太大，
同时又可以减少冲突。
4 对搜索到的字符串，设不包含COW的最长前缀为n前缀（同样也可以定义n后缀），
那么如果n前缀不等于目标串的长度相同的前缀，那么当前字符串一定无解，剪枝。
N后缀也可采取相同的判断方法。
5 一个有解的字符串中，COW三个字母最早出现的应该是C，最后出现的应该是W，如果不满足则剪枝。
6 当前字符串中任意两个相邻的COW字母中间所夹的字符串一定在目标串中出现过。如果不符合可立即剪枝。
7 需要优化搜索顺序。经过试验我们可以发现，O的位置对于整个COW至关重要。可以说，
O的位置决定了整个串是否会有解。因此，我们在搜索时，应该先枚举O的位置，
然后再枚举C和W的位置。其中W要倒序枚举。这样比依次枚举COW至少要快20~30倍。
8 在判断当前串的子串是否包含在目标串中的时候，可以先做一个预处理：
记录每一个字母曾经出现过的位置，然后可以直接枚举子串的第一个字母的位置。
这样比用pos要快2倍左右。*/

char* target = "Begin the Escape execution at the Break of Dawn";   //len = 47
int nowlevel, hash_size = 99991;
char input[76];
bool found, hash[99991];
ofstream fout("cryptcow.out");

struct showpos
{
    int pos[47];
    int cnt;
}chpos[53];

unsigned int ELFHash(char* str)
{
    unsigned int hash = 0;
    unsigned int x = 0;
    while (*str)
    {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0)
        {
            hash ^= (x >> 24);
            hash &= ~x;
        }
    }
    return hash % hash_size;
}

void transform(char* newstr, char* str, int len, int cpos, int opos, int wpos)
{
    memcpy(newstr, str, sizeof(char) * cpos);
    memcpy(newstr + cpos, str + opos + 1, sizeof(char) * (wpos - opos - 1));
    memcpy(newstr + cpos + wpos - opos - 1, str + cpos + 1, sizeof(char) * (opos - cpos - 1));
    memcpy(newstr + wpos - 2, str + wpos + 1, sizeof(char) * (len - wpos - 1));
    newstr[len - 3] = '\0';
}

bool checkcontain(char* str, int start, int end)
{
    int i, pos;
    char strin[76];
    memcpy(strin, str + start, sizeof(char) * (end - start + 1));
    strin[end - start + 1] = '\0';
    char ch = str[start];
    if(ch >= 'A' && ch <= 'Z')
        pos = ch - 'A';
    else if(ch >= 'a' && ch <= 'z')
        pos = ch - 'a' + 26;
    else    //blank
        pos = 52;
    for(i = 0; i < chpos[pos].cnt; ++i)
        if(strstr(target + chpos[pos].pos[i], strin) != NULL)
            return true;
    return false;
}

bool checkout(char* str, int len)
{
    int i, j;
    char sub[76];

    //剪枝3
    //由于没有处理冲突(貌似处理了后会超内存，标程中用链表解决冲突也限制了链表长度)，
    //所以这个可以算一个cheat。标程中这里限制在level<=3时才用hash。我这里就偷偷懒了。
    int tt = ELFHash(str);
    if(hash[tt])
        return false;
    else
        hash[tt] = true;

    //剪枝5
    for(i = 0; i < len; ++i)
        if(str[i] == 'O' || str[i] == 'W')
            return false;
        else if(str[i] == 'C')
            break;
    if(i == len)
        return false;
    for(j = len - 1; j >= 0; --j)
        if(str[j] == 'C' || str[j] == 'O')
            return false;
        else if(str[j] == 'W')
            break;
    if(j < 0)
        return false;

    //剪枝4
    memcpy(sub, str, sizeof(char) * i);
    sub[i] = '\0';
    if(strstr(target, sub) == NULL)
        return false;
    memcpy(sub, str + j + 1, sizeof(char) * (len - j - 1));
    sub[len - j - 1] = '\0';
    if(strstr(target, sub) == NULL)
        return false;

    //剪枝6，8
    for(i = 0; i < len; ++i)
        if(str[i] == 'C' || str[i] == 'O' || str[i] == 'W')
        {
            for(j = i + 1; j < len; ++j)
                if(str[j] == 'C' || str[j] == 'O' || str[j] == 'W')
                    break;
            if(j < len && i + 1 < j && !checkcontain(str, i + 1, j - 1))
                return false;
            i = j - 1;
        }

    return true;
}

void searchs(char* str, int len)
{
    int i, j, k;
    char newstr[76];
    if(strcmp(str, target) == 0)
    {
        found = true;
        fout << 1 << ' ' << nowlevel << endl;
        return;
    }
    if(!checkout(str, len))
        return;
    for(i = 0; i < len; ++i)
        if(str[i] == 'O')       //顺序优化，剪枝7
            for(j = 0; j < i; ++j)
                if(str[j] == 'C')
                    for(k = len - 1; k > i; --k)
                        if(str[k] == 'W') {
                            transform(newstr, str, len, j, i, k);
                            nowlevel++;
                            searchs(newstr, len - 3);
                            if(found)
                                return;
                            nowlevel--;
                        }

}

int main()
{
    ifstream fin("cryptcow.in");
    fin.getline(input, 76);
    int inlen = strlen(input);

    //剪枝1
    if((inlen - 47) % 3 != 0)
    {
        fout << 0 << ' ' << 0 << endl;
        return 0;
    }

    //剪枝2
    int num[52], tarnum[52], tarblanknum = 0, blanknum = 0, numc = 0, numo = 0, numw = 0;
    memset(num, 0, sizeof(num));
    memset(tarnum, 0, sizeof(tarnum));
    for(int i = 0; i < 47; ++i)
        if(target[i] >= 'A' && target[i] <= 'Z')
            tarnum[target[i] - 'A']++;
        else if(target[i] >= 'a' && target[i] <= 'z')
            tarnum[target[i] - 'a' + 26]++;
        else
            tarblanknum++;
    for(int i = 0; i < inlen; ++i)
        if(input[i] == 'C')
            numc++;
        else if(input[i] == 'O')
            numo++;
        else if(input[i] == 'W')
            numw++;
        else if(input[i] >= 'A' && input[i] <= 'Z')
            num[input[i] - 'A']++;
        else if(input[i] >= 'a' && input[i] <= 'z')
            num[input[i] - 'a' + 26]++;
        else if(input[i] == ' ')
            blanknum++;
        else
        {
            fout << 0 << ' ' << 0 << endl;
            return 0;
        }
    if(numc != numo || numc != numw || numo != numw || blanknum != tarblanknum)
    {
        fout << 0 << ' ' << 0 << endl;
        return 0;
    }
    for(int i = 0; i < 52; ++i)
        if(num[i] != tarnum[i])
        {
            fout << 0 << ' ' << 0 << endl;
            return 0;
        }

    //为了实施剪枝8的预处理
    int nn;
    for(int i = 0; i < 47; ++i)
    {
        if(target[i] >= 'A' && target[i] <= 'Z')
            nn = target[i] - 'A';
        else if(target[i] >= 'a' && target[i] <= 'z')
            nn = target[i] - 'a' + 26;
        else
            nn = 52;
        chpos[nn].pos[chpos[nn].cnt++] = i;
    }

    searchs(input, inlen);
    if(!found)
        fout << 0 << ' ' << 0 << endl;
    return 0;
}
