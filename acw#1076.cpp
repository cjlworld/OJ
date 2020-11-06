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

const int N=1000+5;
const int dx[]={0,0,0,1,-1},dy[]={0,1,-1,0,0};

int n;
int a[N][N];
int vis[N][N];

struct Node
{
	int x,y;
	Node(int x,int y) : x(x),y(y) {}
	Node() {}
};
queue<Node> q;
Node pre[N][N];
void bfs()
{
	memset(vis,0,sizeof vis);
	memset(pre,-1,sizeof pre);
	
	int i,x,y,u,v;
	
	q.push(Node(0,0)); vis[0][0]=true;
	while(q.size()) {
		x=q.front().x,y=q.front().y;
		q.pop();
		for(i=1;i<=4;i++) {
			u=x+dx[i],v=y+dy[i];
			if(u>=0&&u<n&&v>=0&&v<n&&!vis[u][v]&&a[u][v]==0) {
				vis[u][v]=true;
				pre[u][v]=Node(x,y);
				q.push(Node(u,v));
			}
		}
	}
	return;
}

void printway(int x,int y)
{
	if(x==-1) return;
	printway(pre[x][y].x,pre[x][y].y);
	printf("%d %d\n",x,y);
	return; 
}

int main()
{
	int i,j;
	scanf("%d",&n);
	for(i=0;i<n;i++) 
		for(j=0;j<n;j++) 
			scanf("%d",&a[i][j]);
	
	
	bfs();
	printway(n-1,n-1);
	return 0;
}

