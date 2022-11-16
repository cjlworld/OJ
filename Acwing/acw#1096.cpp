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

const int N=105;
const int INF=0x3f3f3f3f;
const int dx[]={1,-1,0,0,0,0},dy[]={0,0,1,-1,0,0},dz[]={0,0,0,0,1,-1};

int f,r,c;
char a[N][N][N];

struct State
{
	int x[3];
	State(int a=0,int b=0,int c=0) { x[0]=a; x[1]=b; x[2]=c; }
};
State st,ed;
queue<State> q;
bool vis[N][N][N];
int dis[N][N][N];

int bfs()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	while(q.size()) q.pop();
	
	q.push(st); 
	dis[st.x[0]][st.x[1]][st.x[2]]=0;
	vis[st.x[0]][st.x[1]][st.x[2]]=true;
	
	while(q.size()) {
		State t=q.front(); q.pop();
//		printf("(%d, %d, %d) : %d\n",t.x[0],t.x[1],t.x[2],dis[t.x[0]][t.x[1]][t.x[2]]);
		for(int i=0;i<6;i++) {
			State nw(t.x[0]+dx[i],t.x[1]+dy[i],t.x[2]+dz[i]);
			if(nw.x[0]>f || nw.x[0]<1 || nw.x[1]>r || nw.x[1]<1 || nw.x[2]>c || nw.x[2]<1) 
				continue; 
			if(vis[nw.x[0]][nw.x[1]][nw.x[2]] || a[nw.x[0]][nw.x[1]][nw.x[2]]=='#') continue;
			vis[nw.x[0]][nw.x[1]][nw.x[2]]=true;
			dis[nw.x[0]][nw.x[1]][nw.x[2]]=dis[t.x[0]][t.x[1]][t.x[2]]+1;
			q.push(nw);
		}
	}
	return dis[ed.x[0]][ed.x[1]][ed.x[2]];
}

int main()
{
//	freopen("1.in","r",stdin);
	while(scanf("%d%d%d",&f,&r,&c),f||r||c) {
		for(int i=1;i<=f;i++) {
			for(int j=1;j<=r;j++) {
				scanf("%s",a[i][j]+1);
				for(int k=1;k<=c;k++) 
					if(a[i][j][k]=='S') 
						st=State(i,j,k);
					else if(a[i][j][k]=='E') 
						ed=State(i,j,k);
			}
		}
		
		int ans=bfs();
		if(ans==INF) puts("Trapped!");
		else printf("Escaped in %d minute(s).\n",ans);
	}
	return 0;
}

