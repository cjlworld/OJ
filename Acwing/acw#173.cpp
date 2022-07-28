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

const int N=1024; 
const int INF=0x3f3f3f3f;
const int dx[]={-1,0,1,0},dy[]={0,1,0,-1};

int n,m;
char a[N][N];
int dis[N][N];
bool vis[N][N];
queue<PII> q;

void bfs()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) 
			if(a[i][j]=='1') {
				dis[i][j]=0;
				vis[i][j]=true;
				q.push(PII(i,j));
			}
	
	int x,y,nx,ny;
	while(q.size()) {
		x=q.front().first; y=q.front().second;
		q.pop();
		
		for(int i=0;i<4;i++) {
			nx=x+dx[i]; ny=y+dy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=m && !vis[nx][ny]) {
				dis[nx][ny]=dis[x][y]+1;
				vis[nx][ny]=true;
				q.push(PII(nx,ny));
			} 
		}
	}
} 
 
int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) 
		scanf("%s",a[i]+1);
	
	bfs();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) 
			printf("%d ",dis[i][j]);
		puts("");
	}		
	return 0;
}

