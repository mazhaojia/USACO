/*
ID: mazhaoj1
PROG: fence4
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;    //详见解题报告：http://www.docin.com/app/p?id=52574473

struct point
{
    double x,y;
    point(){}
    point(double x,double y)
    {
        this->x=x;
        this->y=y;
    }
    point operator + (const point& p) const
    {
        point np;
        np.x=this->x+p.x;
        np.y=this->y+p.y;
        return np;
    }
    point operator - (const point& p) const
    {
        point np;
        np.x=this->x-p.x;
        np.y=this->y-p.y;
        return np;
    }
    double operator * (const point& p) const  //叉乘，>0 clockwise ，<0 counterclockwise , =0 collinear
    {
        return this->x*p.y-p.x*this->y;
    }
};

double det(point p1,point p2)   //叉乘，>0 clockwise ，<0 counterclockwise , =0 collinear
{
   return p1.x*p2.y-p2.x*p1.y;
}

double direction(point pi,point pj,point pk) // >0 pipk clockwise from pipj , <0 pipk counterclockwise from pipj , =0 pipk collinear pipj
{
    return (pk-pi)*(pj-pi);
}

double consecutivedirection(point pi,point pj,point pk) // pipjpk is consecutive , >0 pjpk rightturn , <0 pjpk leftturn =0 pipjpk collinear
{
    return (pk-pi)*(pj-pi);
}
double distance(point p1,point p2)     //两点间的距离
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}
bool onsegment(point pi,point pj,point pk)
{
    if(min(pi.x,pj.x)<=pk.x && max(pi.x,pj.x)>=pk.x && min(pi.y,pj.y)<=pk.y && max(pi.y,pj.y)>=pk.y)
        return true;
    else
        return false;
}

int segment_intersection(point p1,point p2,point p3,point p4)  // p1p2,p3p4 intersection?
{
    double d1,d2,d3,d4;
    d1=direction(p3,p4,p1);
    d2=direction(p3,p4,p2);
    d3=direction(p1,p2,p3);
    d4=direction(p1,p2,p4);
    if( ((d1>0 && d2<0) || (d1<0 && d2>0)) && ((d3>0 && d4<0) || (d3<0 && d4>0)) )
        return 1;
    else if(abs(d1)<0.000001 && onsegment(p3,p4,p1))
        return 0;
    else if(abs(d2)<0.000001 && onsegment(p3,p4,p2))
        return 0;
    else if(abs(d3)<0.000001 && onsegment(p1,p2,p3))
        return 0;
    else if(abs(d4)<0.000001 && onsegment(p1,p2,p4))
        return 0;
    else
        return -1;
}

point user, corners[200];
int n;
bool cansee[200];

struct segment
{
    point p1, p2;
}seg[200];

void seeline(double angle)
{
    double mindis = 100000;
    int firstsee = -1;
    double lx = cos(angle);
    double ly = sin(angle);
    point p;
    p.x = lx;
    p.y = ly;
    double k, t;
    for(int i = 0; i < n; ++i)
    {
        if(det(seg[i].p1 - user, p) * det(seg[i].p2 - user, p) >= 0)
            continue;
        if(abs(seg[i].p2.x - seg[i].p1.x) < 0.000001)
            k = (seg[i].p1.x - user.x) / lx;
        else
        {
            t = (seg[i].p2.y - seg[i].p1.y) / (seg[i].p2.x - seg[i].p1.x);
            k = (t * (seg[i].p1.x - user.x) +  user.y - seg[i].p1.y) / (t * lx - ly);
        }
        if(k > 0 && k < mindis)
        {
            mindis = k;
            firstsee = i;
        }
    }
    if(firstsee != -1)
        cansee[firstsee] = true;
}

void sendbeam()
{
    for(int i = 0; i < n; ++i)
    {
        double angle = atan2(corners[i].y - user.y, corners[i].x - user.x);
        seeline(angle + 0.000001);
        seeline(angle - 0.000001);
    }
}

int main()  //详见解题报告：http://www.docin.com/app/p?id=52574473
{
    ifstream fin("fence4.in");
    ofstream fout("fence4.out");
    fin >> n;
    fin >> user.x >> user.y;
    for(int i = 0; i < n; ++i)
        fin >> corners[i].x >> corners[i].y;
    for(int i = 0; i < n - 1; ++i)
    {
        seg[i].p1 = corners[i];
        seg[i].p2 = corners[i + 1];
    }
    seg[n - 1].p1 = corners[0];
    seg[n - 1].p2 = corners[n - 1];
    for(int i = 0 ;i < n; ++i)
        for(int j = 0; j < n; ++j)
            if(i != j && segment_intersection(seg[i].p1, seg[i].p2, seg[j].p1, seg[j].p2) == 1)
            {
                fout << "NOFENCE" << endl;
                return 0;
            }

    sendbeam();
    int ans = 0;
    for(int i = 0; i < n; ++i)
        if(cansee[i])
            ans++;
    fout << ans << endl;    //输出要求先按第二点排序,再第一点,实际上,只需要把最后一条线段的两点交换顺序,再把最后两条线段交换顺序,输出即可
    for(int i = 0; i < n - 2; ++i)
        if(cansee[i])
            fout << seg[i].p1.x << ' ' << seg[i].p1.y << ' ' << seg[i].p2.x << ' ' << seg[i].p2.y << endl;
    if(cansee[n - 1])
        fout << seg[n - 1].p1.x << ' ' << seg[n - 1].p1.y << ' ' << seg[n - 1].p2.x << ' ' << seg[n - 1].p2.y << endl;
    if(cansee[n - 2])
        fout << seg[n - 2].p1.x << ' ' << seg[n - 2].p1.y << ' ' << seg[n - 2].p2.x << ' ' << seg[n - 2].p2.y << endl;
    return 0;
}
