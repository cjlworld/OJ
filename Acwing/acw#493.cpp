#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int INF=1e9+5;

bool isprime(int x)
{
	if(x==1||x==0) return false;
	for(int i=2;i*i<=x;i++) 
		if(x%i==0) return false;
	return true;
}
string s;
int cnt[30];

int main()
{
	unsigned i;
	int cmax=0,cmin=INF;
	cin>>s;
	for(i=0;i<s.length();i++) 
		cnt[s[i]-'a']++;
	for(i=0;i<26;i++) 
		if(cnt[i])
			cmax=max(cmax,cnt[i]),cmin=min(cmin,cnt[i]);
	if(isprime(cmax-cmin)) 
		printf("Lucky Word\n%d\n",cmax-cmin);
	else printf("No Answer\n0\n");
	return 0;
}

