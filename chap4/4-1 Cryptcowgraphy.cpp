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
using namespace std;    //����BT��һ�⡣������

/*ժ¼��nocow�ϼ�֦����~��ȫ��~���Լ��ĳ���Ҳû��ȫ�õ�~
Cut:
1 ������ӵ�COW��һ��ģ���˸������ַ������ַ�����Ӧ�õ���47��Ŀ���ַ����ĳ��ȣ�+3*k��
���������Ϳ�ֱ���ж��޽⡣
2 ����COW�����ַ��⣬�������ַ��ĸ���Ӧ�ú�Ŀ�괮��һ�¡������һ��Ҳ��ֱ���ж��޽⡣
3 �����м�϶�����ֺܶ���ͬ������������Ҫ��һ��hash����¼����������Щ�ַ�����
ÿ������һ���ַ����������ء�����ظ�ֱ�Ӽ�֦��������ַ�����hash�������Բ���ELFhash��
������ELFhash����ֵ̫�������ú���ֵ��һ��������ȡ�࣬�������Ա���hash����̫��
ͬʱ�ֿ��Լ��ٳ�ͻ��
4 �����������ַ������費����COW���ǰ׺Ϊnǰ׺��ͬ��Ҳ���Զ���n��׺����
��ô���nǰ׺������Ŀ�괮�ĳ�����ͬ��ǰ׺����ô��ǰ�ַ���һ���޽⣬��֦��
N��׺Ҳ�ɲ�ȡ��ͬ���жϷ�����
5 һ���н���ַ����У�COW������ĸ������ֵ�Ӧ����C�������ֵ�Ӧ����W��������������֦��
6 ��ǰ�ַ����������������ڵ�COW��ĸ�м����е��ַ���һ����Ŀ�괮�г��ֹ�����������Ͽ�������֦��
7 ��Ҫ�Ż�����˳�򡣾����������ǿ��Է��֣�O��λ�ö�������COW������Ҫ������˵��
O��λ�þ������������Ƿ���н⡣��ˣ�����������ʱ��Ӧ����ö��O��λ�ã�
Ȼ����ö��C��W��λ�á�����WҪ����ö�١�����������ö��COW����Ҫ��20~30����
8 ���жϵ�ǰ�����Ӵ��Ƿ������Ŀ�괮�е�ʱ�򣬿�������һ��Ԥ����
��¼ÿһ����ĸ�������ֹ���λ�ã�Ȼ�����ֱ��ö���Ӵ��ĵ�һ����ĸ��λ�á�
��������posҪ��2�����ҡ�*/

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

    //��֦3
    //����û�д����ͻ(ò�ƴ����˺�ᳬ�ڴ棬���������������ͻҲ������������)��
    //�������������һ��cheat�����������������level<=3ʱ����hash���������͵͵���ˡ�
    int tt = ELFHash(str);
    if(hash[tt])
        return false;
    else
        hash[tt] = true;

    //��֦5
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

    //��֦4
    memcpy(sub, str, sizeof(char) * i);
    sub[i] = '\0';
    if(strstr(target, sub) == NULL)
        return false;
    memcpy(sub, str + j + 1, sizeof(char) * (len - j - 1));
    sub[len - j - 1] = '\0';
    if(strstr(target, sub) == NULL)
        return false;

    //��֦6��8
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
        if(str[i] == 'O')       //˳���Ż�����֦7
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

    //��֦1
    if((inlen - 47) % 3 != 0)
    {
        fout << 0 << ' ' << 0 << endl;
        return 0;
    }

    //��֦2
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

    //Ϊ��ʵʩ��֦8��Ԥ����
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
