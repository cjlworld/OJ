// acw#368 
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

const int N=7e5+5;
int one[N],idx;
int Next[N],edge[N],ver[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int n,m;

int dis[N],cnt[N];
bool vis[N];
queue<int> q;

bool spfa()
{
	memset(dis,0,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	
	int i,x,y,z;
	q.push(0),vis[0]=true;
	while(q.size()) {
		x=q.front(); q.pop();
		if(++cnt[x]>n) return false;
		vis[x]=false;
		for(i=one[x];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(dis[x]+z>dis[y]) {
				if(y==x) return false;
				dis[y]=dis[x]+z;
				if(!vis[y]) 
					q.push(y),vis[y]=true;
			}
		}
	}
	return true;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int opt,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) AddEdge(x,y,0),AddEdge(y,x,0);
		else if(opt==2) AddEdge(x,y,1);
		else if(opt==3) AddEdge(y,x,0);
		else if(opt==4) AddEdge(y,x,1);
		else AddEdge(x,y,0);
	}
	for(i=n;i>=1;i--)
		AddEdge(0,i,1);
	if(spfa()) {
		LL ans=0;
		for(i=1;i<=n;i++) 
			ans+=dis[i];
		printf("%lld\n",ans);
	}
	else printf("-1\n");
	return 0;
}

