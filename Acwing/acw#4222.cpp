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
typedef pair<int,int> PII; 
typedef long double LD;
typedef unsigned long long ULL;

const int N=256;
const int INF=0x3f3f3f3f;

int A,B,C;

int dis[N][N];
bool vis[N][N];
PII pre[N][N];
int rec[N][N];

queue<PII> q; 

void print(int x,int y)
{
	if(rec[x][y]==0) return;
	print(pre[x][y].first,pre[x][y].second);
	switch(rec[x][y]) {
		case 1 : puts("FILL(1)"); break;
		case 2 : puts("FILL(2)"); break;
		case 3 : puts("DROP(1)"); break;
		case 4 : puts("DROP(2)"); break;
		case 5 : puts("POUR(1,2)"); break;
		case 6 : puts("POUR(2,1)"); break;
	}
}

void Update(PII nxt,PII cur,int num)
{
	if(vis[nxt.first][nxt.second]) return;
//	printf("(%d, %d)\n",nxt.first,nxt.second);
	vis[nxt.first][nxt.second]=true;
	dis[nxt.first][nxt.second]=dis[cur.first][cur.second]+1;
	pre[nxt.first][nxt.second]=cur;
	rec[nxt.first][nxt.second]=num;	
	q.push(nxt);
	
	if(nxt.first==C || nxt.second==C) {
		printf("%d\n",dis[nxt.first][nxt.second]);
		print(nxt.first,nxt.second);
		exit(0);
	}
}

void bfs()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	memset(rec,0,sizeof rec);
	
	q.push(PII(0,0)); dis[0][0]=0; vis[0][0]=true;
	while(q.size()) {
		int x=q.front().first,y=q.front().second;
		q.pop();
		
		Update(PII(A,y),PII(x,y),1); // FILL(1)
		Update(PII(x,B),PII(x,y),2); // FILL(2)
		Update(PII(0,y),PII(x,y),3);
		Update(PII(x,0),PII(x,y),4); 
		Update(PII(x-min(x,B-y),y+min(x,B-y)),PII(x,y),5); // POUR(1,2)
		Update(PII(x+min(y,A-x),y-min(y,A-x)),PII(x,y),6);
	}
}

int main()
{
//	freopen("1.in","r",stdin);
	cin>>A>>B>>C;
	bfs();
	puts("impossible");
	return 0;
}

