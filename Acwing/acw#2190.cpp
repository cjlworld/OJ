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
LL a[N],tot; // ��ʾ��������������Ҫ�Ƕ������ˣ�����ͼ���Ҫ�����룬���� T.
// ����������� i-->T �ıߣ� i ����㴦�ڶ������״̬��

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
	
	// Step 1, ��ת�� ��Դ�����½���������⡣
	// ÿһ�� ��Դ�����½������ �� ȥ�� s->t �ıߺ󣬶���Ӧ һ�� ��Դ�����½������ �� 
	memset(one,-1,sizeof one);
	for(i=1;i<=m;i++) {
		scanf("%lld%lld%lld%lld",&x,&y,&low,&up);
		AddEdge(x,y,up-low);
		a[x]+=low,a[y]-=low;
	}
	for(i=1;i<=n;i++) {
		// ������ƽ�⣺���츽��ͼʹ����������ƽ�⡣
		if(a[i]>0) AddEdge(i,T,a[i]);
		else if(a[i]<0) AddEdge(S,i,-a[i]),tot-=a[i];
	}
	AddEdge(t,s,INF); // ������˱� �����ں���������
	
	LL maxflow=0;
	while(bfs()) 
		while((x=dinic(S,INF)))
			maxflow+=x;
	
	// �ж��Ƿ������� �����������ԭͼû�е�������ء�
	if(maxflow<tot) puts("No Solution");
	else {
		// Step 2, �Ѿ���һ�� ��Դ�����½������ ת���� һ�� ��Դ�����½��������
		// ȥ�� t->s �ı߼��ɡ�����ǰҪ��¼ t->s ���Ѿ������������� (����߿���������)�� 
		LL ans=edge[idx-1];
		edge[idx-1]=edge[idx-2]=0; // ɾ�ߡ�
		
		// Step 3, �Ѿ���һ����Դ�����½������ �� ����ͼ��ת������С����
		//  ans-MaxFlow(t,s); �����壺��������� 
		
		S=t,T=s;
		while(bfs())
			while((x=dinic(S,INF)))
				ans-=x;
		
		printf("%lld\n",ans);
	}
	return 0;
}

