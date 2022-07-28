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

const int N=256;
const int dx[]={0,-2,-1,1,2,2,1,-1,-2};
const int dy[]={0,1,2,2,1,-1,-2,-2,-1};

int n,m;
char a[N][N];
struct Node
{
	int x,y;
	Node(int x,int y) : x(x),y(y) {}
};

queue<Node> q;
int dis[N][N];
bool vis[N][N];

void spfa(Node u)
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	while(q.size()) q.pop();
	
	int i,x,y;
	q.push(u); dis[u.x][u.y]=0,vis[u.x][u.y]=true;
	while(q.size()) {
		x=q.front().x,y=q.front().y;
		q.pop();
		
		for(i=1;i<=8;i++) {
			u.x=x+dx[i],u.y=y+dy[i];
			if(u.x>=1&&u.x<=n&&u.y>=1&&u.y<=m&&a[u.x][u.y]!='*'&&dis[u.x][u.y]>dis[x][y]+1) {
				dis[u.x][u.y]=dis[x][y]+1;
				if(!vis[u.x][u.y]) {
					q.push(u);
					vis[u.x][u.y]=true;
				}
			}
		}
	}
	return;
}
int main()
{
	int i,j;
	int x,y;
	cin>>n>>m;
	swap(n,m);
	for(i=1;i<=n;i++) 
		scanf("%s",a[i]+1);
	for(i=1;i<=n;i++) 
		for(j=1;j<=m;j++) {
			if(a[i][j]=='K') 
				spfa(Node(i,j));
			else if(a[i][j]=='H') 
				x=i,y=j;
		}
	cout<<dis[x][y];
	return 0;
}

