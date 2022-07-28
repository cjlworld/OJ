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

const int N=5e5+5;
int one[N],idx;
int Next[N],ver[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int n,m;

stack<int> S;
int dfn[N],low[N],times;
int id[N];
int all;

void tarjan(int x)
{
	dfn[x]=low[x]=++times;
	S.push(x);
	int i,y;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!id[y]) low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]) {
		all++;
		while(S.top()!=x) {
			id[S.top()]=all;
			S.pop();
		}
		id[x]=all,S.pop();
	}
}

int din[N];

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y);
	}
	for(i=1;i<=n;i++) 
		if(!dfn[i]) tarjan(i);
	for(x=1;x<=n;x++) 
		for(i=one[x];i;i=Next[i]) {
			y=ver[i];
			if(id[x]!=id[y]) din[id[y]]++;
		}
	int ans=0;
	for(i=1;i<=all;i++) 
		ans+=(din[i]==0);
	printf("%d\n",ans);
	return 0;
}

