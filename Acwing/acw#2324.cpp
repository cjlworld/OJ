#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef pair<int,int> PII;

const int N=1e4+5;
const double INF=1e9;

int one[N],idx;
int ver[N],Next[N];
double edge[N];
inline void AddEdge(int a,int b,double c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
	Next[idx]=one[b]; ver[idx]=a; edge[idx]=0; one[b]=idx++;
	
//	printf("%d --> %d : %.2lf\n",a,b,c);
}

int n,m,S,T;

int d[N],cur[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S); d[S]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0 && d[y]==-1) {
				d[y]=d[x]+1;
				q.push(y);
				if(y==T) return true;
			}
		}
	}
	return false;
}

double dinic(int x,double limit)
{
	if(x==T) return limit;
	double k,flow=0;
	for(int i=cur[x];~i && flow<limit;i=Next[i]) {
		int y=ver[cur[x]=i];
		if(edge[i]>0 && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k==0) d[y]=-1;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}


PII edges[N];
int deg[N];
bool check(double g)
{
	memset(one,-1,sizeof one);
	idx=0;
	int i;
	for(i=1;i<=m;i++) {
		int x=edges[i].first,y=edges[i].second;
		AddEdge(x,y,1); AddEdge(y,x,1);
	}
	for(i=1;i<=n;i++) 
		AddEdge(S,i,m),AddEdge(i,T,2*g-deg[i]+m);
	
	double maxflow=0,x;
	while(bfs()) 
		while((x=dinic(S,INF))>0)
			maxflow+=x;
//	printf("maxflow is %.2lf , maxflow-m*n is %.2lf\n",maxflow,maxflow-m*n);
	return (maxflow-m*n>=0);
}

vector<int> ans;
bool st[N];
void dfs(int now)
{
	if(!st[now]) 
		ans.push_back(now),st[now]=true;
	for(int i=one[now];~i;i=Next[i])
		if(edge[i]>0 && !st[ver[i]]) dfs(ver[i]);
}

int main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	int i;
	int x,y;
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	S=n+1,T=n+2;
	for(i=1;i<=m;i++) {
		scanf("%d%d",&x,&y);
		edges[i]=PII(x,y);
		deg[x]++,deg[y]++;
	}
	
	double L=0,R=m,mid;
	while(L+1e-8<R) {
		mid=(L+R)/2;
		if(check(mid)) R=mid;
		else L=mid;
		
//		printf("[L,R] is [%.2lf , %.2lf]\n",L,R);
	}
	
	check(L);
	dfs(S);
	if(ans.size()==1) {
		printf("1\n1\n");
		return 0;
	}
	printf("%llu\n",ans.size()-1);
	sort(ans.begin(),ans.end());
	for(i=0;i<(int)ans.size()-1;i++) 
		printf("%d\n",ans[i]);
	
//	printf("%.2lf\n",R);
	return 0;
}

