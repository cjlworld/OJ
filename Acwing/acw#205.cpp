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

const int N=2e7+5;
const int MOD=10000,XH=15000;
int f[N];

//map<int,int> mp;

int main()
{
//	freopen("1.in","r",stdin);
	int i;//,t;
	f[0]=0,f[1]=1;
//	for(i=2;i<=N-1;i++) {
//		f[i]=(f[i-1]+f[i-2])%MOD;
//		t=f[i-1]*MOD+f[i];
//		if(mp.count(t)) {
//			printf("%d",i-1-mp[t]);
//			break;
//		}
//		else mp[t]=i-1;	
//	}
	for(i=2;i<=XH+5;i++)
		f[i]=(f[i-1]+f[i-2])%MOD;
	
	int n;
	while(scanf("%d",&n),~n) {
		printf("%d\n",f[n%XH]);
	}
 	return 0;
}

