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

const int N=11,S=(1<<11),INF=0x3f3f3f3f;
const int dx[]={0,0,1,-1},dy[]={-1,1,0,0};

int n,m,p,mw,mk;

int w[N][N][4]; // w[i][j][k] = -1 , 0 , 1 // 不可走/ 可走 / 有门 
vector<int> a[N][N]; // key;

int direc(int x1,int y1,int x2,int y2)
{
	int u,v,i;
	for(i=0;i<4;i++) {
		u=x1+dx[i],v=y1+dy[i];
		if(u==x2&&v==y2) 
			return i;
	}
	return 0;
}

int dis[N][N][S];
bool vis[N][N][S];

struct Node
{
	int x,y,key;
	Node(int x,int y,int key) 
		: x(x),y(y),key(key) {}
};

queue<Node> q;

inline int add(int x,const vector<int> &v)
{
	for(int i=0;i<(int)v.size();i++) 
		x|=(1<<(v[i]-1));
	return x;
}

void bfs()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	
	int i;
	int x,y,z,u,v,wk;
	
	q.push(Node(1,1,add(0,a[1][1])));
	dis[1][1][add(0,a[1][1])]=0;
	
	while(q.size()) {
		x=q.front().x,y=q.front().y,z=q.front().key;
		q.pop();
		
		for(i=0;i<4;i++) {
			if(w[x][y][i]==-1) continue;  // is a wall;
			else if(w[x][y][i] && !((z>>(w[x][y][i]-1))&1)) continue; // is a door && can't pass
			
			// can pass;
			
			u=x+dx[i],v=y+dy[i];
			if(u<1||u>n||v<1||v>m) continue; // border
			
			wk=add(z,a[u][v]);
			
			if(!vis[u][v][wk]) {
				vis[u][v][wk]=true;
				dis[u][v][wk]=dis[x][y][z]+1;
				q.push(Node(u,v,wk));
			}
		}
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	int x1,y1,x2,y2;
	
	cin>>n>>m>>p;
	
	cin>>mw;
	
	while(mw--) {
		cin>>x1>>y1>>x2>>y2>>z;
		
		if(z>0) { // is a door
			w[x1][y1][direc(x1,y1,x2,y2)]=z;
			w[x2][y2][direc(x2,y2,x1,y1)]=z;
		}
		
		else if(z==0) { // is a wall
			w[x1][y1][direc(x1,y1,x2,y2)]=-1;
			w[x2][y2][direc(x2,y2,x1,y1)]=-1;
		}
	}
	
	cin>>mk; // nums of key;
	
	while(mk--) {
		cin>>x>>y>>z;
		a[x][y].push_back(z);
	}
	
	bfs();
	
	int ans=INF;
	for(i=0;i<(1<<p);i++)
		ans=min(ans,dis[n][m][i]);
	
	if(ans==INF) printf("-1\n");
	else printf("%d\n",ans);
	return 0;
}

