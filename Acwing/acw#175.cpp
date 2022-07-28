#include<cstdio>
#include<iostream>
#include<queue>
#include<cstring>
#define LL long long
using namespace std;
//第一行包含正整数n 和m，表示电路板的行数和列数。
//之后n 行，每行m 个字符，字符是"/"和"\"中的一个，表示标准件的方向。
//（m,n≤500）
const int N=500+20;
const int dx[]={0,-1,-1,1,1};
const int dy[]={0,-1,1,-1,1};
int n,m;
bool a[N][N][5];
bool vis[N][N];
struct node
{
	int x,y;
	int step;
};
deque<node> q;
int BFS()
{
	memset(vis,0,sizeof(vis));
	while(q.size()) q.pop_back();
	node u,v;
	int i;
	vis[1][1]=true;
	u.step=0; u.x=1; u.y=1;
	q.push_back(u);
	while(q.size()) {
		u=q.front(); q.pop_front();
//		printf("%d %d %d\n",u.x,u.y,u.step);
		if(u.x==n+1&&u.y==m+1) return u.step;
		vis[u.x][u.y]=true;
		for(i=1;i<=4;i++) {
			if(u.x+dx[i]<1||u.x+dx[i]>n+1||u.y+dy[i]<1||u.y+dy[i]>m+1) 
				continue;
			v.x=u.x+dx[i];
			v.y=u.y+dy[i];
			if(vis[v.x][v.y]) continue;
			if(a[u.x][u.y][i]) {
				v.step=u.step;
				q.push_front(v);
			}
			else {
				v.step=u.step+1;
				q.push_back(v);
			}
 		}
	}
	return -1;
}
int main()
{
	int i,j;
	char c;
	int T,ans;
	cin>>T;
	while(T--) {
		memset(a,0,sizeof a);
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++) {
			for(j=1;j<=m;j++) {
				cin>>c;
				if(c=='/') a[i+1][j][2]=true,a[i][j+1][3]=true;
				else a[i][j][4]=true,a[i+1][j+1][1]=true;
			}
		}
		ans=BFS();
		if(ans==-1) printf("NO SOLUTION\n");
		else printf("%d\n",ans);
	}
	return 0;
}
