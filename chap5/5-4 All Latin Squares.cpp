/*
ID: mazhaoj1
PROG: latin
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

/*
[ת]�����ֱ�������ǲ��еģ���֦���԰�����
1���Ե�һ��Ҳ�̶�Ϊ1,2,3,��n������ǵ�ÿ�ַ���������ͨ���ѵڶ��е���n�����ŵõ���������õķ���������(n-1)!�Ϳ����ˡ�
2�����һ�п��Բ����ѣ��ض��н⡣
3. Maigo�ĳ�ǿ��֦��
  1 2 3 4 5
  2 1 4 5 3
  ��ʱ���Եõ�2���û�Ȧ(1,2)(3,4,5)
  1 2 3 4 5
  2 3 1 5 4
  ��һ���������ʱΪ(1,2,3)(4,5)
��ʱ�Ѻ����з���ǰ3��֮ǰ������͵�һ������ǵȼ۵ģ����еĸı䲻Ӱ��⣬�������Ľ�ĸ����͵�һ�������ȡ�
����������ֻ���¼һ������Ľ�ĸ���������֮��ȼ۵������ֱ�ӰѼ�¼��ֵ�ӵ������Ｔ�ɡ�
��������ȼ۵��ҽ����û�Ȧ�ĸ�����ͬ���������û�Ȧ�ĳ����������ȡ�������Hash���ж��Ƿ�ȼۣ�
Hash[i,j]��ʾ�û�Ȧ����Ϊi�������û�Ȧ���ȵĻ�Ϊjʱ��ĸ������򲻻���ֳ�ͻ��
*/

int n, table[8][8], mulsum, cntsum, circlelen, hash[8][50];
long long ans;
bool markrow[8][8], markcol[8][8], calced[8];

int searchh(int row, int col)
{
    int temp, result = 0;
    if(row == n)
        return 1;
    if(row == 3 && col == 2)    //���������ν�ĵڶ��к͵�һ��(1234567)���û�Ȧ
    {
        memset(calced, false, sizeof(calced));
        cntsum = 0;
        mulsum = 1;
        for(int i = 1; i <= n; ++i)
        {
            if(calced[i])
                continue;
            calced[i] = true;
            circlelen = 1;
            for(int j = table[2][i]; j != i; j = table[2][j])
            {
                calced[j] = true;
                circlelen++;
            }
            cntsum++;
            mulsum *= circlelen;
        }
        if(hash[cntsum][mulsum] != 0)
            return hash[cntsum][mulsum];
    }
    for(int i = 1; i <= n; ++i)
    {
        if(markrow[row][i] || markcol[col][i])
            continue;
        temp = table[row][col];
        table[row][col] = i;
        markrow[row][i] = true;
        markcol[col][i] = true;
        if(col == n)
            result += searchh(row + 1, 2);
        else
            result += searchh(row, col + 1);
        markrow[row][i] = false;
        markcol[col][i] = false;
        table[row][col] = temp;
    }
    if(row == 3 && col == 2)
        hash[cntsum][mulsum] = result;
    return result;
}

int main()
{
    ifstream fin("latin.in");
    ofstream fout("latin.out");
    fin >> n;
    for(int i = 1; i <= n; ++i)
    {
        table[1][i] = i;
        markrow[1][i] = true;
        markcol[i][i] = true;
        table[i][1] = i;
        markrow[i][i] = true;
        markcol[1][i] = true;
    }
    ans = searchh(2, 2);
    for(int i = n - 1; i >= 2; --i)
        ans *= i;
    fout << ans << endl;
    return 0;
}
