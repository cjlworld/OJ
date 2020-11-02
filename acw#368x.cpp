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

int dis[N];
bool vis[N];

bool spfa(int u) //">="找最长 
{
	vis[u]=true;   //记录堆栈中的点，如果两次出现一个点，说明存在环； 
	for(int i=one[u];i;i=Next[i]) {
		int v=ver[i],l=edge[i];
		if(dis[u]+l>dis[v]) {
			dis[v]=dis[u]+l;
			if(vis[v]) return false; //如果在图上转了一圈并得到一个更优的值，那一定存在正环； 
			if(!spfa(v)) return false; //一旦发生错误，层层返回 
		}
	}
	vis[u]=false; //注销 
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
	if(spfa(0)) {
		LL ans=0;
		for(i=1;i<=n;i++) 
			ans+=dis[i];
		printf("%lld\n",ans);
	}
	else printf("-1\n");
	return 0;
}

