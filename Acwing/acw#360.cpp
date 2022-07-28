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

const int N=1e5+5,INF=0x3f3f3f3f;

int one[N],hs[N],idx=1;
int ver[N],Next[N],edge[N];
void AddEdge(int h[],int a,int b,int c)
{
	Next[++idx]=h[a];
	h[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int newcnt;

int dfn[N],low[N],times;
int fu[N],fw[N];

int s[N],stot[N]; // 环上的前缀和，i 所在环上的总和 
void BuildCircle(int x,int y,int w)
{
	int i,sum=w;
	AddEdge(hs,x,++newcnt,0);
	for(i=y;i^x;i=fu[i]) {
		s[i]=sum;
		sum+=fw[i];
	}
	// ? 
	s[x]=stot[x]=sum;
	//  
	for(i=y;i^x;i=fu[i]) {
		stot[i]=sum;
		AddEdge(hs,newcnt,i,min(s[i],sum-s[i]));
	}
//	stot[x]=sum;
}

void tarjan(int x,int from)
{
	dfn[x]=low[x]=++idx;
	int i,y,z;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i],z=edge[i];
		if(!dfn[y]) {
			tarjan(y,i);
			fu[y]=x,fw[y]=z;
			low[x]=min(low[x],low[y]);
			if(low[y]>dfn[x]) 
				AddEdge(hs,x,y,z);
		}
		else if(i^from^1) 
			low[x]=min(low[x],dfn[y]);
	}
	
	for(i=one[x];i;i=Next[i]) {
		y=ver[i],z=edge[i];
//		if(low[y]==dfn[x] && fu[y]^x) 
		if(dfn[y]>dfn[x] && fu[y]^x)
			BuildCircle(x,y,z);
	}
}

int up[N][21],dep[N],w[N];
void deal_first(int x,int fa,int ww)
{
	int i,y;
	up[x][0]=fa;
	dep[x]=dep[fa]+1;
	w[x]=w[fa]+ww;
	
	for(i=1;i<=20;i++) {
		if(!up[up[x][i-1]][i-1]) break;
		up[x][i]=up[up[x][i-1]][i-1];
	}
	for(i=hs[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x,edge[i]);
	}
}
int lca(int &x,int &y)
{
	int i;
	if(dep[x]<dep[y]) swap(x,y);
	for(i=20;i>=0;i--) 
		if(dep[up[x][i]]>=dep[y])
			x=up[x][i];
	if(x==y) return x;
	for(i=20;i>=0;i--) 
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i];
	return up[x][0];
}

int n,m,Q;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,x2,y2,z,t;
	int ans;
	
	scanf("%d%d%d",&n,&m,&Q);
	newcnt=n;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(one,x,y,z),AddEdge(one,y,x,z);
	}
	
	tarjan(1,-1);
	deal_first(1,-1,0);
	
	while(Q--) {
		scanf("%d%d",&x,&y);
		x2=x,y2=y,z=lca(x2,y2);

		if(z<=n) ans=w[x]+w[y]-2*w[z];
		else {
			t=abs(s[x2]-s[y2]);
			ans=w[x]+w[y]-w[x2]-w[y2]+min(t,stot[x2]-t);
		}
		printf("%d\n",ans);
	}
	return 0;
}

