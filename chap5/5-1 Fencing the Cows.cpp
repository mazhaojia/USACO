/*
ID: mazhaoj1
PROG: fc
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;	//直接套模板，汗

#define MAX 10000
struct point
{
    double x,y;
    point operator - (const point& p) const
    {
        point np;
        np.x=(this->x)-p.x;
        np.y=(this->y)-p.y;
        return np;
    }
    double operator * (const point& p) const  //叉乘，>0 clockwise ，<0 counterclockwise , =0 collinear
    {
        return (this->x)*p.y-p.x*(this->y);
    }
};
double direction(point pi,point pj,point pk) // >0 pipk clockwise from pipj , <0 pipk counterclockwise from pipj , =0 pipk collinear pipj
{
    return (pk-pi)*(pj-pi);
}
double distances(point p1,point p2)     //两点间的距离
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
point result[MAX];     //保存凸包上的点
point p[MAX];      //输入的点
int top,nums;     //top 栈顶，nums 输入点的数量
int cmp(const void *p1,const void *p2)
{
    point *p3,*p4;
    double m;
    p3=(point*)p1;
    p4=(point*)p2;
    m=direction(p[0],(*p3),(*p4));
    if(m>0) return 1;
    else if(abs(m)<=0.000001 && (distances(p[0],(*p3))<distances(p[0],(*p4))))
        return 1;
    else return -1;
}
void convexhull()
{
    int j;
    for(j=0;j<=2;j++)
    {
        result[j].x=p[j].x;
        result[j].y=p[j].y;
    }
    top=2;
    for(j=3;j<nums;j++)
    {
       while(direction(result[top-1],result[top],p[j])>=0 && top>=2)
            top--;
       result[top+1].x=p[j].x;
       result[top+1].y=p[j].y;
       top++;
    }
}   //then make sth use of the result[], top points exactly the last element!!
void prepare()
{
    int k,pos;
    point pp,temp;
    pp.x=pp.y=999999999;
    for(k=0;k<nums;k++)
    {
       if(pp.y>p[k].y)
       {
           pp=p[k];
           pos=k;
       }
       else if(pp.y==p[k].y && pp.x>p[k].x)
       {
           pp.x=p[k].x;
           pos=k;
       }
    }
    temp=p[0];
    p[0]=p[pos];
    p[pos]=temp;
    qsort(&p[1],nums-1,sizeof(point),cmp);
    convexhull();
}

int main()
{
    ifstream fin("fc.in");
    ofstream fout("fc.out");
    fout.precision(2);
    fout.setf(ios::fixed);
    int i;
    double len;
    fin >> nums;
    for(i=0;i<nums;i++)
        fin >> p[i].x >> p[i].y;
    if(nums==1)
    {
       fout << "0.00" << endl;
       return 0;
    }
    else if(nums==2)
    {
       fout << 2*distances(p[0],p[1]) << endl;
       return 0;
    }
    prepare();
    len=0.0;
    for(i=0;i<top;i++)
       len=len+distances(result[i],result[i+1]);
    len=len+distances(p[0],result[top]);
    fout << len << endl;
    return 0;
}
