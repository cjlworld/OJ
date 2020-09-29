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

const int N=256;
const int dx[]={0,-1,-1,0,1,1,1,0,-1};
const int dy[]={0,0,1,1,1,0,-1,-1,-1};
int n,m; // swap
char a[N][N];

int dis[N][N];
bool vis[N][N];

queue<PII> q;
void bfs(int x,int y)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof (vis));
	while(q.size()) q.pop();
	
	int i;
	int u,v;
	q.push(PII(x,y)); dis[x][y]=0,vis[x][y]=true;
	while(q.size()) {
		x=q.front().first,y=q.front().second;
		q.pop();
		for(i=1;i<=8;i++) {
			u=x+dx[i],v=y+dy[i];
			if(u>=1&&u<=n&&v>=1&&v<=m&&a[u][v]!='*'&&!vis[u][v]) {
				vis[u][v]=true;
				dis[u][v]=dis[x][y]+1;
				q.push(PII(u,v));
			}
		}
	}
	return;
}

int main()
{
//	freopen("1.in","r",stdin);
	int i,j;
	int x,y;
	cin>>n>>m>>x>>y; swap(n,m);
	swap(x,y);
	for(i=1;i<=n;i++) 
		scanf("%s",a[i]+1);
	bfs(x,y);
	int ans=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++) 
			if(a[i][j]=='.')
				ans=max(ans,dis[i][j]);
	cout<<ans;
	return 0;
}

