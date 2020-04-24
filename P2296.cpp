#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
using namespace std;
const int M=200000+5;
const int N=10000+5;
struct pic
{
	int tot;
	int one[N];
	int ver[M],Next[M];
	void AddEdge(int a,int b)
	{
		tot++;
		Next[tot]=one[a];
		one[a]=tot;
		ver[tot]=b;
		return;
	}
};
pic a,b; //a---normal , b---contrary
int n,m;
int s,t;
queue<int> q;
bool vis[N];
void BFS(int st)
{
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	int x,y,z;
	int i,j;
	vis[st]=true;
	q.push(st);
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=b.one[x];i>0;i=b.Next[i]) {
			y=b.ver[i];
			if(!vis[y]) {
				vis[y]=true;
				q.push(y);
			}
		}
	}
	return;
}
bool cc[N];
int dis[N];
int bfs(int st)
{
	memset(vis,0,sizeof vis);
	memset(dis,-1,sizeof dis);
	while(q.size()) q.pop();
	int i,j;
	int x,y,z;
	if(cc[st]) return -1;
	q.push(st);
	vis[st]=true;
	dis[st]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=a.one[x];i>0;i=a.Next[i]) {
			y=a.ver[i];
			if(cc[y]) continue;
			if(vis[y]) continue;
			vis[y]=true;
			dis[y]=dis[x]+1;
			q.push(y);
		}
	}
	return dis[t];
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		a.AddEdge(x,y);
		b.AddEdge(y,x);
	}
	scanf("%d%d",&s,&t);
	BFS(t);
	for(i=1;i<=n;i++) {
		if(!vis[i]) { //i---t with no connetion
			cc[i]=true;
			for(j=b.one[i];j>0;j=b.Next[j]) {
				cc[b.ver[j]]=true;
			}
		}
	}
	cout<<bfs(s);
	return 0;
}

