#include<cstdio>
using namespace std;

const int N=1024;

int n,m;
int deg[N];

int par[N];
int Find(int x)
{
	if(par[x]!=x) return par[x]=Find(par[x]);
	else return x;
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,x,y;
	
	while(scanf("%d",&n),n) {
		scanf("%d",&m);
		for(i=1;i<=n;i++) 
			par[i]=i,deg[i]=0;
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			deg[x]++,deg[y]++;
			par[Find(x)]=Find(y);
		}
		int flag=1;
		
		for(i=1;i<=n;i++) 
			if(Find(i)!=Find(1)) break;
		if(i<=n) flag=0;
		
		for(i=1;i<=n;i++) 
			if(deg[i]&1) break;
		if(i<=n) flag=0;
		
		printf("%d\n",flag);
	}
	return 0;
}

