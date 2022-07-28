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
typedef pair<LL,int> PLI;

const int N=5e6+5;

int one[N],idx;
int ver[N],Next[N];
LL edge[N];
void AddEdge(int a,int b,LL c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	
//	printf("%d %d %lld \n",a,b,c);
}

int n,m;
LL C;

priority_queue<PLI,vector<PLI>,greater<PLI> > q;
LL dis[N];
bool vis[N];

int start,final;

void Dijstra(int x)
{
	memset(vis,0,sizeof vis);
	memset(dis,0x3f,sizeof dis);
	while(q.size()) q.pop();
	
	int i,y;
	LL z;
	q.push(PLI(0,x)),dis[x]=0;
	
	while(q.size()) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(i=one[x];i;i=Next[i]) {
			y=ver[i],z=edge[i];
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(PLI(dis[y],y));
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j,x,y;
	LL z;
	scanf("%d%d%lld",&n,&m,&C);
	for(i=1;i<=m;i++) {
		scanf("%d%d%lld",&x,&y,&z);
		AddEdge(x,y,z);
	}
	for(i=1;i<=n;i++) 
		for(j=1;j<=n;j<<=1) 
			AddEdge(i,i^j,j*C);

	scanf("%d%d",&start,&final);
	Dijstra(start);
	printf("%lld\n",dis[final]);
	return 0;
}
