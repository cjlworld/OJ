#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1024,M=2e4+5;
int one[N];
int Next[M],ver[M],edge[M],idx;
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//=====================================
int n,m,k;
priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;
int dis[N];
bool vis[N];
int Dijstra(int t)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	int i;
	int x,y,z;
	q.push(make_pair(0,1)); dis[1]=0;
	while(q.size()>0) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=(edge[i]>t);
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(make_pair(dis[y],y));
			}
		}
	}
	return dis[n];
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d%d",&n,&m,&k);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	int L=-1,R=1e6+5,mid;
	while(L+1<R) {
		mid=(L+R)>>1;
		if(Dijstra(mid)<=k) R=mid;
		else L=mid; 
	}
	if(R==1e6+5) cout<<"-1";
	else cout<<R;
	return 0;
}

