/*
ID: mazhaoj1
PROG: hidden
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

string str, temp;
int num;

/*
SOLVE 1: ��С��ʾ�����ο�2003����Ҽ�ѵ�����ģ�
"��Դ��<ǳ������С��ʾ����˼�����ַ���ѭ��ͬ�������е�Ӧ��>"
����ȡ�Ա�����[url]http://blog.csdn.net/cclsoft/archive/2010/04/09/5467743.aspx[/url]
������������i + k - lȡ��ȡ�ࣺ[url]http://whitedeath.is-programmer.com/posts/18404.html[/url]
ע����������2���ַ����Ƚϣ���������������һ���ַ���������MinimumRepresentation��j�±��1��ʼ

int MinimumRepresentation(char *s, int l)
{
    int i = 0, j = 1, k = 0, t;
    while(i < l && j < l && k < l)
    {
        t = s[(i + k) >= l ? i + k - l : i + k] - s[(j + k) >= l ? j + k - l : j + k];
        if(!t)
            k++;
        else
        {
            if(t > 0)
                i = i + k + 1;
            else
                j = j + k + 1;
            if(i == j)
                ++j;
            k = 0;
        }
    }
    return (i < j ? i : j);
}

int main()
{
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    temp.reserve(73);
    str.reserve(200001);
    fin >> num;
    getline(fin, temp);
    while(getline(fin, temp))
        str += temp;
    fout << MinimumRepresentation(const_cast<char*>(str.c_str()), str.size()) << endl;
}
*/

//SOLVE 2: ��׺���飬�ο�2004�꣬2009����Ҽ�ѵ�����ģ�"�����ڣ�<��׺����>"��"����幣�<��׺���顪�������ַ�������������>"
#define maxn 200002
int wa[maxn],wb[maxn],wv[maxn],wss[maxn];   //��������

//da�㷨����
int cmp(int *r,int a,int b,int l)
{return r[a]==r[b]&&r[a+l]==r[b+l];}
void da(int *r,int *sa,int n,int m)
{
     int i,j,p,*x=wa,*y=wb,*t;
     for(i=0;i<m;i++) wss[i]=0;
     for(i=0;i<n;i++) wss[x[i]=r[i]]++;
     for(i=1;i<m;i++) wss[i]+=wss[i-1];
     for(i=n-1;i>=0;i--) sa[--wss[x[i]]]=i;
     for(j=1,p=1;p<n;j*=2,m=p)
     {
       for(p=0,i=n-j;i<n;i++) y[p++]=i;
       for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
       for(i=0;i<n;i++) wv[i]=x[y[i]];
       for(i=0;i<m;i++) wss[i]=0;
       for(i=0;i<n;i++) wss[wv[i]]++;
       for(i=1;i<m;i++) wss[i]+=wss[i-1];
       for(i=n-1;i>=0;i--) sa[--wss[wv[i]]]=y[i];
       for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
       x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
     }
     return;
}

//dc3�㷨����
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)
int c0(int *r,int a,int b)
{return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}
int c12(int k,int *r,int a,int b)
{if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
 else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];}
void sort(int *r,int *a,int *b,int n,int m)
{
     int i;
     for(i=0;i<n;i++) wv[i]=r[a[i]];
     for(i=0;i<m;i++) wss[i]=0;
     for(i=0;i<n;i++) wss[wv[i]]++;
     for(i=1;i<m;i++) wss[i]+=wss[i-1];
     for(i=n-1;i>=0;i--) b[--wss[wv[i]]]=a[i];
     return;
}
void dc3(int *r,int *sa,int n,int m)
{
     int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
     r[n]=r[n+1]=0;
     for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
     sort(r+2,wa,wb,tbc,m);
     sort(r+1,wb,wa,tbc,m);
     sort(r,wa,wb,tbc,m);
     for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
     rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
     if(p<tbc) dc3(rn,san,tbc,p);
     else for(i=0;i<tbc;i++) san[rn[i]]=i;
     for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
     if(n%3==1) wb[ta++]=n-1;
     sort(r,wb,wa,ta,m);
     for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
     for(i=0,j=0,p=0;i<ta && j<tbc;p++)
     sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
     for(;i<ta;p++) sa[p]=wa[i++];
     for(;j<tbc;p++) sa[p]=wb[j++];
     return;
}

//����ʼ
int sa[maxn * 3];   //����dc3����Ϊmaxn���ɣ��˴����Ҫ��dc3�������maxn * 3
int r[maxn * 3];    //����dc3����Ϊmaxn���ɣ��˴����Ҫ��dc3�������maxn * 3
int main()
{
    ifstream fin("hidden.in");
    ofstream fout("hidden.out");
    temp.reserve(73);
    str.reserve(200000);
    fin >> num;
    getline(fin, temp);
    while(getline(fin, temp))
        str += temp;
    str += str;
    num *= 2;
    for(int i = 0; i < num; ++i)
        r[i] = str[i] - 'a' + 1;
    r[num] = 27;    //������1������������������aaa�����������⣬���nocow��
    r[num + 1] = 0; //��׺���麯����Ҫ����������������һ��0������0ǰ���ÿ������Ҫ����0
   // da(r, sa, num + 2, 28); //�����㷨�����һ�������Ǳ����������������һ����
    dc3(r, sa, num + 2, 28);    //dc3�㷨����Ҫע��r�Ŀ��ÿռ����Ϊ����������������3����
    fout << sa[1] << endl;  //������Ϊ�����˸�0������sa[0]�ض���num+1��sa[1]��������Ҫ�ҵĴ�
}
