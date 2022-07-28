// AcWing 349 ºÚ°µ³Ç±¤
// algorithm : ×î¶ÌÂ·¾¶Ê÷ 
// https://www.acwing.com/problem/content/351/ 
#include<queue>
#include<cstdio>
#include<cstring>
#include<iostream>
typedef long long LL;
typedef unsigned long long ULL;
using namespace std;
const int N=1000+5,M=N*N;
const LL MOD=(1ll<<31ll)-1ll;
int one[N],idx;
int Next[M],ver[M],edge[M];
inline void AddEdge(int a,int b,int c)
{
	Next[++idx]=one[a];
	one[a]=idx;
	ver[idx]=b;
	edge[idx]=c;
	return;
}
//==============================
int dis[N];
bool vis[N];
int n,m;
LL f[N];
void Dijstra()
{
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	priority_queue< pair<int,int> , vector< pair<int,int> > , greater< pair<int,int> > > q;
	while(q.size()) q.pop();
	q.push(make_pair(0,1)),dis[1]=0;
	int i,x,y,z;
	while(q.size()>0) {
		x=q.top().second; q.pop();
		if(vis[x]) continue;
		vis[x]=true;
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[y]>dis[x]+z) {
				dis[y]=dis[x]+z;
				q.push(make_pair(dis[y],y));
			}
		}
	}
	return;
}
int main()
{
//	freopen("1.in","r",stdin);
	int i;
	int x,y,z;
	scanf("%d%d",&n,&m);
	for(i=1;i<=m;i++) {
		scanf("%d%d%d",&x,&y,&z);
		AddEdge(x,y,z);
		AddEdge(y,x,z);
	}
	Dijstra();
	for(x=1;x<=n;x++) {
		for(i=one[x];i>0;i=Next[i]) {
			y=ver[i]; z=edge[i];
			if(dis[y]==dis[x]+z) 	
				f[y]++;
		}
	} 
	LL ans=1;
	for(i=1;i<=n;i++) 
		if(f[i]!=0)
			ans=ans*f[i]%MOD;
	cout<<ans;
	return 0;
}

