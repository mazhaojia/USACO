/*
ID: mazhaoj1
PROG: lgame
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

/*[转]对于1个单词，我们只要在字典中扫一遍，记录每个单词的分数和它是否能被所给字母组成。
对于2个单词，我们只找所有能被组成的单词，再判断由它们组合的词组是否能被所给字母组成。
对于最终结果排序输出。*/

int score[26] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7, 6, 3, 5, 2, 3, 5, 7, 2, 1, 2, 4, 6, 6, 7, 5, 7};
int incnt[26], wdcnt[26], wcnt, newwcnt, maxscore, anscnt;
struct compond
{
    char word1[8], word2[8];
    int score;
}word[10000], ans[5000];

int cmp(const void* aa, const void* bb)
{
    compond* a = (compond*)aa;
    compond* b = (compond*)bb;
    int t = strcmp(a->word1, b->word1);
    if(t == 0)
    {
        if(a->word2[0] == '\0')
            return -1;
        if(b->word2[0] == '\0')
            return 1;
        return strcmp(a->word2, b->word2);
    }
    return t;
}

int main()
{
    ifstream fin("lgame.in");
    ofstream fout("lgame.out");
    ifstream dicin("lgame.dict");
    char str[8];
    fin.getline(str, 8);
    for(char* p = str; *p != '\0'; ++p)
        incnt[*p - 'a']++;
    dicin.getline(word[wcnt].word1, 8);
    char* p;
    while(word[wcnt].word1[0] != '.')
    {
        memset(wdcnt, 0, sizeof(wdcnt));
        for(p = word[wcnt].word1; *p != '\0'; ++p)
        {
            wdcnt[*p - 'a']++;
            if(wdcnt[*p - 'a'] > incnt[*p - 'a'])
                break;
        }
        if(*p == '\0')
        {
            for(p = word[wcnt].word1; *p != '\0'; ++p)
                word[wcnt].score += score[*p - 'a'];
            wcnt++;
        }
        dicin.getline(word[wcnt].word1, 8);
    }
    newwcnt = wcnt;
    for(int i = 0; i < wcnt; ++i)
    {
        if(maxscore < word[i].score)
            maxscore = word[i].score;
        for(int j = i; j < wcnt; ++j)
        {
            memset(wdcnt, 0, sizeof(wdcnt));
            for(p = word[i].word1; *p != '\0'; ++p)
                wdcnt[*p - 'a']++;
            for(p = word[j].word1; *p != '\0'; ++p)
            {
                wdcnt[*p - 'a']++;
                if(wdcnt[*p - 'a'] > incnt[*p - 'a'])
                    break;
            }
            if(*p == '\0')
            {
                strcpy(word[newwcnt].word1, word[i].word1);
                strcpy(word[newwcnt].word2, word[j].word1);
                word[newwcnt].score = word[i].score + word[j].score;
                if(maxscore < word[newwcnt].score)
                    maxscore = word[newwcnt].score;
                newwcnt++;
            }
        }
    }
    fout << maxscore << endl;
    for(int i = 0; i < newwcnt; ++i)
    {
        if(word[i].score == maxscore)
        {
            strcpy(ans[anscnt].word1, word[i].word1);
            if(word[i].word2[0] != '\0')
                strcpy(ans[anscnt].word2, word[i].word2);
            anscnt++;
        }
    }
    qsort(ans, anscnt, sizeof(ans[0]), cmp);
    for(int i = 0; i < anscnt; ++i)
    {
        fout << ans[i].word1;
        if(ans[i].word2[0] != '\0')
            fout << ' ' << ans[i].word2;
        fout << endl;
    }
    return 0;
}
