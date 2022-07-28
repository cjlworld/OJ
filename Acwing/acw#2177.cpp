#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=512,M=2e4+5,INF=1e9;
int one[N];
int ver[M],Next[M],edge[M],idx=1;
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a]; one[a]=idx; ver[idx]=b; edge[idx]=c;
	Next[++idx]=one[b]; one[b]=idx; ver[idx]=a; edge[idx]=0;
	return;
}
//===============================================
int n,m,S,T;
int d[N],cur[N];
queue<int> q;
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()) q.pop();
	q.push(S); d[S]=1,cur[S]=one[S];
	int i,x,y;
	while(q.size()>0) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i] && d[y]==-1) {
				d[y]=d[x]+1;
				cur[y]=one[y];
				if(y==T) return true;
				q.push(y);
			}
		}
	}
	return false;
}
int dinic(int x,int limit)
{
	if(x==T) return limit;
	int flow=0,y,i,k;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) // 1.流量上界优化
	{
		cur[x]=i; // 2.当前弧优化 
		y=ver[i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k==0) d[y]=-1; // 3.无贡献优化 
			edge[i]-=k;
			edge[i^1]+=k;
			flow+=k;
		}	
	}
	return flow; 
}
bool vis[N];
void dfs(int x)
{
	if(x<=0||vis[x]) return;
	vis[x]=true;
	int i;
	for(i=one[x+n];i>0;i=Next[i]) 
		if(ver[i]!=T&&edge[i]==1) 
			break;
	dfs(ver[i]);
	printf("%d ",x);
	for(i=one[x];i>0;i=Next[i]) 
		if(ver[i]>n&&edge[i]==0&&ver[i]!=S)
			break;
	dfs(ver[i]-n);
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i,x,y;
	scanf("%d%d",&n,&m);
	S=2*n+1; T=2*n+2;
	for(i=1;i<=n;i++) {
		AddEdge(S,i,1);
		AddEdge(i+n,T,1);
	}
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		AddEdge(x,y+n,1);
	}
//	for(i=4*n+2;i<=idx;i+=2) 
//		if(edge[i]>0)
//			printf("%d %d\n",ver[i^1],ver[i]);
//	puts("--------------");
	int maxflow=0,ans=0;
	while(bfs()) 
		while((x=dinic(S,INF))) 
			maxflow+=x;
	vis[0]=true;
	for(i=1;i<=n;i++) {
		if(!vis[i]) {
			dfs(i);
			ans++;
			printf("\n");
		}
	}
	cout<<ans<<endl;
//	puts("----------");
//	for(i=4*n+2;i<=idx;i+=2) 
//		if(edge[i]>0)
//			printf("%d %d\n",ver[i^1],ver[i]);
//		printf("%d ---> %d  %d\n",ver[i^1],ver[i],edge[i]);
	
	return 0;
}
//	topsort();
//	for(i=1;i<=tot;i++) {
//		for(j=0;j<(int)e[i].size();j++) {
//			printf("%d ",e[i][j]);
//		}
//		printf("\n");
//	}

//int dep[N];
//vector<int> v[N],e[N];
//int tot=0;
//int belong[N];
//void topsort()
//{
//	memset(dep,0,sizeof dep);
//	while(q.size()) q.pop();
//	int i,x,y;
// 	for(i=2;i<=idx;i+=2) {
// 		if(ver[i]==S||ver[i]==T||ver[i^1]==S||ver[i^1]==T) 
// 			continue;
//		if(edge[i]==0) {
//			x=(ver[i^1]>n) ? ver[i^1]
//			v[ver[i^1]%n].push_back(ver[i]%n),dep[ver[i]%n]++;
//		}
//			
//	}
//	for(i=1;i<=n;i++) 
//		if(dep[i]==0) {
//			q.push(i); 
//			e[++tot].push_back(i);
//			belong[i]=tot;
//		}
//			
//	while(q.size()) {
//		x=q.front(); q.pop();
//		for(vector<int>::iterator it=v[x].begin();it!=v[x].end();it++) {
//			y=*it;
//			belong[y]=belong[x];
//			e[belong[y]].push_back(y);
//			dep[y]--;
//			if(dep[y]==0) 
//				q.push(y);
//		}
//	}
//	return;
//}
