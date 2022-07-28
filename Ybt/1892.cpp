#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=5e5+5;
int one[N],idx=1;
int ver[2*N],Next[2*N],edge[2*N];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//=========================================
int dfn[N],times=0,org[N],fir[N],up[N];
int a[20*N],tot=0;
int w[N];
int n,m;
void dfs(int x,int fa)
{
	int i,y;
	dfn[x]=++times;
	org[times]=x;
	a[fir[x]=++tot]=dfn[x];
//	cout<<tot<<endl;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		w[y]=w[x]+edge[i];
		up[y]=i;
//		cout<<x<<endl;
//		printf("%d ---> %d\n",x,y);
		dfs(y,x);		
		a[++tot]=dfn[x];
	}
	return;
}
int f[3*N][30];
int lca(int x,int y)
{
	x=fir[x]; y=fir[y];
	if(x>y) swap(x,y);
	int tmp=log2(y-x+1);
	return org[min(f[x][tmp],f[y-(1<<tmp)+1][tmp])];
}
struct path
{
	int x,y,w;
}b[N];
int c[N];
void Review(int x,int fa)
{
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Review(y,x);
		c[x]+=c[y];
	}
	return;	
}
bool check(int lit)
{
	int i;
	memset(c,0,sizeof c);
	int cnt=0,cmax=0;
	for(i=1;i<=m;i++) 
		if(b[i].w>lit) {
			c[b[i].x]++; c[b[i].y]++; 
			c[lca(b[i].x,b[i].y)]-=2;
			cnt++;
			cmax=max(cmax,b[i].w);
		}
	Review(1,0);
	for(i=2;i<=n;i++) 
		if(c[i]==cnt&&cmax-edge[up[i]]<=lit) 
			return true;
	return false;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	
	dfs(1,0);
	
//	for(i=1;i<=n;i++) 
//		printf("%d ",w[i]);
//	printf("\n------------\n");
	for(i=1;i<=tot;i++) 
		f[i][0]=a[i];//,printf("%d ",a[i]);
//	printf("\n");
	for(i=1;(1<<i)<=tot;i++) 
		for(j=1;j+(1<<i)-1<=tot;j++) 
			f[j][i]=min(f[j][i-1],f[j+(1<<(i-1))][i-1]);//,printf("%d %d : %d \n",j,i,f[j][i]);
	
	int L=-1,R=0,mid;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&b[i].x,&b[i].y);
		b[i].w=w[b[i].x]+w[b[i].y]-2*w[lca(b[i].x,b[i].y)];
		R=max(R,b[i].w+1);
//		printf("%d %d lca : %d cost : %d\n",b[i].x,b[i].y,lca(b[i].x,b[i].y),b[i].w);
	}
//	cout<<R<<endl;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(check(mid)) R=mid;
		else L=mid;
	}
	cout<<R;
	return 0;
}

