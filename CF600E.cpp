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

const int N=2e5+5;

int one[N],idx;
int Next[N],ver[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;	
}

int siz[N],son[N];

void dfs1(int x,int fa)
{
	int i,y;
	siz[x]=1;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		dfs1(y,x);
		if(siz[y]>siz[son[x]]) son[x]=y;
		siz[x]+=siz[y];
	}
}

int cnt[N],col[N],maxc;
LL sum;

void count(int x,int fa,int val,int ban)
{
	cnt[col[x]]+=val;
	if(cnt[col[x]]>maxc) maxc=cnt[col[x]],sum=0;
	if(cnt[col[x]]==maxc) sum+=col[x];
	
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa||y==ban) continue;
		count(y,x,val,ban);
	}
}
LL f[N];

void dfs2(int x,int fa,bool keep)
{
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(y==fa||y==son[x]) continue;
		dfs2(y,x,false);
	}
	if(son[x]) dfs2(son[x],x,true);
	count(x,fa,1,son[x]);
	f[x]=sum;
	if(!keep) count(x,fa,-1,0),maxc=sum=0;
}

int n;

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++) scanf("%d",&col[i]);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y),AddEdge(y,x);
	}
	dfs1(1,0);
	dfs2(1,0,false);
	for(i=1;i<=n;i++) 
		printf("%lld ",f[i]);
	return 0;
}

