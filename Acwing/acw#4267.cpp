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

const int N=1e5+5;

int n,m;
int par[N];

int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }

int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d%d",&n,&m),n||m) {
		for(int i=1;i<=n;i++) par[i]=i;
		for(int i=1,k,fir,x;i<=m;i++) {
			scanf("%d",&k);
			if(k==0) continue;
			scanf("%d",&fir); ++fir;
			for(int j=2;j<=k;j++) {
				scanf("%d",&x); ++x;
				if(Find(x)==Find(fir)) continue;
				par[Find(x)]=Find(fir);
			}
		}
		
		int ans=0;
		for(int i=1;i<=n;i++) 
			if(Find(i)==Find(1)) ans++;
		printf("%d\n",ans);
	}
	return 0;
}

