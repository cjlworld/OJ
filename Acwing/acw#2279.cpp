#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=200+5,M=1000+5;
const double INF=1e9,eps=1e-3;
int one[N],idx=0;
int ver[M],Next[M];
double edge[M];
inline void AddEdge(int a,int b,double c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}
//======================================
struct Edge
{
	int a,b;
	double c;
}e[M];
int n,m,S,T;
queue<int> q;
int d[N],cur[N];
bool bfs()
{
	memset(d,-1,sizeof d);
	while(q.size()) q.pop();
	int i;
	int x,y;
	q.push(S); d[S]=1,cur[S]=one[S];
	while(q.size()>0) {
		x=q.front(); q.pop();
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i];
			if(edge[i]>0&&d[y]==-1) {
				d[y]=d[x]+1;
				cur[y]=one[y];
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
	double flow=0.0,k;
	int y,i;
	for(i=cur[x];i>0&&flow<limit;i=Next[i]) {
		cur[x]=i;
		y=ver[i];
		if(edge[i]>0&&d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(k<=eps) d[y]=-1;
			edge[i]-=k;
			edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}
bool check(double t)
{
	int i;
	double res=0.0,x;
	memset(one,0,sizeof one);
	memset(ver,0,sizeof ver);
	memset(Next,0,sizeof Next);
	memset(edge,0,sizeof edge);
	idx=1;
	for(i=1;i<=m;i++) {
		if(e[i].c-t<=0) res+=e[i].c-t;
		else AddEdge(e[i].a,e[i].b,e[i].c-t),AddEdge(e[i].b,e[i].a,e[i].c-t);
	}
	while(bfs()) 
		while((x=dinic(S,INF))>0) {
			res+=x;
			if(res>=0) return true;
		}	
	return res>=0;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	scanf("%d%d%d%d",&n,&m,&S,&T);
	double L=0.0,R=0.0,mid;
	for(i=1;i<=m;i++) {
		scanf("%d%d%lf",&e[i].a,&e[i].b,&e[i].c);
		R=max(R,e[i].c);
	}
	while(L+eps<R) {
		mid=(L+R)/2;
		if(check(mid)) L=mid; 
		else R=mid;
	}
	printf("%.2f",R);
	return 0;
}

