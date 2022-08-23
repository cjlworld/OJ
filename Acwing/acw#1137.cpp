#include<set>
#include<map>
#include<queue>
#include<stack>
#include<cmath>
#include<ctime>
#include<bitset>
#include<vector>
#include<cstdio>
#include<complex>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef pair<int,int> PII;
typedef unsigned long long ULL;

const int N=20000+5;
const int INF=0x3f3f3f3f;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int n,m,st,w;

priority_queue<PII,vector<PII>,greater<PII> > q;
int dis[N];
bool vis[N];

void Dijstra(int st)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	while(q.size()) q.pop();
	
	q.push(PII(dis[st]=0,st));
	while(q.size()) {
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		
		for(int i=one[x],y,z;~i;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[y]>dis[x]+z) 
				q.push(PII(dis[y]=dis[x]+z,y));
		}
	}
}


int main()
{
//	freopen("1.in","r",stdin); 
	
	while(scanf("%d%d%d",&n,&m,&st)==3) {
		memset(one,-1,sizeof one); idx=0;
		for(int i=1,x,y,z;i<=m;i++) {
			scanf("%d%d%d",&x,&y,&z);
			AddEdge(y,x,z);
		}
		Dijstra(st);
		
		scanf("%d",&w);
		int ans=INF;
		for(int i=1,x;i<=w;i++) {
			scanf("%d",&x);
			ans=min(ans,dis[x]);
		}
		if(ans==INF) puts("-1");
		else printf("%d\n",ans);
	}
		
	return 0;
}

