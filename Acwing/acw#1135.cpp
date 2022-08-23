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

const int N=2e5+5;
const int INF=0x3f3f3f3f;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int n,m;
int a[6];
int dist[6][6];

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
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(PII(dis[y],y));
			}
		}
	}
}


int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	a[0]=1;
	for(int i=1;i<=5;i++) 
		scanf("%d",&a[i]);
	
	memset(one,-1,sizeof one);
	for(int i=1,x,y,z;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	
	for(int i=1;i<=5;i++) {
		Dijstra(a[i]);
		for(int j=0;j<=5;j++) 
			dist[i][j]=dis[a[j]];
	}
	
	int tmp[6]={0,1,2,3,4,5};
	int ans=INF;
	
	do {
		int sum=0;
		for(int i=1;i<=5;i++) 
			sum+=dist[tmp[i]][tmp[i-1]];
		ans=min(ans,sum);
	}while(next_permutation(tmp+1,tmp+6));
	
	printf("%d\n",ans);
	return 0;
}

