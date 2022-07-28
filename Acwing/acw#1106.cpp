#include<bits/stdc++.h>

using namespace std;
typedef long long LL;
typedef long double LD;
typedef unsigned long long ULL;

const int N=1024;
const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};

int n;
int a[N][N];
bool vis[N][N]; 

queue< pair<int,int> > q;
vector< pair<int,int> > v;

int top,valley;

void bfs(pair<int,int> st)
{
	while(q.size()) q.pop();
	v.clear();
	
	q.push(st); vis[st.first][st.second]=true;
	v.push_back(st);
	
	int x,y,nx,ny;
	while(q.size()) {
		x=q.front().first; y=q.front().second;
		q.pop();
		
		for(int i=0;i<8;i++) {
			nx=x+dx[i]; ny=y+dy[i];
			if(nx>=1 && nx<=n && ny>=1 && ny<=n && a[nx][ny]==a[x][y] && !vis[nx][ny]) {
				vis[nx][ny]=true;
				v.push_back(pair<int,int>(nx,ny));
				q.push(pair<int,int>(nx,ny));
			}
				
		}
	}
	int flag_top=1,flag_valley=1;
	for(int i=0;i<(int)v.size();i++) {
		x=v[i].first; y=v[i].second;
		for(int j=0;j<8;j++) {
			nx=x+dx[j]; ny=y+dy[j];
			if(nx<1 || nx>n || ny<1 || ny>n || a[nx][ny]==a[x][y]) 
				continue;
			else if(a[nx][ny]<a[x][y]) flag_valley=0;
			else flag_top=0;
		}
	}
	top+=flag_top;
	valley+=flag_valley;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d",&n);
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			scanf("%d",&a[i][j]);
			
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=n;j++) 
			if(!vis[i][j]) 
				bfs(pair<int,int>(i,j));
	
	printf("%d %d\n",top,valley);
	return 0;
}

