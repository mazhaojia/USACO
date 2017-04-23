/*
ID: mazhaoj1
PROG: combo
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
using namespace std;

bool found[1000000];

int calc(int* a, int n)
{
	int aa, bb, cc, ret = 0;
	for(int i = -2; i <= 2; ++i)
	{
		aa = a[0];
		aa += i;
		if(aa <= 0)
			aa += n;
		else if(aa > n)
			aa -= n;
		for(int j = -2; j <= 2; ++j)
		{
			bb = a[1];
			bb += j;
			if(bb <= 0)
				bb += n;
			else if(bb > n)
				bb -= n;
			for(int k = -2; k <= 2; ++k)
			{
				cc = a[2];
				cc += k;
				if(cc <= 0)
					cc += n;
				else if(cc > n)
					cc -= n;
				if(!found[aa * 100 + bb * 10 + cc])
				{
					ret++;
					found[aa * 100 + bb * 10 + cc] = true;
				}
			}
		}
	}
	return ret;
}

int main()
{
	ifstream fin("combo.in");
	ofstream fout("combo.out");
	int n, a[3], b[3];
	while(fin >> n)
	{
		memset(found, false, sizeof(found));
		for(int i = 0; i < 3; ++i)
			fin >> a[i];
		for(int i = 0; i < 3; ++i)
			fin >> b[i];
		if(n == 1)
			fout << 1 << endl;
		else if(n == 2)
			fout << 8 << endl;
		else
			fout << calc(a, n) + calc(b, n) << endl;
	}
}
