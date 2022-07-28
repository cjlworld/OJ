#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int INF=(-1u)>>1;
const int N=1024;
const int M=2e4+5;
int one[N];
int edge[M],Next[M],ver[M];
int tot=1;
inline void AddEdge(const int &a,const int &b,const int &c)
{
	Next[++tot]=one[a];
	one[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
//=======================================
int n,m,s,t;
bool vis[N];
int infc[N],pre[N];
queue<int> q;
int maxflow=0;
bool EK()
{
	memset(vis,0,sizeof vis);
	memset(infc,0,sizeof infc);
	memset(pre,0,sizeof pre);
	while(q.size()) q.pop();
	q.push(s); vis[s]=true; infc[s]=INF;
	int x,y,z;
	int i;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(vis[y]||z==0) continue;
			infc[y]=min(infc[x],z);
			pre[y]=i;
			vis[y]=true;
			q.push(y);
 		}
	}
	if(infc[t]==0) return false;
	return true;
}
void Upflow()
{
	maxflow+=infc[t];
	for(int now=t,i;now>0;now=ver[i^1]) {
		i=pre[now];
		edge[i]-=infc[t];
		edge[i^1]+=infc[t];
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,0);
	}
	while(EK()) Upflow();
	cout<<maxflow;
	return 0;
}


