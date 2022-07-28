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

const int N=1e5+5;
int one[N],idx=1;
int ver[N],Next[N];
void AddEdge(int a,int b)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
}

int ans,tmp;
int dfn[N],low[N],times,all;

void tarjan(int x,int fa)
{
	dfn[x]=low[x]=++times;
	int i,y,sum=0;
	for(i=one[x];i;i=Next[i]) {
		y=ver[i];
		if(!dfn[y]) {
			tarjan(y,x);
			low[x]=min(low[x],low[y]);
			if(low[y]>=dfn[x]) sum++;
		}
		else if(y!=fa) 
			low[x]=min(low[x],dfn[y]);
	}
	tmp=max(tmp,sum+(fa>0));
}

int n,m;

int main()
{
//	freopen("1.in","r",stdin);
	int i,x,y;
	while(scanf("%d%d",&n,&m)==2) {
		if(n==0&&m==0) break;
		memset(one,0,sizeof one);
		idx=1;
		for(i=1;i<=m;i++) {
			scanf("%d%d",&x,&y);
			x++,y++;
			AddEdge(x,y),AddEdge(y,x);
		}
		ans=0;
		memset(dfn,0,sizeof dfn);
		memset(low,0,sizeof low);
		times=all=0;
		
		for(i=1;i<=n;i++) {
			if(!dfn[i]) {
				tmp=0;
				tarjan(i,0);
				ans=max(ans,tmp);
				all++;
			}
		}
		ans=ans+all-1;
		printf("%d\n",ans);
	}
	return 0;
}

