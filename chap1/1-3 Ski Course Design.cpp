/*
ID: mazhaoj1
PROG: skidesign
LANG: C++
*/
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	ifstream fin("skidesign.in");
	ofstream fout("skidesign.out");
	int n, hills[1000], result;
	while(fin >> n)
	{
		result = 2147483647;
		int temp = 0;
		for(int i = 0; i < n; ++i)
			fin >> hills[i];
		sort(hills, hills + n);
		int i = hills[0];
		while(true)
		{
			int j = i + 17;
			if(j > hills[n - 1])
				break;
			temp = 0;
			for(int k = 0; k < n; ++k)
			{
				if(hills[k] > i)
					break;
				temp += (i - hills[k]) * (i - hills[k]);
			}
			for(int k = n - 1; k >= 0; --k)
			{
				if(hills[k] < j)
					break;
				temp += (hills[k] - j) * (hills[k] - j);
			}
			if(result > temp)
				result = temp;
			++i;
		}
		if(result > temp)
			result = temp;
		fout << result << endl;
	}
}
