#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int M=3000+5;
const int N=2000+5;
int T;
int n,m;
//接下来 M行，每行三个整数 a,b,w，表示a→b 有一条权值为 w的边（若 w<0 则为单向，否则双向）。
int one[N];
int Next[2*M],ver[2*M],edge[2*M];
int tot=0;
inline void AddEdge(int a,int b,int c)
{
	tot++;
	Next[tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
int cnt[N];
bool vis[N];
int dis[N];
//priority_queue< pair<int,int> > q;
queue<int> q;
inline bool spfa()
{
	memset(cnt,0,sizeof(cnt));
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	while(q.size()) q.pop();
	
	int i,j;
	int x,y,z;
	dis[1]=0;
	vis[1]=true;
	cnt[1]++;
//	q.push(make_pair(cnt[1],1));
	q.push(1);
	do {
//		x=q.top().second; q.pop();
		x=q.front(); q.pop();
		vis[x]=false;
		if(cnt[x]>n+2) return true;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[x]+z<dis[y]) {
				dis[y]=dis[x]+z;
				if(!vis[y]) {
					vis[y]=true;
			//		q.push(make_pair(cnt[y],y));
					q.push(y);
					cnt[y]++;
				}
			}
		}
	} while(q.size());
	return false;
}
void Init()
{
	memset(one,0,sizeof(one));
	memset(Next,0,sizeof(Next));
	memset(ver,0,sizeof(ver));
	memset(edge,0,sizeof(edge));
	tot=0;
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k;
	int x,y,z;
	scanf("%d",&T);
	while(T--) {
		Init();
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++) {
			scanf("%d%d%d",&x,&y,&z);
			AddEdge(x,y,z);
			if(z>=0) AddEdge(y,x,z);
		}
		if(spfa()) puts("YE5");
		else puts("N0");
//		for(i=1;i<=n;i++) {
//			printf("%d ",dis[i]);
//		}
//		putchar('\n');
//		for(i=1;i<=n;i++) 
//			printf("%d ",cnt[i]);
//		putchar('\n');
	}
	return 0;
}

