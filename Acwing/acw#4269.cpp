#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const LL INF=0x3f3f3f3f;

int n,m;
set<string> S;

LL year(string str)
{
	LL x=0;
	for(int i=6;i<=13;i++) 
		x=x*10+(str[i]-'0');
	return x;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	string str; str.resize(18);
	for(int i=1;i<=n;i++) {
		scanf("%s",&str[0]);
		S.insert(str); 
	}
	
	string school_min,come_min;
	int ans=0;
	
	scanf("%d",&m);
	for(int i=1;i<=m;i++) {
		scanf("%s",&str[0]);
		if(!come_min.length() || year(str)<year(come_min)) 
			come_min=str;
		if(S.count(str)) {
			if(!school_min.length() || year(str)<year(school_min))	
				school_min=str;
			ans++;
		}
	}
	
	printf("%d\n",ans);
	if(ans) printf("%s\n",school_min.c_str());
	else printf("%s\n",come_min.c_str());
	return 0;
}

