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
#include<complex>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=2e5+5;

struct Edge
{
	int a,b;
	LL c;
}e[N];
bool cmp(Edge x,Edge y)
{
	return x.c<y.c;
}

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) 
		scanf("%d%d%lld",&e[i].a,&e[i].b,&e[i].c);
		
	for(i=1;i<=n;i++) par[i]=i;
	sort(e+1,e+m+1,cmp);
	LL ans=0;
	int cnt=0;
	for(i=1;i<=m;i++) {
		x=Find(e[i].a); y=Find(e[i].b);
		if(x==y) continue;
		ans+=e[i].c;
		par[x]=y;
		cnt++;
		if(cnt==n-1) break;
	}
	if(cnt<n-1) puts("orz");
	else printf("%lld\n",ans);
	return 0;
}

