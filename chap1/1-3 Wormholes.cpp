/*
ID: mazhaoj1
PROG: wormhole
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

int n, ret;
struct hole
{
	int x, y;
} holes[12];

struct p
{
	int a, b;
}selected[6];

vector<p> pairs;

int xnext[12], length;

bool visited[12];

bool dfs2(int curHole, int cnt)
{
	if(cnt > n)
		return true;
	if(xnext[curHole] == -1)
		return false;
	for(int i = 0; i < n / 2; ++i)
	{
		if(selected[i].a == xnext[curHole])
			return dfs2(selected[i].b, cnt + 1);
		if(selected[i].b == xnext[curHole])
			return dfs2(selected[i].a, cnt + 1);
	}
	return false;
}

bool hasCircle()
{
	for(int i = 0; i < n / 2; ++i)
		if(dfs2(selected[i].a, 1) || dfs2(selected[i].b, 1))
			return true;
	return false;
}

void dfs(int start, int level)
{
	if(level == n / 2)
	{
		if(hasCircle())
			ret++;
		return;
	}
	for(int i = start; i < length; ++i)
	{
		if(visited[pairs[i].a] || visited[pairs[i].b])
			continue;
		selected[level] = pairs[i];
		visited[pairs[i].a] = visited[pairs[i].b] = true;
		dfs(i + 1, level + 1);
		visited[pairs[i].a] = visited[pairs[i].b] = false;
	}
}

int main()
{
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");
	while(fin >> n)
	{
		for(int i = 0; i < n; ++i)
			fin >> holes[i].x >> holes[i].y;
		for(int i = 0; i < n; ++i)
		{
			int j, nearestX = 2147483647, nearestHole = -1;
			for(j = 0; j < n; ++j)
			{
				if(i != j && holes[i].y == holes[j].y && holes[i].x > holes[j].x)
				{
					if(nearestX > holes[i].x - holes[j].x)
					{
						nearestX = holes[i].x - holes[j].x;
						nearestHole = j;
					}
				}
			}
			xnext[i] = nearestHole;
		}
		for(int i = 0; i < n; ++i)
		{
			for(int j =  i + 1; j < n; ++j)
			{
				p pp;
				pp.a = i;
				pp.b = j;
				pairs.push_back(pp);
			}
		}
		length = pairs.size();
		ret = 0;
		memset(visited, false, sizeof(visited));
		dfs(0, 0);
		fout << ret << endl;
	}
}
