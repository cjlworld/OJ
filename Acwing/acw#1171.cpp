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

const int N=4e4+5,LOGN=19;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int up[N][LOGN],dep[N],s[N];

void deal_first(int x,int fa)
{
	up[x][0]=fa; 
	dep[x]=dep[fa]+1;
	
	for(int i=1;i<LOGN;i++) 
		up[x][i]=up[up[x][i-1]][i-1];
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i]; 
		if(y==fa) continue;
		s[y]=s[x]+edge[i];
		deal_first(y,x);
	}
}

int lca(int x,int y)
{
	if(dep[x]<dep[y]) swap(x,y); // Jump x
	for(int i=LOGN-1;i>=0;i--) 
		if(up[x][i] && dep[up[x][i]]>=dep[y]) 
			x=up[x][i];
	if(x==y) return x;
	for(int i=LOGN-1;i>=0;i--) 
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i];
	return up[x][0];
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	for(int i=1,x,y,z;i<=n-1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z); AddEdge(y,x,z);
	} 
	
	deal_first(1,0);
	for(int i=1,x,y;i<=m;i++) {
		scanf("%d%d",&x,&y);
		printf("%d\n",s[x]+s[y]-2*s[lca(x,y)]);
	}
	return 0;
}

