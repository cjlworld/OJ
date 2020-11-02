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

const int N=1e5+5,M=1e6+5;
int one[N],hs[N],idx=1;
int ver[M],Next[M];
void AddEdge(int h[],int a,int b)
{
	Next[++idx]=h[a];
	h[a]=idx;
	ver[idx]=b;
}

int dfn[N],low[N],times;
int id[N],all;
stack<int> S;

void tarjan(int x,int from)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y,i);
			low[x]=min(low[x],low[y]);
		}
		else if(i!=(from^1)) 
			low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		all++;
		while(S.top()!=x) 
			id[S.top()]=all,S.pop();
		id[x]=all,S.pop();
	}
}

int up[N][21],dep[N];
void deal_first(int x,int fa)
{
	int i,y;
	up[x][0]=fa,dep[x]=dep[fa]+1;	
	for(i=1;i<=20;i++) {
		if(!up[up[x][i-1]][i-1]) break;
		up[x][i]=up[up[x][i-1]][i-1];
	}
	for(i=hs[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x);
	}
}
int lcadis(int x,int y)
{
	int i,res=0;
	if(dep[x]<dep[y]) swap(x,y);
	for(i=20;i>=0;i--) 
		if(dep[up[x][i]]>=dep[y])
			x=up[x][i],res+=(1<<i);
	
	if(x==y) return res;
	for(i=20;i>=0;i--) 
		if(up[x][i]!=up[y][i]) 
			x=up[x][i],y=up[y][i],res+=(1<<i)*2;
	return res+2;
}

int n,m,Q;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(one,x,y),AddEdge(one,y,x);
	}
	for(i=1;i<=n;i++) 
		if(!dfn[i]) tarjan(i,0);
	
	for(x=1;x<=n;x++) 
		for(i=one[x];i;i=Next[i]) {
			y=ver[i];
			if(id[x]!=id[y]) AddEdge(hs,id[x],id[y]);
		}
	deal_first(1,0);
	scanf("%d",&Q);
	while(Q--) {
		scanf("%d%d",&x,&y);
		printf("%d\n",lcadis(id[x],id[y]));
	}
	return 0;
}

