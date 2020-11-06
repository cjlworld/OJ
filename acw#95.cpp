#include<set>
#include<map>
#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
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

const int N=256,S=1<<25,INF=0x3f3f3f3f,End=(1<<25)-1;
const int dx[]={0,0,1,-1},dy[]={1,-1,0,0};
int g[N],tot;

bool vis[S];
int dis[S];

void bfs(int x)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	queue<int> q;
	q.push(x),dis[x]=0,vis[x]=true;
	int i,y;
	while(q.size()) {
		x=q.front(); q.pop();
		for(i=1;i<=tot;i++) {
			y=x^g[i];
			if(!vis[y]) {
				vis[y]=true;
				dis[y]=dis[x]+1;
				if(dis[y]<6) q.push(y);
			}
		}
	}
}
int main()
{
//	freopen("1.in","r",stdin);
	int i,j,k,x,y,z;
	char c;
	for(i=0;i<5;i++) 
		for(j=0;j<5;j++) {
			z=1<<(i*5+j);
			for(k=0;k<4;k++) {
				x=i+dx[k],y=j+dy[k];
				if(x>=0&&x<5&&y>=0&&y<5) 
					z^=1<<(x*5+y);
			}
			g[++tot]=z;
		}

	bfs(End);
	int T;
	cin>>T;
	while(T--) {
		x=0;
		for(i=0;i<25;i++) {
			for(c=getchar();c!='0'&&c!='1';c=getchar());
			if(c=='1') x^=1<<i; 
		}
		if(dis[x]==INF) printf("-1\n");
		else printf("%d\n",dis[x]);
	}
	return 0;
}

