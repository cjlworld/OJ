#include<bits/stdc++.h>
using namespace std;
/*给定 M 条边， N 个点的带权无向图。求 1到 N 的最短路;
第一行：N,M(N≤100000，M≤500000)；
接下来M行3个正整数：
ai,bi,ci表示ai,bi之间有一条长度为ci的路，ci≤1000。*/
const int N=100000+5;
const int M=500000*2+5;
int n,m;
int dis[N];
bool exist[N];
int one[N],adj[N],ver[M],edge[M],Next[M];
int tot=0;
queue<int> q;
void add(int a,int b,int c)
{
	tot++;
	if(one[a]==0) one[a]=tot;
	Next[adj[a]]=tot;
	adj[a]=tot;
	edge[tot]=c;
	ver[tot]=b;
	return;
}
void Init()
{
	scanf("%d%d",&n,&m);
	tot=0;
	int i,j;
	int a,b,c;
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&a,&b,&c);
		add(a,b,c);
		add(b,a,c);
	}
	return;
}
void SPFA()
{
	memset(dis,127,sizeof(dis));
	memset(exist,0,sizeof(exist));
	int i,j;
	int x,y,z;
	dis[1]=0;
	q.push(1);
	do {
		x=q.front(); q.pop();
		for(i=one[x];i;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[x]+z<dis[y]) {
				dis[y]=dis[x]+z;
				q.push(y);
			}
		}
	} while(!q.empty());
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	SPFA();
	cout<<dis[n];
	return 0;
}

