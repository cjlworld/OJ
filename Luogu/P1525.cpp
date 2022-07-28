#include<bits/stdc++.h>
#define rint register int
#define INF 2147483646
#define LL long long 
using namespace std;
const int N=2e4+5;
const int M=100000+5;
int n,m;
int Next[2*M],ver[2*M],edge[2*M],adj[N],one[N];
int tot=0;
int color[N];
queue<int> q;
int L,R,mid;
inline void add(int a,int b,int c)
{
	tot++;
	if(one[a]==0) one[a]=tot;
	else Next[adj[a]]=tot;
	adj[a]=tot;
	ver[tot]=b;
	edge[tot]=c;
	return;
}
inline bool draw(const int &t)
{
	memset(color,-1,sizeof(color));
	while(q.size()) q.pop();
	int u,v,co;
	for(int i=1;i<=n;i++) {
		if(color[i]!=-1) continue;
		q.push(i);
		color[i]=1;
		do {
			u=q.front(); q.pop();
			co=color[u];
			for(int i=one[u];i;i=Next[i]) {
				if(edge[i]<t) continue;
				v=ver[i]; 
				if(color[v]==co) return false;
				if(color[v]!=-1) continue;
				if(co==1) color[v]=0;
				else color[v]=1;
				q.push(v);
			}
		} while(!q.empty());
	}
	return true;
}
inline void Init()
{
	scanf("%d%d",&n,&m);
	int x,y,z;
	for(rint i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);
		add(y,x,z);
		R=max(R,z);
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	Init();
	L=0; R++;
	while(L+1<R) {
		mid=L+R>>1;
		if(draw(mid)) R=mid;
		else L=mid;
	}
	printf("%d\n",L);
	return 0;
}

