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

const int N=205,M=1e5+5;

int T,n,m;

struct Edge
{
	int a,b,c;
}e[M];
bool cmp(Edge a,Edge b) { return a.c<b.c; }

int par[N],lspar[N];
int Find(int x) { return (par[x]==x) ? x : par[x]=Find(par[x]); }

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	while(T--) {
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) par[i]=i;
		for(int i=1;i<=m;i++) 
			scanf("%d%d%d",&e[i].a,&e[i].b,&e[i].c);
		sort(e+1,e+m+1,cmp);
		int lst=0,ans=0;
		for(int i=1;i<=m;i++) {
			if(e[i].c!=lst) {
				lst=e[i].c;
				for(int i=1;i<=n;i++) 
					lspar[i]=Find(i);
			}
			
			int x=e[i].a,y=e[i].b;
			if(Find(x)!=Find(y)) {
				par[Find(x)]=Find(y);
				ans+=e[i].c;
			}
			else {
				if(lspar[x]!=lspar[y]) {
					ans=-1;
					break;
				}
			}
		}
		if(ans==-1) puts("Not Unique!");
		else printf("%d\n",ans);
	}
	
	return 0;
}

