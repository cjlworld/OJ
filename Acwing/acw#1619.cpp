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
	int i,x,y;
	
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++) 
		par[i]=i,deg[i]=0;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		deg[x]++,deg[y]++;
		par[Find(x)]=Find(y);
	}
	for(i=1;i<=n;i++) 
	    printf("%d ",deg[i]);
	printf("\n");
	
	for(i=1;i<=n;i++) 
		if(Find(i)!=Find(1)) break;
	if(i<=n) {
	    printf("Non-Eulerian\n");
	    return 0;
	}
	int cnt=0;
	for(i=1;i<=n;i++) 
		if(deg[i]&1) cnt++;
	
	if(cnt==0) printf("Eulerian\n");
	else if(cnt==2) printf("Semi-Eulerian\n");
	else printf("Non-Eulerian\n");
	return 0;
}

