#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=10000+5;
int n,m,W;

int vv[N],ww[N],v[N],w[N];

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}
int p[N],tot;

int f[N];
int main()
{
//	freopen("1.in","r",stdin);
	
	int i,j;
	int x,y;
	
	scanf("%d%d%d",&n,&m,&W);
	for(i=1;i<=n;i++) {
		scanf("%d%d",&vv[i],&ww[i]);
		par[i]=i;
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		par[Find(x)]=Find(y);
	}
	
	for(i=1;i<=n;i++) {
		if(p[Find(i)]==0) 
			p[Find(i)]=++tot;
		v[p[par[i]]]+=vv[i];
		w[p[par[i]]]+=ww[i];
	}
	
	for(i=1;i<=tot;i++)
		for(j=W;j>=v[i];j--) 
			f[j]=max(f[j],f[j-v[i]]+w[i]);
	
	cout<<f[W];
	return 0;
}

