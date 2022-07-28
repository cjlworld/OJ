#include<set>
#include<map>
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

const int N=1e5+5,M=2e5+5;

int one[N],idx;
int ver[M],Next[M];
inline void AddEdge(int a,int b)
{
	Next[idx]=one[a]; ver[idx]=b; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; one[b]=idx++;
}

int n,m;
int col[N];
int siz[N],son[N];
int cnt[N],ans[N],cur;

void dfs1(int x,int fa)
{
	int i,y;
	siz[x]=1;
	for(i=one[x];i>0;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		if(siz[y]>siz[son[x]]) 
			son[x]=y;
		siz[x]+=siz[y];
	}
}

inline void Add(int x,int key)
{
	if(key==1) {
		if(!cnt[x]) cur++;
		cnt[x]++;
	}
	else {
		cnt[x]--;
		if(!cnt[x]) cur--;
	}
}

void Count(int x,int fa,int key)
{
	Add(col[x],key);
	for(int i=one[x],y;~i;i=Next[i]) {
		y=ver[i];
		if(y==fa) continue;
		Count(y,x,key);
	}
}

void dfs2(int x,int fa,bool keep)
{
	int i,y;
	for(i=one[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa || y==son[x]) continue;
		dfs2(y,x,false);
	}
	if(son[x]) dfs2(son[x],x,true);
	for(i=one[x];~i;i=Next[i]) {
		y=ver[i];
		if(y==fa || y==son[x]) continue;
		Count(y,x,1);
	}
	Add(col[x],1);
	ans[x]=cur;

	if(!keep) Count(x,fa,-1);
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y;
	scanf("%d",&n);
	memset(one,-1,sizeof one);
	for(i=1;i<=n-1;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	for(i=1;i<=n;i++) 
		scanf("%d",&col[i]);
		
	dfs1(1,0);
	dfs2(1,0,0);
	
	scanf("%d",&m);
	while(m--) {
		scanf("%d",&x);
		printf("%d\n",ans[x]);
	}
	return 0;
}
