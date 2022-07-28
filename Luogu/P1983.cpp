#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#define LL long long
using namespace std;
const int N=2000+5;
/*
int one[N];
int Next[3*N*N],ver[3*N*N],edge[3*N*N];
int tot=0;
inline void AddEdge(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}*/
int w[N][N];
int n,m;
//如果这趟车次停靠了火车站x，
//则始发站、终点站之间所有级别大于等于火车站x的都必须停靠。
//（注意：起始站和终点站自然也算作事先已知需要停靠的站点）
int park[N];
int a[N];
int dis[N];
bool vis[N];
int cnt[N];
queue<int> q;
void SPFA(int st)
{
	memset(cnt,0,sizeof(cnt));
	memset(dis,0,sizeof(dis));
	memset(vis,0,sizeof(vis));
	while(q.size()) q.pop();
	
	int i,j;
	int x,y,z;
	q.push(st);
	dis[st]=0;
	vis[st]=true;
	do {
		x=q.front(); q.pop();
		vis[x]=false;
		if(cnt[x]>n+2) return;
		for(i=1;i<=n;i++) {
		//	y=ver[i]; z=edge[i];
			if(!w[x][i]) continue;
			y=i; z=w[x][i];
			if(dis[x]+z>dis[y]) {
				dis[y]=dis[x]+z;
				if(!vis[y]) {
					q.push(y);
					cnt[y]++;
					vis[y]=true;
				}
			}
		}
	} while(q.size());
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d%d",&n,&m);
	int i,j,k;
	int x,y,z;
	for(i=1;i<=m;i++) {
		memset(a,0,sizeof(a));
		memset(park,0,sizeof(park));
		scanf("%d",&z);
		for(j=1;j<=z;j++) {
			scanf("%d",&a[j]);
			park[a[j]]=true;
		}
		for(j=a[1];j<=a[z];j++) {
			if(park[j]) continue;
			for(k=1;k<=z;k++) 
	//			AddEdge(j,a[k],1);
				w[j][a[k]]=1;
		}
	}
	for(i=1;i<=n;i++) 
//		AddEdge(0,i,1);
		w[0][i]=1;
	SPFA(0);
	int ans=0;
	for(i=1;i<=n;i++) 
		ans=max(ans,dis[i]);
	printf("%d\n",ans);
	return 0;
}

