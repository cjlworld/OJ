#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef pair<int,int> PII;

const int N=10000+5,M=1000+5,INF=1e9+5;
int n,m,k;
int dis[N][M];
int a[N],b[N],g[N];
bool lim[N][M],vis[N][M];
int ach;

struct Queue
{
	PII q[N];
	int hh,tt;
	inline PII front() { return q[hh%2006]; }
	inline void pop() { hh++; }
	inline void push(const PII &t) { tt++,q[tt%2006]=t; }
	inline bool empty() { return hh>tt; }
	Queue() { hh=1,tt=0; }
}q;

void BFS()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	int i,j;
	int x,y;
	for(i=m;i>=1;i--) 
		q.push(PII(0,i)),dis[0][i]=0,vis[0][i]=true;
	while(!q.empty()) {
		x=q.front().first,y=q.front().second;
		q.pop();
//		if(x>ach) printf("%d %d\n",x,y);
		ach=max(ach,x);
		if(x==n) continue;
		
		vis[x][y]=false;
		
		for(i=y+a[x],j=1;i<m;i+=a[x],j++) {
			if(!lim[x+1][i]) continue;
			if(dis[x+1][i]>dis[x][y]+j) {
				dis[x+1][i]=dis[x][y]+j;
				if(!vis[x+1][i])
					q.push(PII(x+1,i)),vis[x+1][i]=true;
			}
			else break;
		}
		
		if(i>=m&&lim[x+1][m]&&dis[x+1][m]>dis[x][y]+j) {
			dis[x+1][m]=dis[x][y]+j;
			if(!vis[x+1][m]) 
				q.push(PII(x+1,m)),vis[x+1][m]=true;
		}
		
		if(y-b[x]>0&&lim[x+1][y-b[x]]&&dis[x+1][y-b[x]]>dis[x][y]) {
			dis[x+1][y-b[x]]=dis[x][y];
			if(!vis[x+1][y-b[x]])
				q.push(PII(x+1,y-b[x])),vis[x+1][y-b[x]]=true;
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	for(i=0;i<=n-1;i++)
		scanf("%d%d",&a[i],&b[i]);
	memset(lim,true,sizeof lim);
	for(i=1;i<=k;i++) {
		scanf("%d%d%d",&x,&y,&z);
		for(j=1;j<=y;j++) lim[x][j]=false;
		for(j=z;j<=m;j++) lim[x][j]=false;
		g[++g[0]]=x;
	}
	sort(g+1,g+g[0]+1);
	BFS();
	int ans=dis[0][0];
	for(i=1;i<=m;i++) 
		ans=min(ans,dis[n][i]);
	if(ans!=dis[0][0]) printf("1\n%d",ans);
	else {
		for(ans=0,i=1;i<=g[0];i++) 
			if(ach>=g[i]) ans=i;
		printf("0\n%d",ans);
	}
	return 0;
}
