#include<cstdio>
#include<iostream>

using namespace std;
const int N=1e5+5;

int par[N],d[N];
int Find(int x)
{
	if(par[x]!=x) {
		int root=Find(par[x]);
		d[x]=(d[par[x]]+d[x])%2;
		par[x]=root;
	}
	return par[x];
} 
int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) par[i]=i;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		if(Find(x)!=Find(y)) {
			int root=par[x];
			par[root]=y;
			// d[x]+d[root] = 1 (mod 2)
			// d[root] = 1-d[x] (mod 2)
			d[root]=1-d[x];	
		}
		else if((d[x]+d[y])%2!=1) return puts("No")&0;
	}
	puts("Yes");	
	return 0;
}

