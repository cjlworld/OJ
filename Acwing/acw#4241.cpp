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
typedef unsigned long long ULL;
typedef pair<int,int> PII; 

const int N=1000+5,M=N*N+5;
const int INF=0x3f3f3f3f;

int idx,one[N]; // 从 0 开始，[0, idx) 是用过的 
int ver[M],edge[M],nxt[M];
void AddEdge(int a,int b,int c)
{
	ver[idx]=b; edge[idx]=c; nxt[idx]=one[a]; one[a]=idx++;
}

int T,n,m;
bool vis[N];
int dis[N]; // dis[x]: 1 到 x 的最大承重 
priority_queue<PII> q;

void Dijstra()
{
	memset(vis,0,sizeof vis);
	memset(dis,0,sizeof dis);
	while(q.size()) q.pop();
	
	q.push(PII(dis[1]=INF,1));
	while(q.size()) {
		int x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		
		for(int i=one[x];~i;i=nxt[i]) {
			int y=ver[i],z=edge[i];
			if(!vis[y] && dis[y]<min(dis[x],z)) {
				dis[y]=min(dis[x],z);
				q.push(PII(dis[y],y));
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	scanf("%d",&T);
	for(int times=1;times<=T;times++) {
		memset(one,-1,sizeof one); idx=0;
		
		scanf("%d%d",&n,&m);
		for(int i=0;i<m;i++) {
			int x,y,z;
			scanf("%d%d%d",&x,&y,&z);
			AddEdge(x,y,z); AddEdge(y,x,z);
		}
		Dijstra();
		printf("Scenario #%d:\n%d\n\n",times,dis[n]);
	}
	return 0;
}

