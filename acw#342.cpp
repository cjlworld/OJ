#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=25000+5,M=2e5+5;
int one[N];
int ver[M],Next[M],edge[M],from[M],idx;
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	from[idx]=a;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//================================
int n,m1,m2,S;
int dis[N];
bool vis[N];
int dep[N];
queue<int> up;
int id[N],cnt=0;
vector<int> v[N];
void Dijstra(int S)
{
	priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
	while(q.size()) q.pop();
	int i;
	int x,y,z;
	for(i=0;i<(int)v[S].size();i++) 
		q.push(make_pair(dis[v[S][i]],v[S][i]));//cout<<v[S][i]<<endl;
	while(q.size()>0) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(id[y]==id[x]&&dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(make_pair(dis[y],y));
			}
			else if(id[y]!=id[x]) {
		//		cout<<x<<" "<<y<<endl;
				dis[y]=min(dis[y],dis[x]+z);
				dep[id[y]]--;
				if(dep[id[y]]==0) 
					up.push(id[y]);
			}
				
		}
	}
	return;
}

void bfs(int st)
{
	queue<int> q;
	while(q.size()) q.pop();
	q.push(st); id[st]=++cnt;
	int i,x,y;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(id[y]==0) {
				id[y]=id[x];
				q.push(y);
			}
		}
	}
	return;
}
void topsort()
{
	memset(dis,0x3f,sizeof dis);
	dis[S]=0;
	int i,x;
	for(i=1;i<=cnt;i++)
		if(dep[i]==0) 
			up.push(i);
	while(up.size()>0) {
		x=up.front(); up.pop();
		Dijstra(x);
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d%d%d",&n,&m1,&m2,&S);
	for(i=1;i<=m1;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	for(i=1;i<=n;i++) 
		if(id[i]==0) 
			bfs(i);
	for(i=1;i<=n;i++) 
		v[id[i]].push_back(i);
	for(i=1;i<=m2;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		dep[id[y]]++;
	}
	topsort();
	for(i=1;i<=n;i++) {
		if(dis[i]>dis[0]/3) 
			printf("NO PATH\n");
		else printf("%d\n",dis[i]);
	}
	return 0;
}

