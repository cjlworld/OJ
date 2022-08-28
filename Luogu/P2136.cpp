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

const int N=2e4+5;

int one[N],idx;
int ver[N],Next[N],edge[N];
void AddEdge(int a,int b,int c)
{
	Next[idx]=one[a]; ver[idx]=b; edge[idx]=c; one[a]=idx++;
}

int n,m;

queue<int> q;
int cnt[N]; // cnt[x] 为 S 到 x 当前最短路的边数 
int dis[N];
bool vis[N];

bool spfa(int st) // 存在负环返回 true  
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,false,sizeof vis);
	memset(cnt,0,sizeof cnt);
	while(q.size()) q.pop();
	
	q.push(st); dis[st]=0;
	while(q.size()) {
		int x=q.front(); q.pop();
		vis[x]=false;
		for(int i=one[x],y,z;~i;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				cnt[y]=cnt[x]+1;
				if(cnt[y]>=n) return true;
				if(!vis[y]) q.push(y),vis[y]=true;
			}
		}
	}
	return false;
}

int main()
{
//	freopen("1.in","r",stdin);
	
	scanf("%d%d",&n,&m);
	memset(one,-1,sizeof one);
	for(int i=1,x,y,z;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,-z);
	}
	
	if(spfa(1)) 
		return puts("Forever love")&0;
	int ans=dis[n];
	spfa(n); ans=min(ans,dis[1]);
	printf("%d\n",ans);
	return 0;
}

