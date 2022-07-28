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
typedef pair<int,int> PII;

const int N=40000+5,INF=0x3f3f3f3f;

int one[N],idx;
int Next[N],ver[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
}

int dis[N];
bool vis[N];
int p[N],cnt;

void Dijstra(int x)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	memset(p,0,sizeof p); cnt=0;
	priority_queue<PII,vector<PII>,greater<PII> > q;
	
	int i,y,z;
	q.push(PII(0,x)),dis[x]=0;
	while(q.size()) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		p[++cnt]=x;
		for(i=one[x];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(PII(dis[y],y));
			}
		}
	}
}

LL f[N][2]; // f[x][0] 最短计数，f[x][0]+1 最短+1
int T,n,m,s,t;

int main()
{
	freopen("1.in","r",stdin);
	int i,j;
	int x,y,z;
	scanf("%d",&T);
	while(T--) {
		memset(one,0,sizeof one);
		memset(f,0,sizeof f);
		idx=0;
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++) {
			scanf("%d%d%d",&x,&y,&z);
			AddEdge(x,y,z);
		}
		scanf("%d%d",&s,&t);
		Dijstra(s);
		f[s][0]=1;
//		for(j=1;j<=n;j++) {
//			x=p[j];
//			for(i=one[x];i;i=Next[i]) {
//				y=ver[i],z=edge[i];
//				if(dis[y]==dis[x]+z) f[y][0]+=f[x][0],f[y][1]+=f[x][1];
//				else if(dis[y]+1==dis[x]+z) f[y][1]+=f[x][0];
//			}
//		}
		for(j=1;j<=n;j++) {
			x=p[j];
			for(i=one[x];i;i=Next[i]) {
				y=ver[i],z=edge[i];
				if(dis[y]==dis[x]+z) f[y][0]+=f[x][0];
				else if(dis[y]+1==dis[x]+z) f[y][1]+=f[x][0];
			}
		}
		for(j=1;j<=n;j++) {
			x=p[j];
			for(i=one[x];i;i=Next[i]) {
				y=ver[i],z=edge[i];
				if(dis[y]==dis[x]+z) f[y][1]+=f[x][1];
			}
		}
		printf("%lld\n",f[t][0]+f[t][1]);
	}
	return 0;
}

