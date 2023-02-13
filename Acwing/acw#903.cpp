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

const int N=256,M=N*N*4;
const int INF=0x3f3f3f3f;

int one[N],idx;
int ver[M],edge[M],Next[M];
void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

// 点代表选定了 这个优惠品 但 还没买的已花价格

int m,n;
int a[N],b[N]; // 价格，地位 

int dis[N][N]; // dis[i][j] 走到 i 点，限制地位为 [j-m,j] 
bool vis[N][N];
priority_queue<pair<int,PII>,vector<pair<int,PII> >,greater<pair<int,PII> > > q;

void Dijstra(int st)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	while(q.size()) q.pop();
	
	for(int i=n;i>=m;i--) 
		if(b[st]>=i-m && b[st]<=i)
			q.push(make_pair(dis[st][i]=0,make_pair(st,i)));
			
	while(q.size()) {
		int x=q.top().second.first,k=q.top().second.second;
		q.pop();
		if(vis[x][k]) continue;
		vis[x][k]=true;
		for(int i=one[x];~i;i=Next[i]) {
			int y=ver[i],z=edge[i];
			if(y!=n+1 && (b[y]<k-m || b[y]>k)) continue;
			if(dis[y][k]>dis[x][k]+z) {
				dis[y][k]=dis[x][k]+z;
				q.push(make_pair(dis[y][k],make_pair(y,k)));
			}
		} 
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	memset(one,-1,sizeof one);
	scanf("%d%d",&m,&n);
	
	int x,y,z;
	for(int i=1;i<=n;i++) {
		scanf("%d%d%d",&a[i],&b[i],&z);
		while(z--) {
			scanf("%d%d",&x,&y);
			AddEdge(i,x,y);
		}
		AddEdge(i,n+1,a[i]);
	}
	Dijstra(1);
	int ans=INF;
	for(int i=1;i<=n;i++) 
		ans=min(ans,dis[n+1][i]);
	printf("%d\n",ans);
	return 0;
}

