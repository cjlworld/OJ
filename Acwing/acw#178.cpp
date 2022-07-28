#include<set>
#include<cmath>
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
#define LL long long
#define rint register int
using namespace std;
const int N=1000+5;
const int M=100000+5; 
const LL INF=1e13;
LL fdis[N+10];
bool vis[N];
priority_queue< pair<LL,int> , vector< pair<LL,int> > , greater< pair<LL,int> > > q;
multiset< pair<LL,int> > S;
struct Graph
{
	int one[N];
	int ver[M],Next[M];
	LL edge[M];
	int tot;
	inline void AddEdge(const int &a,const int &b,const LL &c)
	{
		tot++;
		Next[tot]=one[a];
		one[a]=tot;
		ver[tot]=b;
		edge[tot]=c;
		return;
	}
	inline void Dijstra(int st,LL *dis)
	{
		while(q.size()) q.pop();
		fill(dis,dis+N+1,INF);
		memset(vis,0,sizeof vis);
		int i;
		int x,y;
		LL z;
		dis[st]=0.0;
		q.push(pair<LL,int>(0.0,st));
		while(q.size()>0)
		{
			x=q.top().second; q.pop();
			if(vis[x]) continue;
			vis[x]=true;
			for(i=one[x];i>0;i=Next[i]) {
				y=ver[i]; z=edge[i];
				if(dis[x]+z<dis[y]) {
					dis[y]=dis[x]+z;
					q.push(pair<LL,int>(dis[y],y));
				}
			}
		}
		return;
	}
	inline int kspath(int st,int end,LL *fdis,int k)
	{
		S.clear();
		int i;
		int x,y;
		int res=0;
		LL z,cost;
		for(i=one[st];i>0;i=Next[i]) 
		    S.insert(pair<LL,int>(edge[i]+fdis[ver[i]],ver[i]));
		while(S.size()>0) {
			x=S.begin()->second; cost=S.begin()->first-fdis[x];
			S.erase(S.begin());
			if(x==end) {
				res++;
				if(res==k) 
				    return cost;
			}
			for(i=one[x];i>0;i=Next[i]) {
				y=ver[i]; z=edge[i]+cost+fdis[y];
				S.insert(pair<LL,int>(z,y));
			}
			while((LL)S.size()>k&&S.size()>0) 
					S.erase((--S.end()));
		}
		return -1;
	}
}A,B;
//==============================================
int n,m;
int s,t,k;
int main()
{
	int i;
	int x,y;
	LL z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%lld",&x,&y,&z);
		A.AddEdge(x,y,z);
		B.AddEdge(y,x,z);
	}
	scanf("%d%d%d",&s,&t,&k);
	B.Dijstra(t,fdis);
	printf("%d\n",A.kspath(s,t,fdis,k));
	return 0;
}
