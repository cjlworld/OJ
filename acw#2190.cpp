#include<set>
#include<map>
#include<queue>
#include<stack>
#include<ctime>
#include<cmath>
#include<bitset>
#include<vector>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

const int N=1e5+5,M=7e5+5;
const LL INF=0x3f3f3f3f3f3f3f3f;

int one[N],idx;
int ver[M],Next[M];
LL edge[M];
inline void AddEdge(int a,int b,LL c)
{
	Next[idx]=one[a],ver[idx]=b,edge[idx]=c,one[a]=idx++;
	Next[idx]=one[b],ver[idx]=a,edge[idx]=0,one[b]=idx++;
}

int n,m,S,T,s,t;
LL a[N],tot; // 表示多流出的流量，要是多流出了，附加图里就要多流入，连到 T.
// 这样如果不看 i-->T 的边， i 这个点处于多流入的状态。

int cur[N],d[N];
queue<int> q;

bool bfs()
{
	memset(d,-1,sizeof d);
	memcpy(cur,one,sizeof cur);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(S),d[S]=0;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=one[x];~i;i=Next[i]) {
			y=ver[i];
			if(edge[i] && d[y]==-1) {
				d[y]=d[x]+1;
				q.push(y);
				if(y==T) return true;
			}
		}
	}
	return false;
}

int dinic(int x,LL limit)
{
	if(x==T) return limit;
	int i,k,y,flow=0;
	for(i=cur[x];~i && flow<limit;i=Next[i]) {
		y=ver[cur[x]=i];
		if(edge[i] && d[y]==d[x]+1) {
			k=dinic(y,min(edge[i],limit-flow));
			if(!k) d[y]=-1;
			edge[i]-=k,edge[i^1]+=k;
			flow+=k;
		}
	}
	return flow;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	LL x,y,low,up;
	
	scanf("%d%d%d%d",&n,&m,&s,&t);
	S=n+1,T=n+2;
	
	// Step 1, 先转成 无源汇上下界可行流问题。
	// 每一个 无源汇上下界可行流 在 去掉 s->t 的边后，都对应 一个 有源汇上下界可行流 。 
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%lld%lld%lld%lld",&x,&y,&low,&up);
		AddEdge(x,y,up-low);
		a[x]+=low,a[y]-=low;
	}
	for(i=1;i<=n;i++) {
		// 流量不平衡：构造附加图使两流量叠加平衡。
		if(a[i]>0) AddEdge(i,T,a[i]);
		else if(a[i]<0) AddEdge(S,i,-a[i]),tot-=a[i];
	}
	AddEdge(t,s,INF); // 最后加入此边 ，便于后续操作。
	
	LL maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	
	// 判断是否满流， 如果不满，则原图没有调整的余地。
	if(maxflow<tot) puts("No Solution");
	else {
		// Step 2, 已经有一个 无源汇上下界可行流 转化成 一个 有源汇上下界可行流。
		// 去掉 t->s 的边即可。（此前要记录 t->s ）已经流过的流量。 (反向边可退流的量)。 
		LL ans=edge[idx-1];
		edge[idx-1]=edge[idx-2]=0; // 删边。
		
		// Step 3, 已经有一个有源汇上下界可行流 的 附加图，转化成最小流。
		//  ans-MaxFlow(t,s); （含义：疯狂退流） 
		
		S=t,T=s;
		while(bfs())
			while((x=dinic(S,INF)))
				ans-=x;
		
		printf("%lld\n",ans);
	}
	return 0;
}

