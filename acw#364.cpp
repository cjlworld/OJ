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

const int N=8e5+5;
int one[N],hs[N],idx=1;
int ver[N],Next[N];
void AddEdge(int h[],int a,int b)
{
	Next[++idx]=h[a];
	h[a]=idx;
	ver[idx]=b;
}

// 边双联通分量的判断 dfn[x]==low[x] 
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

int par[N];
int Find(int x) { return ((par[x]==x) ? x : par[x]=Find(par[x])); }
// Find(x) 找到下一个 x 的祖先（包括 x）没有被缩的点。
 
int ans;
int dep[N],fat[N];
void deal_first(int x,int fa)
{
	dep[x]=dep[fa]+1;
	fat[x]=fa;
	int i,y;
	for(i=hs[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		deal_first(y,x);
	}
}

void TQuery(int x,int y)
{
	while(Find(x)!=Find(y)) {
		if(dep[Find(x)]<dep[Find(y)]) 
			swap(x,y);
		ans--;
		x=Find(x),par[x]=fat[x],x=fat[x];
	}
}

int n,m,Q,T;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	
	while(scanf("%d%d",&n,&m),max(n,m)) {
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		memset(id,0,sizeof id);
		memset(one,0,sizeof one);
		memset(hs,0,sizeof hs);
		memset(dep,0,sizeof dep);
		memset(fat,0,sizeof fat);
		while(S.size()) S.pop();
		times=all=0;
		idx=1;
		
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
		ans=all-1;
		for(i=1;i<=all;i++) par[i]=i;
		deal_first(1,0);
		
		scanf("%d",&Q);
		printf("Case %d:\n",++T);
		while(Q--) {
			scanf("%d%d",&x,&y);
			TQuery(id[x],id[y]);
			printf("%d\n",ans);	
		}
		printf("\n");
	}
	return 0;
}

