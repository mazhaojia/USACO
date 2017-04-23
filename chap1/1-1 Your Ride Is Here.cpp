/*
ID: mazhaoj1
PROG: ride
LANG: C++
*/

#include <cstdio>
#include <cstring>
using namespace std;
int main()
{
	char s[20];
	char d[20];
	FILE* fin = fopen("ride.in","r");
	FILE* fout = fopen("ride.out","w");
	while (fscanf(fin, "%s\n", s)!= EOF)
	{
		fscanf(fin, "%s\n", d);
		int cnt1,cnt2,len1,len2;
		len1=strlen(s);
		len2=strlen(d);
		int i;
		cnt1=cnt2=1;
		for(i=0;i<len1;i++)
			cnt1*=s[i]-'A'+1;
		for(i=0;i<len2;i++)
			cnt2*=d[i]-'A'+1;
		if((cnt1%47)==(cnt2%47))
			fprintf(fout,"GO\n");
		else
			fprintf(fout,"STAY\n");
	}
	return 0;
}